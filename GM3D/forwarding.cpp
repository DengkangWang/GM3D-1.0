#include "forwarding.h"
#include "ui_forwarding.h"
#include <using_checkbox_item.h>
#include "forwarditem.h"
#include <QDir>
#include <QFileDialog>
#include <QElapsedTimer>
#include <fstream>
#include <QMessageBox>

Forwarding::Forwarding(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Forwarding)
{
    ui->setupUi(this);
    this->setWindowTitle("Forwarding Model");
    QIcon Icon(":/icon/myicon/forward.png");
    this->setWindowIcon(Icon);
    originalSize=this->size();
    FORWARDITEM={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    GeoInc=53;
    GeoDec=-7;
    GaussMean=0.0;
    GaussStd=0.0;
    AddProportion=0.0;
    storeInitialGeometries(this);
    connect(ui->SelectItemBtn,SIGNAL(clicked(bool)),this,SLOT(GoToForwardItemDialog(bool)));
    connect(ui->SaveDataBtn,SIGNAL(clicked(bool)),this,SLOT(SaveData(bool)));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(ChangedDraw(int)));
}

Forwarding::~Forwarding()
{
    delete ui;
}

void Forwarding::GetModelingMsg(Model mymodel)
{
    MyModel=mymodel;
    FieldParam=mymodel.FieldParam;
    xlen=(FieldParam[1]-FieldParam[0])/FieldParam[6];
    ylen=(FieldParam[3]-FieldParam[2])/FieldParam[7];
    zlen=(FieldParam[5]-FieldParam[4])/FieldParam[8];

    bcelength=std::max(xlen,ylen);
    verlength=std::max(xlen,ylen);
    xm=Eigen::MatrixXd(verlength+1, verlength);
    ym=Eigen::MatrixXd(verlength, verlength+1);

    xm2=Eigen::MatrixXd(2*bcelength,2*bcelength-1);
    ym2=Eigen::MatrixXd(2*bcelength-1,2*bcelength);
    Eigen::ArrayXd row =Eigen::ArrayXd::LinSpaced(verlength+1,FieldParam[0],FieldParam[0] + FieldParam[6] * verlength)-FieldParam[6]/2.0;
    for (int i=0;i<verlength;++i){
        xm.col(i)=row.transpose();
    }

    Eigen::ArrayXd col =Eigen::ArrayXd::LinSpaced(verlength+1,FieldParam[2],FieldParam[2] + FieldParam[7] * verlength)-FieldParam[7]/2.0;
    for (int i=0;i< verlength;++i){
        ym.row(i)=col.transpose();
    }

    Eigen::ArrayXd row2 =Eigen::ArrayXd::LinSpaced(2*bcelength,-(FieldParam[1]-FieldParam[6]),FieldParam[1])+FieldParam[6]/2.0;

    for (int i=0;i<2*bcelength-1;++i){
        xm2.col(i)=row2.transpose();
    }

    Eigen::ArrayXd col2 =Eigen::ArrayXd::LinSpaced(2*bcelength,-(FieldParam[3]-FieldParam[7]),FieldParam[3])+FieldParam[7]/2.0;
    for (int i=0;i<2*bcelength-1;++i){
        ym2.row(i)=col2.transpose();
    }

    depth=QVector<double>(zlen);
    if(FieldParam[9]==0)
    {
        for (int i=0;i<zlen;++i){
            depth[i]=i*FieldParam[8];
        }
    }else if(FieldParam[9]==1){
        xm=xm*100;
        ym=ym*100;
        xm2=xm2*100;
        ym2=ym2*100;
        for (int i=0;i<zlen;++i){
            depth[i]=i*FieldParam[8]*100;
        }
    }else if(FieldParam[9]==2)
    {
        xm=xm*1000;
        ym=ym*1000;
        xm2=xm2*1000;
        ym2=ym2*1000;
        for (int i=0;i<zlen;++i){
            depth[i]=i*FieldParam[8]*1000;
        }
    }


    model =new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList(QStringLiteral("Model list")));
    ui->treeView->setModel(model);

    sphereitem = new UsingCheckboxItem("Sphere");
    cuboiditem = new UsingCheckboxItem("Cuboid");
    cylinderitem=new UsingCheckboxItem("Cylinder");
    irregularitem=new UsingCheckboxItem("Irregular");
    prismoiditem=new UsingCheckboxItem("Polyhedron");
    model->appendRow(sphereitem);
    model->appendRow(cuboiditem);
    model->appendRow(cylinderitem);
    model->appendRow(irregularitem);
    model->appendRow(prismoiditem);

    for(int i=0;i<MyModel.SPHERELIST.size();i++){
        auto item=new UsingCheckboxItem(MyModel.SPHERELIST[i].Name);
        sphereitem->appendRow(item);
        item->setCheckState(Qt::Checked);
    }

    for(int i=0;i<MyModel.CUBOIDLIST.size();i++){
        auto item=new UsingCheckboxItem(MyModel.CUBOIDLIST[i].Name);
        cuboiditem->appendRow(item);
        item->setCheckState(Qt::Checked);
    }

    for(int i=0;i<MyModel.CYLINDERLIST.size();i++){
        auto item=new UsingCheckboxItem(MyModel.CYLINDERLIST[i].Name);
        cylinderitem->appendRow(item);
        item->setCheckState(Qt::Checked);
    }

    for(int i=0;i<MyModel.IRREGULARLIST.size();i++){
        auto item=new UsingCheckboxItem(MyModel.IRREGULARLIST[i].Name);
        irregularitem->appendRow(item);
        item->setCheckState(Qt::Checked);
    }

    for(int i=0;i<MyModel.PRISMOIDLIST.size();i++){
        auto item=new UsingCheckboxItem(MyModel.PRISMOIDLIST[i].Name);
        prismoiditem->appendRow(item);
        item->setCheckState(Qt::Checked);
    }
    ui->treeView->expandAll();
}

void Forwarding::GetForwardItemList(QVector<int> forwarditem, double geodec, double geoinc,double obheight,double gaussmean,double gaussstd,double addproportion)
{
    FORWARDITEM=forwarditem;
    GeoInc=geoinc;
    GeoDec=geodec;
    ObHeight=obheight;
    GaussMean=gaussmean;
    GaussStd=gaussstd;
    AddProportion=addproportion;
    //qDebug()<<AddProportion<<" "<<GaussMean<<" "<<GaussStd;
    //需要正演的密度矩阵和磁化率矩阵
    QVector<QVector<QVector<double>>> forwardd(xlen,QVector<QVector<double>>(ylen,QVector<double>(zlen, 0.0)));
    QVector<QVector<QVector<double>>> forwardm(xlen,QVector<QVector<double>>(ylen,QVector<double>(zlen, 0.0)));

    //将所有被选中的模型数据并入一个数组
    for(int i=0;i<MyModel.SPHERELIST.size();i++){
        if(sphereitem->child(i)->checkState()==Qt::Checked){
            BodyInc=MyModel.SPHERELIST[i].Inclination;
            BodyDec=MyModel.SPHERELIST[i].Declination;

            for (int ii=0;ii<xlen;++ii){
                for(int jj=0;jj<ylen;jj++){
                    for (int kk=0;kk<zlen;kk++){

                        forwardd[ii][jj][kk]+=MyModel.SPHERELIST[i].SpaceDensity[ii][jj][kk];
                        forwardm[ii][jj][kk]+=MyModel.SPHERELIST[i].SpaceMagnetization[ii][jj][kk];
                    }
                }
            }
        }

    }


    for(int i=0;i<MyModel.CUBOIDLIST.size();i++){
        if(cuboiditem->child(i)->checkState()==Qt::Checked){
            BodyInc=MyModel.CUBOIDLIST[i].Inclination;
            BodyDec=MyModel.CUBOIDLIST[i].Declination;
            for (int ii=0;ii<xlen;++ii){
                for(int jj=0;jj<ylen;jj++){
                    for (int kk=0;kk<zlen;kk++){
                        forwardd[ii][jj][kk]+=MyModel.CUBOIDLIST[i].SpaceDensity[ii][jj][kk];
                        forwardm[ii][jj][kk]+=MyModel.CUBOIDLIST[i].SpaceMagnetization[ii][jj][kk];
                    }
                }
            }
        }
    }

    for(int i=0;i<MyModel.CYLINDERLIST.size();i++){
        if(cylinderitem->child(i)->checkState()==Qt::Checked){
            BodyInc=MyModel.CYLINDERLIST[i].Inclination;
            BodyDec=MyModel.CYLINDERLIST[i].Declination;
            for (int ii=0;ii<xlen;++ii){
                for(int jj=0;jj<ylen;jj++){
                    for (int kk=0;kk<zlen;kk++){
                        forwardd[ii][jj][kk]+=MyModel.CYLINDERLIST[i].SpaceDensity[ii][jj][kk];
                        forwardm[ii][jj][kk]+=MyModel.CYLINDERLIST[i].SpaceMagnetization[ii][jj][kk];
                    }
                }
            }
        }
    }

    for(int i=0;i<MyModel.IRREGULARLIST.size();i++){
        if(irregularitem->child(i)->checkState()==Qt::Checked){
            BodyInc=MyModel.IRREGULARLIST[i].Inclination;
            BodyDec=MyModel.IRREGULARLIST[i].Declination;
            for (int ii=0;ii<xlen;++ii){
                for(int jj=0;jj<ylen;jj++){
                    for (int kk=0;kk<zlen;kk++){
                        forwardd[ii][jj][kk]+=MyModel.IRREGULARLIST[i].SpaceDensity[ii][jj][kk];
                        forwardm[ii][jj][kk]+=MyModel.IRREGULARLIST[i].SpaceMagnetization[ii][jj][kk];
                    }
                }
            }
        }
    }

    for(int i=0;i<MyModel.PRISMOIDLIST.size();i++){
        if(prismoiditem->child(i)->checkState()==Qt::Checked){
            BodyInc=MyModel.PRISMOIDLIST[i].Inclination;
            BodyDec=MyModel.PRISMOIDLIST[i].Declination;
            for (int ii=0;ii<xlen;++ii){
                for(int jj=0;jj<ylen;jj++){
                    for (int kk=0;kk<zlen;kk++){
                        forwardd[ii][jj][kk]+=MyModel.PRISMOIDLIST[i].SpaceDensity[ii][jj][kk];
                        forwardm[ii][jj][kk]+=MyModel.PRISMOIDLIST[i].SpaceMagnetization[ii][jj][kk];
                    }
                }
            }
        }
    }

     /*模型物理属性数据加载完毕*/

    //设置一个重力正演类

    GraFWD mygrafwd(xm,ym,xlen,ylen,depth,ObHeight,forwardd);
    auto start1 = std::chrono::high_resolution_clock::now();
    mygrafwd.getFWDANS(FORWARDITEM);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto times1 = std::chrono::duration_cast<std::chrono::duration<double>>(end1 - start1);

    qDebug()<<xlen;
    qDebug()<<ylen;
    if (FORWARDITEM[0]) {
        oG = mygrafwd.G.topLeftCorner(ylen, xlen);
        G = mygrafwd.G.topLeftCorner(ylen, xlen);
        addGaussianNoise(G, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[1]) {
        oGxx = mygrafwd.Gxx.topLeftCorner(ylen, xlen);
        Gxx = mygrafwd.Gxx.topLeftCorner(ylen, xlen);
        addGaussianNoise(Gxx, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[2]) {
        oGxy = mygrafwd.Gxy.topLeftCorner(ylen, xlen);
        Gxy = mygrafwd.Gxy.topLeftCorner(ylen, xlen);
        addGaussianNoise(Gxy, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[3]) {
        oGxz = mygrafwd.Gxz.topLeftCorner(ylen, xlen);
        Gxz = mygrafwd.Gxz.topLeftCorner(ylen, xlen);
        addGaussianNoise(Gxz, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[4]) {
        oGyy = mygrafwd.Gyy.topLeftCorner(ylen, xlen);
        Gyy = mygrafwd.Gyy.topLeftCorner(ylen, xlen);
        addGaussianNoise(Gyy, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[5]) {
        oGyz = mygrafwd.Gyz.topLeftCorner(ylen, xlen);
        Gyz = mygrafwd.Gyz.topLeftCorner(ylen, xlen);
        addGaussianNoise(Gyz, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[6]) {
        oGzz = mygrafwd.Gzz.topLeftCorner(ylen, xlen);
        Gzz = mygrafwd.Gzz.topLeftCorner(ylen, xlen);
        addGaussianNoise(Gzz, GaussMean, GaussStd, AddProportion);
    }




    //磁正演测试
    MagFWD mymagfwd(xm,ym,xm2,ym2,xlen,ylen,depth,ObHeight,GeoInc,GeoDec,BodyInc,BodyDec,forwardm);
    auto start2 = std::chrono::high_resolution_clock::now();
    mymagfwd.GetFWAns(FORWARDITEM);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto times2 = std::chrono::duration_cast<std::chrono::duration<double>>(end2 - start2);
    QString message = QString(
                          "Forward modeling completed!\n\n"
                          "Gravity forward calculation time: %1 s\n"
                          "Magnetic forward calculation time: %2 s")
                          .arg(times1.count(), 0, 'f', 3)  // Gravity time, 3 decimal places
                          .arg(times2.count(), 0, 'f', 3); // Magnetic time, 3 decimal places
    QMessageBox::information(this, "Completed!", message);

    // 磁相关数据
    if (FORWARDITEM[7]) {
        T = mymagfwd.T.topLeftCorner(ylen, xlen);
        oT = mymagfwd.T.topLeftCorner(ylen, xlen);
        addGaussianNoise(T, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[8]) {
        Hax = mymagfwd.Hax.topLeftCorner(ylen, xlen);
        oHax = mymagfwd.Hax.topLeftCorner(ylen, xlen);
        addGaussianNoise(Hax, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[9]) {
        Hay = mymagfwd.Hay.topLeftCorner(ylen, xlen);
        oHay = mymagfwd.Hay.topLeftCorner(ylen, xlen);
        addGaussianNoise(Hay, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[10]) {
        Za = mymagfwd.Za.topLeftCorner(ylen, xlen);
        oZa = mymagfwd.Za.topLeftCorner(ylen, xlen);
        addGaussianNoise(Za, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[11]) {
        Bxx = mymagfwd.Bxx.topLeftCorner(ylen, xlen);
        oBxx = mymagfwd.Bxx.topLeftCorner(ylen, xlen);
        addGaussianNoise(Bxx, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[12]) {
        Bxy = mymagfwd.Bxy.topLeftCorner(ylen, xlen);
        oBxy = mymagfwd.Bxy.topLeftCorner(ylen, xlen);
        addGaussianNoise(Bxy, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[13]) {
        Bxz = mymagfwd.Bxz.topLeftCorner(ylen, xlen);
        oBxz = mymagfwd.Bxz.topLeftCorner(ylen, xlen);
        addGaussianNoise(Bxz, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[14]) {
        Byy = mymagfwd.Byy.topLeftCorner(ylen, xlen);
        oByy = mymagfwd.Byy.topLeftCorner(ylen, xlen);
        addGaussianNoise(Byy, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[15]) {
        Byz = mymagfwd.Byz.topLeftCorner(ylen, xlen);
        oByz = mymagfwd.Byz.topLeftCorner(ylen, xlen);
        addGaussianNoise(Byz, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[16]) {
        Bzz = mymagfwd.Bzz.topLeftCorner(ylen, xlen);
        oBzz = mymagfwd.Bzz.topLeftCorner(ylen, xlen);
        addGaussianNoise(Bzz, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[17]) {
        Tx = mymagfwd.Tx.topLeftCorner(ylen, xlen);
        oTx = mymagfwd.Tx.topLeftCorner(ylen, xlen);
        addGaussianNoise(Tx, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[18]) {
        Ty = mymagfwd.Ty.topLeftCorner(ylen, xlen);
        oTy = mymagfwd.Ty.topLeftCorner(ylen, xlen);
        addGaussianNoise(Ty, GaussMean, GaussStd, AddProportion);
    }
    if (FORWARDITEM[19]) {
        Tz = mymagfwd.Tz.topLeftCorner(ylen, xlen);
        oTz = mymagfwd.Tz.topLeftCorner(ylen, xlen);
        addGaussianNoise(Tz, GaussMean, GaussStd, AddProportion);
    }



    QString xlabel;
    QString ylabel;
    if(FieldParam[9]==0){
        xlabel="X/(m)";
        ylabel="Y/(m)";
    }else if(FieldParam[9]==1){
        xlabel="X/(hm)";
        ylabel="Y/(hm)";
    }else if(FieldParam[9]==2){
        xlabel="X/(km)";
        ylabel="Y/(km)";
    }



    if(FORWARDITEM[0]){
        PlotAns(G,xlabel,ylabel,"mGal");}
    else {
        QMessageBox::critical(this, tr("绘制失败"), tr("当前选择绘图的项目未计算！请选择其他项目"));}

}

void Forwarding::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    qreal scaleX = (qreal)width() /originalSize.width();
    qreal scaleY = (qreal)height()/originalSize.height();
    for (auto it = m_initialGeometries.begin(); it != m_initialGeometries.end(); ++it) {
        QWidget *widget = it.key();
        QRect geom = it.value();
        int newX = geom.x() * scaleX;
        int newY = geom.y() * scaleY;
        int newWidth = geom.width() * scaleX;
        int newHeight = geom.height() * scaleY;
        widget->setGeometry(newX, newY, newWidth, newHeight);
    }
 PaintAxis=QRect(InitPaintAxis.x()*scaleX,InitPaintAxis.y()*scaleY,InitPaintAxis.width()*scaleX,InitPaintAxis.height()*scaleY);
}

void Forwarding::paintEvent(QPaintEvent*)
{

}

void Forwarding::storeInitialGeometries(QWidget *widget)
{
    for (QObject *child : widget->children()) {
        if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            m_initialGeometries[childWidget] = childWidget->geometry();
            storeInitialGeometries(childWidget);
        }
    }
}

void Forwarding::SaveFWDANStoFile(const QString &folderPath, const QString &fileName, const Eigen::MatrixXd &matrix)
{
    QString filePath = QDir(folderPath).filePath(fileName);
    std::ofstream file(filePath.toStdString());
    if (!file.is_open()) {
        throw std::runtime_error(QString("无法打开文件: %1").arg(filePath).toStdString());
    }
    file << matrix.format(Eigen::IOFormat(Eigen::FullPrecision, 0, " ", "\n"));
    if (file.bad()) {
        file.close();
        throw std::runtime_error(QString("写入文件失败: %1").arg(filePath).toStdString());
    }

    file.close();
}

void Forwarding::PlotAns(const Eigen::MatrixXd &matrix,const QString xLabel,const QString yLabel,const QString colorbarLabel)
{

    mCustomPlot = new QCustomPlot(this);
    mCustomPlot->setGeometry(PaintAxis.toRect());
    int rows = matrix.rows();
    int cols = matrix.cols();

    // 创建颜色映射
    QCPColorMap *colorMap = new QCPColorMap(mCustomPlot->xAxis, mCustomPlot->yAxis);
    colorMap->data()->setSize(cols, rows);
    colorMap->data()->setRange(QCPRange(0, (cols - 1)*FieldParam[6]), QCPRange(0, (rows - 1)*FieldParam[7]));

    // 填充数据
    for (int xIndex = 0; xIndex < cols; ++xIndex) {
        for (int yIndex = 0; yIndex < rows; ++yIndex) {
            colorMap->data()->setData(xIndex*FieldParam[6], yIndex*FieldParam[7], matrix(yIndex, xIndex));
        }
    }

    // 设置颜色条
    QCPColorScale *colorScale = new QCPColorScale(mCustomPlot);
    mCustomPlot->plotLayout()->addElement(0, 1, colorScale);
    colorMap->setColorScale(colorScale);
    colorScale->setType(QCPAxis::atRight);
    colorScale->axis()->setLabel(colorbarLabel);
    QCPColorGradient jetGradient(QCPColorGradient::gpJet);
    colorMap->setGradient(jetGradient);
    mCustomPlot->xAxis->setLabel(xLabel);
    mCustomPlot->yAxis->setLabel(yLabel);

    // 自动缩放范围
    colorMap->rescaleDataRange(true);
    mCustomPlot->xAxis->setRange(0, (cols - 1)*FieldParam[6]);
    mCustomPlot->yAxis->setRange(0, (rows - 1)*FieldParam[7]);

    // 绘制并显示
    mCustomPlot->replot();
    mCustomPlot->show();

}

//void Forwarding::PlotAns(const Eigen::MatrixXd &matrix, const QString xLabel, const QString yLabel, const QString colorbarLabel)
//{
//    mCustomPlot = new QCustomPlot(this);
//    int rows = matrix.rows();
//    int cols = matrix.cols();

//    // 1. 计算数据在x和y方向的实际长度
//    double xLength = (cols > 1) ? (cols - 1) * FieldParam[6] : 1.0;
//    double yLength = (rows > 1) ? (rows - 1) * FieldParam[7] : 1.0;
//    double dataAspectRatio = xLength / yLength;  // 数据的宽高比

//    // 2. 定义原始绘图区域和颜色条宽度
//    const int colorbarWidth = 50;              // 颜色条预留宽度
//    double maxPlotWidth = PaintAxis.width() - colorbarWidth;  // 主绘图区最大可用宽度
//    double maxPlotHeight = PaintAxis.height();                // 主绘图区最大可用高度

//    // 3. 根据数据比例计算最佳绘图区域尺寸
//    double targetPlotWidth, targetPlotHeight;
//    if (dataAspectRatio >= 1.0) {
//        // x方向更长：以最大高度为基准
//        targetPlotHeight = maxPlotHeight;
//        targetPlotWidth = targetPlotHeight * dataAspectRatio;
//        if (targetPlotWidth > maxPlotWidth) {
//            targetPlotWidth = maxPlotWidth;
//            targetPlotHeight = targetPlotWidth / dataAspectRatio;
//        }
//    } else {
//        // y方向更长：以最大宽度为基准
//        targetPlotWidth = maxPlotWidth;
//        targetPlotHeight = targetPlotWidth / dataAspectRatio;
//        if (targetPlotHeight > maxPlotHeight) {
//            targetPlotHeight = maxPlotHeight;
//            targetPlotWidth = targetPlotHeight * dataAspectRatio;
//        }
//    }

//    // 4. 计算居中位置的起始坐标
//    double totalWidth = targetPlotWidth + colorbarWidth;  // 包含颜色条的总宽度
//    double totalHeight = targetPlotHeight;                // 总高度

//    // 计算x方向偏移：使新画布在原始区域内水平居中
//    double xOffset = PaintAxis.x() + (PaintAxis.width() - totalWidth) / 2;
//    // 计算y方向偏移：使新画布在原始区域内垂直居中
//    double yOffset = PaintAxis.y() + (PaintAxis.height() - totalHeight) / 2;

//    // 5. 设置调整后的居中画布
//    QRectF adjustedPaintAxis(xOffset, yOffset, totalWidth, totalHeight);
//    mCustomPlot->setGeometry(adjustedPaintAxis.toRect());

//    QCPColorMap *colorMap = new QCPColorMap(mCustomPlot->xAxis, mCustomPlot->yAxis);
//    colorMap->data()->setSize(cols, rows);
//    colorMap->data()->setRange(QCPRange(0, xLength), QCPRange(0, yLength));

//    // 填充数据
//    for (int xIndex = 0; xIndex < cols; ++xIndex) {
//        for (int yIndex = 0; yIndex < rows; ++yIndex) {
//            colorMap->data()->setData(xIndex*FieldParam[6], yIndex*FieldParam[7], matrix(yIndex, xIndex));
//        }
//    }

//    // 设置颜色条
//    QCPColorScale *colorScale = new QCPColorScale(mCustomPlot);
//    mCustomPlot->plotLayout()->addElement(0, 1, colorScale);
//    colorMap->setColorScale(colorScale);
//    colorScale->setType(QCPAxis::atRight);
//    colorScale->axis()->setLabel(colorbarLabel);
//    QCPColorGradient jetGradient(QCPColorGradient::gpJet);
//    colorMap->setGradient(jetGradient);
//    mCustomPlot->xAxis->setLabel(xLabel);
//    mCustomPlot->yAxis->setLabel(yLabel);

//    // 自动缩放范围
//    colorMap->rescaleDataRange(true);
//    mCustomPlot->xAxis->setRange(0, xLength);
//    mCustomPlot->yAxis->setRange(0, yLength);

//    // 绘制并显示
//    mCustomPlot->replot();
//    mCustomPlot->show();
//}


/**
 * 为Eigen::MatrixXd添加高斯噪声
 * @param matrix 目标矩阵
 * @param mean 高斯分布均值
 * @param stddev 高斯分布标准差
 * @param proportion 受影响元素的比例(0.0-1.0)
 */
void Forwarding::addGaussianNoise(Eigen::MatrixXd &matrix, double mean, double stddev, double proportion)
{
    if (proportion <= 0.0 || matrix.size() == 0) return;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::normal_distribution<> noiseDist(mean, stddev);
    std::uniform_real_distribution<> probDist(0.0, 1.0);
    for (Eigen::Index i = 0; i < matrix.size(); ++i) {
        // 根据比例决定是否添加噪声
        if (probDist(gen) <= proportion) {
            matrix.data()[i] += noiseDist(gen);
        }
    }
}

void Forwarding::GoToForwardItemDialog(bool)
{
    forwarditem*myforwarditem=new forwarditem(this);
    myforwarditem->GetForwardItem(FORWARDITEM,GeoDec,GeoInc,ObHeight,GaussMean,GaussStd,AddProportion);
    myforwarditem->show();
}

void Forwarding::SaveData(bool)
{
    QString filePath = QFileDialog::getSaveFileName(
        this,
        tr("保存数据文件"),
        "uFileName",
        tr("文本文件 (*.txt);;数据文件 (*.dat)")
    );

    if (filePath.isEmpty())
        return;

    try {
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw std::runtime_error("无法打开文件: " + filePath.toStdString());

        QTextStream out(&file);
        out.setRealNumberPrecision(6);
        out.setRealNumberNotation(QTextStream::FixedNotation);

        // 定义固定列宽
        const int COLUMN_WIDTH = 14;
        QStringList headers ;
        // 构建表头和数据指针列表
        if(FieldParam[9]==0) {
            headers = {"X/(m)", "Y/(m)"};
        }else if(FieldParam[9]==1){
            headers = {"X/(hm)", "Y/(hm)"};
        }else if(FieldParam[9]==2){
            headers = {"X/(km)", "Y/(km)"};
        }

        QVector<Eigen::MatrixXd*> dataPtrs;

        // 重力相关数据
        if (FORWARDITEM[0]) { headers << "OriginG"<<"ErrorG";    dataPtrs.push_back(&oG); dataPtrs.push_back(&G);  }
        if (FORWARDITEM[1]) { headers << "OriginGxx"<<"ErrorGxx"; dataPtrs.push_back(&oGxx); dataPtrs.push_back(&Gxx); }
        if (FORWARDITEM[2]) { headers << "OriginGxy"<<"ErrorGxy"; dataPtrs.push_back(&oGxy); dataPtrs.push_back(&Gxy); }
        if (FORWARDITEM[3]) { headers << "OriginGxz"<<"ErrorGxz"; dataPtrs.push_back(&oGxz); dataPtrs.push_back(&Gxz); }
        if (FORWARDITEM[4]) { headers << "OriginGyy"<<"ErrorGyy"; dataPtrs.push_back(&oGyy); dataPtrs.push_back(&Gyy); }
        if (FORWARDITEM[5]) { headers << "OriginGyz"<<"ErrorGyz"; dataPtrs.push_back(&oGyz); dataPtrs.push_back(&Gyz); }
        if (FORWARDITEM[6]) { headers << "OriginGzz"<<"ErrorGzz"; dataPtrs.push_back(&oGzz); dataPtrs.push_back(&Gzz);}

        // 磁相关数据
        if (FORWARDITEM[7]) { headers << "OriginT"<<"ErrorT";   dataPtrs.push_back(&oT);  dataPtrs.push_back(&T); }
        if (FORWARDITEM[8]) { headers << "OriginTHax"<<"ErrorHax";  dataPtrs.push_back(&oHax); dataPtrs.push_back(&Hax); }
        if (FORWARDITEM[9]) { headers << "OriginTHay"<<"ErrorHay";  dataPtrs.push_back(&oHay); dataPtrs.push_back(&Hay); }
        if (FORWARDITEM[10]) { headers << "OriginTZa"<<"ErrorZa";   dataPtrs.push_back(&oZa); dataPtrs.push_back(&Za); }
        if (FORWARDITEM[11]) { headers << "OriginTBxx"<<"ErrorBxx";  dataPtrs.push_back(&oBxx); dataPtrs.push_back(&Bxx); }
        if (FORWARDITEM[12]) { headers << "OriginTBxy"<<"ErrorBxy";  dataPtrs.push_back(&oBxy); dataPtrs.push_back(&Bxy); }
        if (FORWARDITEM[13]) { headers << "OriginTBxz"<<"ErrorBxz";  dataPtrs.push_back(&oBxz); dataPtrs.push_back(&Bxz); }
        if (FORWARDITEM[14]) { headers << "OriginTByy"<<"ErrorByy";  dataPtrs.push_back(&oByy); dataPtrs.push_back(&Byy); }
        if (FORWARDITEM[15]) { headers << "OriginTByz"<<"ErrorByz";  dataPtrs.push_back(&oByz); dataPtrs.push_back(&Byz); }
        if (FORWARDITEM[16]) { headers << "OriginTBzz"<<"ErrorBzz";  dataPtrs.push_back(&oBzz); dataPtrs.push_back(&Bzz); }
        if (FORWARDITEM[17]) { headers << "OriginTTx"<<"ErrorTx";    dataPtrs.push_back(&oTx); dataPtrs.push_back(&Tx); }
        if (FORWARDITEM[18]) { headers << "OriginTTy"<<"ErrorTy";   dataPtrs.push_back(&oTy); dataPtrs.push_back(&Ty); }
        if (FORWARDITEM[19]) { headers << "OriginTTz"<<"ErrorTz";   dataPtrs.push_back(&oTz); dataPtrs.push_back(&Tz); }

        // 检查是否有数据要保存
        if (dataPtrs.isEmpty()) {
            file.close();
            QFile::remove(filePath);
            QMessageBox::information(this, tr("无需保存"), tr("所有矩阵均为零矩阵，未保存任何文件。"));
            return;
        }

        // 写入表头
        for (const QString& header : headers) {
            out << qSetFieldWidth(COLUMN_WIDTH) << header;
        }
        out << "\n";
        out << qSetFieldWidth(0);

        // 确保所有矩阵大小一致
        if (dataPtrs.isEmpty()) throw std::runtime_error("无有效数据");

        for (int i = 0; i < xlen; ++i) {
            for (int j = 0; j < ylen; ++j) {

                out << qSetFieldWidth(COLUMN_WIDTH) << i*FieldParam[7];
                out << qSetFieldWidth(COLUMN_WIDTH) << j*FieldParam[6];
                for (Eigen::MatrixXd* mat : dataPtrs) {
                    out << qSetFieldWidth(COLUMN_WIDTH) << (*mat)(j, i);
                }
                out << "\n";
            }
        }

        file.close();
        QMessageBox::information(this, tr("保存成功"), tr("已成功保存数据到: %1").arg(filePath));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("保存失败"), tr("保存数据时出错: %1").arg(e.what()));
    }
}

void Forwarding::ChangedDraw(int index)
{
    QString xlabel;
    QString ylabel;
    if(FieldParam[9]==0){
        xlabel="X/(m)";
        ylabel="Y/(m)";
    }else if(FieldParam[9]==1){
        xlabel="X/(hm)";
        ylabel="Y/(hm)";
    }else if(FieldParam[9]==2){
        xlabel="X/(km)";
        ylabel="Y/(km)";
    }
    switch (index) { 
    case 0:
    {
        if(FORWARDITEM[0]){
            PlotAns(G,xlabel,ylabel,"mGal");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 1:
    {
        if(FORWARDITEM[1]){
            PlotAns(Gxx,xlabel,ylabel,"E");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 2:
    {
        if(FORWARDITEM[2]){
            PlotAns(Gxy,xlabel,ylabel,"E");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 3:
    {
        if(FORWARDITEM[3]){
            PlotAns(Gxz,xlabel,ylabel,"E");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 4:
    {
        if(FORWARDITEM[4]){
            PlotAns(Gyy,xlabel,ylabel,"E");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 5:
    {
        if(FORWARDITEM[5]){
            PlotAns(Gyz,xlabel,ylabel,"E");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 6:
    {
        if(FORWARDITEM[6]){
            PlotAns(Gzz,xlabel,ylabel,"E");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 7:
    {
        if(FORWARDITEM[7]){
            PlotAns(T,xlabel,ylabel,"nT");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 8:
    {
        if(FORWARDITEM[8]){
            PlotAns(Hax,xlabel,ylabel,"nT");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 9:
    {
        if(FORWARDITEM[9]){
            PlotAns(Hay,xlabel,ylabel,"nT");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 10:
    {
        if(FORWARDITEM[10]){
            PlotAns(Za,xlabel,ylabel,"nT");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 11:
    {
        if(FORWARDITEM[11]){
            PlotAns(Bxx,xlabel,ylabel,"nT/m");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 12:
    {
        if(FORWARDITEM[12]){
            PlotAns(Bxy,xlabel,ylabel,"nT/m");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 13:
    {
        if(FORWARDITEM[13]){
            PlotAns(Bxz,xlabel,ylabel,"nT/m");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 14:
    {
        if(FORWARDITEM[14]){
            PlotAns(Byy,xlabel,ylabel,"nT/m");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 15:
    {
        if(FORWARDITEM[15]){
            PlotAns(Byz,xlabel,ylabel,"nT/m");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 16:
    {
        if(FORWARDITEM[16]){
            PlotAns(Bzz,xlabel,ylabel,"nT/m");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 17:
    {
        if(FORWARDITEM[17]){
            PlotAns(Tx,xlabel,ylabel,"nT/m");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 18:
    {
        if(FORWARDITEM[18]){
            PlotAns(Ty,xlabel,ylabel,"nT/m");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    case 19:
    {
        if(FORWARDITEM[19]){
            PlotAns(Tz,xlabel,ylabel,"nT/m");}
        else{
            QMessageBox::critical(this, tr("绘制失败"), tr("该项目未计算！"));}
    }
        break;
    default:
        break;
    }


}


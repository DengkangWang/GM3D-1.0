#include "addirregulardialog.h"
#include "ui_addirregulardialog.h"
#include <QEvent>
#include <QMouseEvent>
#include <QSignalMapper>
#include <QCoreApplication>
#include <cmath>
//extern QVector<int> SOURCE;
//QVector<int> SOURCE={0,100,0,100,0,100,1,1,1,1};
AddIrregularDialog::AddIrregularDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddIrregularDialog)
{   ui->setupUi(this);
    this->setWindowTitle("Add Irregular Model");
    QIcon Icon(":/icon/myicon/custom.png");
    this->setWindowIcon(Icon);
    originalSize=this->size();
    storeInitialGeometries(this);
    setMouseTracking(true);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    QPushButton *ButtonList[9]={ui->circularbtn,ui->rectbtn,ui->custombtn,ui->clickbtn,ui->copybtn,ui->pastebtn,ui->clearbtn,ui->finishbtn,ui->cancelbtn};
    QSignalMapper * myaddmodelbtnmapper=new QSignalMapper(this);
    for (int i =0;i<9;i++){
        connect(ButtonList[i],SIGNAL(clicked(bool)),myaddmodelbtnmapper,SLOT(map()));
        myaddmodelbtnmapper->setMapping(ButtonList[i],i);
    }
    connect(myaddmodelbtnmapper,SIGNAL(mappedInt(int)),this,SLOT(BtnMapper(int)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxIndexChanged(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged(int)));
    connect(ui->okbtn,SIGNAL(clicked(bool)),this,SLOT(backtomodeling(bool)));
    connect(ui->PaletteBtn,SIGNAL(clicked(bool)),SLOT(ChooseModelColor(bool)));
    connect(ui->BuildButton,SIGNAL(clicked(bool)),this,SLOT(BuildBtnChecked(bool)));
    connect(ui->EraseButton,SIGNAL(clicked(bool)),this,SLOT(EraseBtnChecked(bool)));
    xlen=static_cast<int>((SOURCE[1]-SOURCE[0])/SOURCE[6]);
    ylen=static_cast<int>((SOURCE[3]-SOURCE[2])/SOURCE[7]);
    zlen=static_cast<int>((SOURCE[5]-SOURCE[4])/SOURCE[8]);
    xgridInterval =pixwidth/(xlen);
    ygridInterval =pixhigh/(ylen);
}

AddIrregularDialog::~AddIrregularDialog()
{
    delete ui;

}

void AddIrregularDialog::GetModelingMsg(IrregularModel newirregular,QVector<float> fieldparam)
{

    SOURCE=fieldparam;
    xlen=static_cast<int>((SOURCE[1]-SOURCE[0])/SOURCE[6]);
    ylen=static_cast<int>((SOURCE[3]-SOURCE[2])/SOURCE[7]);
    zlen=static_cast<int>((SOURCE[5]-SOURCE[4])/SOURCE[8]);
    xgridInterval =pixwidth/(xlen);
    ygridInterval =pixhigh/(ylen);
    xrange=xlen;
    yrange=ylen;
    SpaceDensity=newirregular.SpaceDensity;
    SpaceMagnetization=newirregular.SpaceDensity;
    ui->DecEdit->setText(QString::number(newirregular.Declination));
    ui->IncEdit->setText(QString::number(newirregular.Inclination));
    ui->NameEdit->setText(newirregular.Name);
    ui->spinBox->setValue(1);

    for (int i=0;i<xlen;++i){
        for(int j=0;j<ylen;++j){
            if (SpaceDensity[i][j][0]!=0){
                SelectedUnitCoordinate.append(QRectF(i*xgridInterval+xstart, (ylen-j-1)*ygridInterval+ystart, xgridInterval, ygridInterval));
            }

        }
    }
    color=newirregular.Color;

    update();
}

void AddIrregularDialog::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    { if((e->pos().x()<=(xstart+pixwidth))&&(e->pos().y()<=(ystart+pixhigh))&&(e->pos().x()>=xstart)&&(e->pos().y()>=ystart)){

            switch (drawmode) {

            case 0:
            {
                circlemode[0][0]=e->pos().x();
                circlemode[0][1]=e->pos().y();
            }
            break;
            case 1:
            {
                rectmode[0][0]=e->pos().x();
                rectmode[0][1]=e->pos().y();
            }
            break;
            case 2:
            {
                CustomLineArray.append(QPoint(e->pos().x(),e->pos().y()));
            }
            break;
            case 3:
            {   //单击模式，如果点击的单元格之前已经选中过，为取消
                //如果没有选中过，为选中
                getMyAxisCoordinate(e);
                QRectF valueToChoose=QRectF(MyAxisX*xgridInterval+xstart, MyAxisY*ygridInterval+ystart, xgridInterval, ygridInterval);
                int index = SelectedUnitCoordinate.indexOf(valueToChoose);
                if(State){
                    //Bulid State，选中了一个未创建的单元格
                    if(index == -1) SelectedUnitCoordinate.append(valueToChoose);
                }else{
                    //Erase State，擦除了一个创建的单元格
                    if(index != -1) SelectedUnitCoordinate.remove(index);
                }
            }
            break;
            default:
                break;
            }
        }
    }
    update();
}

void AddIrregularDialog::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() == Qt::LeftButton)
    {   //在画板内
        if((e->pos().x()<=(xstart+pixwidth))&&(e->pos().y()<=(ystart+pixhigh))&&(e->pos().x()>=xstart)&&(e->pos().y()>=ystart)){
            switch (drawmode) {
            case 0:
            {
               circlemode[1][0]=e->pos().x();
               circlemode[1][1]=e->pos().y();
            }
                break;
            case 1:
            {
                rectmode[1][0]=e->pos().x();
                rectmode[1][1]=e->pos().y();
            }
                break;
            case 2:
            {
                CustomLineArray.append(QPoint(e->pos().x(),e->pos().y()));
            }
                break;
            default:
                break;
            }

        }
        update();
    }
}

void AddIrregularDialog::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if((e->pos().x()<=(xstart+pixwidth))&&(e->pos().y()<=(ystart+pixhigh))&&(e->pos().x()>=xstart)&&(e->pos().y()>=ystart)){
            switch (drawmode) {
            case 0:
            {
                getCircleModeAns();
                circlemode[0][0]=0;
                circlemode[0][1]=0;
                circlemode[1][0]=0;
                circlemode[1][1]=0;
            }

                break;
            case 1:
            {
                getRectModeAns();
                rectmode[0][0]=0;
                rectmode[0][1]=0;
                rectmode[1][0]=0;
                rectmode[1][1]=0;
            }
                break;
            case 2:
            {   QPolygon polygon(CustomLineArray);
                getCustomModeAns();
                CustomLineArray.clear();
            }
                 break;
            default:
                break;
            }
        }
    }
    update();
}

void AddIrregularDialog::paintEvent(QPaintEvent *)

{
   QPainter painter(this);
   // 设置坐标区背景色
   painter.setBrush(QBrush(Qt::white));
   painter.drawRect(xstart, ystart, pixwidth, pixhigh);
   // 绘制坐标
   paintAxis(painter);
   // 绘制选中的单元
   paintSelectedUnit(painter);
   if (drawmode==1){
        paintRect(painter) ;
   }

   if(drawmode==0){
        paintCircle(painter);
   }

   if(drawmode==2){
        paintCustom(painter);
   }

}

//用于绘制坐标区
void AddIrregularDialog::paintAxis(QPainter &painter)
{
    // The unit of distance of the axis label
    static const QString units[] = {"m", "hm", "km"};
    QString xlabel = QString("X/(%1)").arg(units[static_cast<int>(SOURCE[9])]);
    QString ylabel = QString("Y/(%1)").arg(units[static_cast<int>(SOURCE[9])]);
    QString zlabel = QString("Z/(%1)").arg(units[static_cast<int>(SOURCE[9])]);

    // The position of the axis label
    QPoint posXlabel = QPoint(xstart + pixwidth/2, ystart + pixhigh + 25);
    QPoint posYlabel = QPoint(xstart-25, ystart + pixhigh/2);

    struct ProfileData {
        QString xLabel;
        QString yLabel;
        int xNum;
        int yNum;
        double x0;
        double y0;
        double dx;
        double dy;
    };

    const ProfileData profileData[] = {
        {xlabel, ylabel, xlen, ylen, SOURCE[0], SOURCE[2], +SOURCE[6], SOURCE[7]}, // case 0
        {xlabel, zlabel, xlen, zlen, SOURCE[0], SOURCE[4], +SOURCE[6], SOURCE[8]}, // case 1
        {ylabel, zlabel, ylen, zlen, SOURCE[2], SOURCE[4], +SOURCE[7], SOURCE[8]}  // case 2
    };

    xgridInterval =pixwidth/profileData[drawprofile].xNum;
    ygridInterval =pixhigh/profileData[drawprofile].yNum;

    // vertical line
    for (int i = 0; i < profileData[drawprofile].xNum; ++i) {
        painter.drawLine(
            QPoint(xstart + i * xgridInterval, ystart),  // 起点：顶部边界
            QPoint(xstart + i * xgridInterval, pixhigh + ystart)  // 终点：底部边界
            );
    };
    // horizontal line
    for (int i = 0; i < profileData[drawprofile].yNum; ++i) {
        painter.drawLine(
            QPoint(xstart, i * ygridInterval + ystart),  // 起点：左侧边界
            QPoint(xstart + pixwidth, i * ygridInterval + ystart)  // 终点：右侧边界
            );
    };
    // tick
    painter.setFont(QFont("Consolas", 7));
    for (int i = 0; i <= profileData[drawprofile].xNum; i+=5) {
        painter.drawText(
            QPoint(i * xgridInterval + xstart, ystart + pixhigh + 12),
            QString::number(profileData[drawprofile].x0 + i * profileData[drawprofile].dx)
            );
    }
    for (int i = 0; i <= profileData[drawprofile].yNum; i+=5) {
        painter.drawText(
            QPoint(xstart - 12, i * ygridInterval + ystart),
            QString::number(profileData[drawprofile].y0 + i * profileData[drawprofile].dy)
            );
    }
    // Axis label
    painter.setFont(QFont("Consolas", 10));
    painter.drawText(posXlabel, profileData[drawprofile].xLabel);
    painter.save();
    painter.translate(posYlabel);
    painter.rotate(-90);
    painter.drawText(0, 0, profileData[drawprofile].yLabel);
    painter.restore();
}

//将界面坐标转换成自定义坐标区坐标
void AddIrregularDialog::getMyAxisCoordinate(QMouseEvent *e)
{
    MyAxisX=qRound((e->pos().x()-xstart)/xgridInterval);
    MyAxisY=qRound((e->pos().y()-ystart)/ygridInterval);
}

void AddIrregularDialog::paintSelectedUnit(QPainter &painter)
{
    if(SelectedUnitCoordinate.size()>0){
    painter.setBrush(QBrush(QColor(255, 0, 0)));
    painter.drawRects(&SelectedUnitCoordinate[0],SelectedUnitCoordinate.size());}
}

void AddIrregularDialog::paintRect(QPainter &painter)
{   painter.setOpacity(0.3); // 设置画刷的不透明度，0.0表示完全透明，1.0表示完全不透明
    painter.setBrush(Qt::blue); // 设置画刷颜色
    painter.drawRect(QRectF(rectmode[0][0],rectmode[0][1],rectmode[1][0]-rectmode[0][0],rectmode[1][1]-rectmode[0][1]));

}

void AddIrregularDialog::paintCircle(QPainter &painter)
{
    painter.setOpacity(0.3); // 设置画刷的不透明度，0.0表示完全透明，1.0表示完全不透明
    painter.setBrush(Qt::blue); // 设置画刷颜色
    double r=std::sqrt((circlemode[1][0]-circlemode[0][0])*(circlemode[1][0]-circlemode[0][0])+(circlemode[1][1]-circlemode[0][1])*(circlemode[1][1]-circlemode[0][1]));
    painter.drawEllipse(QRect(circlemode[0][0]-r,circlemode[0][1]-r,2*r,2*r));
}

void AddIrregularDialog::paintCustom(QPainter &painter)
{
    painter.setOpacity(0.3); // 设置画刷的不透明度，0.0表示完全透明，1.0表示完全不透明
    painter.setBrush(Qt::blue); // 设置画刷颜色
    QPolygon polygon(CustomLineArray);
    painter.drawPolygon(polygon);
}

void AddIrregularDialog::getCircleModeAns()
{
    circlemode[0][0]=round((circlemode[0][0]-xstart)/xgridInterval)*xgridInterval+xstart;
    circlemode[0][1]=round((circlemode[0][1]-ystart)/ygridInterval)*ygridInterval+ystart;
    double r=sqrt((circlemode[1][0]-circlemode[0][0])*(circlemode[1][0]-circlemode[0][0])+(circlemode[1][1]-circlemode[0][1])*(circlemode[1][1]-circlemode[0][1]));

    int circxstart=static_cast<int>((circlemode[0][0]-r-xstart)/xgridInterval);
    int circxend=static_cast<int>((circlemode[0][0]+r-xstart)/xgridInterval)+1;
    int circystart=static_cast<int>((circlemode[0][1]-r-ystart)/ygridInterval);
    int circyend=static_cast<int>((circlemode[0][1]+r-ystart)/ygridInterval)+1;

    circxstart=(circxstart<0)?0:circxstart;
    circxend=(circxend<xrange)?circxend:xrange;
    circystart=(circystart<0)?0:circystart;
    circyend=(circyend<yrange)?circyend:yrange;

    QRectF valueToChoose;

        for (int i=circxstart;i<circxend;++i){
            for (int j=circystart;j<circyend;++j){

                if((((i+0.5)*xgridInterval+xstart-circlemode[0][0])*((i+0.5)*xgridInterval+xstart-circlemode[0][0])+((j+0.5)*ygridInterval+ystart-circlemode[0][1])*((j+0.5)*ygridInterval+ystart-circlemode[0][1]))<=(r*r)){
                valueToChoose=QRectF(i*xgridInterval+xstart, j*ygridInterval+ystart, xgridInterval, ygridInterval);
                int index = SelectedUnitCoordinate.indexOf(valueToChoose);
                if(State){
                    //Bulid State，选中了一个未创建的单元格
                    if(index == -1) SelectedUnitCoordinate.append(valueToChoose);
                }else{
                    //Erase State，擦除了一个创建的单元格
                    if(index != -1) SelectedUnitCoordinate.remove(index);
                }

            }
            }
        }
}

void AddIrregularDialog::getRectModeAns()
{
    int rectxstart=static_cast<int>((rectmode[0][0]-xstart)/xgridInterval);
    int rectystart=static_cast<int>((rectmode[0][1]-ystart)/ygridInterval);
    int rectxend=static_cast<int>((rectmode[1][0]-xstart)/xgridInterval);
    int rectyend=static_cast<int>((rectmode[1][1]-ystart)/ygridInterval);

    rectxstart=(rectxstart<0)?0:rectxstart;
    rectxend=(rectxend<xrange-1)?rectxend:xrange-1;
    rectystart=(rectystart<0)?0:rectystart;
    rectyend=(rectyend<yrange-1)?rectyend:yrange-1;

    QRectF valueToChoose;
    for (int i=rectxstart;i<=rectxend;++i){
        for (int j=rectystart;j<=rectyend;++j){

            valueToChoose=QRectF(i*xgridInterval+xstart, j*ygridInterval+ystart, xgridInterval, ygridInterval);
            int index = SelectedUnitCoordinate.indexOf(valueToChoose);
            if(State){
                //Bulid State，选中了一个未创建的单元格
                if(index == -1) SelectedUnitCoordinate.append(valueToChoose);
            }else{
                //Erase State，擦除了一个创建的单元格
                if(index != -1) SelectedUnitCoordinate.remove(index);
            }
        }
    }
}

void AddIrregularDialog::getCustomModeAns()
{
    int minX = INT_MAX;
    int minY = INT_MAX;
    int maxX = INT_MIN;
    int maxY = INT_MIN;
    for(const QPoint &CustomLineArray : CustomLineArray) {
        minX = std::min(minX, CustomLineArray.x());
        minY = std::min(minY, CustomLineArray.y());
        maxX = std::max(maxX, CustomLineArray.x());
        maxY = std::max(maxY, CustomLineArray.y());
    }
    int minx=static_cast<int>((minX-xstart)/xgridInterval);
    int miny=static_cast<int>((minY-ystart)/ygridInterval);
    int maxx=static_cast<int>((maxX-xstart)/xgridInterval);
    int maxy=static_cast<int>((maxY-ystart)/ygridInterval);
    QPolygon polygon(CustomLineArray);
    QRectF valueToChoose;
    for (int i=minx;i<=maxx;++i){
        for(int j=miny;j<maxy;++j){
        QPoint point=QPoint((i+0.5)*xgridInterval+xstart,(j+0.5)*ygridInterval+ystart);
        bool isInside = polygon.containsPoint(point, Qt::OddEvenFill);
        if (isInside){
            valueToChoose=QRectF(i*xgridInterval+xstart, j*ygridInterval+ystart, xgridInterval, ygridInterval);
            int index = SelectedUnitCoordinate.indexOf(valueToChoose);
            if(State){
                //Bulid State，选中了一个未创建的单元格
                if(index == -1) SelectedUnitCoordinate.append(valueToChoose);
            }else{
                //Erase State，擦除了一个创建的单元格
                if(index != -1) SelectedUnitCoordinate.remove(index);
            }
        }
        }
    }
}

void AddIrregularDialog::resizeEvent(QResizeEvent *event)
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

    xstart=intixstart*scaleX;
    ystart=intiystart*scaleY;
    pixhigh=intipixhigh*scaleY;
    pixwidth=intipixwidth*scaleX;
    xgridInterval =pixwidth/(xlen);
    ygridInterval =pixhigh/(ylen);
    update();
}

void AddIrregularDialog::backtomodeling(bool)
{
    Modeling*modeling=qobject_cast<Modeling*>(parent());
    IrregularModel irregular;
    QString dec=ui->DecEdit->text();
    QString inc=ui->IncEdit->text();
    irregular.SetProperty(SpaceDensity,SpaceMagnetization,dec.toDouble(),inc.toDouble(),color,ui->NameEdit->text());
    modeling->getAddIrregularDiaglogMsg(irregular);
    this->close();
}

void AddIrregularDialog::BtnMapper(int index)
{
    switch (index) {
    case 0:
    {
        drawmode=0;
    }
        break;
    case 1:
    {
        drawmode=1;
    }
        break;
    case 2:
    {
        drawmode=2;
    }
        break;
    case 3:
    {      
        drawmode=3;
    }
        break;
    case 4:
    {   //复制当前存档
        CopySelectedUnitCoordinate=SelectedUnitCoordinate;

    }
        break;
    case 5:
    {   //粘贴复制的存档
        SelectedUnitCoordinate=CopySelectedUnitCoordinate;
        update();
    }
        break;
    case 6:
    {
        //清除当前界面
        SelectedUnitCoordinate.clear();
        update();
    }
        break;
    case 7:
    {
        //保存当前界面
        HadSavedLayer=true;
        int layer=BuiltLayer;
        QRectF point;
        double density, magnetization;
        QString error;
        if (validateInputs(density, magnetization, error)) {
            switch (drawprofile) {
            case 0:{
                for (int i = 0; i < SelectedUnitCoordinate.length(); ++i) {
                    point=SelectedUnitCoordinate[i];
                    MyAxisX=qRound((point.topLeft().x()-xstart)/xgridInterval);
                    MyAxisY=ylen-1-qRound((point.topLeft().y()-ystart)/ygridInterval);
                    SpaceDensity[MyAxisX][MyAxisY][layer]=density;
                    SpaceMagnetization[MyAxisX][MyAxisY][layer]=magnetization;
                }
            }

            break;
            case 1:{

                for (int i = 0; i < SelectedUnitCoordinate.length(); ++i) {
                    point=SelectedUnitCoordinate[i];
                    MyAxisX=xlen-1-qRound((point.topLeft().x()-xstart)/xgridInterval);
                    MyAxisY=qRound((point.topLeft().y()-ystart)/ygridInterval);
                    SpaceDensity[MyAxisX][layer][MyAxisY]=density;
                    SpaceMagnetization[MyAxisX][layer][MyAxisY]=magnetization;
                }
            }

            break;
            case 2:{
                for (int i = 0; i < SelectedUnitCoordinate.length(); ++i) {
                    point=SelectedUnitCoordinate[i];
                    MyAxisX=qRound((point.topLeft().x()-xstart)/xgridInterval);
                    MyAxisY=qRound((point.topLeft().y()-ystart)/ygridInterval);
                    SpaceDensity[layer][MyAxisX][MyAxisY]=density;
                    SpaceMagnetization[layer][MyAxisX][MyAxisY]=magnetization;
                }

            }
            break;
            default:
                break;
            }
            ui->spinBox->setValue(ui->spinBox->value()+1);
        } else {
            QMessageBox::warning(this, "Input Error", error);
        }


    }
        break;
    case 8:
    {
        SelectedUnitCoordinate.clear();
        update();
    }
        break;
    default:
        break;
    }
}

void AddIrregularDialog::onComboBoxIndexChanged(int index)
{  //改变绘制剖面

    switch (index) {
    case 0:
    {   drawprofile=0;
       }
        break;
    case 1:
    {
        drawprofile=1;
    }
        break;
    case 2:
    {
        drawprofile=2;
    }
        break;
    default:
        break;
    }

    if(drawprofile==0){
        xrange=xlen;
        yrange=ylen;
    }else if(drawprofile==1){
        xrange=xlen;
        yrange=zlen;
    }else if(drawprofile ==2){
        xrange=ylen;
        yrange=xlen;
    }

    update();
}

void AddIrregularDialog::onSpinBoxValueChanged(int newlayer)
{
    if (!HadSavedLayer){
        //用户没按 SaveLayer 按钮，自动保存

        int layer=BuiltLayer;
        QRectF point;
        double density, magnetization;
        QString error;
        if (validateInputs(density, magnetization, error)) {
            switch (drawprofile) {
            case 0:{
                for (int i = 0; i < SelectedUnitCoordinate.length(); ++i) {
                    point=SelectedUnitCoordinate[i];
                    MyAxisX=qRound((point.topLeft().x()-xstart)/xgridInterval);
                    MyAxisY=ylen-1-qRound((point.topLeft().y()-ystart)/ygridInterval);
                    SpaceDensity[MyAxisX][MyAxisY][layer]=density;
                    SpaceMagnetization[MyAxisX][MyAxisY][layer]=magnetization;
                }
            }

            break;
            case 1:{

                for (int i = 0; i < SelectedUnitCoordinate.length(); ++i) {
                    point=SelectedUnitCoordinate[i];
                    MyAxisX=xlen-1-qRound((point.topLeft().x()-xstart)/xgridInterval);
                    MyAxisY=qRound((point.topLeft().y()-ystart)/ygridInterval);
                    SpaceDensity[MyAxisX][layer][MyAxisY]=density;
                    SpaceMagnetization[MyAxisX][layer][MyAxisY]=magnetization;
                }
            }

            break;
            case 2:{
                for (int i = 0; i < SelectedUnitCoordinate.length(); ++i) {
                    point=SelectedUnitCoordinate[i];
                    MyAxisX=qRound((point.topLeft().x()-xstart)/xgridInterval);
                    MyAxisY=qRound((point.topLeft().y()-ystart)/ygridInterval);
                    SpaceDensity[layer][MyAxisX][MyAxisY]=density;
                    SpaceMagnetization[layer][MyAxisX][MyAxisY]=magnetization;
                }

            }
            break;
            default:
                break;
            }
        } else {
            QMessageBox::warning(this, "Input Error", error);
        }
    }
    // 检查层值是否小于1
    if (newlayer < 1) {
        QMessageBox::warning(this, "Input Error", "Layer number must be at least 1!", QMessageBox::Ok);
        ui->spinBox->setValue(1); // 恢复最小值
        return;
    }

    int layerIndex = newlayer - 1;
    SelectedUnitCoordinate.clear();

    // 根据drawprofile确定最大层值
    int maxLayerCount = 0;
    bool isValidLayer = true;

    switch(drawprofile) {
    case 0: // Z方向视图
       maxLayerCount = zlen; // Z维度的最大层数
        ui->spinBox->setMaximum(zlen);
        if (layerIndex > zlen) isValidLayer = false;
        break;

    case 1: // Y方向视图
       maxLayerCount = ylen; // Y维度的最大层数
         ui->spinBox->setMaximum(ylen);
        if (layerIndex > ylen) isValidLayer = false;
        break;

    case 2: // X方向视图
        ui->spinBox->setMaximum(xlen);
        if (layerIndex > xlen) isValidLayer = false;
        break;

    default:
        isValidLayer = false;
        break;
    }

    // 处理无效层值
    if (!isValidLayer) {
        QMessageBox::warning(this, "Input Error",
                             QString("Layer number must be between 1 and %1 for this view!").arg(maxLayerCount),
                             QMessageBox::Ok);
        ui->spinBox->setValue(qMin(newlayer, maxLayerCount)); // 恢复有效范围
        return;
    }

    // 层值有效，继续处理
    switch(drawprofile) {
    case 0: {
        for (int i=0; i<xlen; ++i) {
            for(int j=0; j<ylen; ++j) {
                if (SpaceDensity[i][j][layerIndex]!=0 || SpaceMagnetization[i][j][layerIndex]!=0) {
                    //把三维数组中的值先取出来
                    SelectedUnitCoordinate.append(QRectF((xlen-1-i)*xgridInterval+xstart, j*ygridInterval+ystart, xgridInterval, ygridInterval));
                    SpaceDensity[i][j][layerIndex]=0;
                    SpaceMagnetization[i][j][layerIndex]=0;
                }
            }
        }
    } break;

    case 1: {
        for (int i=0; i<xlen; ++i) {
            for(int j=0; j<zlen; ++j) {
                if (SpaceDensity[i][layerIndex][j]!=0 || SpaceMagnetization[i][layerIndex][j]!=0) {
                    SelectedUnitCoordinate.append(QRectF((xlen-1-i)*xgridInterval+xstart, j*ygridInterval+ystart, xgridInterval, ygridInterval));
                    SpaceDensity[i][layerIndex][j]=0;
                    SpaceMagnetization[i][layerIndex][j]=0;
                }
            }
        }
    } break;

    case 2: {
        for (int i=0; i<ylen; ++i) {
            for(int j=0; j<zlen; ++j) {
                if (SpaceDensity[layerIndex][i][j]!=0 || SpaceMagnetization[layerIndex][i][j]!=0) {
                    SelectedUnitCoordinate.append(QRectF(i*xgridInterval+xstart, j*ygridInterval+ystart, xgridInterval, ygridInterval));

                    SpaceDensity[layerIndex][i][j]=0;
                    SpaceMagnetization[layerIndex][i][j];
                }
            }
        }
    } break;

    default:
        break;
    }
    HadSavedLayer=false;
    BuiltLayer=newlayer-1;
    update();
}


void AddIrregularDialog::ChooseModelColor(bool)
{
    color=QColorDialog::getColor(color,this,"Choose Model Color");
}

void AddIrregularDialog::BuildBtnChecked(bool checked)
{
    if(checked){
        ui->EraseButton->setChecked(false);
        State=true;
    }
}

void AddIrregularDialog::EraseBtnChecked(bool checked)
{
    if(checked){
        ui->BuildButton->setChecked(false);
        State=false;
    }
}

void AddIrregularDialog::storeInitialGeometries(QWidget *widget)
{
    for (QObject *child : widget->children()) {
        if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            m_initialGeometries[childWidget] = childWidget->geometry();
            storeInitialGeometries(childWidget);
        }
    }

}

bool AddIrregularDialog::validateInputs(double &density, double &magnetization, QString &errorMessage)
{

    const QString denText = ui->DenEdit->text().trimmed();
    const QString mText = ui->MEdit->text().trimmed();

    if (denText.isEmpty() || mText.isEmpty()) {
        errorMessage = "Density and Magnetization cannot be empty!";
        return false;
    }

    bool denOk, mOk;
    density = denText.toDouble(&denOk);
    magnetization = mText.toDouble(&mOk);

    if (!denOk || !mOk) {
        errorMessage = "Density and Magnetization must be numeric values!";
        return false;
    }

    if (qFuzzyCompare(density, 0.0) && qFuzzyCompare(magnetization, 0.0)) {
        errorMessage = "At least one of Density or Magnetization must be non-zero!";
        return false;
    }

    return true;
}




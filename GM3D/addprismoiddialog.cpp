#include "addprismoiddialog.h"
#include "ui_addprismoiddialog.h"

AddPrismoidDialog::AddPrismoidDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddPrismoidDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Prismoid Model");
    QIcon Icon(":/icon/myicon/prismoid.png");
    this->setWindowIcon(Icon);
    originalSize=this->size();
    storeInitialGeometries(this);
    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(backtomodeling(bool)));
    connect(ui->PaletteBtn,SIGNAL(clicked(bool)),this,SLOT(ChooseModelColor(bool)));
    this->setAttribute(Qt::WA_DeleteOnClose,true);
}

AddPrismoidDialog::~AddPrismoidDialog()
{
    delete ui;
}

void AddPrismoidDialog::GetModelingMsg(PrismoidModel newprismoid,QVector<float> fieldParam)
{
    ui->Bottomx1->setText(QString::number(newprismoid.Param[0]));
    ui->Bottomx2->setText(QString::number(newprismoid.Param[1]));
    ui->Bottomy1->setText(QString::number(newprismoid.Param[2]));
    ui->Bottomy2->setText(QString::number(newprismoid.Param[3]));
    ui->Topx1->setText(QString::number(newprismoid.Param[4]));
    ui->Topx2->setText(QString::number(newprismoid.Param[5]));
    ui->Topy1->setText(QString::number(newprismoid.Param[6]));
    ui->Topy2->setText(QString::number(newprismoid.Param[7]));
    ui->h1->setText(QString::number(newprismoid.Param[8]));
    ui->h2->setText(QString::number(newprismoid.Param[9]));
    ui->comboBox->setCurrentIndex(newprismoid.Direction);
    ui->DenEdit->setText(QString::number(newprismoid.Density));
    ui->MEdit->setText(QString::number(newprismoid.Magnetization));
    ui->NameEdit->setText(newprismoid.Name);
    ui->DecEdit->setText(QString::number(newprismoid.Declination));
    ui->IncEdit->setText(QString::number(newprismoid.Inclination));
    color=newprismoid.Color;
    FieldParam=fieldParam;
    if (FieldParam[9]==0){
        ui->UnitLable->setText("Unit:m");
    }else if(FieldParam[9]==1){
        ui->UnitLable->setText("Unit:hm");
    }else if(FieldParam[9]==2){
        ui->UnitLable->setText("Unit:km");
    }
}

void AddPrismoidDialog::resizeEvent(QResizeEvent *event)
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
}

void AddPrismoidDialog::storeInitialGeometries(QWidget *widget)
{
    for (QObject *child : widget->children()) {
        if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            m_initialGeometries[childWidget] = childWidget->geometry();
            storeInitialGeometries(childWidget);
        }
    }
}

bool AddPrismoidDialog::validateCubeParameters(const QVector<double> &params, double density, double m, int direction, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, QString &errorMessage)
{
    // 检查参数数量
    if (params.size() != 10) {
        errorMessage = "Invalid parameter";
        return false;
    }

    // 提取参数
    double bottomX1 = params[0];
    double bottomX2 = params[1];
    double bottomY1 = params[2];
    double bottomY2 = params[3];
    double topX1 = params[4];
    double topX2 = params[5];
    double topY1 = params[6];
    double topY2 = params[7];
    double h1 = params[8];
    double h2 = params[9];

    // 检查物理属性
    if (density == 0 && m == 0) {
        errorMessage = "Model physical properties not set";
        return false;
    }


    // 根据方向确定高度对应的维度
    double minDim1, maxDim1, minDim2, maxDim2, minDim3, maxDim3;

    switch (direction) {
    case 0: // 高度沿X轴
        minDim1 = qMin(h1, h2);
        maxDim1 = qMax(h1, h2);
        minDim2 = qMin(bottomY1, topY1);
        maxDim2 = qMax(bottomY2, topY2);
        minDim3 = qMin(bottomX1, topX1);
        maxDim3 = qMax(bottomX2, topX2);
        break;

    case 1: // 高度沿Y轴
        minDim1 = qMin(bottomX1, topX1);
        maxDim1 = qMax(bottomX2, topX2);
        minDim2 = qMin(h1, h2);
        maxDim2 = qMax(h1, h2);
        minDim3 = qMin(bottomY1, topY1);
        maxDim3 = qMax(bottomY2, topY2);
        break;

    case 2: // 高度沿Z轴
        minDim1 = qMin(bottomX1, topX1);
        maxDim1 = qMax(bottomX2, topX2);
        minDim2 = qMin(bottomY1, topY1);
        maxDim2 = qMax(bottomY2, topY2);
        minDim3 = qMin(h1, h2);
        maxDim3 = qMax(h1, h2);
        break;
    }

    // 检查是否在建模空间内
    bool withinBounds = true;

    if (direction == 0) { // X方向高度
        withinBounds = (minDim1 >= xmin && maxDim1 <= xmax &&
                        minDim2 >= ymin && maxDim2 <= ymax &&
                        minDim3 >= zmin && maxDim3 <= zmax);
    } else if (direction == 1) { // Y方向高度
        withinBounds = (minDim1 >= xmin && maxDim1 <= xmax &&
                        minDim2 >= ymin && maxDim2 <= ymax &&
                        minDim3 >= zmin && maxDim3 <= zmax);
    } else { // Z方向高度
        withinBounds = (minDim1 >= xmin && maxDim1 <= xmax &&
                        minDim2 >= ymin && maxDim2 <= ymax &&
                        minDim3 >= zmin && maxDim3 <= zmax);
    }

    if (!withinBounds) {
        errorMessage = "Prismoid exceeds modeling space boundaries";
        return false;
    }

    // 检查底面和顶面是否有面积
    double bottomArea = qAbs((bottomX2 - bottomX1) * (bottomY2 - bottomY1));
    double topArea = qAbs((topX2 - topX1) * (topY2 - topY1));

    if (bottomArea <= 0 || topArea <= 0) {
        errorMessage = "Bottom or top face has zero area";
        return false;
    }

    return true;
}

void AddPrismoidDialog::backtomodeling(bool)
{
    Modeling*modeling=qobject_cast<Modeling*>(parent());
    QVector<double>Param;
    Param.append(ui->Bottomx1->text().toDouble());
    Param.append(ui->Bottomx2->text().toDouble());
    Param.append(ui->Bottomy1->text().toDouble());
    Param.append(ui->Bottomy2->text().toDouble());
    Param.append(ui->Topx1->text().toDouble());
    Param.append(ui->Topx2->text().toDouble());
    Param.append(ui->Topy1->text().toDouble());
    Param.append(ui->Topy2->text().toDouble());
    Param.append(ui->h1->text().toDouble());
    Param.append(ui->h2->text().toDouble());
    double declination=ui->DecEdit->text().toDouble();
    double inclination=ui->IncEdit->text().toDouble();
    double density=ui->DenEdit->text().toDouble();
    double m=ui->MEdit->text().toDouble();
    int Direction=ui->comboBox->currentIndex();
    QString name=ui->NameEdit->text();

    QString errorMessage;
    if (validateCubeParameters(Param, density, m, Direction,
                               FieldParam[0], FieldParam[1], FieldParam[2], FieldParam[3], FieldParam[4], FieldParam[5], errorMessage)) {
        QMessageBox::information(this, "Success", "Modeling completed");

        PrismoidModel prismoid;
        prismoid.SetProperty(density,m,declination,inclination,color,name,Param,Direction);
        modeling->getAddPrismoidDialogMsg(prismoid);
        this->close();
    } else {
        QMessageBox::warning(this, "Input Error", errorMessage);
    }



}

void AddPrismoidDialog::ChooseModelColor(bool)
{
   color=QColorDialog::getColor(color,this,"Choose Model Color");
}

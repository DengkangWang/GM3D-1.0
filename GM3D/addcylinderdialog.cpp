#include "addcylinderdialog.h"
#include "ui_addcylinderdialog.h"

AddCylinderDialog::AddCylinderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCylinderDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Cylinder Model");
    QIcon Icon(":/icon/myicon/cylinder.png");
    this->setWindowIcon(Icon);
    originalSize=this->size();
    storeInitialGeometries(this);
    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(backtomodeling(bool)));
    connect(ui->PaletteBtn,SIGNAL(clicked(bool)),this,SLOT(ChooseModelColor(bool)));
    this->setAttribute(Qt::WA_DeleteOnClose,true);
}

AddCylinderDialog::~AddCylinderDialog()
{
    delete ui;
}

void AddCylinderDialog::GetModelingMsg(CylinderModel newcylinder,QVector<float> fieldParam)
{
    ui->REdit->setText(QString::number(newcylinder.Radius));
    ui->CxEdit->setText(QString::number(newcylinder.CenterX));
    ui->CyEdit->setText(QString::number(newcylinder.CenterY));
    ui->CzEdit->setText(QString::number(newcylinder.CenterZ));
    ui->DenEdit->setText(QString::number(newcylinder.Density));
    ui->MEdit->setText(QString::number(newcylinder.Magnetization));
    ui->NameEdit->setText(newcylinder.Name);
    ui->DecEdit->setText(QString::number(newcylinder.Declination));
    ui->IncEdit->setText(QString::number(newcylinder.Inclination));
    ui->LEdit->setText(QString::number(newcylinder.Length));
    ui->comboBox->setCurrentIndex(newcylinder.Direction);
    color=newcylinder.Color;
    FieldParam=fieldParam;
    if (FieldParam[9]==0){
        ui->UnitLabel->setText("Unit:m");
    }else if(FieldParam[9]==1){
        ui->UnitLabel->setText("Unit:hm");
    }else if(FieldParam[9]==2){
        ui->UnitLabel->setText("Unit:km");
    }
}

void AddCylinderDialog::resizeEvent(QResizeEvent *event)
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

void AddCylinderDialog::backtomodeling(bool)
{   Modeling*modeling=qobject_cast<Modeling*>(parent());
    QString cx=ui->CxEdit->text();
    QString cy=ui->CyEdit->text();
    QString cz=ui->CzEdit->text();
    QString den=ui->DenEdit->text();
    QString m=ui->MEdit->text();
    QString dec=ui->DecEdit->text();
    QString inc=ui->IncEdit->text();
    QString l=ui->LEdit->text();
    QString r=ui->REdit->text();
    int d=ui->comboBox->currentIndex();

    QString errorMessage;
    if (validateCylinderParameters(cx, cy, cz, den, m, r, l, d,
                                   FieldParam[0], FieldParam[1], FieldParam[2], FieldParam[3], FieldParam[4], FieldParam[5], errorMessage)) {
        QMessageBox::information(this, "Success", "Modeling completed");
        CylinderModel cylinder;
        cylinder.SetProperty(cx.toDouble(),cy.toDouble(),cz.toDouble(),l.toDouble(),r.toDouble(),d,den.toDouble(),
                             m.toDouble(),dec.toDouble(),inc.toDouble(),color,ui->NameEdit->text());
        modeling->getAddCylinderDialogMsg(cylinder);
        this->close();
    } else {
        QMessageBox::warning(this, "Input Error", errorMessage);
    }

}

void AddCylinderDialog::ChooseModelColor(bool)
{
 color=QColorDialog::getColor(color,this,"Choose Model Color");
}

void AddCylinderDialog::storeInitialGeometries(QWidget *widget)
{
    for (QObject *child : widget->children()) {
        if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            m_initialGeometries[childWidget] = childWidget->geometry();
            storeInitialGeometries(childWidget);
        }
    }
}

bool AddCylinderDialog::validateCylinderParameters(const QString &cx, const QString &cy, const QString &cz, const QString &den, const QString &m, const QString &radius, const QString &length, int direction, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, QString &errorMessage)
{
    // 转换为数值
    bool cxOk, cyOk, czOk, denOk, mOk, radiusOk, lengthOk;
    double cxVal = cx.toDouble(&cxOk);
    double cyVal = cy.toDouble(&cyOk);
    double czVal = cz.toDouble(&czOk);
    double denVal = den.toDouble(&denOk);
    double mVal = m.toDouble(&mOk);
    double radiusVal = radius.toDouble(&radiusOk);
    double lengthVal = length.toDouble(&lengthOk);

    // 检查数值转换是否成功
    if (!cxOk || !cyOk || !czOk || !denOk || !mOk || !radiusOk || !lengthOk) {
        errorMessage = "Invalid numeric input";
        return false;
    }

    // 检查物理属性
    if (denVal == 0 && mVal == 0) {
        errorMessage = "Model physical properties not set";
        return false;
    }

    // 检查半径和长度为正数
    if (radiusVal <= 0 || lengthVal <= 0) {
        errorMessage = "Radius and length must be positive values";
        return false;
    }

    // 检查方向是否有效
    if (direction < 0 || direction > 2) {
        errorMessage = "Invalid cylinder direction";
        return false;
    }

    // 计算圆柱体边界
    double xMinCylinder = cxVal;
    double xMaxCylinder = cxVal;
    double yMinCylinder = cyVal;
    double yMaxCylinder = cyVal;
    double zMinCylinder = czVal;
    double zMaxCylinder = czVal;

    // 根据延伸方向调整边界
    switch (direction) {
    case 0: // 沿X轴延伸
        xMinCylinder -= lengthVal / 2.0;
        xMaxCylinder += lengthVal / 2.0;
        yMinCylinder -= radiusVal;
        yMaxCylinder += radiusVal;
        zMinCylinder -= radiusVal;
        zMaxCylinder += radiusVal;
        break;
    case 1: // 沿Y轴延伸
        xMinCylinder -= radiusVal;
        xMaxCylinder += radiusVal;
        yMinCylinder -= lengthVal / 2.0;
        yMaxCylinder += lengthVal / 2.0;
        zMinCylinder -= radiusVal;
        zMaxCylinder += radiusVal;
        break;
    case 2: // 沿Z轴延伸
        xMinCylinder -= radiusVal;
        xMaxCylinder += radiusVal;
        yMinCylinder -= radiusVal;
        yMaxCylinder += radiusVal;
        zMinCylinder -= lengthVal / 2.0;
        zMaxCylinder += lengthVal / 2.0;
        break;
    }

    // 检查是否在建模空间内
    if (xMinCylinder < xmin || xMaxCylinder > xmax ||
        yMinCylinder < ymin || yMaxCylinder > ymax ||
        zMinCylinder < zmin || zMaxCylinder > zmax) {
        errorMessage = "Cylinder exceeds modeling space boundaries";
        return false;
    }

    return true;
}

#include "addspheredialog.h"
#include "ui_addspheredialog.h"

//#include "modeling.h"

AddSphereDialog::AddSphereDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSphereDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Sphere Model");
    QIcon Icon(":/icon/myicon/sphere.png");
    this->setWindowIcon(Icon);
    originalSize=this->size();
    storeInitialGeometries(this);
    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(backtomodeling(bool)));
    connect(ui->PaletteBtn,SIGNAL(clicked(bool)),this,SLOT(ChooseModelColor(bool)));
    this->setAttribute(Qt::WA_DeleteOnClose,true);
}

AddSphereDialog::~AddSphereDialog()
{
    delete ui;
}

void AddSphereDialog::GetModelingMsg(SphereModel newsphere,QVector<float> fieldParam)
{
    ui->REdit->setText(QString::number(newsphere.Radius));
    ui->CxEdit->setText(QString::number(newsphere.CenterX));
    ui->CyEdit->setText(QString::number(newsphere.CenterY));
    ui->CzEdit->setText(QString::number(newsphere.CenterZ));
    ui->DenEdit->setText(QString::number(newsphere.Density));
    ui->MEdit->setText(QString::number(newsphere.Magnetization));
    ui->NameEdit->setText(newsphere.Name);
    ui->DecEdit->setText(QString::number(newsphere.Declination));
    ui->IncEdit->setText(QString::number(newsphere.Inclination));
    color=newsphere.Color;
    FieldParam=fieldParam;
    if (FieldParam[9]==0){
        ui->UnitLable->setText("Unit:m");
    }else if(FieldParam[9]==1){
        ui->UnitLable->setText("Unit:hm");
    }else if(FieldParam[9]==2){
        ui->UnitLable->setText("Unit:km");
    }
}

void AddSphereDialog::resizeEvent(QResizeEvent *event)
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

void AddSphereDialog::backtomodeling(bool)
{
    Modeling*modeling=qobject_cast<Modeling*>(parent());
    SphereModel newsphere;
    QString cx=ui->CxEdit->text();
    QString cy=ui->CyEdit->text();
    QString cz=ui->CzEdit->text();
    QString den=ui->DenEdit->text();
    QString m=ui->MEdit->text();
    QString dec=ui->DecEdit->text();
    QString inc=ui->IncEdit->text();
    QString r=ui->REdit->text();

    QString errorMessage;
    if (validateSphereParameters(cx, cy, cz, den, m, r,
                                 FieldParam[0], FieldParam[1], FieldParam[2], FieldParam[3], FieldParam[4], FieldParam[5],
                                 errorMessage)) {
        QMessageBox::information(this, "Success", "Modeling completed");

        newsphere.SetPorperty(r.toDouble(),cx.toDouble(),cy.toDouble(),cz.toDouble(),den.toDouble(),m.toDouble(),dec.toDouble(),
                              inc.toDouble(),ui->NameEdit->text(),color);
        modeling->getAddSphereDialogMsg(newsphere);
        this->close();
    } else {
        QMessageBox::warning(this, "Input Error", errorMessage);
    }

}


void AddSphereDialog::ChooseModelColor(bool)
{
    color = QColorDialog::getColor(Qt::white, this, "choose color");
}

void AddSphereDialog::storeInitialGeometries(QWidget *widget)
{
    for (QObject *child : widget->children()) {
        if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            m_initialGeometries[childWidget] = childWidget->geometry();
            storeInitialGeometries(childWidget);
        }
    }
}

bool AddSphereDialog::validateSphereParameters(const QString &cx, const QString &cy, const QString &cz, const QString &den, const QString &m, const QString &radius, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, QString &errorMessage)
{
    // 转换为数值
    bool cxOk, cyOk, czOk, denOk, mOk, radiusOk;
    double cxVal = cx.toDouble(&cxOk);
    double cyVal = cy.toDouble(&cyOk);
    double czVal = cz.toDouble(&czOk);
    double denVal = den.toDouble(&denOk);
    double mVal = m.toDouble(&mOk);
    double radiusVal = radius.toDouble(&radiusOk);

    // 检查数值转换是否成功
    if (!cxOk || !cyOk || !czOk || !denOk || !mOk || !radiusOk) {
        errorMessage = "Invalid numeric input";
        return false;
    }

    // 检查物理属性
    if (denVal == 0 && mVal == 0) {
        errorMessage = "Model physical properties not set";
        return false;
    }

    // 检查半径为正数
    if (radiusVal <= 0) {
        errorMessage = "Radius must be a positive value";
        return false;
    }

    // 计算球体边界（中心点加减半径）
    double xMinSphere = cxVal - radiusVal;
    double xMaxSphere = cxVal + radiusVal;
    double yMinSphere = cyVal - radiusVal;
    double yMaxSphere = cyVal + radiusVal;
    double zMinSphere = czVal - radiusVal;
    double zMaxSphere = czVal + radiusVal;

    // 检查是否在建模空间内
    if (xMinSphere < xmin || xMaxSphere > xmax ||
        yMinSphere < ymin || yMaxSphere > ymax ||
        zMinSphere < zmin || zMaxSphere > zmax) {
        errorMessage = "Sphere exceeds modeling space boundaries";
        return false;
    }

    return true;
}

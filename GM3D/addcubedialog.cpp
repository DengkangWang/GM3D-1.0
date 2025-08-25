#include "addcubedialog.h"
#include "ui_addcubedialog.h"
#include "QString"
AddCubeDialog::AddCubeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCubeDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Cuboid Model");
    QIcon Icon(":/icon/myicon/cube.png");
    this->setWindowIcon(Icon);

    originalSize=this->size();
    storeInitialGeometries(this);
    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(backtomodeling(bool)));
    connect(ui->PaletteBtn,SIGNAL(clicked(bool)),this,SLOT(ChooseModelColor(bool)));
    this->setAttribute(Qt::WA_DeleteOnClose,true);
}

AddCubeDialog::~AddCubeDialog()
{
    delete ui;
}

void AddCubeDialog::GetModelingMsg(CuboidModel newcuboid,QVector<float> fieldParam)
{
    ui->CxEdit->setText(QString::number(newcuboid.CenterX));
    ui->CyEdit->setText(QString::number(newcuboid.CenterY));
    ui->CzEdit->setText(QString::number(newcuboid.CenterZ));
    ui->DenEdit->setText(QString::number(newcuboid.Density));
    ui->MEdit->setText(QString::number(newcuboid.Magnetization));
    ui->NameEdit->setText(newcuboid.Name);
    ui->DecEdit->setText(QString::number(newcuboid.Declination));
    ui->IncEdit->setText(QString::number(newcuboid.Inclination));
    ui->LEdit->setText(QString::number(newcuboid.Length));
    ui->WEdit->setText(QString::number(newcuboid.Width));
    ui->HEdit->setText(QString::number(newcuboid.Height));
    color=newcuboid.Color;
    FieldParam=fieldParam;

    if (FieldParam[9]==0){
        ui->UnitLable->setText("Unit:m");
    }else if(FieldParam[9]==1){
        ui->UnitLable->setText("Unit:hm");
    }else if(FieldParam[9]==2){
        ui->UnitLable->setText("Unit:km");
    }
}

void AddCubeDialog::resizeEvent(QResizeEvent *event)
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

void AddCubeDialog::backtomodeling(bool)
{   Modeling*modeling=qobject_cast<Modeling*>(parent());
    QString cx=ui->CxEdit->text();
    QString cy=ui->CyEdit->text();
    QString cz=ui->CzEdit->text();
    QString den=ui->DenEdit->text();
    QString m=ui->MEdit->text();
    QString dec=ui->DecEdit->text();
    QString inc=ui->IncEdit->text();
    QString l=ui->LEdit->text();
    QString w=ui->WEdit->text();
    QString h=ui->HEdit->text();

    QString errorMessage;
    if (validateModelParameters(cx, cy, cz, den, m, l, w, h,
                                FieldParam[0], FieldParam[1], FieldParam[2], FieldParam[3], FieldParam[4], FieldParam[5],
                                errorMessage)) {
        QMessageBox::information(this, "Success", "Modeling completed");

        //模型输入检验正确
        CuboidModel cuboid;
        cuboid.SetProperty(cx.toDouble(),cy.toDouble(),cz.toDouble(),l.toDouble(),w.toDouble(),h.toDouble(),den.toDouble(),
                           m.toDouble(),dec.toDouble(),inc.toDouble(),color,ui->NameEdit->text());
        modeling->getAddCubeDialogMsg(cuboid);
        this->close();

    } else {
        QMessageBox::warning(this, "Input Error", errorMessage);
    }
}

void AddCubeDialog::ChooseModelColor(bool)
{
    color=QColorDialog::getColor(color,this,"Choose Model Color");
}

void AddCubeDialog::storeInitialGeometries(QWidget *widget)
{
    for (QObject *child : widget->children()) {
        if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            m_initialGeometries[childWidget] = childWidget->geometry();
            storeInitialGeometries(childWidget);
        }
    }
}

bool AddCubeDialog::validateModelParameters(const QString &cx, const QString &cy, const QString &cz, const QString &den, const QString &m, const QString &l, const QString &w, const QString &h, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, QString &errorMessage)
{


    bool cxOk, cyOk, czOk, denOk, mOk, lOk, wOk, hOk;
    double cxVal = cx.toDouble(&cxOk);
    double cyVal = cy.toDouble(&cyOk);
    double czVal = cz.toDouble(&czOk);
    double denVal = den.toDouble(&denOk);
    double mVal = m.toDouble(&mOk);
    double lVal = l.toDouble(&lOk);
    double wVal = w.toDouble(&wOk);
    double hVal = h.toDouble(&hOk);

    // 检查数值转换是否成功
    if (!cxOk || !cyOk || !czOk || !denOk || !mOk || !lOk || !wOk || !hOk) {
        errorMessage = "Invalid numeric input";
        return false;
    }

    // 检查物理属性
    if (denVal == 0 && mVal == 0) {
        errorMessage = "Model physical properties not set";
        return false;
    }

    // 检查长宽高为正数
    if (lVal <= 0 || wVal <= 0 || hVal <= 0) {
        errorMessage = "Dimensions must be positive values";
        return false;
    }

    // 计算模型边界
    double xMinModel = cxVal - lVal / 2.0;
    double xMaxModel = cxVal + lVal / 2.0;
    double yMinModel = cyVal - wVal / 2.0;
    double yMaxModel = cyVal + wVal / 2.0;
    double zMinModel = czVal - hVal / 2.0;
    double zMaxModel = czVal + hVal / 2.0;

    // 检查是否在建模空间内
    if (xMinModel < xmin || xMaxModel > xmax ||
        yMinModel < ymin || yMaxModel > ymax ||
        zMinModel < zmin || zMaxModel > zmax) {
        errorMessage = "Model exceeds modeling space boundaries";
        return false;
    }

    return true;
}

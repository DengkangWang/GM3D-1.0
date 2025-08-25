#include "sourcesetting.h"
#include "ui_sourcesetting.h"
#include "modeling.h"


SourceSetting::SourceSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SourceSetting)
{
    ui->setupUi(this);
    this->setWindowTitle("Setting Field");
    QIcon Icon(":/icon/myicon/setting.png");
    this->setWindowIcon(Icon);
    originalSize=this->size();
    storeInitialGeometries(this);
    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(CompleteSourceSet(bool)));
    connect(ui->cancelBtn,SIGNAL(clicked(bool)),this,SLOT(CloseDialog(bool)));
    this->setAttribute(Qt::WA_DeleteOnClose,true); //关闭窗口时删除界面，释放空间
}

SourceSetting::~SourceSetting()
{
    delete ui;
}

void SourceSetting::getModelingMsg(QVector<float> Fieldparam)
{  
    SOURCE=Fieldparam;
    ui->xminEdit->setText(QString::number(SOURCE[0]));
    ui->xmaxEdit->setText(QString::number(SOURCE[1]));
    ui->yminEdit->setText(QString::number(SOURCE[2]));
    ui->ymaxEdit->setText(QString::number(SOURCE[3]));
    ui->zminEdit->setText(QString::number(SOURCE[4]));
    ui->zmaxEdit->setText(QString::number(SOURCE[5]));
    ui->xmeshEdit->setText(QString::number(SOURCE[6]));
    ui->ymeshEdit->setText(QString::number(SOURCE[7]));
    ui->zmeshEdit->setText(QString::number(SOURCE[8]));
    ui->comboBox->setCurrentIndex(SOURCE[9]);
}

void SourceSetting::CompleteSourceSet(bool)
{
    QString xmin =ui->xminEdit->text();
    SOURCE[0]=xmin.toFloat();
    QString xmax =ui->xmaxEdit->text();
    SOURCE[1]=xmax.toFloat();
    QString ymin =ui->yminEdit->text();
    SOURCE[2]=ymin.toFloat();
    QString ymax =ui->ymaxEdit->text();
    SOURCE[3]=ymax.toFloat();
    QString zmin =ui->zminEdit->text();
    SOURCE[4]=zmin.toFloat();
    QString zmax =ui->zmaxEdit->text();
    SOURCE[5]=zmax.toFloat();
    QString xmesh =ui->xmeshEdit->text();
    SOURCE[6]=xmesh.toFloat();
    QString ymesh =ui->ymeshEdit->text();
    SOURCE[7]=ymesh.toFloat();
    QString zmesh =ui->zmeshEdit->text();
    SOURCE[8]=zmesh.toFloat();
    SOURCE[9]=ui->comboBox->currentIndex();

    QString errorMessage;
    if (validateModelingSpace(SOURCE, errorMessage)) {
        Modeling*modeling=qobject_cast<Modeling*>(parent());
        modeling->getFieldparamDiaglogMsg(SOURCE);
        this->close();
        QMessageBox::information(this, "Success", "Modeling space parameters set successfully");
    } else {
        QMessageBox::warning(this, "Input Error", errorMessage);
    }


}

void SourceSetting::CloseDialog(bool)
{
    this->close();

}

void SourceSetting::resizeEvent(QResizeEvent *event)
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

void SourceSetting::storeInitialGeometries(QWidget *widget)
{
    for (QObject *child : widget->children()) {
        if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            m_initialGeometries[childWidget] = childWidget->geometry();
            storeInitialGeometries(childWidget);
        }
    }
}

bool SourceSetting::validateModelingSpace(const QVector<float>& source, QString &errorMessage)
{

    if (source.size() != 10) {
        errorMessage = "Invalid source array size (expected 10 elements)";
        return false;
    }
    // 提取参数
    float xmin = source[0];
    float xmax = source[1];
    float ymin = source[2];
    float ymax = source[3];
    float zmin = source[4];
    float zmax = source[5];
    float xmesh = source[6];
    float ymesh = source[7];
    float zmesh = source[8];
    float comboIndex = source[9];

    if (xmin != 0 || ymin != 0 || zmin != 0) {
        errorMessage = "Minimum values (xmin, ymin, zmin) must be 0";
        return false;
    }


    if (xmax <= 0 || ymax <= 0 || zmax <= 0) {
        errorMessage = "Maximum values (xmax, ymax, zmax) must be positive integers";
        return false;
    }

    if (xmesh <= 0 || ymesh <= 0 || zmesh <= 0) {
        errorMessage = "Mesh values (xmesh, ymesh, zmesh) must be positive integers";
        return false;
    }

    if (xmax <= xmin || ymax <= ymin || zmax <= zmin) {
        errorMessage = "Maximum values must be greater than minimum values";
        return false;
    }

    if (comboIndex < 0) {
        errorMessage = "Invalid combo box selection";
        return false;
    }
    return true;
}

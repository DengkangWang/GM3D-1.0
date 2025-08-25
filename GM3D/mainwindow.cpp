#include "mainwindow.h"
#include "modeling.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(m_initialWidth, m_initialHeight);
    CreatNewModelButton = new QPushButton("Create Model", this);
    InputModelButton = new QPushButton("Input Model", this);

    CreatNewModelButton->setGeometry(50, 200, 120, 60);
    CreatNewModelButton->setStyleSheet("font-family: 'Times New Roman'; font-size: 14pt;font-weight:bold");

    InputModelButton->setGeometry(230, 200, 120, 60);
    InputModelButton->setStyleSheet("font-family: 'Times New Roman'; font-size: 14pt;font-weight:bold");

    label = new QLabel(this);
    QPixmap pixmap(":/icon/myicon/HomeIcon.png");
    label->setGeometry(150,50,150,120);
    QSize labelSize = label->size();
    label->setPixmap(pixmap.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    m_initialGeometries[CreatNewModelButton] = {50, 200, 120, 60};
    m_initialGeometries[InputModelButton] = {230, 200, 120, 60};
    m_initialGeometries[label] = {150,50,150,120};

    connect(this->CreatNewModelButton,SIGNAL(clicked(bool)),this,SLOT(CreateNewModel(bool)));
    connect(this->InputModelButton,SIGNAL(clicked(bool)),this,SLOT(InputCreatedModel(bool)));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    qreal scaleX = (qreal)width() / m_initialWidth;
    qreal scaleY = (qreal)height() / m_initialHeight;

    for (auto it = m_initialGeometries.begin(); it != m_initialGeometries.end(); ++it) {
        QWidget *widget = it.key();
        ControlGeometry geom = it.value();

        int newX = geom.x * scaleX;
        int newY = geom.y * scaleY;
        int newWidth = geom.width * scaleX;
        int newHeight = geom.height * scaleY;

        widget->setGeometry(newX, newY, newWidth, newHeight);}
}

void MainWindow::CreateNewModel(bool)
{
    this->hide();
    Model model;
    QVector<float> fieldparam={0,100,0,100,0,100,1,1,1,2};
    QVector<SphereModel>SPHERELIST;
    QVector<CuboidModel>CUBOIDLIST;
    QVector<CylinderModel>CYLINDERLIST;
    QVector<IrregularModel>IRREGULARLIST;
    QVector<PrismoidModel>PRISMOIDLIST;
    model.setModelParam(fieldparam,SPHERELIST,CUBOIDLIST,CYLINDERLIST,IRREGULARLIST,PRISMOIDLIST);
    Modeling* modelingmodule=new Modeling;
    modelingmodule->GetInitialMsg(model);
    modelingmodule->show();
}

void MainWindow::InputCreatedModel(bool)
{
    this->hide();
    Model model;
    QString filePath = QFileDialog::getOpenFileName(this,tr("Choose a model file"),"",tr("(*.bin)"));
    model.ReadModelFile(filePath);
    Modeling* modelingmodule=new Modeling;
    modelingmodule->GetInitialMsg(model);
    modelingmodule->show();
}

MainWindow::~MainWindow() {

}

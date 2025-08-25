#include "modeling.h"
#include "ui_modeling.h"
#include <QPainter>
#include <QSignalMapper>
#include "sourcesetting.h"
#include "addspheredialog.h"
#include "addcubedialog.h"
#include "addcylinderdialog.h"
#include "addirregulardialog.h"
#include "addprismoiddialog.h"
#include "profile.h"

#include <QFileDialog>
#include <QMessageBox>
#include<QProgressDialog>
Modeling::Modeling(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Modeling)
{
    ui->setupUi(this);
    this->setWindowTitle("Modeling");
    QIcon Icon(":/icon/myicon/HomeIcon.png");
    this->setWindowIcon(Icon);
    originalSize=this->size();
    storeInitialGeometries(this);
    QPushButton *addmodelbtn[5]={ui->AddSphereBtn,ui->AddCuboidBtn,ui->AddCylinderBtn,
                                 ui->AddIrreBtn,ui->AddPrismBtn};
    QSignalMapper * myaddmodelbtnmapper;
    myaddmodelbtnmapper =new QSignalMapper(this);
    for (int i =0;i<5;i++){
        connect(addmodelbtn[i],SIGNAL(clicked(bool)),myaddmodelbtnmapper,SLOT(map()));
       myaddmodelbtnmapper->setMapping(addmodelbtn[i],i);
   }
    model =new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList(QStringLiteral("Model list")));
    QIcon sphereIcon(":/icon/myicon/sphere.png");
    QIcon cuboidIcon(":/icon/myicon/cube.png");
    QIcon cylinerIcon(":/icon/myicon/cylinder.png");
    QIcon prismoidIcon(":/icon/myicon/prismoid.png");
    QIcon irregularIcon(":/icon/myicon/custom.png");
    ui->treeView->setModel(model);
    sphereitem=new QStandardItem(sphereIcon,"Sphere");
    cuboiditem =new QStandardItem(cuboidIcon,"Cuboid");
    cylinderitem=new QStandardItem(cylinerIcon,"Cylinder");
    irregularitem=new QStandardItem(prismoidIcon,"Irregular");
    prismoiditem=new QStandardItem(irregularIcon,"Prismoid");
    model->appendRow(sphereitem);
    model->appendRow(cuboiditem);
    model->appendRow(cylinderitem);
    model->appendRow(irregularitem);
    model->appendRow(prismoiditem);
    ui->treeView->expandAll();
    menu = new QMenu(this);
    deleteaction=new QAction("delete",this);
    modifyaction=new QAction("modify",this);

    menu->addAction(deleteaction);
    menu->addAction(modifyaction);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(myaddmodelbtnmapper,SIGNAL(mappedInt(int)),this,SLOT(AddModelBtn(int)));
    connect(ui->FieldParamSetBtn,SIGNAL(clicked(bool)),this,SLOT(SetFieldParamBtn()));
    connect(deleteaction,&QAction::triggered,this,&Modeling::deletenode);
    connect(modifyaction,&QAction::triggered,this,&Modeling::modifynode);
    connect(ui->treeView,&QTreeView::customContextMenuRequested,[this](const QPoint &pos){
        menu->exec(ui->treeView->mapToGlobal(pos));
    });
    connect(ui->OutputBtn,SIGNAL(clicked(bool)),this,SLOT(OutputBtn()));
    connect(ui->OutputBtn_2,SIGNAL(clicked(bool)),this,SLOT(OutputDataBtn()));

    connect(ui->ForwardBtn,SIGNAL(clicked(bool)),this,SLOT(GotoForwarding()));
    connect(ui->profileBtn,SIGNAL(clicked(bool)),this,SLOT(GotoProfile()));
//

}
void Modeling::getAddSphereDialogMsg(SphereModel newsphere)
{
    newsphere.Subdivision(FieldParam[6],FieldParam[7],FieldParam[8],FieldParam[0],FieldParam[1],FieldParam[2],FieldParam[3],FieldParam[4],FieldParam[5]);
    SPHERELIST.append(newsphere);
    QStandardItem *item = new QStandardItem(newsphere.Name);
    sphereitem->appendRow(item);

}

void Modeling::getAddCubeDialogMsg(CuboidModel newcuboid)
{
    newcuboid.Subdivision(FieldParam[6],FieldParam[7],FieldParam[8],FieldParam[0],FieldParam[1],FieldParam[2],FieldParam[3],FieldParam[4],FieldParam[5]);
    CUBOIDLIST.append(newcuboid);
    QStandardItem *item = new QStandardItem(newcuboid.Name);
    cuboiditem->appendRow(item);
}

void Modeling::getAddCylinderDialogMsg(CylinderModel newcylinder)
{
    newcylinder.Subdivision(FieldParam[6],FieldParam[7],FieldParam[8],FieldParam[0],FieldParam[1],FieldParam[2],FieldParam[3],FieldParam[4],FieldParam[5]);
    CYLINDERLIST.append(newcylinder);
    QStandardItem *item = new QStandardItem(newcylinder.Name);
    cylinderitem->appendRow(item);

}

void Modeling::getAddPrismoidDialogMsg(PrismoidModel newprismoid)
{

    newprismoid.Subdivision(FieldParam[6],FieldParam[7],FieldParam[8],FieldParam[0],FieldParam[1],FieldParam[2],FieldParam[3],FieldParam[4],FieldParam[5]);
    PRISMOIDLIST.append(newprismoid);
    QStandardItem *item =new QStandardItem(newprismoid.Name);
    prismoiditem->appendRow(item);

}

void Modeling::getAddIrregularDiaglogMsg(IrregularModel newIrregular)
{
    IRREGULARLIST.append(newIrregular);
    QStandardItem *item = new QStandardItem(newIrregular.Name);
    irregularitem->appendRow(item);
}

void Modeling::getFieldparamDiaglogMsg(QVector<float> fieldparam)
{
    FieldParam=fieldparam;
}

/**
 * @brief Modeling::GetInitialMsg
 * Set the initial parameters of the modeling module, including the model, field size, etc.
 * @param Model model
 */

void Modeling::GetInitialMsg(Model model)
{

    FieldParam=model.FieldParam;
    AxisLen[0]=((FieldParam[1]-FieldParam[0])/FieldParam[6]);
    AxisLen[1]=((FieldParam[3]-FieldParam[2])/FieldParam[7]);
    AxisLen[2]=((FieldParam[5]-FieldParam[4])/FieldParam[8]);
    IRREGULARLIST=model.IRREGULARLIST;
    CYLINDERLIST=model.CYLINDERLIST;
    SPHERELIST=model.SPHERELIST;
    CUBOIDLIST=model.CUBOIDLIST;
    PRISMOIDLIST=model.PRISMOIDLIST;

    for (int s=0;s<SPHERELIST.length();s++){
        QStandardItem *item = new QStandardItem(SPHERELIST[s].Name);
        sphereitem->appendRow(item);
    }

    for (int irr=0;irr<IRREGULARLIST.length();irr++){
        QStandardItem *item = new QStandardItem(IRREGULARLIST[irr].Name);
        irregularitem->appendRow(item);
    }

    for (int irr=0;irr<CYLINDERLIST.length();irr++){
        QStandardItem *item = new QStandardItem(CYLINDERLIST[irr].Name);
        cylinderitem->appendRow(item);
    }

    for (int irr=0;irr<CUBOIDLIST.length();irr++){
        QStandardItem *item = new QStandardItem(CUBOIDLIST[irr].Name);
        cuboiditem->appendRow(item);
    }

    for (int irr=0;irr<PRISMOIDLIST.length();irr++){
        QStandardItem *item = new QStandardItem(PRISMOIDLIST[irr].Name);
        prismoiditem->appendRow(item);
    }

}

Modeling::~Modeling()
{
    delete ui;
}



/**
 * @brief Modeling::resizeEvent
 * Overide the resizeEvent function to adjust the size of the interface and its controls proportionally.
 * Calculate the scaling ratio of the interface. Then, retrieve the position information of the controls from "m_initialGeometries" and update their new positions proportionally.
 */
void Modeling::resizeEvent(QResizeEvent *event)
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

        for (int i=0;i<7;++i){
            Axis3DPoint[i]= QPointF(InitAxis3DPoint[i].x()*scaleX,InitAxis3DPoint[i].y()*scaleY);
        }
        Axis3D=QRectF(InitAxis3D.x()*scaleX,InitAxis3D.y()*scaleY,InitAxis3D.width()*scaleX,InitAxis3D.height()*scaleY);
        AxisX=QRectF(InitAxisX.x()*scaleX,InitAxisX.y()*scaleY,InitAxisX.width()*scaleX,InitAxisX.height()*scaleY);
        AxisY=QRectF(InitAxisY.x()*scaleX,InitAxisY.y()*scaleY,InitAxisY.width()*scaleX,InitAxisY.height()*scaleY);
        AxisZ=QRectF(InitAxisZ.x()*scaleX,InitAxisZ.y()*scaleY,InitAxisZ.width()*scaleX,InitAxisZ.height()*scaleY);

        Axis3Dlen[0]=InitAxis3Dlen[0]*scaleX;
        Axis3Dlen[1]=InitAxis3Dlen[1]*scaleY;
        Axis3Dlen[2]=InitAxis3Dlen[2]*scaleY;

}

/**
 * @brief Modeling::paintEvent
 */
void Modeling::paintEvent(QPaintEvent*)
{
    update();
    AxisLen[0]=((FieldParam[1]-FieldParam[0])/FieldParam[6]);
    AxisLen[1]=((FieldParam[3]-FieldParam[2])/FieldParam[7]);
    AxisLen[2]=((FieldParam[5]-FieldParam[4])/FieldParam[8]);
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(Axis3D);
    painter.drawRect(AxisX);
    painter.drawRect(AxisY);
    painter.drawRect(AxisZ);

    PaintAxis(painter);
    PaintModel(painter);
    PaintProfile(painter);
}


/**
 * @brief Modeling::storeInitialGeometries
 * Obtain the position information of all controls on the interface.
 * Pair the controls with their position information and store them in a hash table "m_initialGeometries" for subsequent proportional scaling of the interface.
 * @param your interface
 */
void Modeling::storeInitialGeometries(QWidget *widget)
{
    for (QObject *child : widget->children()) {
        if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            m_initialGeometries[childWidget] = childWidget->geometry();
            storeInitialGeometries(childWidget);
        }
    }
}

/**
 * @brief Modeling::PaintAxis
 * @param painter
 */
void Modeling::PaintAxis(QPainter &painter)
{


    QBrush Axis3DBursh(QColor(240,240,237));
    painter.setBrush(Axis3DBursh);
    QPolygonF polygon;
    polygon<<Axis3DPoint[0]<<Axis3DPoint[3]<<Axis3DPoint[4]<<Axis3DPoint[2]<<Axis3DPoint[6]<<Axis3DPoint[5];
    painter.drawPolygon(polygon);

    painter.setPen(QPen(Qt::black,1.5));
    painter.drawLine(Axis3DPoint[0],Axis3DPoint[1]);
    painter.drawLine(Axis3DPoint[0],Axis3DPoint[3]);
    painter.drawLine(Axis3DPoint[0],Axis3DPoint[5]);
    painter.drawLine(Axis3DPoint[1],Axis3DPoint[4]);
    painter.drawLine(Axis3DPoint[1],Axis3DPoint[6]);
    painter.drawLine(Axis3DPoint[2],Axis3DPoint[4]);
    painter.drawLine(Axis3DPoint[2],Axis3DPoint[6]);
    painter.drawLine(Axis3DPoint[3],Axis3DPoint[4]);
    painter.drawLine(Axis3DPoint[5],Axis3DPoint[6]);

    painter.setPen(QPen(Qt::black, 0.5));
    painter.setFont(QFont("Times", 7));
    int xgrid=AxisLen[0]/10;

    for(int i=0;i<=AxisLen[0];i+=xgrid){
        painter.drawLine(cood3Dto2D(i,0,0),cood3Dto2D(i,AxisLen[1],0));
        painter.drawText(cood3Dto2D(i,0,0)+QPoint(0,18), QString::number(i*FieldParam[6]));
    }



    int ygrid=AxisLen[1]/10;
    for(int i=ygrid;i<=AxisLen[1];i+=ygrid){
        painter.drawLine(cood3Dto2D(0,i,0),cood3Dto2D(AxisLen[0],i,0));
        painter.drawText(cood3Dto2D(0,i,0)+QPoint(0,18), QString::number(i*FieldParam[7]));
    }
    int zgrid=AxisLen[2]/10;

   for(int i=AxisLen[2];i>=0;i-=zgrid){
        painter.drawLine(cood3Dto2D(AxisLen[0],0,i),cood3Dto2D(AxisLen[0],AxisLen[1],i));
        painter.drawLine(cood3Dto2D(0,AxisLen[1],i),cood3Dto2D(AxisLen[0],AxisLen[1],i));
        painter.drawText(cood3Dto2D(AxisLen[0],0,i)+QPoint(-18,0), QString::number(FieldParam[5]-i*FieldParam[8]));

   }

   //z剖面
   for(int i=0;i<AxisLen[0];i+=xgrid){
    painter.drawLine(coodZprofile(i,AxisLen[1]),coodZprofile(i,0));
   }
   for(int i=0;i<AxisLen[1];i+=ygrid){
    painter.drawLine(coodZprofile(AxisLen[0],i),coodZprofile(0,i));
   }

   //x剖面

   for(int i=0;i<AxisLen[2];i+=zgrid){
       painter.drawLine(coodXprofile(AxisLen[1],i),coodXprofile(0,i));
   }
   for(int i=0;i<AxisLen[1];i+=ygrid){
       painter.drawLine(coodXprofile(i,AxisLen[2]),coodXprofile(i,0));
   }

   //y剖面
   for(int i=0;i<AxisLen[0];i+=xgrid){
       painter.drawLine(coodYprofile(i,AxisLen[2]),coodYprofile(i,0));
   }
   for(int i=0;i<AxisLen[2];i+=zgrid){
       painter.drawLine(coodYprofile(AxisLen[0],i),coodYprofile(0,i));
   }
   painter.setFont(QFont("Consolas", 10));



   if(FieldParam[9]==0){
       painter.drawText(cood3Dto2D(AxisLen[0],0,AxisLen[2]/2)+QPoint(-40,-20),"Depth(m)");
       painter.drawText(cood3Dto2D(AxisLen[0]/2,0,0)+QPoint(0,40), "X-Axis(m)");
       painter.drawText(cood3Dto2D(0,AxisLen[1]/2,0)+QPoint(0,40), "Y-Axis(m)");
   }else if(FieldParam[9]==1){
       painter.drawText(cood3Dto2D(AxisLen[0],0,AxisLen[2]/2)+QPoint(-40,-20),"Depth(hm)");
       painter.drawText(cood3Dto2D(AxisLen[0]/2,0,0)+QPoint(0,40), "X-Axis(hm)");
       painter.drawText(cood3Dto2D(0,AxisLen[1]/2,0)+QPoint(0,40), "Y-Axis(hm)");
   }else if(FieldParam[9]==2){
       painter.drawText(cood3Dto2D(AxisLen[0],0,AxisLen[2]/2)+QPoint(-40,-20),"Depth(km)");
       painter.drawText(cood3Dto2D(AxisLen[0]/2,0,0)+QPoint(0,40), "X-Axis(km)");
       painter.drawText(cood3Dto2D(0,AxisLen[1]/2,0)+QPoint(0,40), "Y-Axis(km)");
   }

   painter.drawText(QPointF(AxisZ.x()+AxisZ.width()/2,AxisZ.y()-2), "X");
   painter.drawText(QPointF(AxisY.x()+AxisY.width()/2,AxisY.y()-2), "X");
   painter.drawText(QPointF(AxisX.x()+AxisX.width()/2,AxisX.y()-2), "Z");

   painter.drawText(QPointF(AxisZ.x()-10,AxisZ.y()+AxisZ.height()/2), "Y");
   painter.drawText(QPointF(AxisY.x()-10,AxisY.y()+AxisY.height()/2), "Z");
   painter.drawText(QPointF(AxisX.x()-10,AxisX.y()+AxisX.height()/2), "Y");

   painter.drawText(QPoint(AxisX.x()-5,AxisX.y()), QString::number(FieldParam[2]));
   painter.drawText(QPoint(AxisX.x()+AxisX.width(),AxisX.y()), QString::number(FieldParam[5]));
   painter.drawText(QPoint(AxisX.x()-10,AxisX.y()+AxisX.height()+10), QString::number(FieldParam[3]));

   painter.drawText(QPoint(AxisY.x()-5,AxisY.y()), QString::number(FieldParam[0]));
   painter.drawText(QPoint(AxisY.x()+AxisY.width(),AxisY.y()), QString::number(FieldParam[1]));
   painter.drawText(QPoint(AxisY.x()-10,AxisY.y()+AxisY.height()+10), QString::number(FieldParam[5]));

   painter.drawText(QPoint(AxisZ.x()-5,AxisZ.y()), QString::number(FieldParam[0]));
   painter.drawText(QPoint(AxisZ.x()+AxisZ.width(),AxisZ.y()), QString::number(FieldParam[1]));
   painter.drawText(QPoint(AxisZ.x()-10,AxisZ.y()+AxisZ.height()+10), QString::number(FieldParam[3]));
}

void Modeling::PaintModel(QPainter &painter)
{   int xlen=AxisLen[0];
    int ylen=AxisLen[1];
    int zlen=AxisLen[2];
    for (int s=0;s<SPHERELIST.length();s++){
        QBrush Modelbrush(SPHERELIST[s].Color);
        painter.setBrush(Modelbrush);
        for (int i=xlen-1;i>=0;i-- ){
            for (int j=ylen-1;j>=0;j--){
                for (int k=0;k<zlen;k++){

                    if(SPHERELIST[s].SpaceDensity[i][j][k]!=0||SPHERELIST[s].SpaceMagnetization[i][j][k]!=0){
                        PaintUnit(painter,i,j,k);
                    }
                }
            }
        }
    }

    for (int irr=0;irr<IRREGULARLIST.length();irr++){
        QBrush Modelbrush(IRREGULARLIST[irr].Color);
        painter.setBrush(Modelbrush);
        for (int i=xlen-1;i>=0;i-- ){
            for (int j=ylen-1;j>=0;j--){
                for (int k=0;k<zlen;k++){
                    if(IRREGULARLIST[irr].SpaceDensity[i][j][k]!=0||IRREGULARLIST[irr].SpaceMagnetization[i][j][k]!=0){
                        PaintUnit(painter,i,j,k);
                    }
                }
            }
        }
    }

    for (int irr=0;irr<CYLINDERLIST.length();irr++){

        QBrush Modelbrush(CYLINDERLIST[irr].Color);
        painter.setBrush(Modelbrush);
        for (int i=xlen-1;i>=0;i-- ){
            for (int j=ylen-1;j>=0;j--){
                for (int k=0;k<zlen;k++){
                    if(CYLINDERLIST[irr].SpaceDensity[i][j][k]!=0||CYLINDERLIST[irr].SpaceMagnetization[i][j][k]!=0){
                        PaintUnit(painter,i,j,k);
                    }
                }
            }
        }
    }

    for (int irr=0;irr<CUBOIDLIST.length();irr++){
        QBrush Modelbrush(CUBOIDLIST[irr].Color);
        painter.setBrush(Modelbrush);
        for (int i=xlen-1;i>=0;i-- ){
            for (int j=ylen-1;j>=0;j--){
                for (int k=0;k<zlen;k++){
                    if(CUBOIDLIST[irr].SpaceDensity[i][j][k]!=0||CUBOIDLIST[irr].SpaceMagnetization[i][j][k]!=0){
                        PaintUnit(painter,i,j,k);
                    }
                }
            }
        }
    }

     for (int irr=0;irr<PRISMOIDLIST.length();irr++){
         QBrush Modelbrush(PRISMOIDLIST[irr].Color);
         painter.setBrush(Modelbrush);
         for (int i=xlen-1;i>=0;i-- ){
             for (int j=ylen-1;j>=0;j--){
                 for (int k=0;k<zlen;k++){
                     if(PRISMOIDLIST[irr].SpaceDensity[i][j][k]!=0||PRISMOIDLIST[irr].SpaceMagnetization[i][j][k]!=0){
                        PaintUnit(painter,i,j,k);
                     }
                 }
             }
        }
     }
}

/**
 * @brief Modeling::PaintUnit
 * @param painter
 * @param x
 * @param y
 * @param z
 */
void Modeling::PaintUnit(QPainter &painter, int x, int y, int z)
{   z=AxisLen[2]-z;
    QPolygonF polygon;
    QPointF p1=cood3Dto2D(x,y,z);
    QPointF p2=cood3Dto2D(x+1,y,z);
    QPointF p3=cood3Dto2D(x+1,y,z+1);
    QPointF p4=cood3Dto2D(x+1,y+1,z+1);
    QPointF p5=cood3Dto2D(x,y+1,z+1);
    QPointF p6=cood3Dto2D(x,y+1,+z);
    QPointF p7=cood3Dto2D(x,y,z+1);
    polygon<<p1<<p2<<p3<<p4<<p5<<p6;
    painter.drawPolygon(polygon);

    painter.setPen(QPen(Qt::black, 0.5));
    painter.drawLine(p1,p2);
    painter.drawLine(p2,p3);
    painter.drawLine(p4,p3);
    painter.drawLine(p4,p5);
    painter.drawLine(p5,p6);
    painter.drawLine(p1,p7);
    painter.drawLine(p3,p7);
    painter.drawLine(p5,p7);
}

void Modeling::PaintProfile(QPainter &painter)
{
     int xlen=AxisLen[0];
     int ylen=AxisLen[1];
     int zlen=AxisLen[2];

    for (int s=0;s<SPHERELIST.length();s++){
        QBrush Modelbrush(SPHERELIST[s].Color);
        painter.setBrush(Modelbrush);
        painter.drawEllipse(coodZprofile(SPHERELIST[s].CenterX/FieldParam[6],SPHERELIST[s].CenterY/FieldParam[7]),SPHERELIST[s].Radius/AxisLen[0]/FieldParam[6]*AxisZ.width(),SPHERELIST[s].Radius/AxisLen[1]/FieldParam[7]*AxisZ.height());
        painter.drawEllipse(coodXprofile(SPHERELIST[s].CenterY/FieldParam[7],SPHERELIST[s].CenterZ/FieldParam[8]),SPHERELIST[s].Radius/AxisLen[2]/FieldParam[8]*AxisX.width(),SPHERELIST[s].Radius/AxisLen[1]/FieldParam[7]*AxisX.height());
        painter.drawEllipse(coodYprofile(SPHERELIST[s].CenterX/FieldParam[6],SPHERELIST[s].CenterZ/FieldParam[8]),SPHERELIST[s].Radius/AxisLen[0]/FieldParam[6]*AxisY.width(),SPHERELIST[s].Radius/AxisLen[2]/FieldParam[8]*AxisY.height());
    }

    for (int irr=0;irr<IRREGULARLIST.length();irr++){
        QBrush Modelbrush(IRREGULARLIST[irr].Color);
        painter.setBrush(Modelbrush);

        //z

        for (int i =0;i<xlen;i++){
            for (int j=0;j<ylen;j++){
                for(int k=0;k<zlen;k++){
                    if(IRREGULARLIST[irr].SpaceDensity[i][j][k]!=0||IRREGULARLIST[irr].SpaceMagnetization[i][j][k]!=0){

                        QPointF pz=coodZprofile(i,j);
                        QRectF pzd=QRectF(pz.x(),pz.y(),AxisZ.width()/AxisLen[0],AxisZ.height()/AxisLen[1]);
                        painter.drawRect(pzd);

                         break;
                    }

                }
            }
        }


        //x
        for (int i =0;i<ylen;i++){
            for (int j=0;j<zlen;j++){
                for(int k=0;k<xlen;k++){
                    if(IRREGULARLIST[irr].SpaceDensity[k][i][j]!=0||IRREGULARLIST[irr].SpaceMagnetization[k][i][j]!=0){

                        QPointF px=coodXprofile(i,j);
                        QRectF pxd=QRectF(px.x(),px.y(),AxisX.width()/AxisLen[2],AxisX.height()/AxisLen[1]);
                        painter.drawRect(pxd);
                        break;
                    }

                }
            }
        }

        //y
        for (int i =0;i<xlen;i++){
            for (int j=0;j<zlen;j++){
                for(int k=0;k<ylen;k++){
                    if(IRREGULARLIST[irr].SpaceDensity[i][k][j]!=0||IRREGULARLIST[irr].SpaceMagnetization[i][k][j]!=0){
                        QPointF py=coodYprofile(i,j);
                        QRectF pyd=QRect(py.x(),py.y(),AxisY.width()/AxisLen[0],AxisY.height()/AxisLen[2]);
                        painter.drawRect(pyd);
                        break;
                    }

                }
            }
        }

    }

     for (int irr=0;irr<CYLINDERLIST.length();irr++){
        QBrush Modelbrush(CYLINDERLIST[irr].Color);
        painter.setBrush(Modelbrush);
        switch (CYLINDERLIST[irr].Direction) {
        case 0:
        {
            //x轴向
            painter.drawEllipse(coodXprofile(CYLINDERLIST[irr].CenterY/FieldParam[7],CYLINDERLIST[irr].CenterZ/FieldParam[8]),CYLINDERLIST[irr].Radius/AxisLen[2]*AxisX.width()/FieldParam[8],CYLINDERLIST[irr].Radius/AxisLen[1]/FieldParam[7]*AxisX.height());
            QPointF pz=coodZprofile(CYLINDERLIST[irr].CenterX/FieldParam[6]-CYLINDERLIST[irr].Length/2/FieldParam[6],CYLINDERLIST[irr].CenterY/FieldParam[7]-CYLINDERLIST[irr].Radius/FieldParam[7]);
            painter.drawRect(QRectF(pz.x(),pz.y(),CYLINDERLIST[irr].Length/AxisLen[0]/FieldParam[6]*AxisZ.width(),CYLINDERLIST[irr].Radius*2/AxisLen[1]/FieldParam[7]*AxisZ.height()));
            QPointF py=coodYprofile(CYLINDERLIST[irr].CenterX/FieldParam[6]-CYLINDERLIST[irr].Length/2/FieldParam[6],CYLINDERLIST[irr].CenterZ/FieldParam[8]-CYLINDERLIST[irr].Radius/FieldParam[8]);
            painter.drawRect(QRectF(py.x(),py.y(),CYLINDERLIST[irr].Length/AxisLen[0]/FieldParam[6]*AxisY.width(),CYLINDERLIST[irr].Radius*2/AxisLen[2]/FieldParam[8]*AxisY.height()));

        }
            break;
        case 1:
        {
            //y轴向
            painter.drawEllipse(coodYprofile(CYLINDERLIST[irr].CenterX/FieldParam[6],CYLINDERLIST[irr].CenterZ/FieldParam[8]),CYLINDERLIST[irr].Radius/AxisLen[0]/FieldParam[6]*AxisY.width(),CYLINDERLIST[irr].Radius/AxisLen[2]*AxisY.height()/FieldParam[8]);
            QPointF pz=coodZprofile(CYLINDERLIST[irr].CenterX/FieldParam[6]-CYLINDERLIST[irr].Radius/FieldParam[6],CYLINDERLIST[irr].CenterY/FieldParam[7]-CYLINDERLIST[irr].Length/2/FieldParam[7]);
            painter.drawRect(QRectF(pz.x(),pz.y(),CYLINDERLIST[irr].Radius*2/AxisLen[0]*AxisZ.width()/FieldParam[6],CYLINDERLIST[irr].Length/AxisLen[1]*AxisZ.height()/FieldParam[7]));

            QPointF px=coodXprofile(CYLINDERLIST[irr].CenterX/FieldParam[6]-CYLINDERLIST[irr].Length/2/FieldParam[6],CYLINDERLIST[irr].CenterZ/FieldParam[8]-CYLINDERLIST[irr].Radius/FieldParam[8]);
            painter.drawRect(QRectF(px.x(),px.y(),CYLINDERLIST[irr].Length/AxisLen[0]*AxisX.width()/FieldParam[6],CYLINDERLIST[irr].Radius*2/AxisLen[2]*AxisX.height()/FieldParam[8]));
        }
        break;
        case 2:
        {
           //z轴向
            painter.drawEllipse(coodZprofile(CYLINDERLIST[irr].CenterX/FieldParam[6],CYLINDERLIST[irr].CenterY/FieldParam[7]),CYLINDERLIST[irr].Radius/AxisLen[0]*AxisZ.width()/FieldParam[6],CYLINDERLIST[irr].Radius/AxisLen[0]*AxisZ.height()/FieldParam[7]);

           QPointF px=coodXprofile(CYLINDERLIST[irr].CenterY/FieldParam[7]-CYLINDERLIST[irr].Length/2/FieldParam[7],CYLINDERLIST[irr].CenterZ/FieldParam[8]-CYLINDERLIST[irr].Radius/FieldParam[8]);

           painter.drawRect(QRectF(px.x(),px.y(),CYLINDERLIST[irr].Radius*2/AxisLen[1]*AxisX.width()/FieldParam[7],CYLINDERLIST[irr].Length/AxisLen[2]*AxisX.height()/FieldParam[8]));

          QPointF py=coodYprofile(CYLINDERLIST[irr].CenterX/FieldParam[6]-CYLINDERLIST[irr].Radius/FieldParam[6],CYLINDERLIST[irr].CenterZ/FieldParam[8]-CYLINDERLIST[irr].Length/2/FieldParam[8]);
           painter.drawRect(QRectF(py.x(),py.y(),CYLINDERLIST[irr].Radius*2/AxisLen[0]*AxisX.width()/FieldParam[6],CYLINDERLIST[irr].Length/AxisLen[1]*AxisX.height()/FieldParam[8]));
        }
        break;
        default:
            break;
        }

      }

     for (int irr=0;irr<CUBOIDLIST.length();irr++){
        QBrush Modelbrush(CUBOIDLIST[irr].Color);
        painter.setBrush(Modelbrush);

        QPointF pz=coodZprofile(CUBOIDLIST[irr].CenterX/FieldParam[6]-CUBOIDLIST[irr].Length/2/FieldParam[6],CUBOIDLIST[irr].CenterY/FieldParam[7]-CUBOIDLIST[irr].Width/2/FieldParam[7]);
        painter.drawRect(QRectF(pz.x(),pz.y(),CUBOIDLIST[irr].Length/AxisLen[0]*AxisZ.width()/FieldParam[6],CUBOIDLIST[irr].Width/AxisLen[1]*AxisZ.height()/FieldParam[7]));

        QPointF px=coodXprofile(CUBOIDLIST[irr].CenterY/FieldParam[7]-CUBOIDLIST[irr].Width/2/FieldParam[7],CUBOIDLIST[irr].CenterZ/FieldParam[8]-CUBOIDLIST[irr].Height/2/FieldParam[8]);
        painter.drawRect(QRectF(px.x(),px.y(),CUBOIDLIST[irr].Height/AxisLen[2]*AxisX.width()/FieldParam[7],CUBOIDLIST[irr].Width/AxisLen[1]*AxisX.height()/FieldParam[8]));

        QPointF py=coodYprofile(CUBOIDLIST[irr].CenterX/FieldParam[6]-CUBOIDLIST[irr].Length/2/FieldParam[6],CUBOIDLIST[irr].CenterZ/FieldParam[8]-CUBOIDLIST[irr].Height/2/FieldParam[8]);
        painter.drawRect(QRectF(py.x(),py.y(),CUBOIDLIST[irr].Length/AxisLen[0]*AxisY.width()/FieldParam[6],CUBOIDLIST[irr].Height/AxisLen[2]*AxisY.height()/FieldParam[8]));

     }

     for (int irr=0;irr<PRISMOIDLIST.length();irr++){
        QBrush Modelbrush(PRISMOIDLIST[irr].Color);
        painter.setBrush(Modelbrush);

        switch (PRISMOIDLIST[irr].Direction) {
        case 0:
        {

             QPolygonF polygony;
             polygony<<coodYprofile(PRISMOIDLIST[irr].Param[0]/FieldParam[6],PRISMOIDLIST[irr].Param[8]/FieldParam[8])<<coodYprofile(PRISMOIDLIST[irr].Param[1]/FieldParam[6],PRISMOIDLIST[irr].Param[8]/FieldParam[8])
                      <<coodYprofile(PRISMOIDLIST[irr].Param[5]/FieldParam[6],PRISMOIDLIST[irr].Param[9]/FieldParam[8])<<coodYprofile(PRISMOIDLIST[irr].Param[4]/FieldParam[6],PRISMOIDLIST[irr].Param[9]/FieldParam[8]);
             painter.drawPolygon(polygony);

             QPolygonF polygonx;
             polygonx<<coodXprofile(PRISMOIDLIST[irr].Param[2]/FieldParam[7],PRISMOIDLIST[irr].Param[8]/FieldParam[8])<<coodXprofile(PRISMOIDLIST[irr].Param[3]/FieldParam[7],PRISMOIDLIST[irr].Param[8]/FieldParam[8])
                      <<coodXprofile(PRISMOIDLIST[irr].Param[7]/FieldParam[7],PRISMOIDLIST[irr].Param[9]/FieldParam[8])<<coodXprofile(PRISMOIDLIST[irr].Param[6]/FieldParam[7],PRISMOIDLIST[irr].Param[9]/FieldParam[8]);
             painter.drawPolygon(polygonx);

             QPolygonF polygonz1;
             polygonz1<<coodZprofile(PRISMOIDLIST[irr].Param[0]/FieldParam[6],PRISMOIDLIST[irr].Param[2]/FieldParam[7])<<coodZprofile(PRISMOIDLIST[irr].Param[0]/FieldParam[6],PRISMOIDLIST[irr].Param[3]/FieldParam[7])
                       <<coodZprofile(PRISMOIDLIST[irr].Param[1]/FieldParam[6],PRISMOIDLIST[irr].Param[3]/FieldParam[7])<<coodZprofile(PRISMOIDLIST[irr].Param[1]/FieldParam[6],PRISMOIDLIST[irr].Param[2]/FieldParam[7]);
            painter.drawPolygon(polygonz1);

             QPolygonF polygonz2;
             polygonz2<<coodZprofile(PRISMOIDLIST[irr].Param[4]/FieldParam[6],PRISMOIDLIST[irr].Param[6]/FieldParam[7])<<coodZprofile(PRISMOIDLIST[irr].Param[4]/FieldParam[6],PRISMOIDLIST[irr].Param[7]/FieldParam[7])
                       <<coodZprofile(PRISMOIDLIST[irr].Param[5]/FieldParam[6],PRISMOIDLIST[irr].Param[3]/FieldParam[7])<<coodZprofile(PRISMOIDLIST[irr].Param[5]/FieldParam[6],PRISMOIDLIST[irr].Param[6]/FieldParam[7]);
             painter.drawPolygon(polygonz2);
        }

            break;
        case 1:
            //x
            {

             QPolygonF polygony;
             polygony<<coodYprofile(PRISMOIDLIST[irr].Param[0]/FieldParam[6],PRISMOIDLIST[irr].Param[8]/FieldParam[8])<<coodYprofile(PRISMOIDLIST[irr].Param[1]/FieldParam[6],PRISMOIDLIST[irr].Param[8]/FieldParam[8])
                     <<coodYprofile(PRISMOIDLIST[irr].Param[5]/FieldParam[6],PRISMOIDLIST[irr].Param[9]/FieldParam[8])<<coodYprofile(PRISMOIDLIST[irr].Param[4]/FieldParam[6],PRISMOIDLIST[irr].Param[9]/FieldParam[8]);
             painter.drawPolygon(polygony);

            QPolygonF polygonz;
            polygonz<<coodZprofile(PRISMOIDLIST[irr].Param[2]/FieldParam[7],PRISMOIDLIST[irr].Param[8]/FieldParam[8])<<coodZprofile(PRISMOIDLIST[irr].Param[3]/FieldParam[7],PRISMOIDLIST[irr].Param[8]/FieldParam[8])
                     <<coodZprofile(PRISMOIDLIST[irr].Param[7]/FieldParam[7],PRISMOIDLIST[irr].Param[9]/FieldParam[8])<<coodZprofile(PRISMOIDLIST[irr].Param[6]/FieldParam[7],PRISMOIDLIST[irr].Param[9]/FieldParam[8]);
            painter.drawPolygon(polygonz);

            QPolygonF polygonx1;
            polygonx1<<coodXprofile(PRISMOIDLIST[irr].Param[0]/FieldParam[6],PRISMOIDLIST[irr].Param[2]/FieldParam[7])<<coodXprofile(PRISMOIDLIST[irr].Param[0]/FieldParam[6],PRISMOIDLIST[irr].Param[3]/FieldParam[7])
                      <<coodXprofile(PRISMOIDLIST[irr].Param[1]/FieldParam[6],PRISMOIDLIST[irr].Param[3]/FieldParam[7])<<coodXprofile(PRISMOIDLIST[irr].Param[1]/FieldParam[6],PRISMOIDLIST[irr].Param[2]/FieldParam[7]);
            painter.drawPolygon(polygonx1);

            QPolygonF polygonx2;
            polygonx2<<coodXprofile(PRISMOIDLIST[irr].Param[4]/FieldParam[6],PRISMOIDLIST[irr].Param[6]/FieldParam[7])<<coodXprofile(PRISMOIDLIST[irr].Param[4]/FieldParam[6],PRISMOIDLIST[irr].Param[7]/FieldParam[7])
                      <<coodXprofile(PRISMOIDLIST[irr].Param[5]/FieldParam[6],PRISMOIDLIST[irr].Param[3]/FieldParam[7])<<coodXprofile(PRISMOIDLIST[irr].Param[5]/FieldParam[6],PRISMOIDLIST[irr].Param[6]/FieldParam[7]);
            painter.drawPolygon(polygonx2);
            }
            break;
        case 2:
        {

            QPolygonF polygonx;
            polygonx<<coodZprofile(PRISMOIDLIST[irr].Param[0]/FieldParam[6],PRISMOIDLIST[irr].Param[8]/FieldParam[8])<<coodZprofile(PRISMOIDLIST[irr].Param[1]/FieldParam[6],PRISMOIDLIST[irr].Param[8]/FieldParam[8])
                     <<coodZprofile(PRISMOIDLIST[irr].Param[5]/FieldParam[6],PRISMOIDLIST[irr].Param[9]/FieldParam[8])<<coodZprofile(PRISMOIDLIST[irr].Param[4]/FieldParam[6],PRISMOIDLIST[irr].Param[9]/FieldParam[8]);
            painter.drawPolygon(polygonx);

            QPolygonF polygonz;
            polygonz<<coodYprofile(PRISMOIDLIST[irr].Param[2]/FieldParam[7],PRISMOIDLIST[irr].Param[8]/FieldParam[8])<<coodYprofile(PRISMOIDLIST[irr].Param[3]/FieldParam[7],PRISMOIDLIST[irr].Param[8]/FieldParam[8])
                     <<coodYprofile(PRISMOIDLIST[irr].Param[7]/FieldParam[7],PRISMOIDLIST[irr].Param[9]/FieldParam[8])<<coodYprofile(PRISMOIDLIST[irr].Param[6]/FieldParam[7],PRISMOIDLIST[irr].Param[9]/FieldParam[8]);
            painter.drawPolygon(polygonz);

            QPolygonF polygony1;
            polygony1<<coodXprofile(PRISMOIDLIST[irr].Param[0]/FieldParam[6],PRISMOIDLIST[irr].Param[2]/FieldParam[7])<<coodXprofile(PRISMOIDLIST[irr].Param[0]/FieldParam[6],PRISMOIDLIST[irr].Param[3]/FieldParam[7])
                      <<coodXprofile(PRISMOIDLIST[irr].Param[1]/FieldParam[6],PRISMOIDLIST[irr].Param[3]/FieldParam[7])<<coodXprofile(PRISMOIDLIST[irr].Param[1]/FieldParam[6],PRISMOIDLIST[irr].Param[2]/FieldParam[7]);
            painter.drawPolygon(polygony1);

            QPolygonF polygony2;
            polygony2<<coodXprofile(PRISMOIDLIST[irr].Param[4]/FieldParam[6],PRISMOIDLIST[irr].Param[6]/FieldParam[7])<<coodXprofile(PRISMOIDLIST[irr].Param[4]/FieldParam[6],PRISMOIDLIST[irr].Param[7]/FieldParam[7])
                      <<coodXprofile(PRISMOIDLIST[irr].Param[5]/FieldParam[6],PRISMOIDLIST[irr].Param[3]/FieldParam[7])<<coodXprofile(PRISMOIDLIST[irr].Param[5]/FieldParam[6],PRISMOIDLIST[irr].Param[6]/FieldParam[7]);
            painter.drawPolygon(polygony2);
        }
        break;
        default:
            break;
        }

    }
}
/**
 * @brief Modeling::cood3Dto2D
 * @param x
 * @param y
 * @param z
 * @return
 */
QPointF Modeling::cood3Dto2D(double x, double y, double z)
{
    double xx=Axis3DPoint[2].x()-Axis3Dlen[0]*x/AxisLen[0];
    double xy=Axis3DPoint[2].y()-Axis3Dlen[1]*x/AxisLen[0];
    double yx=Axis3DPoint[2].x()+Axis3Dlen[0]*y/AxisLen[1];
    double yy=Axis3DPoint[2].y()-Axis3Dlen[1]*y/AxisLen[1];

    double xd=(yx-Axis3DPoint[2].x())+xx;
    double yd=(yy-Axis3DPoint[2].y())+xy-Axis3Dlen[2]*z/AxisLen[2];

    return QPointF(xd,yd);

}

QPointF Modeling::coodZprofile(double x, double y)
{
    double yy=AxisZ.y()+AxisZ.height()*y/AxisLen[1];
    double xx=AxisZ.x()+AxisZ.width()*x/AxisLen[0];
    return QPointF(xx,yy);
}

QPointF Modeling::coodXprofile(double y, double z)
{

    double yy=AxisX.y()+AxisX.height()*y/AxisLen[1];
    double xx=AxisX.x()+AxisX.width()*z/AxisLen[2];
    return QPointF(xx,yy);
}

QPointF Modeling::coodYprofile(double x, double z)
{

    double yy=AxisY.y()+AxisY.height()*z/AxisLen[2];
    double xx=AxisY.x()+AxisY.width()*x/AxisLen[0];

    return QPointF(xx,yy);
}

void Modeling::AddModelBtn(int index)
{
    switch (index) {
    case 0:
    {
        SphereModel newsphere;
        QColor color(Qt::red);
        QString Name = "sphere" + QString::number(SPHERELIST.size()+1);
        newsphere.SetPorperty(10,50,50,50,10,10,0,90,Name,color);
        AddSphereDialog*sphere=new AddSphereDialog(this);
        sphere->GetModelingMsg(newsphere,FieldParam);
        sphere->show();
    }
    break;
    case 1:
    {
        CuboidModel newcuboid;
        QColor color(Qt::red);
        QString Name = "cuboid" + QString::number(CUBOIDLIST.size()+1);
        newcuboid.SetProperty(50,50,50,10,10,10,10,10,0,90,color,Name);
        AddCubeDialog* cuboid=new AddCubeDialog(this);
        cuboid->GetModelingMsg(newcuboid,FieldParam);
        cuboid->show();
    }
    break;
    case 2:
    {
        CylinderModel newcylinder;
        QColor color(Qt::red);
        QString Name = "cylinder" + QString::number(CYLINDERLIST.size()+1);
        AddCylinderDialog* cylinder=new AddCylinderDialog(this);
        newcylinder.SetProperty(50,50,50,30,10,0,10,10,0,90,color,Name);
        cylinder->GetModelingMsg(newcylinder,FieldParam);
        cylinder->show();
    }
    break;
    case 3:
    {
        IrregularModel newirregular;
        AddIrregularDialog*irregular=new AddIrregularDialog(this);
        QVector<QVector<QVector<double>>> SpaceDensity;
        QVector<QVector<QVector<double>>> SpaceMagnetization;
        QColor color(Qt::red);
        SpaceDensity.resize(AxisLen[0]);
        for (int i=0;i<SpaceDensity.size();++i){
            SpaceDensity[i].resize(AxisLen[1]);
            for(int j=0;j<SpaceDensity[i].size();++j){
                SpaceDensity[i][j].resize(AxisLen[2]);
            }
        }

        SpaceMagnetization=SpaceDensity;
        QString Name = "irregular" + QString::number(IRREGULARLIST.size()+1);
        newirregular.SetProperty(SpaceDensity,SpaceMagnetization,0,90,color,Name);
        irregular->GetModelingMsg(newirregular,FieldParam);
        irregular->show();
    }

    break;
    case 4:
    {
        PrismoidModel newprismoid;
        AddPrismoidDialog*prismoid=new AddPrismoidDialog(this);
        QVector<double>param={10,20,10,20,10,20,10,20,10,20};
        QColor color(Qt::red);
        int diretion=0;
        QString Name = "prismoid" + QString::number(PRISMOIDLIST.size()+1);
        newprismoid.SetProperty(10.0,10.0,0,90,color,Name,param,diretion);
        prismoid->GetModelingMsg(newprismoid,FieldParam);
        prismoid->show();

    }
    break;
    default:
        break;
    }

}

void Modeling::SetFieldParamBtn(void)
{
    SourceSetting*sourcesetting=new SourceSetting(this);
    sourcesetting->getModelingMsg(FieldParam);
    sourcesetting->show();
}

void Modeling::deletenode()
{
    QModelIndex index =ui->treeView->currentIndex();
    if (index.isValid()){
        switch (index.parent().row()) {
        case 0:
        {
            sphereitem->removeRow(index.row());
            SPHERELIST.removeAt(index.row());
        }
        break;
        case 1:
        {
            cuboiditem->removeRow(index.row());
            CUBOIDLIST.removeAt(index.row());
        }
        break;
        case 2:
        {
            cylinderitem->removeRow(index.row());
            CYLINDERLIST.removeAt(index.row());
        }
        break;
        case 3:
        {
            irregularitem->removeRow(index.row());
            IRREGULARLIST.removeAt(index.row());

        }
        break;
        case 4:
        {
            prismoiditem->removeRow(index.row());
            PRISMOIDLIST.removeAt(index.row());
        }

        default:
            break;
        }
    }
    update();
}

void Modeling::modifynode()
{
    QModelIndex index =ui->treeView->currentIndex();
    if (index.isValid()){
        switch (index.parent().row()) {
        case 0:
        {
            SphereModel newsphere;
            newsphere=SPHERELIST[index.row()];
            AddSphereDialog*sphere=new AddSphereDialog(this);
            sphereitem->removeRow(index.row());
            SPHERELIST.removeAt(index.row());
            sphere->GetModelingMsg(newsphere,FieldParam);
            sphere->show();

        }
        break;
        case 1:
        {
            CuboidModel newcuboid;
            newcuboid=CUBOIDLIST[index.row()];
            AddCubeDialog* cuboid=new AddCubeDialog(this);
            cuboiditem->removeRow(index.row());
            CUBOIDLIST.removeAt(index.row());
            cuboid->GetModelingMsg(newcuboid,FieldParam);
            cuboid->show();
        }
        break;
        case 2:
        {
            CylinderModel newcylinder;
            AddCylinderDialog* cylinder=new AddCylinderDialog(this);
            newcylinder=CYLINDERLIST[index.row()];
            cylinderitem->removeRow(index.row());
            CYLINDERLIST.removeAt(index.row());
            cylinder->GetModelingMsg(newcylinder,FieldParam);
            cylinder->show();
        }
        break;
        case 3:
        {
            IrregularModel newirregular;
            AddIrregularDialog*irregular=new AddIrregularDialog(this);
            newirregular=IRREGULARLIST[index.row()];
            irregularitem->removeRow(index.row());
            IRREGULARLIST.removeAt(index.row());

            irregular->GetModelingMsg(newirregular,FieldParam);
            irregular->show();

        }
        break;
        case 4:
        {
            PrismoidModel newprismoid;
            AddPrismoidDialog*prismoid=new AddPrismoidDialog(this);
            newprismoid=PRISMOIDLIST[index.row()];
            prismoiditem->removeRow(index.row());
            PRISMOIDLIST.removeAt(index.row());
            prismoid->GetModelingMsg(newprismoid,FieldParam);
            prismoid->show();
        }

        default:
            break;
        }
    }
}

void Modeling::OutputBtn()
{
    MyModel.FieldParam=FieldParam;
    MyModel.CYLINDERLIST=CYLINDERLIST;
    MyModel.CUBOIDLIST=CUBOIDLIST;
    MyModel.SPHERELIST=SPHERELIST;
    MyModel.IRREGULARLIST=IRREGULARLIST;
    MyModel.PRISMOIDLIST=PRISMOIDLIST;
    QString filePath = QFileDialog::getSaveFileName(this,tr("Save your Model"), "YourModelName",tr("(*.bin)"));
    MyModel.SaveModelFile(filePath);
    QMessageBox::information(this, tr("Message"), tr("Save successfully!"));
}

void Modeling::OutputDataBtn()
{
    MyModel.FieldParam=FieldParam;
    MyModel.CYLINDERLIST=CYLINDERLIST;
    MyModel.CUBOIDLIST=CUBOIDLIST;
    MyModel.SPHERELIST=SPHERELIST;
    MyModel.IRREGULARLIST=IRREGULARLIST;
    MyModel.PRISMOIDLIST=PRISMOIDLIST;
    QString filePath = QFileDialog::getSaveFileName(this,tr("Save your Model Data"), "YourModelName",tr("(*.txt)"));
    MyModel.SaveDataFile(filePath,AxisLen[0],AxisLen[1],AxisLen[2]);
    QMessageBox::information(this, tr("Message"), tr("Save successfully!"));
}

void Modeling::GotoForwarding()
{
    MyModel.FieldParam=FieldParam;
    MyModel.CYLINDERLIST=CYLINDERLIST;
    MyModel.CUBOIDLIST=CUBOIDLIST;
    MyModel.SPHERELIST=SPHERELIST;
    MyModel.IRREGULARLIST=IRREGULARLIST;
    MyModel.PRISMOIDLIST=PRISMOIDLIST;
    Forwarding*myforward=new Forwarding(this);
    myforward->GetModelingMsg(MyModel);
    myforward->show();
}

void Modeling::GotoProfile()
{   int xlen=AxisLen[0];
    int ylen=AxisLen[1];
    int zlen=AxisLen[2];
    QVector<QVector<QVector<double>>> combinedDensity(xlen, QVector<QVector<double>>(ylen, QVector<double>(zlen, 0.0)));
    QVector<QVector<QVector<double>>> combinedM(xlen, QVector<QVector<double>>(ylen, QVector<double>(zlen, 0.0)));
    for (int i=0;i<SPHERELIST.size();++i) {
        for (int x = 0; x < xlen; ++x) {
            for (int y = 0; y < ylen; ++y) {
                for (int z = 0; z < zlen; ++z) {
                    if (SPHERELIST[i].SpaceDensity[x][y][z] != 0||SPHERELIST[i].SpaceMagnetization[x][y][z] != 0) {
                        combinedDensity[x][y][z] = SPHERELIST[i].SpaceDensity[x][y][z];
                        combinedM[x][y][z] = SPHERELIST[i].SpaceMagnetization[x][y][z];
                    }
                }
            }
        }
    }
    for (int i=0;i<CUBOIDLIST.size();++i) {
        for (int x = 0; x < xlen; ++x) {
            for (int y = 0; y < ylen; ++y) {
                for (int z = 0; z < zlen; ++z) {
                    if (CUBOIDLIST[i].SpaceDensity[x][y][z] != 0||CUBOIDLIST[i].SpaceMagnetization[x][y][z] != 0) {
                        combinedDensity[x][y][z] = CUBOIDLIST[i].SpaceDensity[x][y][z];
                        combinedM[x][y][z] = CUBOIDLIST[i].SpaceMagnetization[x][y][z];
                    }
                }
            }
        }
    }
    for (int i=0;i<CYLINDERLIST.size();++i) {
        for (int x = 0; x < xlen; ++x) {
            for (int y = 0; y < ylen; ++y) {
                for (int z = 0; z < zlen; ++z) {
                    if (CYLINDERLIST[i].SpaceDensity[x][y][z] != 0||CYLINDERLIST[i].SpaceMagnetization[x][y][z] != 0) {
                        combinedDensity[x][y][z] = CYLINDERLIST[i].SpaceDensity[x][y][z];
                        combinedM[x][y][z] =CYLINDERLIST[i].SpaceMagnetization[x][y][z];
                    }
                }
            }
        }
    }
    for (int i=0;i<IRREGULARLIST.size();++i) {
        for (int x = 0; x < xlen; ++x) {
            for (int y = 0; y < ylen; ++y) {
                for (int z = 0; z < zlen; ++z) {
                    if (IRREGULARLIST[i].SpaceDensity[x][y][z] != 0||IRREGULARLIST[i].SpaceMagnetization[x][y][z] != 0) {
                        combinedDensity[x][y][z] = IRREGULARLIST[i].SpaceDensity[x][y][z];
                        combinedM[x][y][z] = IRREGULARLIST[i].SpaceMagnetization[x][y][z];
                    }
                }
            }
        }
    }
    for (int i=0;i<PRISMOIDLIST.size();++i) {
        for (int x = 0; x < xlen; ++x) {
            for (int y = 0; y < ylen; ++y) {
                for (int z = 0; z < zlen; ++z) {
                    if (PRISMOIDLIST[i].SpaceDensity[x][y][z] != 0||PRISMOIDLIST[i].SpaceMagnetization[x][y][z] != 0) {
                        combinedDensity[x][y][z] = PRISMOIDLIST[i].SpaceDensity[x][y][z];
                        combinedM[x][y][z] = PRISMOIDLIST[i].SpaceMagnetization[x][y][z];
                    }
                }
            }
        }
    }
    Profile*myprofile=new Profile();
    myprofile->GetModelMsg(combinedDensity,combinedM,FieldParam);
    myprofile->show();
}




#ifndef MODELING_H
#define MODELING_H


#include <QWidget>
#include<qdebug.h>
//#include "mymodel.h"
#include "forwarding.h"
#include <QStandardItemModel>
#include <QMenu>
namespace Ui {
class Modeling;
}

class Modeling : public QWidget
{
    Q_OBJECT

public:
    explicit Modeling(QWidget *parent = nullptr);

    ~Modeling();
    void GetInitialMsg(Model);
    void getAddSphereDialogMsg(SphereModel);
    void getAddCubeDialogMsg(CuboidModel);
    void getAddCylinderDialogMsg(CylinderModel);
    void getAddPrismoidDialogMsg(PrismoidModel);
    void getAddIrregularDiaglogMsg(IrregularModel);
    void getFieldparamDiaglogMsg(QVector<float>);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent*) override;

private:
    Ui::Modeling *ui;
    QSize originalSize;
    QHash<QWidget*, QRect> m_initialGeometries;
    void storeInitialGeometries(QWidget *widget);
    void PaintAxis(QPainter &painter);
    void PaintModel(QPainter &painter);
    void PaintUnit(QPainter &painter,int x,int y,int z);
    void PaintProfile(QPainter &painter);
    QPointF cood3Dto2D(double x,double y,double z);
    QPointF coodZprofile(double x,double y);
    QPointF coodXprofile(double y,double z);
    QPointF coodYprofile(double x,double z);
    QVector<int> AxisLen={0,0,0};//场区三轴的刻度数
    QVector<QPointF>InitAxis3DPoint={QPointF(567,115),QPointF(567,505),QPointF(567,765),QPointF(199.31,245),QPointF(199.31,635),QPointF(934.69,245),QPointF(934.69,635)};//3D绘图的初始点
    QRectF InitAxis3D=QRectF(170,90,780,700); //初始绘制3D模型的背景
    QRectF InitAxisX=QRectF(980,90,200,200); //初始绘制X背景
    QRectF InitAxisY=QRectF(980,340,200,200); //初始绘制Y背景
    QRectF InitAxisZ=QRectF(980,590,200,200); //初始绘制Z背景
    QVector<QPointF>Axis3DPoint={QPointF(567,115),QPointF(567,505),QPointF(567,765),QPointF(199.31,245),QPointF(199.31,635),QPointF(934.69,245),QPointF(934.69,635)};
    QRectF Axis3D=QRectF(170,90,780,700);
    QRectF AxisX=QRectF(980,90,200,200); //初始绘制X背景
    QRectF AxisY=QRectF(980,340,200,200); //初始绘制Y背景
    QRectF AxisZ=QRectF(980,590,200,200); //初始绘制Z背景
    QVector<double> InitAxis3Dlen={367.69,130,390};//三轴真实物理长度
    QVector<double> Axis3Dlen={367.69,130,390};

    //整个模型的数据集合
    QVector<float> FieldParam;
    QVector<SphereModel>SPHERELIST;
    QVector<CuboidModel>CUBOIDLIST;
    QVector<CylinderModel>CYLINDERLIST;
    QVector<IrregularModel>IRREGULARLIST;
    QVector<PrismoidModel>PRISMOIDLIST;
    Model MyModel;
    // 最后都存入MyModel中用于文件读写

    QStandardItemModel *model;
    QStandardItem *sphereitem;
    QStandardItem *cuboiditem;
    QStandardItem *cylinderitem;
    QStandardItem *irregularitem;
    QStandardItem *prismoiditem;
    QMenu *menu;
    QAction *deleteaction;
    QAction *modifyaction;

private slots:
    void AddModelBtn(int index);
    void SetFieldParamBtn(void);
    void deletenode();
    void modifynode();
    void OutputBtn(void);
    void OutputDataBtn(void);
    void GotoForwarding();
    void GotoProfile();
};

#endif // MODELING_H

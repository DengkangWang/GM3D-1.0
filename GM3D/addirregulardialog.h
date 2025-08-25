#ifndef ADDIRREGULARDIALOG_H
#define ADDIRREGULARDIALOG_H
#include "ui_addirregulardialog.h"
#include <QDialog>
#include<QPainter>
#include "modeling.h"
#include<QColorDialog>
namespace Ui {
class AddIrregularDialog;
}

class AddIrregularDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddIrregularDialog(QWidget *parent = nullptr);
    ~AddIrregularDialog();
    void GetModelingMsg(IrregularModel newirregular,QVector<float> fieldparam);
    void mousePressEvent(QMouseEvent*e);
    void mouseMoveEvent(QMouseEvent*e);
    void mouseReleaseEvent(QMouseEvent*e);
    void paintEvent(QPaintEvent* );
    void paintAxis(QPainter &painter);
    void getMyAxisCoordinate(QMouseEvent*e);
    void paintSelectedUnit(QPainter &painter);
    void paintRect(QPainter &painter);
    void paintCircle(QPainter &painter);
    void paintCustom(QPainter &painter);
    void getCircleModeAns();
    void getRectModeAns();
    void getCustomModeAns();
    void resizeEvent(QResizeEvent *event);

private slots:
    void backtomodeling(bool);
    void BtnMapper(int);
    void onComboBoxIndexChanged(int index);
    void onSpinBoxValueChanged(int newValue);
   // void FinishIrreModeling(bool);
    void ChooseModelColor(bool);
    void BuildBtnChecked(bool);
    void EraseBtnChecked(bool);

private:
    Ui::AddIrregularDialog *ui;
    //画板范围
    double intipixhigh=760;
    double intipixwidth=1000;
    double intixstart=45;
    double intiystart=5;
    double pixhigh=760;
    double pixwidth=1000;
    double xstart=45;
    double ystart=5;
    double xgridInterval;
    double ygridInterval;
    int MyAxisX;
    int MyAxisY;
    int xlen;
    int ylen;
    int zlen;
    int drawmode=3;
    int drawprofile=0; //绘制的剖面 0 ：xy平面；1：xz平面 2：yz平面
    int xrange;
    int yrange;

    QVector<QPoint> CustomLineArray;
    QVector<QRectF> SelectedUnitCoordinate;
    QVector<QRectF> PreSelectedUnitCoordinate;
    int Copy;
    QVector<QRectF> CopySelectedUnitCoordinate;

    QVector<QVector<QVector<double>>> SpaceDensity;
    QVector<QVector<QVector<double>>> SpaceMagnetization;
    int clickpoint[2];
    int circlemode[2][2];
    int rectmode[2][2];
    int xmesh;
    int ymesh;
    bool State=true;
    bool HadSavedLayer=false;
    int BuiltLayer=0;
    QColor color;
    QSize originalSize;
    QHash<QWidget*, QRect> m_initialGeometries;
    void storeInitialGeometries(QWidget *widget);
    QVector<float> SOURCE={0,100,0,100,0,100,1,1,1,1};
    bool validateInputs(double& density, double& magnetization, QString& errorMessage);
};

#endif // ADDIRREGULARDIALOG_H

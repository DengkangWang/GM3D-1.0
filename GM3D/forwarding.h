#ifndef FORWARDING_H
#define FORWARDING_H

#include <QMainWindow>
#include "mymodel.h"
#include <Eigen/Dense>
#include "QStandardItem"
#include "bce.h"
#include "qcustomplot.h"
namespace Ui {
class Forwarding;
}

class Forwarding : public QMainWindow
{
    Q_OBJECT

public:
    explicit Forwarding(QWidget *parent = nullptr);
    ~Forwarding();
    void GetModelingMsg(Model mymodel);
    void GetForwardItemList(QVector<int> forwarditem,double geodec,double geoinc,double obheight,double gaussmean,double gaussstd,double addproportion);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent*) override;

private:
    Ui::Forwarding *ui;
    QSize originalSize;
    QHash<QWidget*, QRect> m_initialGeometries;
    void storeInitialGeometries(QWidget *widget);
    void SaveFWDANStoFile(const QString& folderPath, const QString& fileName, const Eigen::MatrixXd& matrix);
    void PlotAns(const Eigen::MatrixXd& matrix,const QString xLabel,const QString yLabel, const QString colorbarLabel);
    Model MyModel;
    QVector<float> FieldParam;
    QStandardItemModel *model;
    QStandardItem *sphereitem;
    QStandardItem *cuboiditem;
    QStandardItem *cylinderitem;
    QStandardItem *irregularitem;
    QStandardItem *prismoiditem;
    Eigen::MatrixXd xm;
    Eigen::MatrixXd ym;
    Eigen::MatrixXd xm2;
    Eigen::MatrixXd ym2;
    QVector<double>depth;
    int xlen;
    int ylen;
    int zlen;
    int bcelength;
    int verlength;
    QCustomPlot* mCustomPlot;
    bool FirstDraw=true;
    QVector<int> FORWARDITEM;
    double GeoDec=53.0;
    double GeoInc=-7.0;
    double ObHeight=0.0;
    double BodyInc=90.0;
    double BodyDec=0;
    double  GaussMean,GaussStd,AddProportion;
    void addGaussianNoise(Eigen::MatrixXd& matrix, double mean, double stddev,double proportion);

    //正演结果：重力
    Eigen::MatrixXd G;
    Eigen::MatrixXd Gxx;
    Eigen::MatrixXd Gxy;
    Eigen::MatrixXd Gxz;
    Eigen::MatrixXd Gyy;
    Eigen::MatrixXd Gyz;
    Eigen::MatrixXd Gzz;
    Eigen::MatrixXd oG;
    Eigen::MatrixXd oGxx;
    Eigen::MatrixXd oGxy;
    Eigen::MatrixXd oGxz;
    Eigen::MatrixXd oGyy;
    Eigen::MatrixXd oGyz;
    Eigen::MatrixXd oGzz;

    //正演结果：磁
    Eigen::MatrixXd T;
    Eigen::MatrixXd Tx;
    Eigen::MatrixXd Ty;
    Eigen::MatrixXd Tz;
    Eigen::MatrixXd Hax;
    Eigen::MatrixXd Hay;
    Eigen::MatrixXd Za;
    Eigen::MatrixXd Bxx;
    Eigen::MatrixXd Bxy;
    Eigen::MatrixXd Bxz;
    Eigen::MatrixXd Byy;
    Eigen::MatrixXd Byz;
    Eigen::MatrixXd Bzz;
    Eigen::MatrixXd oT;
    Eigen::MatrixXd oTx;
    Eigen::MatrixXd oTy;
    Eigen::MatrixXd oTz;
    Eigen::MatrixXd oHax;
    Eigen::MatrixXd oHay;
    Eigen::MatrixXd oZa;
    Eigen::MatrixXd oBxx;
    Eigen::MatrixXd oBxy;
    Eigen::MatrixXd oBxz;
    Eigen::MatrixXd oByy;
    Eigen::MatrixXd oByz;
    Eigen::MatrixXd oBzz;

    QRectF InitPaintAxis=QRectF(10,10,700,580);
    QRectF PaintAxis=QRectF(10,10,700,580);


private slots:

    void GoToForwardItemDialog(bool);
    void SaveData(bool);
    void ChangedDraw(int index);

};

#endif // FORWARDING_H

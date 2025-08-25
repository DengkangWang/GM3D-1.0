#include <QVector>
#include <Eigen/Dense>
#include <QDebug>
struct GraFWD
{
    //单层正演
    Eigen::MatrixXd Xm;
    Eigen::MatrixXd Ym;
    int Xlen,Ylen;
    QVector<double>Depth;
    double ObserveHight;
    QVector<QVector<QVector<double>>> Density; //密度矩阵
    // 构造函数:初始化正演网格\观测高度
    GraFWD(Eigen::MatrixXd xm,Eigen::MatrixXd ym,int xlen,int ylen,QVector<double>depth,double observehight,QVector<QVector<QVector<double>>> density) {
        Xm=xm;
        Ym=ym;
        Xlen=xlen;
        Ylen=ylen;
        Depth=depth;
        ObserveHight=observehight;
        Density=density;
    }

    //单层核函数矩阵
    Eigen::MatrixXd gkernel;
    Eigen::MatrixXd gxxkernel;
    Eigen::MatrixXd gxykernel;
    Eigen::MatrixXd gxzkernel;
    Eigen::MatrixXd gyykernel;
    Eigen::MatrixXd gyzkernel;
    Eigen::MatrixXd gzzkernel;
    //正演结果
    Eigen::MatrixXd G;
    Eigen::MatrixXd Gxx;
    Eigen::MatrixXd Gxy;
    Eigen::MatrixXd Gxz;
    Eigen::MatrixXd Gyy;
    Eigen::MatrixXd Gyz;
    Eigen::MatrixXd Gzz;


    //计算单层核函数
    void CalKernal(QVector<int> forwarditem,double H1,double H2);

    //最终结果
    void getFWDANS(QVector<int> forwarditem);


};

struct MagFWD
{
    Eigen::MatrixXd Xm;
    Eigen::MatrixXd Ym;
    Eigen::MatrixXd Xm2;
    Eigen::MatrixXd Ym2;
    QVector<double>Depth;
    double ObserveHight;
    //背景场的磁场方向
    double MagInc;
    double MagDec;

    //磁异常的磁化方向
    double BodyInc;
    double BodyDec;

    int Xlen,Ylen;
    //
    QVector<QVector<QVector<double>>> Magnetization; //密度矩阵
    MagFWD(Eigen::MatrixXd xm,Eigen::MatrixXd ym,Eigen::MatrixXd xm2,Eigen::MatrixXd ym2,int xlen,int ylen,QVector<double>depth,double observehight,double maginc,double magdec,double bodyinc,double bodydec,QVector<QVector<QVector<double>>> magnetization) {
        Xm=xm;
        Ym=ym;
        Xm2=xm2;
        Ym2=ym2;
        Xlen=xlen;
        Ylen=ylen;
        Depth=depth;
        ObserveHight=observehight;
        MagInc=maginc;
        MagDec=magdec;
        BodyInc=bodyinc;
        BodyDec=bodydec;
        Magnetization=magnetization;
    }

    //单层核函数矩阵
    Eigen::MatrixXd haxkernel;
    Eigen::MatrixXd haykernel;
    Eigen::MatrixXd zakernel;
    Eigen::MatrixXd bxxkernel;
    Eigen::MatrixXd bxykernel;
    Eigen::MatrixXd bxzkernel;
    Eigen::MatrixXd byykernel;
    Eigen::MatrixXd byzkernel;
    Eigen::MatrixXd bzzkernel;

    //正演结果
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

    void CalKernel_Ver(QVector<int> forwarditem,double H1,double H2);
    void CalKernel_nonVer(QVector<int> forwarditem,double H1,double H2,double k1,double k2,double k3);
    void GetFWAns(QVector<int> forwarditem);
};

Eigen::MatrixXd Myfft2(QVector<double> den, QVector<double> ker,int Rows,int Cols);
Eigen::MatrixXd Myfft2NonVer(QVector<double> den, QVector<double> ker,int Rows,int Cols,int xlen,int ylen);
Eigen::MatrixXd Myatan2(const Eigen::MatrixXd& Matrix1,const Eigen::MatrixXd& Matrix2);
Eigen::MatrixXd BuildGraBCEMatrix(const Eigen::MatrixXd& Matrix,int type);
Eigen::MatrixXd BuildVerMagBCEMatrix(const Eigen::MatrixXd& Matrix,int type);
Eigen::MatrixXd BuildNonVerMagBCEMatrix(const Eigen::MatrixXd& Matrix);
QVector<QVector<double>> convertEigenToQVector(const Eigen::MatrixXd& matrix);
QVector<double> eigenMatrixToQVector(const Eigen::MatrixXd& matrix);
QVector<double> processSlice(int zz, const QVector<QVector<QVector<double>>>& d, int xlen, int ylen,int verlength,bool& IsAllZero);
QVector<double> processSliceNonVer(int zz, const QVector<QVector<QVector<double>>>& d, int xlen, int ylen,int bcexlen, int bceylen,bool& IsAllZero);
inline QDebug operator<<(QDebug dbg, const Eigen::MatrixXd& mat) {
    dbg.nospace() << "Matrix(" << mat.rows() << "x" << mat.cols() << "):\n";
    for (int i = 0; i < mat.rows(); ++i) {
        for (int j = 0; j < mat.cols(); ++j) {
            dbg.nospace() << qSetFieldWidth(12) << mat(i, j);
        }
        dbg.nospace() << "\n";
    }
    return dbg.space();
}

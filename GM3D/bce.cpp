#include "bce.h"
#include<QDebug>
#include<iostream>
#include "fftw3.h"
#include <fstream>
void GraFWD::CalKernal(QVector<int> forwarditem ,double H1 ,double H2)
{
   //used to calculate gravity forward kernel matrix of each layer.
   //H1 and H2 are top of layer and bottom of layer respectivrly.
   QVector<Eigen::MatrixXd> X(2);
   QVector<Eigen::MatrixXd> Y(2);
   QVector<Eigen::MatrixXd> H(2);
   Eigen::MatrixXd h1(Ym.rows(),Xm.cols());
   Eigen::MatrixXd h2(Ym.rows(),Xm.cols());
   Y[1]=Ym.block(0,1,Ym.rows(),Ym.cols()-1);
   Y[0]=Ym.block(0,0,Ym.rows(),Ym.cols()-1);
   X[1]=Xm.block(1,0,Xm.rows()-1,Xm.cols());
   X[0]=Xm.block(0,0,Xm.rows()-1,Xm.cols());
   H[0]=h1.setConstant(ObserveHight+H1);
   H[1]=h2.setConstant(ObserveHight+H2);


    Eigen::MatrixXd Uijk(Ym.rows(),Xm.cols());
    Eigen::MatrixXd Rijk2(Ym.rows(),Xm.cols());
    Eigen::MatrixXd Rijk(Ym.rows(),Xm.cols());
    Eigen::MatrixXd arg_logYplusR(Ym.rows(),Xm.cols());
    Eigen::MatrixXd arg_logXplusR(Ym.rows(),Xm.cols());
    Eigen::MatrixXd arg_logZplusR(Ym.rows(),Xm.cols());
    Eigen::MatrixXd arg_atanZRdivisionXY(Ym.rows(),Xm.cols());
    Eigen::MatrixXd arg_atanXRdivisionYZ(Ym.rows(),Xm.cols());
    Eigen::MatrixXd arg_atanXZdivisionYR(Ym.rows(),Xm.cols());
    gkernel.setZero(Ym.rows(),Xm.cols());
    gxxkernel.setZero(Ym.rows(),Xm.cols());
    gxykernel.setZero(Ym.rows(),Xm.cols());
    gxzkernel.setZero(Ym.rows(),Xm.cols());
    gyykernel.setZero(Ym.rows(),Xm.cols());
    gyzkernel.setZero(Ym.rows(),Xm.cols());
    gzzkernel.setZero(Ym.rows(),Xm.cols());
//计算核矩阵

 for (int i=0;i<2;++i){
        for (int j=0;j<2;++j){
            for (int k=0;k<2;++k){
                //公共因子
                Uijk.setConstant(-pow(-1,i)*pow(-1,j)*pow(-1,k));
                Rijk2=X[i].array()*X[i].array()+Y[j].array()*Y[j].array()+H[k].array()*H[k].array();
                Rijk=Rijk2.array().sqrt();

                arg_logXplusR=(X[i]+Rijk).array().log();
                arg_logYplusR=(Y[j]+Rijk).array().log();
                arg_atanZRdivisionXY=Myatan2((H[k].array()*Rijk.array()),(X[i].array()*Y[j].array()));

                if (forwarditem[0]){

                    gkernel=gkernel.array()-Uijk.array()*(X[i].array()*arg_logYplusR.array()+Y[j].array()*arg_logXplusR.array()+H[k].array()*arg_atanZRdivisionXY.array());

                }
                
                if (forwarditem[1]){
                    arg_atanXRdivisionYZ=Myatan2((X[i].array()*Rijk.array()).array(),(Y[j].array()*H[k].array()).array());
                    gxxkernel=gxxkernel.array()-Uijk.array()*arg_atanXRdivisionYZ.array();
                }
                
                if (forwarditem[2]){
                    arg_logZplusR=(H[k]+Rijk).array().log();
                    gxykernel=gxykernel.array()+Uijk.array()*arg_logZplusR.array();
                }
                
                if (forwarditem[3]){
                     gxzkernel=gxzkernel.array()-Uijk.array()*arg_logYplusR.array();
                }
                
                if (forwarditem[4]){
                    arg_atanXZdivisionYR=Myatan2((X[i].array()*H[k].array()),(Y[j].array()*Rijk.array()));//(/).array().atan();
                    gyykernel=gyykernel.array()+Uijk.array()*arg_atanXZdivisionYR.array();
                }
                
                if (forwarditem[5]){
                    gyzkernel=gyzkernel.array()-Uijk.array()*arg_logXplusR.array();
                }
                
                if (forwarditem[6]){
                    gzzkernel=gzzkernel.array()-Uijk.array()*arg_atanZRdivisionXY.array();
                }
            }
        }
    }

}



//计算傅里叶变换
Eigen::MatrixXd Myfft2(QVector<double> den, QVector<double> ker, int Rows, int Cols)
{

    fftw_complex* denin=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Rows*Cols);
    fftw_complex* denout=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Rows*Cols);
    fftw_complex* kerin=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Rows*Cols);
    fftw_complex* kerout=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Rows*Cols);
    fftw_complex* ansin=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Rows*Cols);
    fftw_complex* ansout=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Rows*Cols);
    for (int i=0;i<Rows;++i){
        for (int j=0;j<Cols;++j){
            denin[i*Cols+j][0]=den[i*Cols+j];   //实部
            denin[i*Cols+j][1]=0;//虚部
            kerin[i*Cols+j][0]=ker[i*Cols+j];
            kerin[i*Cols+j][1]=0;
        }
    }

    fftw_plan denplan = fftw_plan_dft_2d(Rows, Cols, denin, denout, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(denplan);

    fftw_plan kerplan = fftw_plan_dft_2d(Rows, Cols, kerin, kerout, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(kerplan);

    for (int i = 0; i < Rows; i++){
        for (int j = 0; j < Cols; j++) {
            ansin[i * Cols + j][0] = kerout[i*Cols+j][0]*denout[i*Cols+j][0]-kerout[i*Cols+j][1]*denout[i*Cols+j][1]; // 实部
            ansin[i * Cols + j][1] = kerout[i*Cols+j][1]*denout[i*Cols+j][0]+kerout[i*Cols+j][0]*denout[i*Cols+j][1]; // 虚部
        }
    }

    fftw_plan ansplan = fftw_plan_dft_2d(Rows, Cols, ansin, ansout, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(ansplan);
    Eigen::MatrixXd ans(Rows/2,Cols/2);

    for(int i=0;i<Rows/2;++i){
      for(int j=0;j<Cols/2;++j){
         ans(i, j)=ansout[i*Cols+j][0]/(Rows*Cols);
   }

   }

    return ans;
}

void MagFWD::CalKernel_Ver(QVector<int> forwarditem, double H1, double H2)
{
    //used to calculate vertical magnetization magnetic kernel matrix of each layer.
    //H1 and H2 are top of layer and bottom of layer respectivrly.
    QVector<Eigen::MatrixXd> X(2);
    QVector<Eigen::MatrixXd> Y(2);
    QVector<Eigen::MatrixXd> H(2);
    Eigen::MatrixXd h1(Ym.rows(),Xm.cols());
    Eigen::MatrixXd h2(Ym.rows(),Xm.cols());
    Y[0]=Ym.block(0,1,Ym.rows(),Ym.cols()-1);
    Y[1]=Ym.block(0,0,Ym.rows(),Ym.cols()-1);
    X[0]=Xm.block(1,0,Xm.rows()-1,Xm.cols());
    X[1]=Xm.block(0,0,Xm.rows()-1,Xm.cols());

    H[0]=h1.setConstant(ObserveHight+H1);
    H[1]=h2.setConstant(ObserveHight+H2);

    Eigen::MatrixXd Uijk(Ym.rows(),Xm.cols());
    Eigen::MatrixXd Rijk2(Ym.rows(),Xm.cols());
    Eigen::MatrixXd Rijk(Ym.rows(),Xm.cols());

    haxkernel.setZero(Ym.rows(),Xm.cols());
    haykernel.setZero(Ym.rows(),Xm.cols());
    zakernel.setZero(Ym.rows(),Xm.cols());
    bxxkernel.setZero(Ym.rows(),Xm.cols());
    bxykernel.setZero(Ym.rows(),Xm.cols());
    bxzkernel.setZero(Ym.rows(),Xm.cols());
    byykernel.setZero(Ym.rows(),Xm.cols());
    byzkernel.setZero(Ym.rows(),Xm.cols());
    bzzkernel.setZero(Ym.rows(),Xm.cols());
    for (int i=0;i<2;++i){
     for (int j=0;j<2;++j){
            for (int k=0;k<2;++k){
                //公共因子
                Uijk.setConstant(-pow(-1,i)*pow(-1,j)*pow(-1,k));
                Rijk2=X[i].array()*X[i].array()+Y[j].array()*Y[j].array()+H[k].array()*H[k].array();
                Rijk=Rijk2.array().sqrt();
                if (forwarditem[8]){
                    haxkernel=haxkernel.array()-Uijk.array()*((Rijk+Y[j]).array().log());
                }

                if (forwarditem[9]){
                    haykernel=haykernel.array()-Uijk.array()*((Rijk+X[i]).array().log()).array();
                }

                if (forwarditem[10]){
                    zakernel=zakernel.array()+Uijk.array()*Myatan2(X[i].array()*Y[j].array(),H[k].array()*Rijk.array()).array();
                }

                if (forwarditem[11]){
                    bxxkernel=bxxkernel.array()-Uijk.array()*(X[i].array()/(Rijk.array()*(Rijk+Y[j]).array()));
                }

                if (forwarditem[12]){
                    bxykernel=bxykernel.array()-Uijk.array()/Rijk.array();
                }

                if (forwarditem[13]){
                    bxzkernel=bxzkernel.array()-Uijk.array()*(H[k].array()/(Rijk.array()*(Rijk+Y[j]).array()));
                }

                if (forwarditem[14]){
                    byykernel=byykernel.array()-Uijk.array()*(Y[j].array()/(Rijk.array()*(Rijk+X[i]).array()));
                }

                if (forwarditem[15]){
                    byzkernel=byzkernel.array()-Uijk.array()*(H[j].array()/(Rijk.array()*(Rijk+X[i]).array()));
                }

                if (forwarditem[16]){
                    bzzkernel=bzzkernel.array()-Uijk.array()*((X[i].array()*Y[j].array()*(Rijk.array()*Rijk.array()+H[k].array()*H[k].array()))
                              /((Y[j].array()*Y[j].array()+H[k].array()*H[k].array()).array()*(X[i].array()*X[i].array()+H[k].array()*H[k].array()).array()*Rijk.array()));
                }

            }
        }
    }

}

void GraFWD::getFWDANS(QVector<int> forwarditem)
{
    //重力正演G
    //重力梯度正演 Gxx,Gxy,Gxz,Gyy,Gyz,Gzz

    G.setZero(Ym.rows(),Xm.cols());
    Gxx.setZero(Ym.rows(),Xm.cols());
    Gxy.setZero(Ym.rows(),Xm.cols());
    Gxz.setZero(Ym.rows(),Xm.cols());
    Gyy.setZero(Ym.rows(),Xm.cols());
    Gyz.setZero(Ym.rows(),Xm.cols());
    Gzz.setZero(Ym.rows(),Xm.cols());
    Eigen::MatrixXd bceg;
    Eigen::MatrixXd bcegxx;
    Eigen::MatrixXd bcegxy;
    Eigen::MatrixXd bcegxz;
    Eigen::MatrixXd bcegyy;
    Eigen::MatrixXd bcegzz;
    Eigen::MatrixXd bcegyz;
    QVector<double> LayerDensity;
    QVector<double> LayerKernel;

    for(int zz=0;zz<Depth.size()-1;zz++){
        bool IsAllZero=true;

        LayerDensity = processSlice(zz, Density,Xlen,Ylen,Ym.rows(),IsAllZero);
        if (IsAllZero) {
            continue;
        }


        CalKernal(forwarditem,Depth[zz],Depth[zz+1]);
        if (forwarditem[0]){

            bceg=BuildGraBCEMatrix(gkernel,0);
            LayerKernel = eigenMatrixToQVector(bceg);
            G=G+Myfft2(LayerDensity,LayerKernel,bceg.rows(),bceg.cols());

        }

        if (forwarditem[1]){
            bcegxx=BuildGraBCEMatrix(gxxkernel,1);
            LayerKernel = eigenMatrixToQVector(bcegxx);
            Gxx=Gxx+Myfft2(LayerDensity,LayerKernel,bcegxx.rows(),bcegxx.cols());
        }

        if (forwarditem[2]){
            bcegxy=BuildGraBCEMatrix(gxykernel,2);
            LayerKernel = eigenMatrixToQVector(bcegxy);
            Gxy=Gxy+Myfft2(LayerDensity,LayerKernel,bcegxy.rows(),bcegxy.cols());
        }

        if (forwarditem[3]){
            bcegxz=BuildGraBCEMatrix(gxzkernel,3);
            LayerKernel = eigenMatrixToQVector(bcegxz);
            Gxz=Gxz+Myfft2(LayerDensity,LayerKernel,bcegxz.rows(),bcegxz.cols());
        }

        if (forwarditem[4]){
            bcegyy=BuildGraBCEMatrix(gyykernel,4);
            LayerKernel = eigenMatrixToQVector(bcegyy);
            Gyy=Gyy+Myfft2(LayerDensity,LayerKernel,bcegyy.rows(),bcegyy.cols());
        }

        if (forwarditem[5]){
            bcegyz=BuildGraBCEMatrix(gyzkernel,5);
            LayerKernel = eigenMatrixToQVector(bcegyz);
            Gyz=Gyz+Myfft2(LayerDensity,LayerKernel,bcegyz.rows(),bcegyz.cols());
        }

        if (forwarditem[6]){
            bcegzz=BuildGraBCEMatrix(gzzkernel,6);
            LayerKernel = eigenMatrixToQVector(bcegzz);
            Gzz=Gzz+Myfft2(LayerDensity,LayerKernel,bcegzz.rows(),bcegzz.cols());
        }

    }
    double parm1=6.67e-3;
    double parm2=66.7;
    G=G*parm1;
    Gxx=-Gxx*parm2;
    Gxy=-Gxy*parm2;
    Gxz=-Gxz*parm2;
    Gyy=-Gyy*parm2;
    Gyz=-Gyz*parm2;
    Gzz=-Gzz*parm2;
}

void MagFWD::CalKernel_nonVer(QVector<int> forwarditem, double H1, double H2, double k1, double k2, double k3)
{
    QVector<Eigen::MatrixXd> X(2);
    QVector<Eigen::MatrixXd> Y(2);
    QVector<Eigen::MatrixXd> H(2);
    Eigen::MatrixXd h1(Ym2.rows(),Xm2.cols());
    Eigen::MatrixXd h2(Ym2.rows(),Xm2.cols());
    Y[1]=Ym2.block(0,1,Ym2.rows(),Ym2.cols()-1);
    Y[0]=Ym2.block(0,0,Ym2.rows(),Ym2.cols()-1);
    X[1]=Xm2.block(1,0,Xm2.rows()-1,Xm2.cols());
    X[0]=Xm2.block(0,0,Xm2.rows()-1,Xm2.cols());
    H[0]=h1.setConstant(ObserveHight+H1);
    H[1]=h2.setConstant(ObserveHight+H2);

    Eigen::MatrixXd Uijk(Ym2.rows(),Xm2.cols());
    Eigen::MatrixXd Rijk2(Ym2.rows(),Xm2.cols());
    Eigen::MatrixXd Rijk(Ym2.rows(),Xm2.cols());

    Eigen::MatrixXd LogRPlusZ(Ym2.rows(),Xm2.cols());
    Eigen::MatrixXd LogRPlusY(Ym2.rows(),Xm2.cols());
    Eigen::MatrixXd LogRPlusX(Ym2.rows(),Xm2.cols());
    Eigen::MatrixXd XDPMRPlusZ(Ym2.rows(),Xm2.cols());
    Eigen::MatrixXd XDPMRPlusY(Ym2.rows(),Xm2.cols());
    Eigen::MatrixXd YDRMRPlusX(Ym2.rows(),Xm2.cols());
    Eigen::MatrixXd YDRMRPlusZ(Ym2.rows(),Xm2.cols());
    Eigen::MatrixXd ZDPMRPlusY(Ym2.rows(),Xm2.cols());
    Eigen::MatrixXd ZDPMRPlusX(Ym2.rows(),Xm2.cols());
    haxkernel.setZero(Ym2.rows(),Xm2.cols());
    haykernel.setZero(Ym2.rows(),Xm2.cols());
    zakernel.setZero(Ym2.rows(),Xm2.cols());
    bxxkernel.setZero(Ym2.rows(),Xm2.cols());
    bxykernel.setZero(Ym2.rows(),Xm2.cols());
    bxzkernel.setZero(Ym2.rows(),Xm2.cols());
    byykernel.setZero(Ym2.rows(),Xm2.cols());
    byzkernel.setZero(Ym2.rows(),Xm2.cols());
    bzzkernel.setZero(Ym2.rows(),Xm2.cols());
    for (int i=0;i<2;i++){
        for (int j=0;j<2;j++){
            for (int k=0;k<2;k++){
                //公共因子
                Uijk.setConstant(-pow(-1,i)*pow(-1,j)*pow(-1,k));
                Rijk2=X[i].array()*X[i].array()+Y[j].array()*Y[j].array()+H[k].array()*H[k].array();
                Rijk=Rijk2.array().sqrt();

                if (forwarditem[8]||forwarditem[9]){
                    LogRPlusZ=(Rijk+H[k]).array().log();
                }

                if (forwarditem[8]||forwarditem[10]){

                    LogRPlusY=(Rijk+Y[j]).array().log();
                }

                if (forwarditem[9]||forwarditem[10]){

                    LogRPlusX=(Rijk+X[i]).array().log();
                }

                if (forwarditem[11]||forwarditem[12]){
                    //bxx bxy
                    XDPMRPlusZ=X[i].array()/(Rijk.array()*(Rijk+H[k]).array());
                }

                if (forwarditem[11]||forwarditem[13]){
                    //bxx bxz
                    XDPMRPlusY=X[i].array()/(Rijk.array()*(Rijk+Y[j]).array());
                }
                if (forwarditem[14]||forwarditem[15]){
                    //byy byz
                    YDRMRPlusX=Y[j].array()/(Rijk.array()*(Rijk+X[i]).array());
                }

                if (forwarditem[14]||forwarditem[12]){
                    //byy byz
                    YDRMRPlusZ=Y[j].array()/(Rijk.array()*(Rijk+H[k]).array());
                }

                if (forwarditem[13]||forwarditem[16]){
                    //bzz bxz
                    ZDPMRPlusY=H[k].array()/(Rijk.array()*(Rijk+Y[j]).array());
                }

                if (forwarditem[15]||forwarditem[16]){
                    //bzz byz
                    ZDPMRPlusX=H[k].array()/(Rijk.array()*(Rijk+X[i]).array());
                }

                if (forwarditem[8]){
                    haxkernel=haxkernel.array()-Uijk.array()*(k1*Myatan2(Y[j].array()*H[k].array(),X[i].array()*Rijk.array()).array()-k2*LogRPlusZ.array()-k3*LogRPlusY.array()).array();
                }

                if (forwarditem[9]){
                    haykernel=haykernel.array()+Uijk.array()*(-k1*LogRPlusZ.array()+k2*Myatan2(X[i].array()*H[k].array(),Y[j].array()*Rijk.array()).array()-k3*LogRPlusX.array()).array();
                }

                if (forwarditem[10]){
                     zakernel=zakernel.array()+Uijk.array()*(-k1*LogRPlusY.array()-k2*LogRPlusX.array()+k3*Myatan2(X[i].array()*Y[j].array(),H[k].array()*Rijk.array()).array()).array();
                }

                if (forwarditem[11]){
                     Eigen::MatrixXd arg(Ym2.rows(),Xm2.cols());
                     arg=(Y[j].array()*H[k].array()*(Rijk2.array()+X[i].array()*X[i].array()).array()).array()/
                        ((X[i].array()*X[i].array()+H[k].array()*H[k].array()).array()*(X[i].array()*X[i].array()+Y[j].array()*Y[j].array()).array()*Rijk.array());
                     bxxkernel=bxxkernel.array()+Uijk.array()*(-k1*arg.array()-k2*XDPMRPlusZ.array()-k3*XDPMRPlusY.array()).array();
                }

                if (forwarditem[12]){
                     bxykernel=bxykernel.array()+Uijk.array()*(-k1*XDPMRPlusZ.array()-k2*YDRMRPlusZ.array()-k3/Rijk.array()).array();
                }

                if (forwarditem[13]){
                    bxzkernel=bxzkernel.array()+Uijk.array()*(-k1*XDPMRPlusY.array()-k2/Rijk.array()-k3*ZDPMRPlusY.array()).array();
                }

                if (forwarditem[14]){
                     Eigen::MatrixXd arg(Ym2.rows(),Xm2.cols());
                     arg=(X[i].array()*H[k].array()*(Rijk2.array()+Y[j].array()*Y[j].array()).array())/
                           ((Y[j].array()*Y[j].array()+H[k].array()*H[k].array()).array()*(X[i].array()*X[i].array()+Y[j].array()*Y[j].array()).array()*Rijk.array());
                     byykernel=byykernel.array()+Uijk.array()*(-k1*YDRMRPlusZ.array()-k2*arg.array()-k3*YDRMRPlusX.array()).array();
                }

                if (forwarditem[15]){
                    byzkernel=byzkernel.array()+Uijk.array()*(-k1/Rijk.array()-k2*YDRMRPlusX.array()-k3*ZDPMRPlusX.array()).array();
                }

                if (forwarditem[16]){
                     Eigen::MatrixXd arg(Ym2.rows(),Xm2.cols());
                     arg=(X[i].array()*Y[j].array()*(Rijk2.array()+H[k].array()*H[k].array()).array()).array()/
                           ((X[i].array()*X[i].array()+H[k].array()*H[k].array()).array()*(H[k].array()*H[k].array()+Y[j].array()*Y[j].array()).array()*Rijk.array());
                     bzzkernel=bzzkernel.array()+Uijk.array()*(-k1*ZDPMRPlusY.array()-k2*ZDPMRPlusX.array()-k3*arg.array());
                }

            }
        }
    }
}

void MagFWD::GetFWAns(QVector<int> forwarditem)
{
    //磁正演G
    //磁梯度正演
    Hax.setZero(Ym.rows(),Xm.cols());
    Hay.setZero(Ym.rows(),Xm.cols());
    Za.setZero(Ym.rows(),Xm.cols());
    Bxx.setZero(Ym.rows(),Xm.cols());
    Bxy.setZero(Ym.rows(),Xm.cols());
    Bxz.setZero(Ym.rows(),Xm.cols());
    Byy.setZero(Ym.rows(),Xm.cols());
    Byz.setZero(Ym.rows(),Xm.cols());
    Bzz.setZero(Ym.rows(),Xm.cols());
    Eigen::MatrixXd bcehax;
    Eigen::MatrixXd bcehay;
    Eigen::MatrixXd bceza;
    Eigen::MatrixXd bcebxx;
    Eigen::MatrixXd bcebxy;
    Eigen::MatrixXd bcebxz;
    Eigen::MatrixXd bcebyy;
    Eigen::MatrixXd bcebyz;
    Eigen::MatrixXd bcebzz;
    QVector<double> LayerMagnetination;
    QVector<double> LayerKernel;
    double k1=cos(BodyInc/180.0*3.1415926)*cos(BodyDec/180.0*3.1415926);
    double k2=cos(BodyInc/180.0*3.1415926)*sin(BodyDec/180.0*3.1415926);
    double k3=sin(BodyInc/180.0*3.1415926);

    for(int zz=0;zz<Depth.size()-1;zz++){

        if (qFuzzyCompare(BodyInc, 90.0)){
            //垂直磁化
            bool IsAllZero=true;
            LayerMagnetination = processSlice(zz,Magnetization,Xlen,Ylen,Ym.rows(),IsAllZero);
            if (IsAllZero) {
                continue;
            }
            CalKernel_Ver(forwarditem,Depth[zz],Depth[zz+1]);
            if (forwarditem[8]){
                bcehax=BuildVerMagBCEMatrix(haxkernel,8);
                LayerKernel = eigenMatrixToQVector(bcehax);
                Hax=Hax+Myfft2(LayerMagnetination,LayerKernel,bcehax.rows(),bcehax.cols());
            }

            if (forwarditem[9]){
                bcehay=BuildVerMagBCEMatrix(haykernel,9);
                LayerKernel = eigenMatrixToQVector(bcehay);
                Hay=Hay+Myfft2(LayerMagnetination,LayerKernel,bcehay.rows(),bcehay.cols());
            }

            if (forwarditem[10]){
                bceza=BuildVerMagBCEMatrix(zakernel,10);
                LayerKernel = eigenMatrixToQVector(bceza);
                Za=Za+Myfft2(LayerMagnetination,LayerKernel,bceza.rows(),bceza.cols());
            }

            if (forwarditem[11]){
                bcebxx=BuildVerMagBCEMatrix(bxxkernel,11);
                LayerKernel = eigenMatrixToQVector(bcebxx);
                Bxx=Bxx+Myfft2(LayerMagnetination,LayerKernel,bcebxx.rows(),bcebxx.cols());
            }

            if (forwarditem[12]){
                bcebxy=BuildVerMagBCEMatrix(bxykernel,12);
                LayerKernel = eigenMatrixToQVector(bcebxy);
                Bxy=Bxy+Myfft2(LayerMagnetination,LayerKernel,bcebxy.rows(),bcebxy.cols());
            }

            if (forwarditem[13]){
                bcebxz=BuildVerMagBCEMatrix(bxzkernel,13);
                LayerKernel = eigenMatrixToQVector(bcebxz);
                Bxz=Bxz+Myfft2(LayerMagnetination,LayerKernel,bcebxz.rows(),bcebxz.cols());
            }

            if (forwarditem[14]){
                bcebyy=BuildVerMagBCEMatrix(byykernel,14);
                LayerKernel = eigenMatrixToQVector(bcebyy);
                Byy=Byy+Myfft2(LayerMagnetination,LayerKernel,bcebyy.rows(),bcebyy.cols());
            }

            if (forwarditem[15]){
                bcebyz=BuildVerMagBCEMatrix(byzkernel,15);
                LayerKernel = eigenMatrixToQVector(bcebyz);
                Byz=Byz+Myfft2(LayerMagnetination,LayerKernel,bcebyz.rows(),bcebyz.cols());
            }

            if (forwarditem[16]){
                bcebzz=BuildVerMagBCEMatrix(bzzkernel,16);
                LayerKernel = eigenMatrixToQVector(bcebzz);
                Bzz=Bzz+Myfft2(LayerMagnetination,LayerKernel,bcebzz.rows(),bcebzz.cols());
            }
            }else{
            bool IsAllZero=true;
                LayerMagnetination = processSliceNonVer(zz,Magnetization,Xlen,Ylen,Ym2.rows()+1,Xm2.cols()+1,IsAllZero);
                if (IsAllZero) {
                    continue;
                }

                CalKernel_nonVer(forwarditem,Depth[zz],Depth[zz+1],k1,k2,k3);
                if (forwarditem[8]){
                    bcehax=BuildNonVerMagBCEMatrix(haxkernel);
                    LayerKernel = eigenMatrixToQVector(bcehax);
                    Hax=Hax+Myfft2NonVer(LayerMagnetination,LayerKernel,bcehax.rows(),bcehax.cols(),Ym.rows(),Xm.cols());

                }

                if (forwarditem[9]){
                    bcehay=BuildNonVerMagBCEMatrix(haykernel);
                    LayerKernel = eigenMatrixToQVector(bcehay);
                    Hay=Hay+Myfft2NonVer(LayerMagnetination,LayerKernel,bcehay.rows(),bcehay.cols(),Ym.rows(),Xm.cols());
                }

                if (forwarditem[10]){
                    bceza=BuildNonVerMagBCEMatrix(zakernel);
                    LayerKernel = eigenMatrixToQVector(bceza);
                    Za=Za+Myfft2NonVer(LayerMagnetination,LayerKernel,bceza.rows(),bceza.cols(),Ym.rows(),Xm.cols());
                }

                if (forwarditem[11]){
                    bcebxx=BuildNonVerMagBCEMatrix(bxxkernel);
                    LayerKernel = eigenMatrixToQVector(bcebxx);
                    Bxx=Bxx+Myfft2NonVer(LayerMagnetination,LayerKernel,bcebxx.rows(),bcebxx.cols(),Ym.rows(),Xm.cols());
                }

                if (forwarditem[12]){
                    bcebxy=BuildNonVerMagBCEMatrix(bxykernel);
                    LayerKernel = eigenMatrixToQVector(bcebxy);
                    Bxy=Bxy+Myfft2NonVer(LayerMagnetination,LayerKernel,bcebxy.rows(),bcebxy.cols(),Ym.rows(),Xm.cols());
                }

                if (forwarditem[13]){
                    bcebxz=BuildNonVerMagBCEMatrix(bxzkernel);
                    LayerKernel = eigenMatrixToQVector(bcebxz);
                    Bxz=Bxz+Myfft2NonVer(LayerMagnetination,LayerKernel,bcebxz.rows(),bcebxz.cols(),Ym.rows(),Xm.cols());
                }

                if (forwarditem[14]){
                    bcebyy=BuildNonVerMagBCEMatrix(byykernel);
                    LayerKernel = eigenMatrixToQVector(bcebyy);
                    Byy=Byy+Myfft2NonVer(LayerMagnetination,LayerKernel,bcebyy.rows(),bcebyy.cols(),Ym.rows(),Xm.cols());
                }

                if (forwarditem[15]){
                    bcebyz=BuildNonVerMagBCEMatrix(byzkernel);
                    LayerKernel = eigenMatrixToQVector(bcebyz);
                    Byz=Byz+Myfft2NonVer(LayerMagnetination,LayerKernel,bcebyz.rows(),bcebyz.cols(),Ym.rows(),Xm.cols());
                }

                if (forwarditem[16]){
                    bcebzz=BuildNonVerMagBCEMatrix(bzzkernel);
                    LayerKernel = eigenMatrixToQVector(bcebzz);
                    Bzz=Bzz+Myfft2NonVer(LayerMagnetination,LayerKernel,bcebzz.rows(),bcebzz.cols(),Ym.rows(),Xm.cols());
                }
        }
    }
    Hax=Hax*100.0;
    Hay=Hay*100.0;
    Za=-Za*100.0;
    Bxx=Bxx*100.0;
    Bxy=Bxy*100.0;
    Bxz=-Bxz*100.0;
    Byy=Byy*100.0;
    Byz=-Byz*100.0;
    Bzz=Bzz*100.0;

    double I=MagInc/180.0*3.1415926;
    double D=MagDec/180.0*3.1415926;
    double sin_I = sin(I);
    double cos_I = cos(I);
    double cos_D = cos(D);
    double sin_D = sin(D);
    if (forwarditem[7]){
        T = Za * sin_I + Hax * cos_I * cos_D + Hay * cos_I * sin_D;}
    if(forwarditem[17]){
        Tx=Bxx*cos_D*cos_I+Bxy*cos_I*sin_D+Bxz*sin_I;

    }
    if(forwarditem[18]){
        Ty=Bxy*cos_D*cos_I+Byy*cos_I*sin_D+Byz*sin_I;

    }
    if(forwarditem[19]){
        Tz=Bxz*cos_D*cos_I+Byz*cos_I*sin_D+Bzz*sin_I;

    }
}


Eigen::MatrixXd Myatan2(const Eigen::MatrixXd &Matrix1,const Eigen::MatrixXd &Matrix2)
{
    Eigen::MatrixXd result(Matrix1.rows(),Matrix1.cols());
    for(int i=0;i<Matrix1.rows();++i){
        for (int j=0;j<Matrix1.cols();++j){
            result(i,j)=std::atan2(Matrix1(i,j),Matrix2(i,j));
        }
    }
    return result;
}

Eigen::MatrixXd BuildGraBCEMatrix(const Eigen::MatrixXd &Matrix, int type)
{
    // build extend matrix for bce method;
    // gravity.
    switch (type) {
    case 0:
    {
        Eigen::MatrixXd bceg(2*Matrix.rows(),2*Matrix.cols());
        bceg.setZero();
        bceg.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bceg.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=bceg.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bceg.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=bceg.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bceg;
    }
    break;
    case 1:
    {
        Eigen::MatrixXd bcegxx(2*Matrix.rows(),2*Matrix.cols());
        bcegxx.setZero();
        bcegxx.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegxx.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=bcegxx.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegxx.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=bcegxx.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegxx;
    }
    break;
    case 2:
    {
        Eigen::MatrixXd bcegxy(2*Matrix.rows(),2*Matrix.cols());
        bcegxy.setZero();
        bcegxy.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegxy.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=-bcegxy.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegxy.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=-bcegxy.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegxy;
    }
    break;
    case 3:
    {
        Eigen::MatrixXd bcegxz(2*Matrix.rows(),2*Matrix.cols());
        bcegxz.setZero();
        bcegxz.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegxz.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=-bcegxz.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegxz.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=bcegxz.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegxz;
    }
    break;
    case 4:
    {
        Eigen::MatrixXd bcegyy(2*Matrix.rows(),2*Matrix.cols());
        bcegyy.setZero();
        bcegyy.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegyy.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=bcegyy.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegyy.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=bcegyy.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegyy;
    }
    break;
    case 5:
    {
        Eigen::MatrixXd bcegyz(2*Matrix.rows(),2*Matrix.cols());
        bcegyz.setZero();
        bcegyz.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegyz.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=bcegyz.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegyz.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=-bcegyz.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegyz;
    }
    break;
    case 6:
    {
        Eigen::MatrixXd bcegzz(2*Matrix.rows(),2*Matrix.cols());
        bcegzz.setZero();
        bcegzz.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegzz.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=bcegzz.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegzz.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=bcegzz.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegzz;
    }
    break;
    default: {
       // qFatal("Invalid type %d in BuildVerMagBCEMatrix", type);
        return Eigen::MatrixXd::Zero(2*Matrix.rows(), 2*Matrix.cols());
    }
    }
}

Eigen::MatrixXd BuildVerMagBCEMatrix(const Eigen::MatrixXd &Matrix, int type)
{   // build extend matrix for bce method;
    // ver magnetization.
    switch (type) {

    case 8:
    {
        Eigen::MatrixXd bcegx(2*Matrix.rows(),2*Matrix.cols());
        bcegx.setZero();
        bcegx.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegx.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=-bcegx.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegx.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=bcegx.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegx;
    }
    break;
    case 9:
    {
        Eigen::MatrixXd bcegy(2*Matrix.rows(),2*Matrix.cols());
        bcegy.setZero();
        bcegy.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegy.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=bcegy.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegy.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=-bcegy.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegy;
    }
    break;

    case 10:
    {
        Eigen::MatrixXd bcegz(2*Matrix.rows(),2*Matrix.cols());
        bcegz.setZero();
        bcegz.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegz.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=bcegz.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegz.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=bcegz.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegz;
    }
    break;
    case 11:
    {
        Eigen::MatrixXd bcegxx(2*Matrix.rows(),2*Matrix.cols());
        bcegxx.setZero();
        bcegxx.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegxx.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=bcegxx.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegxx.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=bcegxx.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegxx;
    }
    break;
    case 12:
    {
        Eigen::MatrixXd bcegxy(2*Matrix.rows(),2*Matrix.cols());
        bcegxy.setZero();
        bcegxy.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegxy.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=-bcegxy.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegxy.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=-bcegxy.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegxy;
    }
    break;
    case 13:
    {
        Eigen::MatrixXd bcegxz(2*Matrix.rows(),2*Matrix.cols());
        bcegxz.setZero();
        bcegxz.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegxz.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=-bcegxz.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegxz.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=bcegxz.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegxz;
    }
    break;
    case 14:
    {
        Eigen::MatrixXd bcegyy(2*Matrix.rows(),2*Matrix.cols());
        bcegyy.setZero();
        bcegyy.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegyy.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=bcegyy.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegyy.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=bcegyy.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegyy;
    }
    break;
    case 15:
    {
        Eigen::MatrixXd bcegyz(2*Matrix.rows(),2*Matrix.cols());
        bcegyz.setZero();
        bcegyz.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegyz.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=bcegyz.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegyz.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=-bcegyz.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegyz;
    }
    break;
    case 16:
    {
        Eigen::MatrixXd bcegzz(2*Matrix.rows(),2*Matrix.cols());
        bcegzz.setZero();
        bcegzz.block(0,0,Matrix.rows(),Matrix.cols())=Matrix.block(0,0,Matrix.rows(),Matrix.cols());
        bcegzz.block(Matrix.rows()+1,0,Matrix.rows()-1,2*Matrix.cols())=bcegzz.block(1,0,Matrix.rows()-1,2*Matrix.cols()).colwise().reverse();
        bcegzz.block(0,Matrix.cols()+1,2*Matrix.rows(),Matrix.cols()-1)=bcegzz.block(0,1,2*Matrix.rows(),Matrix.cols()-1).rowwise().reverse();
        return bcegzz;
    }
    break;
    default: {
        return Eigen::MatrixXd::Zero(2*Matrix.rows(), 2*Matrix.cols());
    }
    }

}

Eigen::MatrixXd BuildNonVerMagBCEMatrix(const Eigen::MatrixXd &t)
{
    //build extend matrix for bce mathod;
    //non ver magnetization.
    int N = t.rows();
    int M = N + 1;
    Eigen::MatrixXd T = Eigen::MatrixXd::Zero(M, M);
    T.block(1, 1, N, N) = t;
    int N_sub = M / 2;
    Eigen::MatrixXd t11 = T.block(0, 0, N_sub, N_sub);
    Eigen::MatrixXd t12 = T.block(0, N_sub, N_sub, N_sub);
    Eigen::MatrixXd t21 = T.block(N_sub, 0, N_sub, N_sub);
    Eigen::MatrixXd t22 = T.block(N_sub, N_sub, N_sub, N_sub);
    Eigen::MatrixXd e_ext(M, M);
    e_ext.block(0, 0, N_sub, N_sub) = t22;
    e_ext.block(0, N_sub, N_sub, N_sub) = t21;
    e_ext.block(N_sub, 0, N_sub, N_sub) = t12;
    e_ext.block(N_sub, N_sub, N_sub, N_sub) = t11;

    return e_ext;
}

QVector<QVector<double> > convertEigenToQVector(const Eigen::MatrixXd &matrix)
{
    QVector<QVector<double>> result;
    result.reserve(matrix.rows());

    for (int i = 0; i < matrix.rows(); ++i) {
        QVector<double> row;
        row.reserve(matrix.cols());
        for (int j = 0; j < matrix.cols(); ++j) {
            row.append(matrix(i, j));
        }
        result.append(row);
    }

    return result;
}

QVector<double> eigenMatrixToQVector(const Eigen::MatrixXd &matrix)
{
    QVector<double> result;
    result.reserve(matrix.size());
    for (int i = 0; i < matrix.rows(); ++i) {
        for (int j = 0; j < matrix.cols(); ++j) {
            result.append(matrix(i, j));
        }
    }

    return result;
}

QVector<double> processSlice(int zz, const QVector<QVector<QVector<double> > > &d, int xlen, int ylen,int verlength,bool& IsAllZero)
{
    for (int ii = 0; ii < xlen && IsAllZero; ++ii) {
        for (int jj = 0; jj < ylen; ++jj) {
            if (!qFuzzyCompare(d[ii][jj][zz], 0.0)) {
                IsAllZero = false;
                break;
            }
        }
    }

    if (IsAllZero) {
        return QVector<double>(4 * verlength*verlength, 0.0);
    }

    Eigen::MatrixXd f(xlen, ylen);
    for (int ii = 0; ii < xlen; ++ii) {
        for (int jj = 0; jj < ylen; ++jj) {
            f(ii, jj) = d[ii][jj][zz];
        }
    }
    Eigen::MatrixXd f_ext = Eigen::MatrixXd::Zero(2 * verlength, 2 *verlength);
    f_ext.block(0, 0, xlen, ylen) = f;
    return QVector<double>(f_ext.data(), f_ext.data() + f_ext.size());
}

QVector<double> processSliceNonVer(int zz, const QVector<QVector<QVector<double> > > &d, int xlen, int ylen, int bcexlen, int bceylen, bool &IsAllZero)
{
    for (int ii = 0; ii < xlen && IsAllZero; ++ii) {
        for (int jj = 0; jj < ylen; ++jj) {
            if (!qFuzzyCompare(d[ii][jj][zz], 0.0)) {
                IsAllZero = false;
                break;
            }
        }
    }

    if (IsAllZero) {
        return QVector<double>(bcexlen * bceylen, 0.0);
    }

    Eigen::MatrixXd f(xlen, ylen);
    for (int ii = 0; ii < xlen; ++ii) {
        for (int jj = 0; jj < ylen; ++jj) {
            f(ii, jj) = d[ii][jj][zz];
        }
    }
    Eigen::MatrixXd f_ext = Eigen::MatrixXd::Zero(bcexlen, bceylen);

    f_ext.block(0, 0, xlen, ylen) = f;
    qDebug()<<f_ext.cols();
    qDebug()<<f_ext.rows();
    return QVector<double>(f_ext.data(), f_ext.data() + f_ext.size());
}



Eigen::MatrixXd Myfft2NonVer(QVector<double> den, QVector<double> ker, int Rows, int Cols, int xlen, int ylen)
{

    fftw_complex* denin=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Rows*Cols);
    fftw_complex* denout=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Rows*Cols);
    fftw_complex* kerin=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Rows*Cols);
    fftw_complex* kerout=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Rows*Cols);
    fftw_complex* ansin=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Rows*Cols);
    fftw_complex* ansout=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Rows*Cols);
    for (int i=0;i<Rows;++i){
        for (int j=0;j<Cols;++j){
            denin[i*Cols+j][0]=den[i*Cols+j];   //实部
            denin[i*Cols+j][1]=0;//虚部
            kerin[i*Cols+j][0]=ker[i*Cols+j];
            kerin[i*Cols+j][1]=0;
        }
    }

    fftw_plan denplan = fftw_plan_dft_2d(Rows, Cols, denin, denout, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(denplan);

    fftw_plan kerplan = fftw_plan_dft_2d(Rows, Cols, kerin, kerout, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(kerplan);

    for (int i = 0; i < Rows; i++){
        for (int j = 0; j < Cols; j++) {
            ansin[i * Cols + j][0] = kerout[i*Cols+j][0]*denout[i*Cols+j][0]-kerout[i*Cols+j][1]*denout[i*Cols+j][1]; // 实部
            ansin[i * Cols + j][1] = kerout[i*Cols+j][1]*denout[i*Cols+j][0]+kerout[i*Cols+j][0]*denout[i*Cols+j][1]; // 虚部
        }
    }

    fftw_plan ansplan = fftw_plan_dft_2d(Rows, Cols, ansin, ansout, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(ansplan);
    Eigen::MatrixXd ans(xlen,ylen);
    for(int i=0;i<xlen;++i){
        for(int j=0;j<ylen;++j){
            ans(i, j)=ansout[i*Cols+j][0]/(Rows*Cols);
        }
    }
    return ans;
}

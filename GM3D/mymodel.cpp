#include "mymodel.h"
#include<QDebug>

void SphereModel::SetPorperty(double radius,double centerx,double centery,double centerz,double density,double magnetization,double declination,
                              double inclination,QString name,QColor color)
{
    Radius=radius;
    CenterX=centerx;
    CenterY=centery;
    CenterZ=centerz;
    Density=density;
    Magnetization=magnetization;
    Declination=declination;
    Inclination=inclination;
    Name=name;
    Color=color;
}

void SphereModel::Subdivision(float meshx,float meshy,float meshz,float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{

    int xlen=static_cast<int>((xmax-xmin)/meshx);
    int ylen=static_cast<int>(ymax-ymin)/meshy;
    int zlen=static_cast<int>(zmax-zmin)/meshz;

    SpaceDensity.resize(xlen);
    for (int i=0;i<SpaceDensity.size();++i){
        SpaceDensity[i].resize(ylen);
        for(int j=0;j<SpaceDensity[i].size();++j){
            SpaceDensity[i][j].resize(zlen);
        }
    }
    SpaceMagnetization=SpaceDensity;
    int sx1=FindClosestDivisibleNum(CenterX-Radius,meshx);
    int sx2=FindClosestDivisibleNum(CenterX+Radius,meshx);
    int sy1=FindClosestDivisibleNum(CenterY-Radius,meshy);
    int sy2=FindClosestDivisibleNum(CenterY+Radius,meshy);
    int sz1=FindClosestDivisibleNum(CenterZ-Radius,meshz);
    int sz2=FindClosestDivisibleNum(CenterZ+Radius,meshz);
    double s=Radius*sqrt(2)/2;
    int cx1=FindClosestDivisibleNum(CenterX-s,meshx)+1;
    int cx2=FindClosestDivisibleNum(CenterX+s,meshx)-1;
    int cy1=FindClosestDivisibleNum(CenterY-s,meshy)+1;
    int cy2=FindClosestDivisibleNum(CenterY+s,meshy)-1;
    int cz1=FindClosestDivisibleNum(CenterZ-s,meshz)+1;
    int cz2=FindClosestDivisibleNum(CenterZ+s,meshz)-1;


    //中心立方体
    for (int i=cx1;i<cx2;i++){
        for (int j=cy1;j<cy2;j++){
            for (int k=cz1;k<cz2;k++){
                SpaceDensity[i][j][k]=Density;
                SpaceMagnetization[i][j][k]=Magnetization;
            }
        }
    }
    //四周上下部分
    for (int i=sx1;i<sx2;i++){
        for(int j=sy1;j<sy2;j++){
            for(int k=cz2;k<sz2;k++){
                if(((j*meshy-CenterY)*(j*meshy-CenterY)+(k*meshz-CenterZ)*(k*meshz-CenterZ)+(i*meshx-CenterX)*(i*meshx-CenterX))<=Radius*Radius){
                    SpaceDensity[i][j][k]=Density;
                    SpaceMagnetization[i][j][k]=Magnetization;
                }
            }
        }
    }
    for (int i=sx1;i<sx2;i++){
        for(int j=sy1;j<sy2;j++){
            for(int k=sz1;k<cz1;k++){
                if(((j*meshy-CenterY)*(j*meshy-CenterY)+(k*meshz-CenterZ)*(k*meshz-CenterZ)+(i*meshx-CenterX)*(i*meshx-CenterX))<=Radius*Radius){
                    SpaceDensity[i][j][k]=Density;
                    SpaceMagnetization[i][j][k]=Magnetization;
                }
            }
        }
    }
    //四周左右部分
    for (int i=sx1;i<cx1;i++){
        for (int j=sy1;j<sy2;j++){
            for(int k=cz1;k<cz2;k++){
                if(((j*meshy-CenterY)*(j*meshy-CenterY)+(k*meshz-CenterZ)*(k*meshz-CenterZ)+(i*meshx-CenterX)*(i*meshx-CenterX))<=Radius*Radius){
                    SpaceDensity[i][j][k]=Density;
                    SpaceMagnetization[i][j][k]=Magnetization;
                }
            }
        }
    }
    for (int i=cx2;i<sx2;i++){
        for (int j=sy1;j<sy2;j++){
            for(int k=cz1;k<cz2;k++){
                if(((j*meshy-CenterY)*(j*meshy-CenterY)+(k*meshz-CenterZ)*(k*meshz-CenterZ)+(i*meshx-CenterX)*(i*meshx-CenterX))<=Radius*Radius){
                    SpaceDensity[i][j][k]=Density;
                    SpaceMagnetization[i][j][k]=Magnetization;
                }
            }
        }
    }
    //四周前后部分
    for (int i=cx1;i<cx2;i++){
        for (int j=sy1;j<cy1;j++){
            for(int k=cz1;k<cz2;k++){
                if(((j*meshy-CenterY)*(j*meshy-CenterY)+(k*meshz-CenterZ)*(k*meshz-CenterZ)+(i*meshx-CenterX)*(i*meshx-CenterX))<=Radius*Radius){
                    SpaceDensity[i][j][k]=Density;
                    SpaceMagnetization[i][j][k]=Magnetization;

                }
            }
        }
    }

    for (int i=cx1;i<cx2;i++){
        for (int j=cy2;j<sy2;j++){
            for(int k=cz1;k<cz2;k++){
                if(((j*meshy-CenterY)*(j*meshy-CenterY)+(k*meshz-CenterZ)*(k*meshz-CenterZ)+(i*meshx-CenterX)*(i*meshx-CenterX))<=Radius*Radius){
                    SpaceDensity[i][j][k]=Density;
                    SpaceMagnetization[i][j][k]=Magnetization;
                }
            }
        }
    }


}

void CylinderModel::SetProperty(double centerx, double centery, double centerz, double length, double radius, int direction,
                                double density, double magnetization, double declination, double inclination, QColor color, QString name)
{  Length =length;
    Direction=direction;
    Radius=radius;
    CenterX=centerx;
    CenterY=centery;
    CenterZ=centerz;
    Density=density;
    Magnetization=magnetization;
    Declination=declination;
    Inclination=inclination;
    Name=name;
    Color=color;
}

void CylinderModel::Subdivision(float meshx,float meshy,float meshz,float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{
    int xlen=static_cast<int>((xmax-xmin)/meshx);
    int ylen=static_cast<int>(ymax-ymin)/meshy;
    int zlen=static_cast<int>(zmax-zmin)/meshz;
    SpaceDensity.resize(xlen);
    for (int i=0;i<SpaceDensity.size();++i){
        SpaceDensity[i].resize(ylen);
        for(int j=0;j<SpaceDensity[i].size();++j){
            SpaceDensity[i][j].resize(zlen);
        }
    }

    SpaceMagnetization=SpaceDensity;
    switch (Direction) {
    case 0:
    {   //圆柱沿着x轴向方向
        int cx1=FindClosestDivisibleNum(CenterX-Length/2,meshx);
        int cx2=FindClosestDivisibleNum(CenterX+Length/2,meshx);
        int cy1=FindClosestDivisibleNum(CenterY-Radius,meshy);
        int cy2=FindClosestDivisibleNum(CenterY+Radius,meshy);
        int cz1=FindClosestDivisibleNum(CenterZ-Radius,meshz);
        int cz2=FindClosestDivisibleNum(CenterZ+Radius,meshz);
        for (int j=cy1;j<cy2;j++){
            for (int k=cz1;k<cz2;k++){
                if(((j*meshy-CenterY)*(j*meshy-CenterY)+(k*meshz-CenterZ)*(k*meshz-CenterZ))<=Radius*Radius){
                    SpaceDensity[cx1][j][k]=Density;
                    SpaceMagnetization[cx1][j][k]=Magnetization;
                }
            }
        }
        for (int i=cx1+1;i<cx2;i++){
            for (int j=cy1;j<cy2;j++){
                for (int k=cz1;k<cz2;k++){
                    SpaceDensity[i][j][k]=SpaceDensity[cx1][j][k];
                    SpaceMagnetization[i][j][k]=SpaceMagnetization[cx1][j][k];
                }
            }
        }
    }
    break;
    case 1:
    {
        //圆柱沿着y轴方向
        int cy1=FindClosestDivisibleNum(CenterY-Length/2,meshy);
        int cy2=FindClosestDivisibleNum(CenterY+Length/2,meshy);
        int cx1=FindClosestDivisibleNum(CenterX-Radius,meshx);
        int cx2=FindClosestDivisibleNum(CenterX+Radius,meshx);
        int cz1=FindClosestDivisibleNum(CenterZ-Radius,meshz);
        int cz2=FindClosestDivisibleNum(CenterZ+Radius,meshz);
        for (int i=cx1;i<cx2;i++){
            for (int k=cz1;k<cz2;k++){
                if(((i*meshx-CenterX)*(i*meshy-CenterX)+(k*meshz-CenterZ)*(k*meshz-CenterZ))<=Radius*Radius){
                    SpaceDensity[i][cy1][k]=Density;
                    SpaceMagnetization[i][cy1][k]=Magnetization;
                }
            }
        }
        for (int i=cx1;i<cx2;i++){
            for (int j=cy1+1;j<cy2;j++){
                for (int k=cz1;k<cz2;k++){
                    SpaceDensity[i][j][k]=SpaceDensity[i][cy1][k];
                    SpaceMagnetization[i][j][k]=SpaceMagnetization[i][cy1][k];
                }
            }
        }
    }
    break;
    case 2:
    {   //圆柱沿着z轴方向
        int cx1=FindClosestDivisibleNum(CenterX-Radius,meshx);
        int cx2=FindClosestDivisibleNum(CenterX+Radius,meshx);
        int cy1=FindClosestDivisibleNum(CenterY-Radius,meshy);
        int cy2=FindClosestDivisibleNum(CenterY+Radius,meshy);
        int cz1=FindClosestDivisibleNum(CenterZ-Length/2,meshz);
        int cz2=FindClosestDivisibleNum(CenterZ+Length/2,meshz);
        for (int j=cy1;j<cy2;j++){
            for (int i=cx1;i<cx2;i++){
                if(((j*meshy-CenterY)*(j*meshy-CenterY)+(i*meshx-CenterX)*(i*meshx-CenterX))<=Radius*Radius){
                    SpaceDensity[i][j][cz1]=Density;
                    SpaceMagnetization[i][j][cz1]=Magnetization;
                }
            }
        }
        for (int i=cx1;i<cx2;i++){
            for (int j=cy1;j<cy2;j++){
                for (int k=cz1+1;k<cz2;k++){
                    SpaceDensity[i][j][k]=SpaceDensity[i][j][cz1];
                    SpaceMagnetization[i][j][k]=SpaceMagnetization[i][j][cz1];
                }
            }
        }
    }
    break;
    default:
        break;
    }

}



void CuboidModel::SetProperty(double centerx, double centery, double centerz, double length, double width, double height, double density,
                              double magnetization, double declination, double inclination, QColor color, QString name)
{
    Length=length;
    Width=width;
    Height=height;
    CenterX=centerx;
    CenterY=centery;
    CenterZ=centerz;
    Density=density;
    Magnetization=magnetization;
    Declination=declination;
    Inclination=inclination;
    Name=name;
    Color=color;
}

void CuboidModel::Subdivision(float meshx,float meshy,float meshz,float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{
    int xlen=static_cast<int>((xmax-xmin)/meshx);
    int ylen=static_cast<int>(ymax-ymin)/meshy;
    int zlen=static_cast<int>(zmax-zmin)/meshz;
    SpaceDensity.resize(xlen);
    for (int i=0;i<SpaceDensity.size();++i){
        SpaceDensity[i].resize(ylen);
        for(int j=0;j<SpaceDensity[i].size();++j){
            SpaceDensity[i][j].resize(zlen);
        }
    }
    SpaceMagnetization=SpaceDensity;
    int cx1=FindClosestDivisibleNum(CenterX-Length/2,meshx);
    int cx2=FindClosestDivisibleNum(CenterX+Length/2,meshx);
    int cy1=FindClosestDivisibleNum(CenterY-Width/2,meshy);
    int cy2=FindClosestDivisibleNum(CenterY+Width/2,meshy);
    int cz1=FindClosestDivisibleNum(CenterZ-Height/2,meshz);
    int cz2=FindClosestDivisibleNum(CenterZ+Height/2,meshz);

    for (int i=cx1;i<cx2;i++){
        for(int j=cy1;j<cy2;j++){
            for (int k=cz1;k<cz2;k++){

                SpaceDensity[i][j][k]=Density;
                SpaceMagnetization[i][j][k]=Magnetization;
            }
        }
    }

}





void PrismoidModel::Subdivision(float meshx,float meshy,float meshz,float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{
    int xlen=static_cast<int>((xmax-xmin)/meshx);
    int ylen=static_cast<int>(ymax-ymin)/meshy;
    int zlen=static_cast<int>(zmax-zmin)/meshz;
    SpaceDensity.resize(xlen);
    for (int i=0;i<SpaceDensity.size();++i){
        SpaceDensity[i].resize(ylen);
        for(int j=0;j<SpaceDensity[i].size();++j){
            SpaceDensity[i][j].resize(zlen);
        }
    }
   SpaceMagnetization=SpaceDensity;


   switch (Direction) {
   case 0:
   {
       //Z direction
       int bx1=FindClosestDivisibleNum(Param[0],meshx);
       int bx2=FindClosestDivisibleNum(Param[1],meshx);
       int by1=FindClosestDivisibleNum(Param[2],meshy);
       int by2=FindClosestDivisibleNum(Param[3],meshy);
       int tx1=FindClosestDivisibleNum(Param[4],meshx);
       int tx2=FindClosestDivisibleNum(Param[5],meshx);
       int ty1=FindClosestDivisibleNum(Param[6],meshy);
       int ty2=FindClosestDivisibleNum(Param[7],meshy);
       int height1=FindClosestDivisibleNum(Param[8],meshz);
       int height2=FindClosestDivisibleNum(Param[9],meshz);
       int cx1=bx1>tx1?tx1:bx1;
       int cx2=bx2>tx2?bx2:tx2;
       int cy1=by1>ty1?ty1:by1;
       int cy2=by2>ty2?by2:ty2;
       for(int ix=cx1;ix<cx2;ix++){
           for(int iy=cy1;iy<cy2;iy++){
               for(int iz=height1;iz<height2;iz++){
                   if(isPointInsideFrustum(ix,iy,iz,bx1,bx2,by1,by2,tx1,tx2,ty1,ty2,height1,height2)){
                       SpaceDensity[ix][iy][iz]=Density;
                       SpaceMagnetization[ix][iy][iz]=Magnetization;
                   }

               }
           }
       }
   }
       break;
   case 1:
   {
       //x direction
       int bx1=FindClosestDivisibleNum(Param[0],meshz);
       int bx2=FindClosestDivisibleNum(Param[1],meshz);
       int by1=FindClosestDivisibleNum(Param[2],meshy);
       int by2=FindClosestDivisibleNum(Param[3],meshy);
       int tx1=FindClosestDivisibleNum(Param[4],meshz);
       int tx2=FindClosestDivisibleNum(Param[5],meshz);
       int ty1=FindClosestDivisibleNum(Param[6],meshy);
       int ty2=FindClosestDivisibleNum(Param[7],meshy);
       int height1=FindClosestDivisibleNum(Param[8],meshx);
       int height2=FindClosestDivisibleNum(Param[9],meshx);
       int cx1=bx1>tx1?tx1:bx1;
       int cx2=bx2>tx2?bx2:tx2;
       int cy1=by1>ty1?ty1:by1;
       int cy2=by2>ty2?by2:ty2;
       for(int ix=cx1;ix<cx2;ix++){
           for(int iy=cy1;iy<cy2;iy++){
               for(int iz=height1;iz<height2;iz++){
                   if(isPointInsideFrustum(ix,iy,iz,bx1,bx2,by1,by2,tx1,tx2,ty1,ty2,height1,height2)){
                       SpaceDensity[iz][iy][ix]=Density;
                       SpaceMagnetization[iz][iy][ix]=Magnetization;
                   }

               }
           }
       }

   }
   break;
   case 2:
   {
       //y direction
       int bx1=FindClosestDivisibleNum(Param[0],meshz);
       int bx2=FindClosestDivisibleNum(Param[1],meshz);
       int by1=FindClosestDivisibleNum(Param[2],meshx);
       int by2=FindClosestDivisibleNum(Param[3],meshx);
       int tx1=FindClosestDivisibleNum(Param[4],meshz);
       int tx2=FindClosestDivisibleNum(Param[5],meshz);
       int ty1=FindClosestDivisibleNum(Param[6],meshx);
       int ty2=FindClosestDivisibleNum(Param[7],meshx);
       int height1=FindClosestDivisibleNum(Param[8],meshy);
       int height2=FindClosestDivisibleNum(Param[9],meshy);
       int cx1=bx1>tx1?tx1:bx1;
       int cx2=bx2>tx2?bx2:tx2;
       int cy1=by1>ty1?ty1:by1;
       int cy2=by2>ty2?by2:ty2;
       for(int ix=cx1;ix<cx2;ix++){
           for(int iy=cy1;iy<cy2;iy++){
               for(int iz=height1;iz<height2;iz++){
                   if(isPointInsideFrustum(ix,iy,iz,bx1,bx2,by1,by2,tx1,tx2,ty1,ty2,height1,height2)){
                       SpaceDensity[iz][ix][iy]=Density;
                       SpaceMagnetization[iz][ix][iy]=Magnetization;
                   }

               }
           }
       }
   }
   break;
   default:
       break;
   }

}

void PrismoidModel::SetProperty(double density,double magnetization,double declination, double inclination, QColor color, QString name, QVector<double> param,int direction)
{

    Declination=declination;
    Inclination=inclination;
    Density=density;
    Magnetization=magnetization;
    Color=color;
    Name=name;
    Param=param;
    Direction=direction;

}

bool PrismoidModel::isPointInsideFrustum(int px,int py,int pz,int bx1,int bx2,int by1,int by2,int tx1,int tx2,int ty1,int ty2,int h1,int h2)
{
    double t = static_cast<double>(pz-h1) / (h2-h1);
    double xmin=bx1+(tx1-bx1)*t;
    double xmax=bx2+(tx2-bx2)*t;
    double ymin=by1+(ty1-by1)*t;
    double ymax=by2+(ty2-by2)*t;
    return isPointInRectangle(px,py,xmin,xmax,ymin,ymax);
}

int FindClosestDivisibleNum(double Dividend, double Divisor)
{   double result=Dividend/Divisor;

    double roundedresult=round(result);
    int closeInt=static_cast<int>(roundedresult);
    return closeInt;

}

void IrregularModel::SetProperty(QVector<QVector<QVector<double> > > spacedensity, QVector<QVector<QVector<double> > > spacemagnetization, double declination, double inclination, QColor color, QString name)
{
    SpaceDensity=spacedensity;
    SpaceMagnetization=spacemagnetization;
    Declination=declination;
    Inclination=inclination;
    Color=color;
    Name=name;
}



void Model::setModelParam(QVector<float> fieldparam, QVector<SphereModel> sPHERELIST, QVector<CuboidModel> cUBOIDLIST, QVector<CylinderModel> cYLINDERLIST, QVector<IrregularModel> iRREGULARLIST, QVector<PrismoidModel> pRISMOIDLIST)
{
    FieldParam=fieldparam;
    SPHERELIST=sPHERELIST;
    CYLINDERLIST=cYLINDERLIST;
    CUBOIDLIST=cUBOIDLIST;
    IRREGULARLIST=iRREGULARLIST;
    PRISMOIDLIST=pRISMOIDLIST;
}

bool Model::SaveModelFile(const QString fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << *this;
        file.close();
        return true;
    }
    return false;
}

bool Model::ReadModelFile(const QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> *this;
        file.close();
        return true;
    }
    return false;
}

bool Model::SaveDataFile(const QString filename,int xlen,int ylen,int zlen)
{
    QVector<QVector<QVector<double>>> combinedDensity(xlen, QVector<QVector<double>>(ylen, QVector<double>(zlen, 0.0)));
    QVector<QVector<QVector<double>>> combinedM(xlen, QVector<QVector<double>>(ylen, QVector<double>(zlen, 0.0)));
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
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
            QTextStream out(&file);
            out<<"Xmin"<<" "<<"Xmax"<<" "<<"Ymin"<<" "<<"Ymax"<<" "<<"Zmin"<<" "<<"Zmax"<<" "<<"Xmesh"<<" "<<"Ymesh"<<" "<<"Zmesh"<<" ";
            if(FieldParam[9]==0){
                out<<"Unit=m"<<"\n";
            }else if(FieldParam[9]==1){
                out<<"Unit=hm"<<"\n";
            }else if(FieldParam[9]==2){
                out<<"Unit==km"<<"\n";
            }
            for (int i=0;i<9;i++){
                out<<FieldParam[i];
                out<<" ";
            }
          //  qDebug()<<combinedDensity[50][50][50];
            out<<"\n";
            out<<"x"<<"  "<<"y"<<"  "<<"  "<<"z"<<"  "<<"Density"<<"  "<<"Magnetization"<< "\n";
            for (int x = 0; x < xlen; ++x) {
                for (int y = 0; y < ylen; ++y) {
                    for (int z = 0; z < zlen; ++z) {
                        out << x*FieldParam[6] <<" "<< y*FieldParam[7] <<" " << z*FieldParam[8] <<" "<< combinedDensity[x][y][z]<<" "<<combinedM[x][y][z]<< "\n";
                    }
                }
            }
            file.close();
            return true;
        }
    return false;
}

bool isPointInRectangle(int px, int py, double xmin, double xmax, double ymin, double ymax)
{
    return px >= xmin&& px <= xmax && py >= ymin && py <= ymax;
}



#include<QVector>
#include<QColor>
#include <QDataStream>
#include <QFile>

struct SphereModel
{

    SphereModel() {
    }
    double Radius;
    double CenterX;
    double CenterY;
    double CenterZ;
    double Density;
    double Magnetization;
    double Declination;
    double Inclination;
    QColor Color;
    QString Name;
    QVector<QVector<QVector<double>>> SpaceDensity;
    QVector<QVector<QVector<double>>> SpaceMagnetization;

    void SetPorperty(double radius,double centerx,double centery,double centerz,double density,double magnetization,double declination,
                     double inclination,QString name,QColor color);
    void Subdivision(float meshx,float meshy,float meshz,float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
    friend QDataStream &operator<<(QDataStream &out, const SphereModel &data) {
        out << data.Radius << data.CenterX << data.CenterY << data.CenterZ
            << data.Density << data.Magnetization << data.Declination << data.Inclination
            << data.Color << data.Name << data.SpaceDensity << data.SpaceMagnetization;
        return out;
    }
    friend QDataStream &operator>>(QDataStream &in, SphereModel &data) {
        in >> data.Radius >> data.CenterX >> data.CenterY >> data. CenterZ
           >> data.Density >> data.Magnetization >> data.Declination >> data. Inclination
           >> data.Color >> data.Name >> data.SpaceDensity >> data.SpaceMagnetization;
        return in;
    }
};

//cuboid model
struct  CuboidModel
{
    CuboidModel() {}
    double CenterX;
    double CenterY;
    double CenterZ;
    double Length;
    double Width;
    double Height;
    double Density;
    double Magnetization;
    double Declination;
    double Inclination;
    QColor Color;
    QString Name;
    QVector<QVector<QVector<double>>> SpaceDensity;
    QVector<QVector<QVector<double>>> SpaceMagnetization;
    void SetProperty(double centerx,double centery,double centerz,double length,double width,double height,double density,
                     double magnetization,double declination,double inclination, QColor color,QString name);
    void Subdivision(float meshx,float meshy,float meshz,float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
    friend QDataStream &operator<<(QDataStream &out, const CuboidModel &data) {
        out << data.CenterX << data.CenterY << data.CenterZ<<data.Length<<data.Width<<data.Height
            << data.Density << data.Magnetization << data.Declination << data.Inclination
            << data.Color << data.Name << data.SpaceDensity << data.SpaceMagnetization;
        return out;
    }
    friend QDataStream &operator>>(QDataStream &in, CuboidModel &data) {
        in  >> data.CenterX >> data.CenterY >> data. CenterZ>>data.Length>>data.Width>>data.Height
            >> data.Density >> data.Magnetization >> data.Declination >> data. Inclination
            >> data.Color >> data.Name >> data.SpaceDensity >> data.SpaceMagnetization;
        return in;
    }
};

//cylinder model
struct CylinderModel
{
    CylinderModel() {}
    double Radius;
    double CenterX;
    double CenterY;
    double CenterZ;
    int Direction; //延伸方向
    double Length;
    double Density;
    double Magnetization;
    double Declination;
    double Inclination;
    QColor Color;
    QString Name;
    QVector<QVector<QVector<double>>> SpaceDensity;
    QVector<QVector<QVector<double>>> SpaceMagnetization;
    void SetProperty(double centerx,double centery,double centerz,double length,double radius,int direction,double density,
                     double magnetization,double declination,double inclination,QColor color,QString name);
    void Subdivision(float meshx,float meshy,float meshz,float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
    friend QDataStream &operator<<(QDataStream &out, const CylinderModel &data) {
        out << data.Radius << data.CenterX << data.CenterY << data.CenterZ<<data.Direction<<data.Length
            << data.Density << data.Magnetization << data.Declination << data.Inclination
            << data.Color << data.Name << data.SpaceDensity << data.SpaceMagnetization;
        return out;
    }
    friend QDataStream &operator>>(QDataStream &in,CylinderModel &data) {
        in >> data.Radius >> data.CenterX >> data.CenterY >> data. CenterZ>>data.Direction>>data.Length
            >> data.Density >> data.Magnetization >> data.Declination >> data. Inclination
            >> data.Color >> data.Name >> data.SpaceDensity >> data.SpaceMagnetization;
        return in;
    }
};

//irregular model
struct IrregularModel
{
    IrregularModel() {}
    QVector<QVector<QVector<double>>> SpaceDensity;
    QVector<QVector<QVector<double>>> SpaceMagnetization;
    double Declination;
    double Inclination;
    QColor Color;
    QString Name;

    void SetProperty(QVector<QVector<QVector<double>>> SpaceDensity,QVector<QVector<QVector<double>>> SpaceMagnetization,double declination,double inclination,QColor color,QString name);
    friend QDataStream &operator<<(QDataStream &out, const IrregularModel &data) {
        out << data.Declination << data.Inclination
            << data.Color << data.Name << data.SpaceDensity << data.SpaceMagnetization;
        return out;
    }
    friend QDataStream &operator>>(QDataStream &in, IrregularModel &data) {
        in  >> data.Declination >> data. Inclination
            >> data.Color >> data.Name >> data.SpaceDensity >> data.SpaceMagnetization;
        return in;
    }
};

//Prismoid model
struct PrismoidModel
{
    PrismoidModel() {}
    QVector<double> Param;
    QVector<QVector<QVector<double>>> SpaceDensity;
    QVector<QVector<QVector<double>>> SpaceMagnetization;
    double Declination;
    double Inclination;
    int Direction;
    QColor Color;
    QString Name;
    double Density;
    double Magnetization;
    void Subdivision(float meshx,float meshy,float meshz,float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
    void SetProperty(double density,double magnetization,double declination,double inclination,QColor color,QString name,QVector<double>Param, int direction);
    bool isPointInsideFrustum(int px,int py,int pz,int bx1,int bx2,int by1,int by2,int tx1,int tx2,int ty1,int ty2,int h1,int h2);
    friend QDataStream &operator<<(QDataStream &out, const PrismoidModel &data) {
        out << data.Param<<data.Density<<data.Magnetization<<data.Declination << data.Inclination
            << data.Color << data.Name << data.SpaceDensity << data.SpaceMagnetization;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, PrismoidModel &data) {
        in  >>data.Param>> data.Density>>data.Magnetization>>data.Declination >> data. Inclination
            >> data.Color >> data.Name >> data.SpaceDensity >> data.SpaceMagnetization;
        return in;
    }
};

int FindClosestDivisibleNum(double Dividend,double Divisor);
bool isPointInRectangle(int px, int py,double xmin,double xmax,double ymin,double ymax);

struct Model{
    Model(){

    }

    QVector<float> FieldParam;
    QVector<SphereModel>SPHERELIST;
    QVector<CuboidModel>CUBOIDLIST;
    QVector<CylinderModel>CYLINDERLIST;
    QVector<IrregularModel>IRREGULARLIST;
    QVector<PrismoidModel>PRISMOIDLIST;
    void setModelParam(QVector<float> fieldparam, QVector<SphereModel>sPHERELIST,QVector<CuboidModel>cUBOIDLIST,QVector<CylinderModel>cYLINDERLIST,QVector<IrregularModel>iRREGULARLIST, QVector<PrismoidModel>pRISMOIDLIST);

    friend QDataStream &operator<<(QDataStream &out, const Model &data) {
        out << data.FieldParam << data.SPHERELIST << data.CUBOIDLIST << data.CYLINDERLIST << data.IRREGULARLIST << data.PRISMOIDLIST;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, Model &data) {
        in >> data.FieldParam >> data.SPHERELIST >> data.CUBOIDLIST >> data.CYLINDERLIST >> data.IRREGULARLIST >> data.PRISMOIDLIST;
        return in;
    }

    bool SaveModelFile(const QString filename);
    bool ReadModelFile(const QString filename);
    bool SaveDataFile(const QString filename,int xlen,int ylen,int zlen);

};

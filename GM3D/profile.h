#ifndef PROFILE_H
#define PROFILE_H

#include <QMainWindow>
#include <QHash>
namespace Ui {
class Profile;
}

class Profile : public QMainWindow
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();
    void GetModelMsg(QVector<QVector<QVector<double> > > density,QVector<QVector<QVector<double> > > magnatization,QVector<float> FieldParam);


private:
    Ui::Profile *ui;
    QVector<QVector<QVector<double>>> Spacedata;
    QVector<QVector<QVector<double>>> Density;
    QVector<QVector<QVector<double>>> Magnatization;
    QRectF ProfileAxis=QRectF(10,10,750,700);
    QRectF ChooseProfileAxis=QRectF(780,80,210,210);
    QRectF InitProfileAxis=QRectF(10,10,750,700);
    QRectF InitChooseProfileAxis=QRectF(780,80,210,210);
    void PlotProfile(QVector<QVector<double>> profiledata,int rows,int cols);
    void PlotProfileChoose(void);
    QSize originalSize;
    QHash<QWidget*, QRect> m_initialGeometries;
    void storeInitialGeometries(QWidget *widget);


    float xMin=0, xMax=200, yMin=0, yMax=100, zMin=0, zMax=100, xMesh=1, yMesh=1, zMesh=1;
    int xSize, ySize, zSize;
    QVector<QVector<double>> profileData;


    //剖面
    QPoint StartPoint, EndPoint;
    bool firstPointSelected = false;
    QPoint convertToModelCoordinates(QPoint &point);
    QVector<QVector<double>> getProfileData(const QPointF& p1, const QPointF& p2);
private slots:
    void GetProfileData();
    void OutputData();
    void DataChanged(int);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // PROFILE_H

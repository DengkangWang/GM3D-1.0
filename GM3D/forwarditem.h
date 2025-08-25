#ifndef FORWARDITEM_H
#define FORWARDITEM_H

#include <QDialog>

namespace Ui {
class forwarditem;
}

class forwarditem : public QDialog
{
    Q_OBJECT

public:
    explicit forwarditem(QWidget *parent = nullptr);
    ~forwarditem();

    void GetForwardItem(QVector<int> forwarditem,double geodec,double geoinc,double ObHeight,double gaussMean,double guassStd, double addProportion);
private:
    QVector<int> FORWARDITEM;
    double GeoDec,GeoInc,ObHeight;
    double  GaussMean,GaussStd,AddProportion;

private slots:
    void GravityAllSelected(int);
    void MagneticAllSelected(int);
    void CompleteSetting(bool clicked);
    void CloseDialog(bool clicked);


private:
    Ui::forwarditem *ui;
};

#endif // FORWARDITEM_H

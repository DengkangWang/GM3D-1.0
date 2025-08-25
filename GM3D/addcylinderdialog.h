#ifndef ADDCYLINDERDIALOG_H
#define ADDCYLINDERDIALOG_H
#include<QColorDialog>
#include <QDialog>
#include "modeling.h"
namespace Ui {
class AddCylinderDialog;
}

class AddCylinderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCylinderDialog(QWidget *parent = nullptr);
    ~AddCylinderDialog();
    void GetModelingMsg(CylinderModel newcyliner,QVector<float> fieldParam);
protected:
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void backtomodeling(bool);
    void ChooseModelColor(bool);
private:
    Ui::AddCylinderDialog *ui;
    QColor color;
    QSize originalSize;
    QVector<float> FieldParam;
    QHash<QWidget*, QRect> m_initialGeometries;
    void storeInitialGeometries(QWidget *widget);
    bool validateCylinderParameters(
        const QString& cx, const QString& cy, const QString& cz,
        const QString& den, const QString& m,
        const QString& radius, const QString& length, int direction,
        double xmin, double xmax, double ymin, double ymax, double zmin, double zmax,
        QString& errorMessage);
};

#endif // ADDCYLINDERDIALOG_H

#ifndef ADDCUBEDIALOG_H
#define ADDCUBEDIALOG_H
#include "modeling.h"
#include <QDialog>
#include<QColorDialog>
namespace Ui {
class AddCubeDialog;
}

class AddCubeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCubeDialog(QWidget *parent = nullptr);
    ~AddCubeDialog();
    void GetModelingMsg(CuboidModel newcuboid,QVector<float> fieldParam);
protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void backtomodeling(bool);
    void ChooseModelColor(bool);

private:
    Ui::AddCubeDialog *ui;
    QColor color;
    QSize originalSize;
    QVector<float> FieldParam;
    QHash<QWidget*, QRect> m_initialGeometries;
    void storeInitialGeometries(QWidget *widget);
    bool validateModelParameters(
        const QString& cx, const QString& cy, const QString& cz,
        const QString& den, const QString& m,
        const QString& l, const QString& w, const QString& h,
        double xmin, double xmax, double ymin, double ymax, double zmin, double zmax,
        QString& errorMessage);
};

#endif // ADDCUBEDIALOG_H

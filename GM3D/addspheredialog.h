#ifndef ADDSPHEREDIALOG_H
#define ADDSPHEREDIALOG_H
#include <QDialog>
#include "modeling.h"
#include <QColorDialog>
namespace Ui {
class AddSphereDialog;
}

class AddSphereDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSphereDialog(QWidget *parent = nullptr);
    ~AddSphereDialog();
    void GetModelingMsg(SphereModel newsphere,QVector<float> fieldParam);
protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void backtomodeling(bool);
    void ChooseModelColor(bool);
private:
    Ui::AddSphereDialog *ui;
    QColor color;
    QSize originalSize;
    QVector<float> FieldParam;
    QHash<QWidget*, QRect> m_initialGeometries;
    void storeInitialGeometries(QWidget *widget);
    bool validateSphereParameters(
        const QString& cx, const QString& cy, const QString& cz,
        const QString& den, const QString& m,
        const QString& radius,
        double xmin, double xmax, double ymin, double ymax, double zmin, double zmax,
        QString& errorMessage);
};

#endif // ADDSPHEREDIALOG_H

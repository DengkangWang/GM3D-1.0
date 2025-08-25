#ifndef ADDPRISMOIDDIALOG_H
#define ADDPRISMOIDDIALOG_H
#include "modeling.h"
#include <QWidget>
#include<QColorDialog>
namespace Ui {
class AddPrismoidDialog;
}

class AddPrismoidDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPrismoidDialog(QWidget *parent = nullptr);
    ~AddPrismoidDialog();
    void GetModelingMsg(PrismoidModel newcyliner,QVector<float> fieldParam);
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::AddPrismoidDialog *ui;
    QColor color;
    QSize originalSize;
    QVector<float> FieldParam;
    QHash<QWidget*, QRect> m_initialGeometries;
    void storeInitialGeometries(QWidget *widget);
    bool validateCubeParameters(
        const QVector<double>& params,
        double density, double m,
        int direction,
        double xmin, double xmax, double ymin, double ymax, double zmin, double zmax,
        QString& errorMessage);

private slots:
    void backtomodeling(bool);
    void ChooseModelColor(bool);
};

#endif // ADDPRISMOIDDIALOG_H

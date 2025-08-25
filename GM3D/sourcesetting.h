#ifndef SOURCESETTING_H
#define SOURCESETTING_H

#include <QDialog>
#include <QHash>
namespace Ui {
class SourceSetting;
}

class SourceSetting : public QDialog
{
    Q_OBJECT

public:
    explicit SourceSetting(QWidget *parent = nullptr);
    ~SourceSetting();
    void getModelingMsg(QVector<float>);

private slots:
    void CompleteSourceSet(bool);
    void CloseDialog(bool);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::SourceSetting *ui;
    QVector<float> SOURCE={0,0,0,0,0,0,0,0,0,0};

    QSize originalSize;
    QHash<QWidget*, QRect> m_initialGeometries;
    void storeInitialGeometries(QWidget *widget);
    bool validateModelingSpace(const QVector<float>& source, QString& errorMessage);

};

#endif // SOURCESETTING_H

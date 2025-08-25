#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPushButton>
#include <QResizeEvent>
#include <QLabel>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;


private slots:
    void CreateNewModel(bool clicked);
    void InputCreatedModel(bool clicked);
private:

    int m_initialWidth = 400;
    int m_initialHeight = 300;
    QPushButton * CreatNewModelButton;
    QPushButton * InputModelButton;
    QLabel *label;
   // Modeling *modelingmodule=NULL;
    struct ControlGeometry {
        int x, y, width, height;
    };
    QHash<QWidget*, ControlGeometry> m_initialGeometries;
};


#endif // MAINWINDOW_H

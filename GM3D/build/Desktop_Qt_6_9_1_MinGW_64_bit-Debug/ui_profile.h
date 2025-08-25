/********************************************************************************
** Form generated from reading UI file 'profile.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILE_H
#define UI_PROFILE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Profile
{
public:
    QWidget *centralwidget;
    QLabel *label_5;
    QGroupBox *groupBox;
    QComboBox *comboBox;
    QLabel *label_23;
    QLineEdit *StartPointEdit;
    QLineEdit *EndPointEdit;
    QLabel *label_24;
    QLabel *label_25;
    QPushButton *ComfirmBtn;
    QLabel *label_26;
    QPushButton *OutputBtn;
    QComboBox *datacomboBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Profile)
    {
        if (Profile->objectName().isEmpty())
            Profile->setObjectName("Profile");
        Profile->resize(1000, 720);
        centralwidget = new QWidget(Profile);
        centralwidget->setObjectName("centralwidget");
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(780, 20, 171, 31));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        label_5->setFont(font);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(780, 330, 210, 210));
        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(80, 40, 91, 22));
        QFont font1;
        font1.setPointSize(10);
        comboBox->setFont(font1);
        label_23 = new QLabel(groupBox);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(20, 40, 61, 21));
        QFont font2;
        font2.setPointSize(11);
        label_23->setFont(font2);
        StartPointEdit = new QLineEdit(groupBox);
        StartPointEdit->setObjectName("StartPointEdit");
        StartPointEdit->setGeometry(QRect(80, 80, 91, 21));
        StartPointEdit->setFont(font1);
        EndPointEdit = new QLineEdit(groupBox);
        EndPointEdit->setObjectName("EndPointEdit");
        EndPointEdit->setGeometry(QRect(80, 120, 91, 21));
        EndPointEdit->setFont(font1);
        label_24 = new QLabel(groupBox);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(20, 80, 41, 21));
        label_24->setFont(font2);
        label_25 = new QLabel(groupBox);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(20, 120, 41, 21));
        label_25->setFont(font2);
        ComfirmBtn = new QPushButton(groupBox);
        ComfirmBtn->setObjectName("ComfirmBtn");
        ComfirmBtn->setGeometry(QRect(40, 160, 131, 31));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        ComfirmBtn->setFont(font3);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/myicon/ok.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ComfirmBtn->setIcon(icon);
        label_26 = new QLabel(centralwidget);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(780, 0, 171, 31));
        label_26->setFont(font);
        OutputBtn = new QPushButton(centralwidget);
        OutputBtn->setObjectName("OutputBtn");
        OutputBtn->setGeometry(QRect(820, 640, 131, 31));
        OutputBtn->setFont(font3);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/myicon/output.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        OutputBtn->setIcon(icon1);
        datacomboBox = new QComboBox(centralwidget);
        datacomboBox->addItem(QString());
        datacomboBox->addItem(QString());
        datacomboBox->setObjectName("datacomboBox");
        datacomboBox->setGeometry(QRect(820, 583, 131, 31));
        datacomboBox->setFont(font3);
        Profile->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Profile);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        Profile->setMenuBar(menubar);
        statusbar = new QStatusBar(Profile);
        statusbar->setObjectName("statusbar");
        Profile->setStatusBar(statusbar);

        retranslateUi(Profile);

        QMetaObject::connectSlotsByName(Profile);
    } // setupUi

    void retranslateUi(QMainWindow *Profile)
    {
        Profile->setWindowTitle(QCoreApplication::translate("Profile", "MainWindow", nullptr));
        label_5->setText(QCoreApplication::translate("Profile", "to select the line", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Profile", "Profile Set", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Profile", "X Profile", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Profile", "Y Profile", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Profile", "Z Profile", nullptr));

        label_23->setText(QCoreApplication::translate("Profile", "Profile", nullptr));
        label_24->setText(QCoreApplication::translate("Profile", "Start ", nullptr));
        label_25->setText(QCoreApplication::translate("Profile", "End", nullptr));
        ComfirmBtn->setText(QCoreApplication::translate("Profile", "Comfirm", nullptr));
        label_26->setText(QCoreApplication::translate("Profile", "Right-click on the map", nullptr));
        OutputBtn->setText(QCoreApplication::translate("Profile", "Output", nullptr));
        datacomboBox->setItemText(0, QCoreApplication::translate("Profile", "Density", nullptr));
        datacomboBox->setItemText(1, QCoreApplication::translate("Profile", "Magnetization", nullptr));

    } // retranslateUi

};

namespace Ui {
    class Profile: public Ui_Profile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILE_H

/********************************************************************************
** Form generated from reading UI file 'forwarding.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORWARDING_H
#define UI_FORWARDING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Forwarding
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *SelectItemBtn;
    QPushButton *BackBtn;
    QComboBox *comboBox;
    QLabel *label;
    QPushButton *SaveDataBtn;
    QTreeView *treeView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Forwarding)
    {
        if (Forwarding->objectName().isEmpty())
            Forwarding->setObjectName("Forwarding");
        Forwarding->resize(900, 600);
        centralwidget = new QWidget(Forwarding);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(740, 370, 151, 181));
        SelectItemBtn = new QPushButton(groupBox);
        SelectItemBtn->setObjectName("SelectItemBtn");
        SelectItemBtn->setGeometry(QRect(10, 20, 131, 31));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        SelectItemBtn->setFont(font);
        BackBtn = new QPushButton(groupBox);
        BackBtn->setObjectName("BackBtn");
        BackBtn->setGeometry(QRect(10, 140, 131, 31));
        BackBtn->setFont(font);
        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(70, 100, 71, 31));
        comboBox->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 100, 41, 31));
        label->setFont(font);
        SaveDataBtn = new QPushButton(groupBox);
        SaveDataBtn->setObjectName("SaveDataBtn");
        SaveDataBtn->setGeometry(QRect(10, 60, 131, 31));
        SaveDataBtn->setFont(font);
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName("treeView");
        treeView->setGeometry(QRect(740, 10, 150, 341));
        Forwarding->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Forwarding);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 21));
        Forwarding->setMenuBar(menubar);
        statusbar = new QStatusBar(Forwarding);
        statusbar->setObjectName("statusbar");
        Forwarding->setStatusBar(statusbar);

        retranslateUi(Forwarding);

        QMetaObject::connectSlotsByName(Forwarding);
    } // setupUi

    void retranslateUi(QMainWindow *Forwarding)
    {
        Forwarding->setWindowTitle(QCoreApplication::translate("Forwarding", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        SelectItemBtn->setText(QCoreApplication::translate("Forwarding", "Forwarding", nullptr));
        BackBtn->setText(QCoreApplication::translate("Forwarding", "Back", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Forwarding", "G", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Forwarding", "Gxx", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Forwarding", "Gxy", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Forwarding", "Gxz", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("Forwarding", "Gyy", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("Forwarding", "Gyz", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("Forwarding", "Gzz", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("Forwarding", "T", nullptr));
        comboBox->setItemText(8, QCoreApplication::translate("Forwarding", "Hax", nullptr));
        comboBox->setItemText(9, QCoreApplication::translate("Forwarding", "Hay", nullptr));
        comboBox->setItemText(10, QCoreApplication::translate("Forwarding", "Za", nullptr));
        comboBox->setItemText(11, QCoreApplication::translate("Forwarding", "Bxx", nullptr));
        comboBox->setItemText(12, QCoreApplication::translate("Forwarding", "Bxy", nullptr));
        comboBox->setItemText(13, QCoreApplication::translate("Forwarding", "Bxz", nullptr));
        comboBox->setItemText(14, QCoreApplication::translate("Forwarding", "Byy", nullptr));
        comboBox->setItemText(15, QCoreApplication::translate("Forwarding", "Byz", nullptr));
        comboBox->setItemText(16, QCoreApplication::translate("Forwarding", "Bzz", nullptr));
        comboBox->setItemText(17, QCoreApplication::translate("Forwarding", "Tx", nullptr));
        comboBox->setItemText(18, QCoreApplication::translate("Forwarding", "Ty", nullptr));
        comboBox->setItemText(19, QCoreApplication::translate("Forwarding", "Tz", nullptr));

        label->setText(QCoreApplication::translate("Forwarding", "Draw", nullptr));
        SaveDataBtn->setText(QCoreApplication::translate("Forwarding", "Save Data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Forwarding: public Ui_Forwarding {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORWARDING_H

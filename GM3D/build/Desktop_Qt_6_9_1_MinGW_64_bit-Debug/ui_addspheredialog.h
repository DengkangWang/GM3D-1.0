/********************************************************************************
** Form generated from reading UI file 'addspheredialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSPHEREDIALOG_H
#define UI_ADDSPHEREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddSphereDialog
{
public:
    QGroupBox *groupBox;
    QLineEdit *CxEdit;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *CzEdit;
    QLineEdit *CyEdit;
    QLabel *label_4;
    QLineEdit *REdit;
    QLabel *label_5;
    QLabel *UnitLable;
    QGroupBox *groupBox_2;
    QLineEdit *DenEdit;
    QLabel *label_6;
    QLineEdit *MEdit;
    QLabel *label_7;
    QLineEdit *DecEdit;
    QLabel *label_8;
    QLineEdit *IncEdit;
    QLabel *label_9;
    QGroupBox *groupBox_3;
    QLabel *label_10;
    QLineEdit *NameEdit;
    QLabel *label_11;
    QPushButton *PaletteBtn;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *AddSphereDialog)
    {
        if (AddSphereDialog->objectName().isEmpty())
            AddSphereDialog->setObjectName("AddSphereDialog");
        AddSphereDialog->resize(228, 513);
        groupBox = new QGroupBox(AddSphereDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 20, 211, 171));
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        groupBox->setFont(font);
        CxEdit = new QLineEdit(groupBox);
        CxEdit->setObjectName("CxEdit");
        CxEdit->setGeometry(QRect(100, 30, 71, 21));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 54, 21));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 90, 54, 21));
        CzEdit = new QLineEdit(groupBox);
        CzEdit->setObjectName("CzEdit");
        CzEdit->setGeometry(QRect(100, 90, 71, 21));
        CyEdit = new QLineEdit(groupBox);
        CyEdit->setObjectName("CyEdit");
        CyEdit->setGeometry(QRect(100, 60, 71, 21));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 60, 54, 21));
        REdit = new QLineEdit(groupBox);
        REdit->setObjectName("REdit");
        REdit->setGeometry(QRect(100, 120, 71, 21));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 120, 54, 21));
        UnitLable = new QLabel(groupBox);
        UnitLable->setObjectName("UnitLable");
        UnitLable->setGeometry(QRect(10, 150, 161, 16));
        groupBox_2 = new QGroupBox(AddSphereDialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 200, 211, 151));
        groupBox_2->setFont(font);
        DenEdit = new QLineEdit(groupBox_2);
        DenEdit->setObjectName("DenEdit");
        DenEdit->setGeometry(QRect(140, 30, 61, 21));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 30, 111, 21));
        MEdit = new QLineEdit(groupBox_2);
        MEdit->setObjectName("MEdit");
        MEdit->setGeometry(QRect(140, 60, 61, 21));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 60, 121, 21));
        label_7->setFont(font);
        DecEdit = new QLineEdit(groupBox_2);
        DecEdit->setObjectName("DecEdit");
        DecEdit->setGeometry(QRect(140, 90, 61, 21));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 90, 111, 16));
        IncEdit = new QLineEdit(groupBox_2);
        IncEdit->setObjectName("IncEdit");
        IncEdit->setGeometry(QRect(140, 120, 61, 21));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 120, 111, 16));
        groupBox_3 = new QGroupBox(AddSphereDialog);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 360, 211, 91));
        groupBox_3->setFont(font);
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 30, 54, 21));
        NameEdit = new QLineEdit(groupBox_3);
        NameEdit->setObjectName("NameEdit");
        NameEdit->setGeometry(QRect(100, 30, 71, 21));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 60, 54, 21));
        PaletteBtn = new QPushButton(groupBox_3);
        PaletteBtn->setObjectName("PaletteBtn");
        PaletteBtn->setGeometry(QRect(100, 60, 71, 21));
        okBtn = new QPushButton(AddSphereDialog);
        okBtn->setObjectName("okBtn");
        okBtn->setGeometry(QRect(50, 480, 51, 21));
        okBtn->setFont(font);
        cancelBtn = new QPushButton(AddSphereDialog);
        cancelBtn->setObjectName("cancelBtn");
        cancelBtn->setGeometry(QRect(140, 480, 51, 21));
        cancelBtn->setFont(font);

        retranslateUi(AddSphereDialog);

        QMetaObject::connectSlotsByName(AddSphereDialog);
    } // setupUi

    void retranslateUi(QDialog *AddSphereDialog)
    {
        AddSphereDialog->setWindowTitle(QCoreApplication::translate("AddSphereDialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AddSphereDialog", "Size", nullptr));
        label->setText(QCoreApplication::translate("AddSphereDialog", "Center_x", nullptr));
        label_3->setText(QCoreApplication::translate("AddSphereDialog", "Center_z", nullptr));
        label_4->setText(QCoreApplication::translate("AddSphereDialog", "Center_y", nullptr));
        label_5->setText(QCoreApplication::translate("AddSphereDialog", "Radius", nullptr));
        UnitLable->setText(QCoreApplication::translate("AddSphereDialog", "Unit:km", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("AddSphereDialog", "Property", nullptr));
        label_6->setText(QCoreApplication::translate("AddSphereDialog", "Density (g/cm^3)", nullptr));
        label_7->setText(QCoreApplication::translate("AddSphereDialog", "Magnetization(A/m)", nullptr));
        label_8->setText(QCoreApplication::translate("AddSphereDialog", "Declination (\302\260)", nullptr));
        IncEdit->setText(QString());
        label_9->setText(QCoreApplication::translate("AddSphereDialog", "Inclination (\302\260)", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("AddSphereDialog", "Mark", nullptr));
        label_10->setText(QCoreApplication::translate("AddSphereDialog", "name", nullptr));
        label_11->setText(QCoreApplication::translate("AddSphereDialog", "color", nullptr));
        PaletteBtn->setText(QCoreApplication::translate("AddSphereDialog", "palette", nullptr));
        okBtn->setText(QCoreApplication::translate("AddSphereDialog", "ok", nullptr));
        cancelBtn->setText(QCoreApplication::translate("AddSphereDialog", "cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddSphereDialog: public Ui_AddSphereDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSPHEREDIALOG_H

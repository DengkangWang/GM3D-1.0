/********************************************************************************
** Form generated from reading UI file 'addcylinderdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCYLINDERDIALOG_H
#define UI_ADDCYLINDERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddCylinderDialog
{
public:
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QGroupBox *groupBox_3;
    QLabel *label_14;
    QLineEdit *NameEdit;
    QLabel *label_15;
    QPushButton *PaletteBtn;
    QGroupBox *groupBox;
    QLineEdit *CxEdit;
    QLabel *label_2;
    QLabel *label_16;
    QLineEdit *CzEdit;
    QLineEdit *CyEdit;
    QLabel *label_17;
    QLineEdit *REdit;
    QLabel *label_18;
    QLabel *label_20;
    QComboBox *comboBox;
    QLabel *label_19;
    QLineEdit *LEdit;
    QLabel *UnitLabel;
    QGroupBox *groupBox_2;
    QLineEdit *DenEdit;
    QLabel *label_21;
    QLineEdit *MEdit;
    QLabel *label_22;
    QLineEdit *DecEdit;
    QLabel *label_23;
    QLineEdit *IncEdit;
    QLabel *label_24;

    void setupUi(QDialog *AddCylinderDialog)
    {
        if (AddCylinderDialog->objectName().isEmpty())
            AddCylinderDialog->setObjectName("AddCylinderDialog");
        AddCylinderDialog->resize(227, 542);
        okBtn = new QPushButton(AddCylinderDialog);
        okBtn->setObjectName("okBtn");
        okBtn->setGeometry(QRect(60, 510, 51, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        okBtn->setFont(font);
        cancelBtn = new QPushButton(AddCylinderDialog);
        cancelBtn->setObjectName("cancelBtn");
        cancelBtn->setGeometry(QRect(140, 510, 51, 21));
        cancelBtn->setFont(font);
        groupBox_3 = new QGroupBox(AddCylinderDialog);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 410, 211, 91));
        groupBox_3->setFont(font);
        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 30, 54, 21));
        NameEdit = new QLineEdit(groupBox_3);
        NameEdit->setObjectName("NameEdit");
        NameEdit->setGeometry(QRect(100, 30, 71, 21));
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 60, 54, 21));
        PaletteBtn = new QPushButton(groupBox_3);
        PaletteBtn->setObjectName("PaletteBtn");
        PaletteBtn->setGeometry(QRect(100, 60, 71, 21));
        groupBox = new QGroupBox(AddCylinderDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 211, 231));
        groupBox->setFont(font);
        CxEdit = new QLineEdit(groupBox);
        CxEdit->setObjectName("CxEdit");
        CxEdit->setGeometry(QRect(100, 30, 71, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 30, 54, 21));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 90, 54, 21));
        CzEdit = new QLineEdit(groupBox);
        CzEdit->setObjectName("CzEdit");
        CzEdit->setGeometry(QRect(100, 90, 71, 21));
        CyEdit = new QLineEdit(groupBox);
        CyEdit->setObjectName("CyEdit");
        CyEdit->setGeometry(QRect(100, 60, 71, 21));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 60, 54, 21));
        REdit = new QLineEdit(groupBox);
        REdit->setObjectName("REdit");
        REdit->setGeometry(QRect(100, 120, 71, 21));
        label_18 = new QLabel(groupBox);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 120, 54, 21));
        label_20 = new QLabel(groupBox);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(10, 150, 71, 21));
        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(100, 150, 72, 21));
        label_19 = new QLabel(groupBox);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(10, 180, 54, 21));
        LEdit = new QLineEdit(groupBox);
        LEdit->setObjectName("LEdit");
        LEdit->setGeometry(QRect(100, 180, 71, 21));
        UnitLabel = new QLabel(groupBox);
        UnitLabel->setObjectName("UnitLabel");
        UnitLabel->setGeometry(QRect(10, 210, 131, 20));
        groupBox_2 = new QGroupBox(AddCylinderDialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 250, 211, 151));
        groupBox_2->setFont(font);
        DenEdit = new QLineEdit(groupBox_2);
        DenEdit->setObjectName("DenEdit");
        DenEdit->setGeometry(QRect(140, 30, 61, 21));
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(10, 30, 111, 21));
        MEdit = new QLineEdit(groupBox_2);
        MEdit->setObjectName("MEdit");
        MEdit->setGeometry(QRect(140, 60, 61, 21));
        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 60, 121, 21));
        label_22->setFont(font);
        DecEdit = new QLineEdit(groupBox_2);
        DecEdit->setObjectName("DecEdit");
        DecEdit->setGeometry(QRect(140, 90, 61, 21));
        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 90, 111, 16));
        IncEdit = new QLineEdit(groupBox_2);
        IncEdit->setObjectName("IncEdit");
        IncEdit->setGeometry(QRect(140, 120, 61, 21));
        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 120, 111, 16));

        retranslateUi(AddCylinderDialog);

        QMetaObject::connectSlotsByName(AddCylinderDialog);
    } // setupUi

    void retranslateUi(QDialog *AddCylinderDialog)
    {
        AddCylinderDialog->setWindowTitle(QCoreApplication::translate("AddCylinderDialog", "Dialog", nullptr));
        okBtn->setText(QCoreApplication::translate("AddCylinderDialog", "ok", nullptr));
        cancelBtn->setText(QCoreApplication::translate("AddCylinderDialog", "cancel", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("AddCylinderDialog", "Mark", nullptr));
        label_14->setText(QCoreApplication::translate("AddCylinderDialog", "name", nullptr));
        label_15->setText(QCoreApplication::translate("AddCylinderDialog", "color", nullptr));
        PaletteBtn->setText(QCoreApplication::translate("AddCylinderDialog", "palette", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AddCylinderDialog", "Size", nullptr));
        label_2->setText(QCoreApplication::translate("AddCylinderDialog", "Center_x", nullptr));
        label_16->setText(QCoreApplication::translate("AddCylinderDialog", "Center_z", nullptr));
        label_17->setText(QCoreApplication::translate("AddCylinderDialog", "Center_y", nullptr));
        label_18->setText(QCoreApplication::translate("AddCylinderDialog", "Radius", nullptr));
        label_20->setText(QCoreApplication::translate("AddCylinderDialog", "Direction", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("AddCylinderDialog", "x", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("AddCylinderDialog", "y", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("AddCylinderDialog", "z", nullptr));

        label_19->setText(QCoreApplication::translate("AddCylinderDialog", "Length", nullptr));
        UnitLabel->setText(QCoreApplication::translate("AddCylinderDialog", "Unit:km", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("AddCylinderDialog", "Property", nullptr));
        label_21->setText(QCoreApplication::translate("AddCylinderDialog", "Density (g/cm^3)", nullptr));
        label_22->setText(QCoreApplication::translate("AddCylinderDialog", "Magnetization(A/m)", nullptr));
        label_23->setText(QCoreApplication::translate("AddCylinderDialog", "Declination (\302\260)", nullptr));
        IncEdit->setText(QString());
        label_24->setText(QCoreApplication::translate("AddCylinderDialog", "Inclination (\302\260)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddCylinderDialog: public Ui_AddCylinderDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCYLINDERDIALOG_H

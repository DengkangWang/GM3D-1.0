/********************************************************************************
** Form generated from reading UI file 'addcubedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCUBEDIALOG_H
#define UI_ADDCUBEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddCubeDialog
{
public:
    QPushButton *okBtn;
    QPushButton *cancelBtn;
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
    QGroupBox *groupBox;
    QLineEdit *CxEdit;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *CzEdit;
    QLineEdit *CyEdit;
    QLabel *label_4;
    QLineEdit *LEdit;
    QLabel *label_5;
    QLabel *label_12;
    QLineEdit *WEdit;
    QLabel *label_13;
    QLineEdit *HEdit;
    QLabel *UnitLable;

    void setupUi(QDialog *AddCubeDialog)
    {
        if (AddCubeDialog->objectName().isEmpty())
            AddCubeDialog->setObjectName("AddCubeDialog");
        AddCubeDialog->resize(217, 528);
        okBtn = new QPushButton(AddCubeDialog);
        okBtn->setObjectName("okBtn");
        okBtn->setGeometry(QRect(60, 500, 51, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        okBtn->setFont(font);
        cancelBtn = new QPushButton(AddCubeDialog);
        cancelBtn->setObjectName("cancelBtn");
        cancelBtn->setGeometry(QRect(140, 500, 51, 21));
        cancelBtn->setFont(font);
        groupBox_2 = new QGroupBox(AddCubeDialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 240, 201, 151));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setFont(font);
        DenEdit = new QLineEdit(groupBox_2);
        DenEdit->setObjectName("DenEdit");
        DenEdit->setGeometry(QRect(130, 30, 61, 21));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 30, 111, 21));
        MEdit = new QLineEdit(groupBox_2);
        MEdit->setObjectName("MEdit");
        MEdit->setGeometry(QRect(130, 60, 61, 21));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 60, 121, 21));
        label_7->setFont(font);
        DecEdit = new QLineEdit(groupBox_2);
        DecEdit->setObjectName("DecEdit");
        DecEdit->setGeometry(QRect(130, 90, 61, 21));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 90, 111, 16));
        IncEdit = new QLineEdit(groupBox_2);
        IncEdit->setObjectName("IncEdit");
        IncEdit->setGeometry(QRect(130, 120, 61, 21));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 120, 111, 16));
        groupBox_3 = new QGroupBox(AddCubeDialog);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 400, 201, 91));
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
        groupBox = new QGroupBox(AddCubeDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 0, 201, 231));
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
        LEdit = new QLineEdit(groupBox);
        LEdit->setObjectName("LEdit");
        LEdit->setGeometry(QRect(100, 120, 71, 21));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 120, 54, 21));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 180, 71, 21));
        WEdit = new QLineEdit(groupBox);
        WEdit->setObjectName("WEdit");
        WEdit->setGeometry(QRect(100, 180, 71, 21));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 150, 54, 21));
        HEdit = new QLineEdit(groupBox);
        HEdit->setObjectName("HEdit");
        HEdit->setGeometry(QRect(100, 150, 71, 21));
        UnitLable = new QLabel(groupBox);
        UnitLable->setObjectName("UnitLable");
        UnitLable->setGeometry(QRect(10, 210, 161, 16));

        retranslateUi(AddCubeDialog);

        QMetaObject::connectSlotsByName(AddCubeDialog);
    } // setupUi

    void retranslateUi(QDialog *AddCubeDialog)
    {
        AddCubeDialog->setWindowTitle(QCoreApplication::translate("AddCubeDialog", "Dialog", nullptr));
        okBtn->setText(QCoreApplication::translate("AddCubeDialog", "ok", nullptr));
        cancelBtn->setText(QCoreApplication::translate("AddCubeDialog", "cancel", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("AddCubeDialog", "Property", nullptr));
        label_6->setText(QCoreApplication::translate("AddCubeDialog", "Density (g/cm^3)", nullptr));
        label_7->setText(QCoreApplication::translate("AddCubeDialog", "Magnetization(A/m)", nullptr));
        label_8->setText(QCoreApplication::translate("AddCubeDialog", "Declination (\302\260)", nullptr));
        IncEdit->setText(QString());
        label_9->setText(QCoreApplication::translate("AddCubeDialog", "Inclination (\302\260)", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("AddCubeDialog", "Mark", nullptr));
        label_10->setText(QCoreApplication::translate("AddCubeDialog", "name", nullptr));
        label_11->setText(QCoreApplication::translate("AddCubeDialog", "color", nullptr));
        PaletteBtn->setText(QCoreApplication::translate("AddCubeDialog", "palette", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AddCubeDialog", "Size", nullptr));
        label->setText(QCoreApplication::translate("AddCubeDialog", "Center_x", nullptr));
        label_3->setText(QCoreApplication::translate("AddCubeDialog", "Center_z", nullptr));
        label_4->setText(QCoreApplication::translate("AddCubeDialog", "Center_y", nullptr));
        label_5->setText(QCoreApplication::translate("AddCubeDialog", "Long(x)", nullptr));
        label_12->setText(QCoreApplication::translate("AddCubeDialog", "Height(z)", nullptr));
        label_13->setText(QCoreApplication::translate("AddCubeDialog", "Width(y)", nullptr));
        UnitLable->setText(QCoreApplication::translate("AddCubeDialog", "Unit:km", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddCubeDialog: public Ui_AddCubeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCUBEDIALOG_H

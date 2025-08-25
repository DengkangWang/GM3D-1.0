/********************************************************************************
** Form generated from reading UI file 'addprismoiddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPRISMOIDDIALOG_H
#define UI_ADDPRISMOIDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddPrismoidDialog
{
public:
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
    QLineEdit *Bottomx1;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *Bottomy1;
    QLineEdit *Bottomx2;
    QLabel *label_4;
    QLineEdit *Bottomy2;
    QLabel *label_5;
    QLabel *label_12;
    QLineEdit *h1;
    QLabel *label_13;
    QLineEdit *Topx1;
    QLineEdit *Topx2;
    QLabel *label_14;
    QLineEdit *Topy1;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *Topy2;
    QComboBox *comboBox;
    QLabel *label_17;
    QLineEdit *h2;
    QLabel *label_18;
    QLabel *UnitLable;
    QPushButton *cancelBtn;
    QPushButton *okBtn;

    void setupUi(QWidget *AddPrismoidDialog)
    {
        if (AddPrismoidDialog->objectName().isEmpty())
            AddPrismoidDialog->setObjectName("AddPrismoidDialog");
        AddPrismoidDialog->resize(239, 697);
        groupBox_2 = new QGroupBox(AddPrismoidDialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 410, 221, 151));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
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
        label_9->setGeometry(QRect(10, 120, 121, 16));
        groupBox_3 = new QGroupBox(AddPrismoidDialog);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 570, 221, 91));
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
        groupBox = new QGroupBox(AddPrismoidDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 221, 391));
        groupBox->setFont(font);
        Bottomx1 = new QLineEdit(groupBox);
        Bottomx1->setObjectName("Bottomx1");
        Bottomx1->setGeometry(QRect(100, 30, 71, 21));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 71, 21));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 90, 61, 21));
        Bottomy1 = new QLineEdit(groupBox);
        Bottomy1->setObjectName("Bottomy1");
        Bottomy1->setGeometry(QRect(100, 90, 71, 21));
        Bottomx2 = new QLineEdit(groupBox);
        Bottomx2->setObjectName("Bottomx2");
        Bottomx2->setGeometry(QRect(100, 60, 71, 21));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 60, 71, 21));
        Bottomy2 = new QLineEdit(groupBox);
        Bottomy2->setObjectName("Bottomy2");
        Bottomy2->setGeometry(QRect(100, 120, 71, 21));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 120, 71, 21));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 300, 71, 21));
        h1 = new QLineEdit(groupBox);
        h1->setObjectName("h1");
        h1->setGeometry(QRect(100, 300, 71, 21));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 150, 71, 21));
        Topx1 = new QLineEdit(groupBox);
        Topx1->setObjectName("Topx1");
        Topx1->setGeometry(QRect(100, 150, 71, 21));
        Topx2 = new QLineEdit(groupBox);
        Topx2->setObjectName("Topx2");
        Topx2->setGeometry(QRect(100, 180, 71, 21));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 180, 71, 21));
        Topy1 = new QLineEdit(groupBox);
        Topy1->setObjectName("Topy1");
        Topy1->setGeometry(QRect(100, 210, 71, 21));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 210, 71, 21));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 240, 71, 21));
        Topy2 = new QLineEdit(groupBox);
        Topy2->setObjectName("Topy2");
        Topy2->setGeometry(QRect(100, 240, 71, 21));
        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(100, 270, 69, 22));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 270, 71, 21));
        h2 = new QLineEdit(groupBox);
        h2->setObjectName("h2");
        h2->setGeometry(QRect(100, 330, 71, 21));
        label_18 = new QLabel(groupBox);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 330, 71, 21));
        UnitLable = new QLabel(groupBox);
        UnitLable->setObjectName("UnitLable");
        UnitLable->setGeometry(QRect(10, 360, 161, 16));
        cancelBtn = new QPushButton(AddPrismoidDialog);
        cancelBtn->setObjectName("cancelBtn");
        cancelBtn->setGeometry(QRect(150, 670, 51, 21));
        cancelBtn->setFont(font);
        okBtn = new QPushButton(AddPrismoidDialog);
        okBtn->setObjectName("okBtn");
        okBtn->setGeometry(QRect(60, 670, 51, 21));
        okBtn->setFont(font);

        retranslateUi(AddPrismoidDialog);

        QMetaObject::connectSlotsByName(AddPrismoidDialog);
    } // setupUi

    void retranslateUi(QWidget *AddPrismoidDialog)
    {
        AddPrismoidDialog->setWindowTitle(QCoreApplication::translate("AddPrismoidDialog", "Form", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("AddPrismoidDialog", "Property", nullptr));
        label_6->setText(QCoreApplication::translate("AddPrismoidDialog", "Density (g/cm^3)", nullptr));
        label_7->setText(QCoreApplication::translate("AddPrismoidDialog", "Magnetization(A/m)", nullptr));
        label_8->setText(QCoreApplication::translate("AddPrismoidDialog", "Declination (\302\260)", nullptr));
        IncEdit->setText(QString());
        label_9->setText(QCoreApplication::translate("AddPrismoidDialog", "Inclination (\302\260)", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("AddPrismoidDialog", "Mark", nullptr));
        label_10->setText(QCoreApplication::translate("AddPrismoidDialog", "name", nullptr));
        label_11->setText(QCoreApplication::translate("AddPrismoidDialog", "color", nullptr));
        PaletteBtn->setText(QCoreApplication::translate("AddPrismoidDialog", "palette", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AddPrismoidDialog", "Size", nullptr));
        label->setText(QCoreApplication::translate("AddPrismoidDialog", "Top x1", nullptr));
        label_3->setText(QCoreApplication::translate("AddPrismoidDialog", "Top y1", nullptr));
        label_4->setText(QCoreApplication::translate("AddPrismoidDialog", "Top x2", nullptr));
        label_5->setText(QCoreApplication::translate("AddPrismoidDialog", "Top y2", nullptr));
        label_12->setText(QCoreApplication::translate("AddPrismoidDialog", "Height1", nullptr));
        label_13->setText(QCoreApplication::translate("AddPrismoidDialog", "Bottom x1", nullptr));
        Topx2->setText(QString());
        label_14->setText(QCoreApplication::translate("AddPrismoidDialog", "Bottom x2", nullptr));
        label_15->setText(QCoreApplication::translate("AddPrismoidDialog", "Bottom y1", nullptr));
        label_16->setText(QCoreApplication::translate("AddPrismoidDialog", "Bottom y2", nullptr));
        Topy2->setText(QString());
        comboBox->setItemText(0, QCoreApplication::translate("AddPrismoidDialog", "z", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("AddPrismoidDialog", "x", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("AddPrismoidDialog", "y", nullptr));

        label_17->setText(QCoreApplication::translate("AddPrismoidDialog", "Direction", nullptr));
        label_18->setText(QCoreApplication::translate("AddPrismoidDialog", "Height2", nullptr));
        UnitLable->setText(QCoreApplication::translate("AddPrismoidDialog", "Unit:km", nullptr));
        cancelBtn->setText(QCoreApplication::translate("AddPrismoidDialog", "cancel", nullptr));
        okBtn->setText(QCoreApplication::translate("AddPrismoidDialog", "ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddPrismoidDialog: public Ui_AddPrismoidDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPRISMOIDDIALOG_H

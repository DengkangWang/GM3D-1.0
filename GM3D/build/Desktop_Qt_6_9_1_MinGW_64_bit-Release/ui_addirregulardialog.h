/********************************************************************************
** Form generated from reading UI file 'addirregulardialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDIRREGULARDIALOG_H
#define UI_ADDIRREGULARDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_AddIrregularDialog
{
public:
    QPushButton *okbtn;
    QPushButton *pushButton_14;
    QGroupBox *groupBox;
    QPushButton *rectbtn;
    QPushButton *circularbtn;
    QPushButton *custombtn;
    QPushButton *clickbtn;
    QPushButton *copybtn;
    QPushButton *pastebtn;
    QPushButton *clearbtn;
    QPushButton *finishbtn;
    QPushButton *cancelbtn;
    QLabel *label_25;
    QSpinBox *spinBox;
    QLabel *label_26;
    QComboBox *comboBox;
    QRadioButton *BuildButton;
    QRadioButton *EraseButton;
    QGroupBox *groupBox_2;
    QLabel *label_21;
    QLineEdit *DenEdit;
    QLabel *label_22;
    QLineEdit *MEdit;
    QLabel *label_23;
    QLineEdit *DecEdit;
    QLabel *label_24;
    QLineEdit *IncEdit;
    QLabel *label_14;
    QLineEdit *NameEdit;
    QLabel *label_15;
    QPushButton *PaletteBtn;

    void setupUi(QDialog *AddIrregularDialog)
    {
        if (AddIrregularDialog->objectName().isEmpty())
            AddIrregularDialog->setObjectName("AddIrregularDialog");
        AddIrregularDialog->resize(1200, 800);
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        AddIrregularDialog->setFont(font);
        okbtn = new QPushButton(AddIrregularDialog);
        okbtn->setObjectName("okbtn");
        okbtn->setGeometry(QRect(1070, 730, 121, 23));
        okbtn->setFont(font);
        pushButton_14 = new QPushButton(AddIrregularDialog);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(1069, 760, 121, 23));
        pushButton_14->setFont(font);
        groupBox = new QGroupBox(AddIrregularDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(1070, 0, 121, 431));
        rectbtn = new QPushButton(groupBox);
        rectbtn->setObjectName("rectbtn");
        rectbtn->setGeometry(QRect(20, 70, 91, 22));
        rectbtn->setFont(font);
        circularbtn = new QPushButton(groupBox);
        circularbtn->setObjectName("circularbtn");
        circularbtn->setGeometry(QRect(20, 100, 91, 23));
        circularbtn->setFont(font);
        custombtn = new QPushButton(groupBox);
        custombtn->setObjectName("custombtn");
        custombtn->setGeometry(QRect(20, 130, 91, 23));
        custombtn->setFont(font);
        clickbtn = new QPushButton(groupBox);
        clickbtn->setObjectName("clickbtn");
        clickbtn->setGeometry(QRect(20, 160, 91, 23));
        clickbtn->setFont(font);
        copybtn = new QPushButton(groupBox);
        copybtn->setObjectName("copybtn");
        copybtn->setGeometry(QRect(20, 190, 91, 23));
        copybtn->setFont(font);
        pastebtn = new QPushButton(groupBox);
        pastebtn->setObjectName("pastebtn");
        pastebtn->setGeometry(QRect(20, 220, 91, 23));
        pastebtn->setFont(font);
        clearbtn = new QPushButton(groupBox);
        clearbtn->setObjectName("clearbtn");
        clearbtn->setGeometry(QRect(20, 250, 91, 23));
        clearbtn->setFont(font);
        finishbtn = new QPushButton(groupBox);
        finishbtn->setObjectName("finishbtn");
        finishbtn->setGeometry(QRect(20, 280, 91, 23));
        finishbtn->setFont(font);
        cancelbtn = new QPushButton(groupBox);
        cancelbtn->setObjectName("cancelbtn");
        cancelbtn->setGeometry(QRect(20, 310, 91, 23));
        cancelbtn->setFont(font);
        label_25 = new QLabel(groupBox);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(30, 330, 41, 21));
        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(30, 350, 71, 24));
        spinBox->setFont(font);
        spinBox->setMaximum(100000);
        label_26 = new QLabel(groupBox);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(30, 380, 54, 21));
        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(30, 400, 72, 24));
        BuildButton = new QRadioButton(groupBox);
        BuildButton->setObjectName("BuildButton");
        BuildButton->setGeometry(QRect(20, 20, 97, 22));
        BuildButton->setChecked(true);
        EraseButton = new QRadioButton(groupBox);
        EraseButton->setObjectName("EraseButton");
        EraseButton->setGeometry(QRect(20, 40, 97, 22));
        groupBox_2 = new QGroupBox(AddIrregularDialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(1070, 450, 121, 271));
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(10, 20, 101, 23));
        DenEdit = new QLineEdit(groupBox_2);
        DenEdit->setObjectName("DenEdit");
        DenEdit->setGeometry(QRect(10, 40, 91, 20));
        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(0, 60, 121, 21));
        label_22->setFont(font);
        MEdit = new QLineEdit(groupBox_2);
        MEdit->setObjectName("MEdit");
        MEdit->setGeometry(QRect(10, 80, 91, 20));
        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 100, 91, 21));
        DecEdit = new QLineEdit(groupBox_2);
        DecEdit->setObjectName("DecEdit");
        DecEdit->setGeometry(QRect(10, 120, 91, 20));
        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 140, 101, 21));
        IncEdit = new QLineEdit(groupBox_2);
        IncEdit->setObjectName("IncEdit");
        IncEdit->setGeometry(QRect(10, 160, 91, 20));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 180, 41, 23));
        NameEdit = new QLineEdit(groupBox_2);
        NameEdit->setObjectName("NameEdit");
        NameEdit->setGeometry(QRect(10, 200, 91, 20));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 220, 41, 21));
        PaletteBtn = new QPushButton(groupBox_2);
        PaletteBtn->setObjectName("PaletteBtn");
        PaletteBtn->setGeometry(QRect(10, 240, 91, 23));

        retranslateUi(AddIrregularDialog);

        QMetaObject::connectSlotsByName(AddIrregularDialog);
    } // setupUi

    void retranslateUi(QDialog *AddIrregularDialog)
    {
        AddIrregularDialog->setWindowTitle(QCoreApplication::translate("AddIrregularDialog", "Dialog", nullptr));
        okbtn->setText(QCoreApplication::translate("AddIrregularDialog", "Build Completed", nullptr));
        pushButton_14->setText(QCoreApplication::translate("AddIrregularDialog", "Cancel", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AddIrregularDialog", "Profile Operate", nullptr));
        rectbtn->setText(QCoreApplication::translate("AddIrregularDialog", "Rectangle", nullptr));
        circularbtn->setText(QCoreApplication::translate("AddIrregularDialog", "Circular", nullptr));
        custombtn->setText(QCoreApplication::translate("AddIrregularDialog", "Custom", nullptr));
        clickbtn->setText(QCoreApplication::translate("AddIrregularDialog", "Single Click", nullptr));
        copybtn->setText(QCoreApplication::translate("AddIrregularDialog", "Copy", nullptr));
        pastebtn->setText(QCoreApplication::translate("AddIrregularDialog", "Paste", nullptr));
        clearbtn->setText(QCoreApplication::translate("AddIrregularDialog", "Clear Layer", nullptr));
        finishbtn->setText(QCoreApplication::translate("AddIrregularDialog", "Save Layer", nullptr));
        cancelbtn->setText(QCoreApplication::translate("AddIrregularDialog", "Cancel", nullptr));
        label_25->setText(QCoreApplication::translate("AddIrregularDialog", "Layer", nullptr));
        label_26->setText(QCoreApplication::translate("AddIrregularDialog", "Profile", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("AddIrregularDialog", "Z", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("AddIrregularDialog", "Y", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("AddIrregularDialog", "X", nullptr));

        BuildButton->setText(QCoreApplication::translate("AddIrregularDialog", "Build Mode", nullptr));
        EraseButton->setText(QCoreApplication::translate("AddIrregularDialog", "Erase Mode", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("AddIrregularDialog", "Property", nullptr));
        label_21->setText(QCoreApplication::translate("AddIrregularDialog", "Density(g/cm^3)", nullptr));
        DenEdit->setText(QCoreApplication::translate("AddIrregularDialog", "10", nullptr));
        label_22->setText(QCoreApplication::translate("AddIrregularDialog", "Magnetization(A/m)", nullptr));
        MEdit->setText(QCoreApplication::translate("AddIrregularDialog", "10", nullptr));
        label_23->setText(QCoreApplication::translate("AddIrregularDialog", "Declination(\302\260)", nullptr));
        DecEdit->setText(QCoreApplication::translate("AddIrregularDialog", "0", nullptr));
        label_24->setText(QCoreApplication::translate("AddIrregularDialog", "Inclination(\302\260)", nullptr));
        IncEdit->setText(QCoreApplication::translate("AddIrregularDialog", "90", nullptr));
        label_14->setText(QCoreApplication::translate("AddIrregularDialog", "Name", nullptr));
        label_15->setText(QCoreApplication::translate("AddIrregularDialog", "Color", nullptr));
        PaletteBtn->setText(QCoreApplication::translate("AddIrregularDialog", "palette", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddIrregularDialog: public Ui_AddIrregularDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDIRREGULARDIALOG_H

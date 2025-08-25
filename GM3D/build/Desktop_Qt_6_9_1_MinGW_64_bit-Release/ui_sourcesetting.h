/********************************************************************************
** Form generated from reading UI file 'sourcesetting.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOURCESETTING_H
#define UI_SOURCESETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SourceSetting
{
public:
    QGroupBox *groupBox;
    QLabel *label_6;
    QLabel *label_4;
    QLineEdit *zminEdit;
    QLineEdit *xminEdit;
    QLineEdit *zmaxEdit;
    QLineEdit *xmaxEdit;
    QLineEdit *ymaxEdit;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *yminEdit;
    QGroupBox *groupBox_2;
    QLabel *label_7;
    QLineEdit *xmeshEdit;
    QLabel *label_8;
    QLineEdit *ymeshEdit;
    QLabel *label_9;
    QLineEdit *zmeshEdit;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QComboBox *comboBox;
    QLabel *label_10;

    void setupUi(QDialog *SourceSetting)
    {
        if (SourceSetting->objectName().isEmpty())
            SourceSetting->setObjectName("SourceSetting");
        SourceSetting->resize(260, 358);
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        SourceSetting->setFont(font);
        groupBox = new QGroupBox(SourceSetting);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 20, 240, 171));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(140, 130, 41, 21));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(140, 80, 41, 21));
        zminEdit = new QLineEdit(groupBox);
        zminEdit->setObjectName("zminEdit");
        zminEdit->setGeometry(QRect(60, 130, 41, 21));
        xminEdit = new QLineEdit(groupBox);
        xminEdit->setObjectName("xminEdit");
        xminEdit->setGeometry(QRect(60, 30, 41, 21));
        zmaxEdit = new QLineEdit(groupBox);
        zmaxEdit->setObjectName("zmaxEdit");
        zmaxEdit->setGeometry(QRect(180, 130, 41, 21));
        xmaxEdit = new QLineEdit(groupBox);
        xmaxEdit->setObjectName("xmaxEdit");
        xmaxEdit->setGeometry(QRect(180, 30, 41, 21));
        ymaxEdit = new QLineEdit(groupBox);
        ymaxEdit->setObjectName("ymaxEdit");
        ymaxEdit->setGeometry(QRect(180, 80, 41, 21));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 130, 41, 21));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 80, 41, 21));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 41, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 30, 41, 21));
        yminEdit = new QLineEdit(groupBox);
        yminEdit->setObjectName("yminEdit");
        yminEdit->setGeometry(QRect(60, 80, 41, 21));
        groupBox_2 = new QGroupBox(SourceSetting);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 200, 240, 61));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 30, 21, 21));
        xmeshEdit = new QLineEdit(groupBox_2);
        xmeshEdit->setObjectName("xmeshEdit");
        xmeshEdit->setGeometry(QRect(30, 30, 41, 21));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(90, 30, 21, 21));
        ymeshEdit = new QLineEdit(groupBox_2);
        ymeshEdit->setObjectName("ymeshEdit");
        ymeshEdit->setGeometry(QRect(110, 30, 41, 21));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(170, 30, 20, 21));
        zmeshEdit = new QLineEdit(groupBox_2);
        zmeshEdit->setObjectName("zmeshEdit");
        zmeshEdit->setGeometry(QRect(190, 30, 41, 21));
        okBtn = new QPushButton(SourceSetting);
        okBtn->setObjectName("okBtn");
        okBtn->setGeometry(QRect(110, 320, 51, 21));
        cancelBtn = new QPushButton(SourceSetting);
        cancelBtn->setObjectName("cancelBtn");
        cancelBtn->setGeometry(QRect(190, 320, 51, 21));
        comboBox = new QComboBox(SourceSetting);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(60, 280, 51, 21));
        label_10 = new QLabel(SourceSetting);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 280, 41, 21));

        retranslateUi(SourceSetting);

        QMetaObject::connectSlotsByName(SourceSetting);
    } // setupUi

    void retranslateUi(QDialog *SourceSetting)
    {
        SourceSetting->setWindowTitle(QCoreApplication::translate("SourceSetting", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SourceSetting", "Range", nullptr));
        label_6->setText(QCoreApplication::translate("SourceSetting", "Zmax", nullptr));
        label_4->setText(QCoreApplication::translate("SourceSetting", "Ymax", nullptr));
        label_5->setText(QCoreApplication::translate("SourceSetting", "Zmin", nullptr));
        label_3->setText(QCoreApplication::translate("SourceSetting", "Ymin", nullptr));
        label->setText(QCoreApplication::translate("SourceSetting", "Xmin", nullptr));
        label_2->setText(QCoreApplication::translate("SourceSetting", "Xmax", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SourceSetting", "Mesh", nullptr));
        label_7->setText(QCoreApplication::translate("SourceSetting", "X", nullptr));
        label_8->setText(QCoreApplication::translate("SourceSetting", "Y", nullptr));
        label_9->setText(QCoreApplication::translate("SourceSetting", "Z", nullptr));
        okBtn->setText(QCoreApplication::translate("SourceSetting", "ok", nullptr));
        cancelBtn->setText(QCoreApplication::translate("SourceSetting", "cancel", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("SourceSetting", "m", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("SourceSetting", "hm", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("SourceSetting", "km", nullptr));

        label_10->setText(QCoreApplication::translate("SourceSetting", "Unit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SourceSetting: public Ui_SourceSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOURCESETTING_H

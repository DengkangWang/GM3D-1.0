/********************************************************************************
** Form generated from reading UI file 'forwarditem.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORWARDITEM_H
#define UI_FORWARDITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_forwarditem
{
public:
    QGroupBox *GraGroup;
    QCheckBox *GAllBtn;
    QCheckBox *GxxBtn;
    QCheckBox *GxyBtn;
    QCheckBox *GyyBtn;
    QCheckBox *GyzBtn;
    QCheckBox *GxzBtn;
    QCheckBox *GzzBtn;
    QCheckBox *GBtn;
    QGroupBox *MagGroup;
    QCheckBox *MAllBtn;
    QCheckBox *HaxBtn;
    QCheckBox *HayBtn;
    QCheckBox *BxxBtn;
    QCheckBox *BxyBtn;
    QCheckBox *ZaBtn;
    QCheckBox *BxzBtn;
    QCheckBox *TBtn;
    QCheckBox *ByyBtn;
    QCheckBox *BzzBtn;
    QCheckBox *ByzBtn;
    QCheckBox *TxBtn;
    QCheckBox *TyBtn;
    QCheckBox *TzBtn;
    QPushButton *OkBtn;
    QPushButton *CancelBtn;
    QLabel *label;
    QLineEdit *ObserHedit;
    QGroupBox *GeoMaggroup;
    QLineEdit *Iedit;
    QLineEdit *Dedit;
    QLabel *label_4;
    QLabel *label_5;
    QGroupBox *groupBox;
    QLabel *label_6;
    QLineEdit *GaussMean;
    QLabel *label_7;
    QLineEdit *GaussStd;
    QLabel *label_8;
    QLineEdit *AddProportion;

    void setupUi(QDialog *forwarditem)
    {
        if (forwarditem->objectName().isEmpty())
            forwarditem->setObjectName("forwarditem");
        forwarditem->resize(300, 586);
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        forwarditem->setFont(font);
        GraGroup = new QGroupBox(forwarditem);
        GraGroup->setObjectName("GraGroup");
        GraGroup->setGeometry(QRect(10, 130, 280, 121));
        GAllBtn = new QCheckBox(GraGroup);
        GAllBtn->setObjectName("GAllBtn");
        GAllBtn->setGeometry(QRect(10, 30, 51, 21));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Consolas")});
        font1.setBold(true);
        GAllBtn->setFont(font1);
        GxxBtn = new QCheckBox(GraGroup);
        GxxBtn->setObjectName("GxxBtn");
        GxxBtn->setGeometry(QRect(10, 60, 51, 21));
        GxyBtn = new QCheckBox(GraGroup);
        GxyBtn->setObjectName("GxyBtn");
        GxyBtn->setGeometry(QRect(120, 60, 51, 21));
        GyyBtn = new QCheckBox(GraGroup);
        GyyBtn->setObjectName("GyyBtn");
        GyyBtn->setGeometry(QRect(10, 90, 51, 21));
        GyzBtn = new QCheckBox(GraGroup);
        GyzBtn->setObjectName("GyzBtn");
        GyzBtn->setGeometry(QRect(120, 90, 51, 21));
        GxzBtn = new QCheckBox(GraGroup);
        GxzBtn->setObjectName("GxzBtn");
        GxzBtn->setGeometry(QRect(220, 60, 51, 21));
        GzzBtn = new QCheckBox(GraGroup);
        GzzBtn->setObjectName("GzzBtn");
        GzzBtn->setGeometry(QRect(220, 90, 51, 21));
        GBtn = new QCheckBox(GraGroup);
        GBtn->setObjectName("GBtn");
        GBtn->setGeometry(QRect(120, 30, 51, 21));
        MagGroup = new QGroupBox(forwarditem);
        MagGroup->setObjectName("MagGroup");
        MagGroup->setGeometry(QRect(10, 260, 281, 171));
        MAllBtn = new QCheckBox(MagGroup);
        MAllBtn->setObjectName("MAllBtn");
        MAllBtn->setGeometry(QRect(10, 30, 51, 21));
        MAllBtn->setFont(font1);
        HaxBtn = new QCheckBox(MagGroup);
        HaxBtn->setObjectName("HaxBtn");
        HaxBtn->setGeometry(QRect(10, 60, 51, 21));
        HayBtn = new QCheckBox(MagGroup);
        HayBtn->setObjectName("HayBtn");
        HayBtn->setGeometry(QRect(120, 60, 51, 21));
        BxxBtn = new QCheckBox(MagGroup);
        BxxBtn->setObjectName("BxxBtn");
        BxxBtn->setGeometry(QRect(10, 90, 51, 21));
        BxyBtn = new QCheckBox(MagGroup);
        BxyBtn->setObjectName("BxyBtn");
        BxyBtn->setGeometry(QRect(120, 90, 51, 21));
        ZaBtn = new QCheckBox(MagGroup);
        ZaBtn->setObjectName("ZaBtn");
        ZaBtn->setGeometry(QRect(220, 60, 51, 21));
        BxzBtn = new QCheckBox(MagGroup);
        BxzBtn->setObjectName("BxzBtn");
        BxzBtn->setGeometry(QRect(220, 90, 51, 21));
        TBtn = new QCheckBox(MagGroup);
        TBtn->setObjectName("TBtn");
        TBtn->setGeometry(QRect(120, 30, 51, 21));
        ByyBtn = new QCheckBox(MagGroup);
        ByyBtn->setObjectName("ByyBtn");
        ByyBtn->setGeometry(QRect(10, 120, 51, 21));
        BzzBtn = new QCheckBox(MagGroup);
        BzzBtn->setObjectName("BzzBtn");
        BzzBtn->setGeometry(QRect(220, 120, 51, 21));
        ByzBtn = new QCheckBox(MagGroup);
        ByzBtn->setObjectName("ByzBtn");
        ByzBtn->setGeometry(QRect(120, 120, 51, 21));
        TxBtn = new QCheckBox(MagGroup);
        TxBtn->setObjectName("TxBtn");
        TxBtn->setGeometry(QRect(10, 150, 51, 21));
        TyBtn = new QCheckBox(MagGroup);
        TyBtn->setObjectName("TyBtn");
        TyBtn->setGeometry(QRect(120, 150, 51, 21));
        TzBtn = new QCheckBox(MagGroup);
        TzBtn->setObjectName("TzBtn");
        TzBtn->setGeometry(QRect(220, 150, 51, 21));
        OkBtn = new QPushButton(forwarditem);
        OkBtn->setObjectName("OkBtn");
        OkBtn->setGeometry(QRect(150, 550, 41, 21));
        OkBtn->setFont(font1);
        CancelBtn = new QPushButton(forwarditem);
        CancelBtn->setObjectName("CancelBtn");
        CancelBtn->setGeometry(QRect(230, 550, 61, 21));
        CancelBtn->setFont(font1);
        label = new QLabel(forwarditem);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 121, 21));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Consolas")});
        font2.setPointSize(9);
        font2.setBold(true);
        label->setFont(font2);
        ObserHedit = new QLineEdit(forwarditem);
        ObserHedit->setObjectName("ObserHedit");
        ObserHedit->setGeometry(QRect(150, 20, 71, 21));
        GeoMaggroup = new QGroupBox(forwarditem);
        GeoMaggroup->setObjectName("GeoMaggroup");
        GeoMaggroup->setGeometry(QRect(10, 60, 280, 61));
        Iedit = new QLineEdit(GeoMaggroup);
        Iedit->setObjectName("Iedit");
        Iedit->setGeometry(QRect(50, 30, 51, 21));
        Dedit = new QLineEdit(GeoMaggroup);
        Dedit->setObjectName("Dedit");
        Dedit->setGeometry(QRect(190, 30, 51, 21));
        label_4 = new QLabel(GeoMaggroup);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 30, 31, 24));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Consolas")});
        font3.setPointSize(9);
        label_4->setFont(font3);
        label_5 = new QLabel(GeoMaggroup);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(160, 30, 31, 24));
        label_5->setFont(font3);
        groupBox = new QGroupBox(forwarditem);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 440, 281, 91));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 30, 31, 24));
        label_6->setFont(font3);
        GaussMean = new QLineEdit(groupBox);
        GaussMean->setObjectName("GaussMean");
        GaussMean->setGeometry(QRect(40, 30, 71, 21));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(160, 30, 31, 24));
        label_7->setFont(font3);
        GaussStd = new QLineEdit(groupBox);
        GaussStd->setObjectName("GaussStd");
        GaussStd->setGeometry(QRect(190, 30, 71, 21));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 60, 101, 24));
        label_8->setFont(font3);
        AddProportion = new QLineEdit(groupBox);
        AddProportion->setObjectName("AddProportion");
        AddProportion->setGeometry(QRect(110, 60, 81, 21));

        retranslateUi(forwarditem);

        QMetaObject::connectSlotsByName(forwarditem);
    } // setupUi

    void retranslateUi(QDialog *forwarditem)
    {
        forwarditem->setWindowTitle(QCoreApplication::translate("forwarditem", "Dialog", nullptr));
        GraGroup->setTitle(QCoreApplication::translate("forwarditem", "Gravity", nullptr));
        GAllBtn->setText(QCoreApplication::translate("forwarditem", "ALL", nullptr));
        GxxBtn->setText(QCoreApplication::translate("forwarditem", "Gxx", nullptr));
        GxyBtn->setText(QCoreApplication::translate("forwarditem", "Gxy", nullptr));
        GyyBtn->setText(QCoreApplication::translate("forwarditem", "Gyy", nullptr));
        GyzBtn->setText(QCoreApplication::translate("forwarditem", "Gyz", nullptr));
        GxzBtn->setText(QCoreApplication::translate("forwarditem", "Gxz", nullptr));
        GzzBtn->setText(QCoreApplication::translate("forwarditem", "Gzz", nullptr));
        GBtn->setText(QCoreApplication::translate("forwarditem", "G", nullptr));
        MagGroup->setTitle(QCoreApplication::translate("forwarditem", "Magnetic", nullptr));
        MAllBtn->setText(QCoreApplication::translate("forwarditem", "ALL", nullptr));
        HaxBtn->setText(QCoreApplication::translate("forwarditem", "Hax", nullptr));
        HayBtn->setText(QCoreApplication::translate("forwarditem", "Hay", nullptr));
        BxxBtn->setText(QCoreApplication::translate("forwarditem", "Bxx", nullptr));
        BxyBtn->setText(QCoreApplication::translate("forwarditem", "Bxy", nullptr));
        ZaBtn->setText(QCoreApplication::translate("forwarditem", "Za", nullptr));
        BxzBtn->setText(QCoreApplication::translate("forwarditem", "Bxz", nullptr));
        TBtn->setText(QCoreApplication::translate("forwarditem", "\316\224T", nullptr));
        ByyBtn->setText(QCoreApplication::translate("forwarditem", "Byy", nullptr));
        BzzBtn->setText(QCoreApplication::translate("forwarditem", "Bzz", nullptr));
        ByzBtn->setText(QCoreApplication::translate("forwarditem", "Byz", nullptr));
        TxBtn->setText(QCoreApplication::translate("forwarditem", "\316\224Tx", nullptr));
        TyBtn->setText(QCoreApplication::translate("forwarditem", "\316\224Ty", nullptr));
        TzBtn->setText(QCoreApplication::translate("forwarditem", "\316\224Tz", nullptr));
        OkBtn->setText(QCoreApplication::translate("forwarditem", "ok", nullptr));
        CancelBtn->setText(QCoreApplication::translate("forwarditem", "cancel", nullptr));
        label->setText(QCoreApplication::translate("forwarditem", "Observation Height", nullptr));
        GeoMaggroup->setTitle(QCoreApplication::translate("forwarditem", "Geomagnetic field", nullptr));
        label_4->setText(QCoreApplication::translate("forwarditem", "I(\302\260)", nullptr));
        label_5->setText(QCoreApplication::translate("forwarditem", "D(\302\260)", nullptr));
        groupBox->setTitle(QCoreApplication::translate("forwarditem", "Gaussian Noise", nullptr));
        label_6->setText(QCoreApplication::translate("forwarditem", "mean", nullptr));
        GaussMean->setText(QCoreApplication::translate("forwarditem", "1", nullptr));
        label_7->setText(QCoreApplication::translate("forwarditem", "std", nullptr));
        GaussStd->setText(QCoreApplication::translate("forwarditem", "0.1", nullptr));
        label_8->setText(QCoreApplication::translate("forwarditem", "add proportion", nullptr));
        AddProportion->setText(QCoreApplication::translate("forwarditem", "1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class forwarditem: public Ui_forwarditem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORWARDITEM_H

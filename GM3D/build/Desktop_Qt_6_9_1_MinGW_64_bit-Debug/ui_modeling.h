/********************************************************************************
** Form generated from reading UI file 'modeling.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODELING_H
#define UI_MODELING_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Modeling
{
public:
    QGroupBox *groupBox;
    QPushButton *AddSphereBtn;
    QPushButton *AddCuboidBtn;
    QPushButton *AddCylinderBtn;
    QPushButton *AddPrismBtn;
    QPushButton *AddIrreBtn;
    QGroupBox *groupBox_2;
    QPushButton *FieldParamSetBtn;
    QPushButton *OutputBtn;
    QPushButton *OutputBtn_2;
    QPushButton *ForwardBtn;
    QPushButton *profileBtn;
    QTreeView *treeView;

    void setupUi(QWidget *Modeling)
    {
        if (Modeling->objectName().isEmpty())
            Modeling->setObjectName("Modeling");
        Modeling->resize(1200, 800);
        groupBox = new QGroupBox(Modeling);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 0, 541, 80));
        AddSphereBtn = new QPushButton(groupBox);
        AddSphereBtn->setObjectName("AddSphereBtn");
        AddSphereBtn->setGeometry(QRect(10, 30, 80, 40));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/myicon/sphere.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        AddSphereBtn->setIcon(icon);
        AddCuboidBtn = new QPushButton(groupBox);
        AddCuboidBtn->setObjectName("AddCuboidBtn");
        AddCuboidBtn->setGeometry(QRect(120, 30, 80, 40));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/myicon/cube.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        AddCuboidBtn->setIcon(icon1);
        AddCylinderBtn = new QPushButton(groupBox);
        AddCylinderBtn->setObjectName("AddCylinderBtn");
        AddCylinderBtn->setGeometry(QRect(230, 30, 80, 40));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/myicon/cylinder.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        AddCylinderBtn->setIcon(icon2);
        AddPrismBtn = new QPushButton(groupBox);
        AddPrismBtn->setObjectName("AddPrismBtn");
        AddPrismBtn->setGeometry(QRect(340, 30, 80, 40));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/myicon/prismoid.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        AddPrismBtn->setIcon(icon3);
        AddIrreBtn = new QPushButton(groupBox);
        AddIrreBtn->setObjectName("AddIrreBtn");
        AddIrreBtn->setGeometry(QRect(450, 30, 80, 40));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/myicon/custom.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        AddIrreBtn->setIcon(icon4);
        groupBox_2 = new QGroupBox(Modeling);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(620, 0, 571, 81));
        FieldParamSetBtn = new QPushButton(groupBox_2);
        FieldParamSetBtn->setObjectName("FieldParamSetBtn");
        FieldParamSetBtn->setGeometry(QRect(30, 30, 80, 40));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/myicon/setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        FieldParamSetBtn->setIcon(icon5);
        OutputBtn = new QPushButton(groupBox_2);
        OutputBtn->setObjectName("OutputBtn");
        OutputBtn->setGeometry(QRect(140, 30, 80, 40));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/myicon/output.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        OutputBtn->setIcon(icon6);
        OutputBtn_2 = new QPushButton(groupBox_2);
        OutputBtn_2->setObjectName("OutputBtn_2");
        OutputBtn_2->setGeometry(QRect(250, 30, 80, 40));
        OutputBtn_2->setIcon(icon6);
        ForwardBtn = new QPushButton(groupBox_2);
        ForwardBtn->setObjectName("ForwardBtn");
        ForwardBtn->setGeometry(QRect(360, 30, 80, 40));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/myicon/forward.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ForwardBtn->setIcon(icon7);
        profileBtn = new QPushButton(groupBox_2);
        profileBtn->setObjectName("profileBtn");
        profileBtn->setGeometry(QRect(470, 30, 80, 40));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icon/myicon/profile.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        profileBtn->setIcon(icon8);
        treeView = new QTreeView(Modeling);
        treeView->setObjectName("treeView");
        treeView->setGeometry(QRect(20, 90, 120, 561));
        QWidget::setTabOrder(FieldParamSetBtn, OutputBtn);
        QWidget::setTabOrder(OutputBtn, AddPrismBtn);
        QWidget::setTabOrder(AddPrismBtn, AddIrreBtn);
        QWidget::setTabOrder(AddIrreBtn, AddSphereBtn);
        QWidget::setTabOrder(AddSphereBtn, AddCuboidBtn);
        QWidget::setTabOrder(AddCuboidBtn, AddCylinderBtn);

        retranslateUi(Modeling);

        QMetaObject::connectSlotsByName(Modeling);
    } // setupUi

    void retranslateUi(QWidget *Modeling)
    {
        Modeling->setWindowTitle(QCoreApplication::translate("Modeling", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Modeling", "Add Model", nullptr));
        AddSphereBtn->setText(QCoreApplication::translate("Modeling", "Sphere", nullptr));
        AddCuboidBtn->setText(QCoreApplication::translate("Modeling", "Cuboid", nullptr));
        AddCylinderBtn->setText(QCoreApplication::translate("Modeling", "Cylinder", nullptr));
        AddPrismBtn->setText(QCoreApplication::translate("Modeling", "Prismoid", nullptr));
        AddIrreBtn->setText(QCoreApplication::translate("Modeling", "Irregular", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Modeling", "Operate", nullptr));
        FieldParamSetBtn->setText(QCoreApplication::translate("Modeling", "Setting", nullptr));
        OutputBtn->setText(QCoreApplication::translate("Modeling", "Model", nullptr));
        OutputBtn_2->setText(QCoreApplication::translate("Modeling", "Data", nullptr));
        ForwardBtn->setText(QCoreApplication::translate("Modeling", "Forward", nullptr));
        profileBtn->setText(QCoreApplication::translate("Modeling", "Profile", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Modeling: public Ui_Modeling {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODELING_H

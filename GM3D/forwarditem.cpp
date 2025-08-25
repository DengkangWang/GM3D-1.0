#include "forwarditem.h"
#include "ui_forwarditem.h"
#include <iostream>
#include "forwarding.h"

forwarditem::forwarditem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forwarditem)
{
    ui->setupUi(this);
    this->setWindowTitle("Forwarding Model");
    /*********相关参数********/
    connect(ui->GAllBtn,SIGNAL(stateChanged(int)),this,SLOT(GravityAllSelected(int)));
    connect(ui->MAllBtn,SIGNAL(stateChanged(int)),this,SLOT(MagneticAllSelected(int)));
    connect(ui->OkBtn,SIGNAL(clicked(bool)),this,SLOT(CompleteSetting(bool)));
    connect(ui->CancelBtn,SIGNAL(clicked(bool)),this,SLOT(CloseDialog(bool)));

}


forwarditem::~forwarditem()
{
    delete ui;
}

void forwarditem::GetForwardItem(QVector<int> forwarditem, double geodec, double geoinc,double obheight,double gaussMean,double gaussStd,double addProportion)
{
    FORWARDITEM=forwarditem;
    GeoDec=geodec;
    GeoInc=geoinc;
    ObHeight=obheight;
    GaussMean=gaussMean;
    GaussStd=gaussStd;
    AddProportion=addProportion;
    if (FORWARDITEM[0]==1) {
        ui->GBtn->setCheckState(Qt::Checked);
    }else{
        ui->GBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[1]==1) {
        ui->GxxBtn->setCheckState(Qt::Checked);
    }else{
        ui->GxxBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[2]==1) {
        ui->GxyBtn->setCheckState(Qt::Checked);
    }else{
        ui->GxyBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[3]==1) {
        ui->GxzBtn->setCheckState(Qt::Checked);
    }else{
        ui->GxzBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[4]==1) {
        ui->GyyBtn->setCheckState(Qt::Checked);
    }else{
        ui->GyyBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[5]==1) {
        ui->GyzBtn->setCheckState(Qt::Checked);
    }else{
        ui->GyzBtn->setCheckState(Qt::Unchecked);
    }

    if (FORWARDITEM[6]==1) {
        ui->GzzBtn->setCheckState(Qt::Checked);
    }else{
        ui->GzzBtn->setCheckState(Qt::Unchecked);
    }

    /*********磁正演********/
    if (FORWARDITEM[7]==1) {
        ui->TBtn->setCheckState(Qt::Checked);
    }else{
        ui->TBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[8]==1) {
        ui->HaxBtn->setCheckState(Qt::Checked);
    }else{
        ui->HaxBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[9]==1) {
        ui->HayBtn->setCheckState(Qt::Checked);
    }else{
        ui->HayBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[10]==1) {
        ui->ZaBtn->setCheckState(Qt::Checked);
    }else{
        ui->ZaBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[11]==1) {
        ui->BxxBtn->setCheckState(Qt::Checked);
    }else{
        ui->BxxBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[12]==1) {
        ui->BxyBtn->setCheckState(Qt::Checked);
    }else{
        ui->BxyBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[13]==1) {
        ui->BxzBtn->setCheckState(Qt::Checked);
    }else{
        ui->BxzBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[14]==1) {
        ui->ByyBtn->setCheckState(Qt::Checked);
    }else{
        ui->ByyBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[15]==1) {
        ui->ByzBtn->setCheckState(Qt::Checked);
    }else{
        ui->ByzBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[16]==1) {
        ui->BzzBtn->setCheckState(Qt::Checked);
    }else{
        ui->BzzBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[17]==1) {
        ui->TxBtn->setCheckState(Qt::Checked);
    }else{
        ui->TxBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[18]==1) {
        ui->TyBtn->setCheckState(Qt::Checked);
    }else{
        ui->TyBtn->setCheckState(Qt::Unchecked);
    }
    if (FORWARDITEM[19]==1) {
        ui->TzBtn->setCheckState(Qt::Checked);
    }else{
        ui->TzBtn->setCheckState(Qt::Unchecked);
    }


    ui->Dedit->setText(QString::number(GeoDec));
    ui->Iedit->setText(QString::number(GeoInc));
    ui->ObserHedit->setText(QString::number(ObHeight));
    ui->AddProportion->setText(QString::number(addProportion));
    ui->GaussMean->setText(QString::number(gaussMean));
    ui->GaussStd->setText(QString::number(gaussStd));
}

void forwarditem::GravityAllSelected(int state)
{
    if (state==2){
        ui->GBtn->setCheckState(Qt::Checked);
        ui->GxxBtn->setCheckState(Qt::Checked);
        ui->GxyBtn->setCheckState(Qt::Checked);
        ui->GxzBtn->setCheckState(Qt::Checked);
        ui->GyzBtn->setCheckState(Qt::Checked);
        ui->GyyBtn->setCheckState(Qt::Checked);
        ui->GzzBtn->setCheckState(Qt::Checked);}
}

void forwarditem::MagneticAllSelected(int state)
{
    if(state==2){
        ui->TBtn->setCheckState(Qt::Checked);
        ui->BxxBtn->setCheckState(Qt::Checked);
        ui->BxyBtn->setCheckState(Qt::Checked);
        ui->BxzBtn->setCheckState(Qt::Checked);
        ui->ByyBtn->setCheckState(Qt::Checked);
        ui->ByzBtn->setCheckState(Qt::Checked);
        ui->BzzBtn->setCheckState(Qt::Checked);
        ui->TxBtn->setCheckState(Qt::Checked);
        ui->TzBtn->setCheckState(Qt::Checked);
        ui->TyBtn->setCheckState(Qt::Checked);
        ui->HaxBtn->setCheckState(Qt::Checked);
        ui->HayBtn->setCheckState(Qt::Checked);
        ui->ZaBtn->setCheckState(Qt::Checked);
    }
}

void forwarditem::CompleteSetting(bool)
{
    if (ui->GBtn->isChecked()==1){
        FORWARDITEM[0]=1;
    }else{
        FORWARDITEM[0]=0;
    }
    if (ui->GxxBtn->isChecked()==1){
        FORWARDITEM[1]=1;
    }else{
        FORWARDITEM[1]=0;
    }
    if (ui->GxyBtn->isChecked()==1){
        FORWARDITEM[2]=1;
    }else{
        FORWARDITEM[2]=0;
    }
    if (ui->GxzBtn->isChecked()==1){
        FORWARDITEM[3]=1;
    }else{
        FORWARDITEM[3]=0;
    }
    if (ui->GyyBtn->isChecked()==1){
        FORWARDITEM[4]=1;
    }else{
        FORWARDITEM[4]=0;
    }
    if (ui->GyzBtn->isChecked()==1){
        FORWARDITEM[5]=1;
    }else{
        FORWARDITEM[5]=0;
    }
    if (ui->GzzBtn->isChecked()==1){
        FORWARDITEM[6]=1;
    }else{
        FORWARDITEM[6]=0;
    }

    if (ui->TBtn->isChecked()==1){
        FORWARDITEM[7]=1;
    }else{
        FORWARDITEM[7]=0;
    }
    if (ui->HaxBtn->isChecked()==1){
        FORWARDITEM[8]=1;
    }else{
        FORWARDITEM[8]=0;
    }
    if (ui->HayBtn->isChecked()==1){
        FORWARDITEM[9]=1;
    }else{
        FORWARDITEM[9]=0;
    }
    if (ui->ZaBtn->isChecked()==1){
        FORWARDITEM[10]=1;
    }else{
        FORWARDITEM[10]=0;
    }
    if (ui->BxxBtn->isChecked()==1){
        FORWARDITEM[11]=1;
    }else{
        FORWARDITEM[11]=0;
    }
    if (ui->BxyBtn->isChecked()==1){
        FORWARDITEM[12]=1;
    }else{
        FORWARDITEM[12]=0;
    }
    if (ui->BxzBtn->isChecked()==1){
        FORWARDITEM[13]=1;
    }else{
        FORWARDITEM[13]=0;
    }
    if (ui->ByyBtn->isChecked()==1){
        FORWARDITEM[14]=1;
    }else{
        FORWARDITEM[14]=0;
    }
    if (ui->ByzBtn->isChecked()==1){
        FORWARDITEM[15]=1;
    }else{
        FORWARDITEM[15]=0;
    }
    if (ui->BzzBtn->isChecked()==1){
        FORWARDITEM[16]=1;
    }else{
        FORWARDITEM[16]=0;
    }
    if (ui->TxBtn->isChecked()==1){
        FORWARDITEM[17]=1;
    }else{
        FORWARDITEM[17]=0;
    }
    if (ui->TyBtn->isChecked()==1){
        FORWARDITEM[18]=1;
    }else{
        FORWARDITEM[18]=0;
    }
    if (ui->TzBtn->isChecked()==1){
        FORWARDITEM[19]=1;
    }else{
        FORWARDITEM[19]=0;
    }


    QString d=ui->Dedit->text();
    GeoDec=d.toDouble();
    QString i=ui->Iedit->text();
    GeoInc=i.toDouble();
    QString h=ui->ObserHedit->text();
    ObHeight=h.toDouble();
    QString gm=ui->GaussMean->text();
    GaussMean=gm.toDouble();
    QString gs=ui->GaussStd->text();
    GaussStd=gs.toDouble();
    QString ap=ui->AddProportion->text();
    AddProportion=ap.toDouble();
    Forwarding*forwarding=qobject_cast<Forwarding*>(parent());
    forwarding->GetForwardItemList(FORWARDITEM,GeoDec,GeoInc,ObHeight,GaussMean,GaussStd,AddProportion);
    this->close();
}

void forwarditem::CloseDialog(bool)
{
    this->close();
}


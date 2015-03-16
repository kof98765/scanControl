#include "imageentry.h"
#include "ui_imageentry.h"

imageEntry::imageEntry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imageEntry)
{
    ui->setupUi(this);
}

imageEntry::~imageEntry()
{
    delete ui;
}

void imageEntry::on_imgRegister_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void imageEntry::on_takeSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void imageEntry::on_cameraSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void imageEntry::on_triggerSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void imageEntry::on_flashSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void imageEntry::on_lightSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void imageEntry::on_extendLightSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void imageEntry::on_save_clicked()
{

}

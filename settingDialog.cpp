﻿#include "settingDialog.h"
#include "ui_settingDialog.h"
#include <qdebug.h>
#include <QTextCodec>
mySettings::mySettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mySettings)
{
    ui->setupUi(this);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));

    flush_settings();
}

mySettings::~mySettings()
{
    delete ui;
}

void mySettings::flush_settings()
{
    ui->path->setText(set.value("path","D:/image").toString());
    ui->robotIp->setText(set.value("robotIp").toString());
    ui->robotPort->setText(set.value("robotPort").toString());
    ui->cameraIp->setText(set.value("photoIp").toString());
    ui->cameraPort->setText(set.value("photoPort").toString());
    ui->resampleValue->setCurrentIndex(set.value("resampleValue",0).toInt());
    ui->profileCount->setValue(set.value("profileCount",1000).toInt());
    ui->select_device->clear();
    ui->select_device->addItems(set.value("interface","0").toStringList());
    ui->shutter_time->setValue(set.value("shutterTime",100).toInt());
    ui->idle_time->setValue(set.value("idleTime",900).toInt());
    ui->resolution->clear();
    ui->resolution->addItems(set.value("resolutions","0").toStringList());

    ui->median->setCurrentIndex(set.value("median",0).toInt());
    ui->average->setCurrentIndex(set.value("average",0).toInt());
    ui->trigger->setCurrentIndex(set.value("trigger",0).toInt());
    ui->triggerMode->setCurrentIndex(set.value("triggerMode",0).toInt());
    ui->triggerPolarity->setCurrentIndex(set.value("triggerPolarity",0).toInt());
    ui->triggerSource->setCurrentIndex(set.value("triggerSource",0).toInt());
    ui->encoderDivisor->setValue(set.value("encoderDivisor",0).toInt());
    ui->voltage->setCurrentIndex(set.value("voltage",0).toInt());
    ui->digitalInputs->setCurrentIndex(set.value("digitalInputs",0).toInt());

}
void mySettings::on_Button_Yes_clicked()
{
    set.setValue("robotIp",ui->robotIp->text());
    set.setValue("robotPort",ui->robotPort->text().toInt());
    set.setValue("photoIp",ui->cameraIp->text());
    set.setValue("photoPort",ui->cameraPort->text());
    set.setValue("path",ui->path->text());
    set.setValue("idleTime",ui->idle_time->value());
    set.setValue("shutterTime",ui->shutter_time->value());
    set.setValue("profileCount",ui->profileCount->value());
    set.setValue("median",ui->median->currentIndex());
    set.setValue("average",ui->average->currentIndex());
    set.setValue("trigger",ui->trigger->currentIndex());
    set.setValue("triggerMode",ui->triggerMode->currentIndex());
    set.setValue("triggerPolarity",ui->triggerPolarity->currentIndex());
    set.setValue("triggerSource",ui->triggerSource->currentIndex());
    set.setValue("encoderDivisor",ui->encoderDivisor->value());
    set.setValue("voltage",ui->voltage->currentIndex());
    set.setValue("digitalInputs",ui->digitalInputs->currentIndex());

    set.setValue("badMinArea",ui->badMinArea->text());
    set.setValue("badMaxArea",ui->badMaxArea->text());
    set.setValue("badMaxHeight",ui->badMaxHeight->text());
    set.setValue("badMaxWidth",ui->badMaxWidth->text());
    set.setValue("badMinHeight",ui->badMinHeight->text());
    set.setValue("contrast",ui->contrast->text());
    set.setValue("grayDvalue",ui->grayDvalue->text());
    set.setValue("checkMinArea",ui->checkMinArea->text());
    set.setValue("badMinWidth",ui->badMinWidth->text());
    set.setValue("checkMaxArea",ui->checkMaxArea->text());
    set.setValue("erosion",ui->erosion->text());
    set.setValue("badMaxradius",ui->badMaxradius->text());
    set.setValue("minGray",ui->minGray->text());
    set.setValue("maxGray",ui->maxGray->text());
    set.setValue("badMinRadius",ui->badMinRadius->text());
    set.setValue("smothWidth",ui->smothWidth->text());
    set.setValue("smothHeight",ui->smothHeight->text());


    set.sync();
    emit updataSettings();
    close();
}

void mySettings::on_open_clicked()
{

     filePath=QFileDialog::getExistingDirectory(this,QStringLiteral("打开图像目录"),".",QFileDialog::ShowDirsOnly);
     qDebug()<<filePath;
     ui->path->setText(filePath);
}

void mySettings::on_default_2_clicked()
{
    set.setValue("badMinArea",3);
    set.setValue("badMaxArea",200);
    set.setValue("badMaxHeight",40);
    set.setValue("badMaxWidth",40);
    set.setValue("badMinHeight",2);
    set.setValue("contrast",1.0);
    set.setValue("grayDvalue",20);
    set.setValue("checkMinArea",2000000);
    set.setValue("badMinWidth",2);
    set.setValue("checkMaxArea",45700000);
    set.setValue("erosion",200);
    set.setValue("badMaxradius",10);
    set.setValue("minGray",100);
    set.setValue("maxGray",255);
    set.setValue("badMinRadius",1);
    set.setValue("smothWidth",7);
    set.setValue("smothHeight",7);
    set.sync();

    ui->badMinArea->setText(QString::number(3));
    ui->badMaxArea->setText(QString::number(200));
    ui->badMaxHeight->setText(QString::number(40));
    ui->badMaxWidth->setText(QString::number(40));
    ui->badMinHeight->setText(QString::number(2));
    ui->contrast->setText(QString::number(1.0));
    ui->grayDvalue->setText(QString::number(20));
    ui->checkMinArea->setText(QString::number(2000000));
    ui->badMinWidth->setText(QString::number(2));
    ui->checkMaxArea->setText(QString::number(45700000));

    ui->erosion->setText(QString::number(200));
    ui->badMaxradius->setText(QString::number(10));
    ui->minGray->setText(QString::number(100));
    ui->maxGray->setText(QString::number(255));
    ui->badMinRadius->setText(QString::number(1));
    ui->smothWidth->setText(QString::number(7));
    ui->smothHeight->setText(QString::number(7));

}

void mySettings::on_sendButton_clicked()
{
    set.setValue("photoIp",ui->cameraIp->text());
    set.setValue("photoPort",ui->cameraPort->text());
    set.setValue("udpPort",ui->udpPort->text());
    set.sync();

    emit netTest(ui->sendData->text()+"\n");
}
void mySettings::recvData(char *str)
{
    ui->recvData->append(str);
}

void mySettings::on_resampleValue_currentIndexChanged(int index)
{
    set.setValue("resampleValue",index);
}

void mySettings::on_profileCount_valueChanged(int arg1)
{
    set.setValue("profileCount",arg1);
}

void mySettings::on_profile_config_currentIndexChanged(int index)
{
    if(index==4)
        set.setValue("profileConfig",5);
    else if(index==5 | index==6 | index==1)
        set.setValue("profileConfig",1);
    else
        set.setValue("profileConfig",index);

}



void mySettings::on_idle_time_valueChanged(int arg1)
{
    set.setValue("idleTime",arg1);
}

void mySettings::on_shutter_time_valueChanged(int arg1)
{
    set.setValue("shutterTime",arg1);

}
void mySettings::debugMessage(QString str)
{
    ui->debug->append(str);
}

void mySettings::on_select_device_currentIndexChanged(int index)
{
    emit selectDevice(index);
}

void mySettings::on_connecct_clicked()
{
    emit selectDevice(ui->select_device->currentIndex());
}

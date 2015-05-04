#include "settingDialog.h"
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
    qDebug()<<"settings system is run";
}

mySettings::~mySettings()
{
    delete ui;
}

void mySettings::flush_settings()
{
    if(set.value("kingsIP",0)!=0)
    {
        ui->ip0->setValue(set.value("kingsIp",0).toStringList().at(0).toInt());
        ui->ip16->setValue(set.value("kingsIp",0).toStringList().at(1).toInt());
        ui->ip24->setValue(set.value("kingsIp",0).toStringList().at(2).toInt());
        ui->ip32->setValue(set.value("kingsIp",0).toStringList().at(3).toInt());
    }
    ui->miyiCheck->setChecked(!set.value("kingsCheck",false).toBool());
    ui->check_num->setValue(set.value("check_num",4).toInt());
    ui->sendPosComboBox->setCurrentIndex(set.value("sendPos",0).toInt());
    ui->minMeasuringRange->setText(set.value("minMeasuringRange","-7.5").toString());
    ui->maxMeasuringRange->setText(set.value("maxMeasuringRange","7.5").toString());
    ui->imgNum->setValue(set.value("imgNum",8).toInt());
    ui->commandPort->setValue(set.value("commandPort",24691).toInt());
    ui->dataPort->setValue(set.value("dataPort",24692).toInt());
    ui->freq->setValue(set.value("freq",10).toInt());
    set.setValue("dataPort",ui->dataPort->value());
    set.setValue("freq",ui->freq->value());
    ui->path->setText(set.value("path","D:/image").toString());
    ui->robotIp->setText(set.value("robotIp","127.0.0.1").toString());
    ui->robotPort->setText(set.value("robotPort",4000).toString());
    ui->cameraIp->setText(set.value("photoIp").toString());
    ui->cameraPort->setText(set.value("photoPort").toString());
    ui->resampleValue->setCurrentIndex(set.value("resampleValue",0).toInt());
    ui->profileCount->setValue(set.value("profileCount",1000).toInt());
    ui->select_device->clear();
    ui->select_device->addItems(set.value("interface","0").toStringList());

    ui->resolution->clear();
    ui->resolution->addItems(set.value("resolutions","0").toStringList());

    ui->median->setCurrentIndex(set.value("median",0).toInt());
    ui->average->setCurrentIndex(set.value("average",0).toInt());
    ui->trigger->setCurrentIndex(set.value("trigger",0).toInt());
    ui->triggerMode->setCurrentIndex(set.value("triggerMode",0).toInt());
    ui->triggerPolarity->setCurrentIndex(set.value("triggerPolarity",0).toInt());
    ui->triggerSource->setCurrentIndex(set.value("triggerSource",0).toInt());

    ui->voltage->setCurrentIndex(set.value("voltage",0).toInt());
    ui->digitalInputs->setCurrentIndex(set.value("digitalInputs",0).toInt());
    ui->threshold->setValue(set.value("threshold",128).toInt());
    ui->autoThreshold->setCurrentIndex(set.value("autoThreshold",0).toInt());
    ui->exposure->setCurrentIndex(set.value("exposeTime",0).toInt());
    ui->rate->setValue(set.value("rate",25).toInt());
    ui->doubleTurn->setChecked(set.value("doubleTurn",false).toBool());
    ui->usb->setChecked(!set.value("mode").toBool());
}
void mySettings::on_Button_Yes_clicked()
{
    QStringList str;
    str<<QString("%1").arg(ui->ip0->value());
    str<<QString("%1").arg(ui->ip16->value());
    str<<QString("%1").arg(ui->ip24->value());
    str<<QString("%1").arg(ui->ip32->value());
    set.setValue("check_value",ui->check_num->value());
    set.setValue("kingsCheck",ui->kingsCheck->isChecked());
    set.setValue("sendPos",ui->sendPosComboBox->currentIndex());
    set.setValue("minMeasuringRange",ui->minMeasuringRange->text());
    set.setValue("maxMeasuringRange",ui->maxMeasuringRange->text());
    set.setValue("imgNum",ui->imgNum->value());
    set.setValue("doubleTurn",ui->doubleTurn->isChecked());
    set.setValue("mode",ui->Ethernet->isChecked()?1:0);
    set.setValue("kingsIp",str);
    set.setValue("commandPort",ui->commandPort->value());
    set.setValue("dataPort",ui->dataPort->value());
    set.setValue("freq",ui->freq->value());
    set.setValue("robotIp",ui->robotIp->text());
    set.setValue("robotPort",ui->robotPort->text().toInt());
    set.setValue("photoIp",ui->cameraIp->text());
    set.setValue("photoPort",ui->cameraPort->text());
    set.setValue("path",ui->path->text());

    set.setValue("profileCount",ui->profileCount->value());
    set.setValue("median",ui->median->currentIndex());
    set.setValue("average",ui->average->currentIndex());
    set.setValue("trigger",ui->trigger->currentIndex());
    set.setValue("triggerMode",ui->triggerMode->currentIndex());
    set.setValue("triggerPolarity",ui->triggerPolarity->currentIndex());
    set.setValue("triggerSource",ui->triggerSource->currentIndex());

    set.setValue("voltage",ui->voltage->currentIndex());
    set.setValue("digitalInputs",ui->digitalInputs->currentIndex());
    set.setValue("threshold",ui->threshold->value());
    set.setValue("autoThreshold",ui->autoThreshold->currentIndex());
    set.setValue("rate",ui->rate->value());
    set.setValue("exposeTime",ui->exposure->currentIndex());

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
    emit upDataNetwork(ui->robotIp->text(),ui->robotPort->text().toInt());
    close();
}

void mySettings::on_open_clicked()
{

     filePath=QFileDialog::getOpenFileName(this,QStringLiteral("打开图像"),".",("image (*.tif *.bmp *.jpg *.jpeg)"));
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

void mySettings::debugMessage(QString str)
{
    ui->debug->append(str);
}


void mySettings::on_connecct_clicked()
{
    emit selectDevice(ui->select_device->currentIndex());
}

void mySettings::on_testValue_valueChanged(double arg1)
{
    set.setValue("testValue",arg1);
}

void mySettings::on_trigger_currentIndexChanged(int index)
{
    emit setExternTrigger(index);
}

void mySettings::on_exposure_currentIndexChanged(const QString &arg1)
{
    double s=arg1.toDouble();
    double i=(1000-ui->rate->value()*s)/ui->rate->value();
    emit postExposeTime(s*100,i*100);
}

void mySettings::on_rate_valueChanged(int arg1)
{
    double s=ui->exposure->currentText().toDouble();
    double i=(1000-arg1*s)/ui->rate->value();
    emit postExposeTime(s*100,i*100);
}

void mySettings::on_readSet_clicked()
{
    flush_settings();
}

#include "dialogcameralight.h"
#include "ui_dialogcameralight.h"

DialogCameraLight::DialogCameraLight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCameraLight)
{
    ui->setupUi(this);
}

DialogCameraLight::~DialogCameraLight()
{
    delete ui;
}

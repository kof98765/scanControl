#include "laser.h"

Laser::Laser(QObject *parent) :
    QThread(parent)
{
}
void Laser::initDevice(){}

void Laser::startGetData(){}
void Laser::stopGetData(){}
void Laser::flushSettings(){}
void Laser::setDispMode(int mode){}
void Laser::setTransferMode(int mode){}

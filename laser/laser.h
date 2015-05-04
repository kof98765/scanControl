#ifndef LASER_H
#define LASER_H

#include <QThread>

class Laser : public QThread
{
    Q_OBJECT
public:
    Laser(QObject *parent = 0);
    bool testConnect();
signals:
    void heartPack();
    void Error(QString);
    void putImagebyPointer1(double *pdValueZ,int width,int height);
    void putImagebyPointer3(double *x,double *y,double *z,int width,int height);
    void dispSingleFrame(unsigned short *,unsigned short *,double *x,double *y,int size);
public slots:
    virtual void initDevice();

    virtual void startGetData();
    virtual void stopGetData();
    virtual void flushSettings();
    virtual void setDispMode(int mode);
    virtual void setTransferMode(int mode);
};

#endif // LASER_H

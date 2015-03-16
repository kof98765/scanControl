#ifndef HALCONCLASS_H
#define HALCONCLASS_H
#include "HalconCpp.h"
#include <QWindow>
#include <QDebug>
#include <QThread>
using namespace Halcon;

class halconClass:public QThread
{
    Q_OBJECT
public:

    halconClass(QObject *parent = 0);
    void pointDetect();
    void zoomIn();
    void zoomOut();
    void saveResult();
    void startThread();

    void one_white_line();
    void two_black_line();
    void three_black_block();
    void four_white_block();
    void five_black_block();
    void six_senve_night_white_line();
    void eight_white_line();
    void sixteen_white_line();
    void seventeen_white_line();

    void E128_detect();

    void stopThread();
    void open_the_window(int handle,int width,int height);
    HTuple WindowHandle;
    void disp_img(QString);
    void moveImg(int x,int y);
    void setMinMaxLength(double min,double max);
    void setMinMaxArea(double min,double max);
    void setUseDefault(bool def);
    void set_pos(int x,int y);
    typedef void (halconClass::*detect_action)();
    static detect_action menu[];
protected:
    void run();
private:
    QString fileName;
    int img_width,img_height;
    QMutex locker;
    bool stopped;
    int count;
    int posX,posY;
    double scale;
    int win_width,win_height;
    bool useDefault;

    Hobject result_img,Image;


    HTuple minLength;
    HTuple maxLength;
    HTuple minArea;
    HTuple maxArea;



public slots:

signals:
    void detectFinish();
    void stopMove();
    void sumResult(int type,int num);
    void badResult(int type,int x,int y,int width,int height,int length);

};

#endif // HALCONCLASS_H

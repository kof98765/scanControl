﻿#ifndef HALCONCLASS_H
#define HALCONCLASS_H
#include "HalconCpp.h"
#include <QWindow>
#include <QDebug>
#include <QThread>
#include <QSettings>
#include <QTime>
#include <fstream>
using namespace std;
using namespace Halcon;

class halconClass:public QThread
{
    Q_OBJECT
public:

    halconClass(QObject *parent = 0);
    void pointDetect();

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
    void readMTX(QString str);
    void RectHeightSub();


    void stopThread();
    void open_the_window(int handle,int width,int height);
    HTuple WindowHandle;
    void threedControl(double lastRow, double lastCol, double Row, double Column,QString mode);
    void reset();
    void moveImg(int x,int y);
    void setMinMaxLength(double min,double max);
    void setMinMaxArea(double min,double max);
    void setUseDefault(bool def);
    void set_pos(int x,int y);
    void readSettings();
    void setMode(QString str);
    void clearRect();
    int step;
    typedef void (halconClass::*detect_action)();
    detect_action menu[9];
protected:
    void run();
private:
    QString fileName;
    QSettings set;
    QString path;
    HTuple lastRow, lastCol;
    int img_width,img_height;
    QMutex locker;
    bool stopped;
    int count;
    int posX,posY;
    double scale;
    int win_width,win_height;
    bool useDefault;
    bool is3D;

    Hobject result_img,Image,RGBImage;
    QList<Hobject*> rectList;
    HTuple minLength;
    HTuple maxLength;
    HTuple minArea;
    HTuple maxArea;

    int badMinArea;
    int badMaxArea;
    int badMaxHeight;
    int badMaxWidth;
    int badMinHeight;
    double contrast;
    int grayDvalue;
    int checkMinArea;
    int badMinWidth;
    int checkMaxArea;
    int erosion;
    int badMaxradius;
    int minGray;
    int maxGray;
    int badMinRadius;
    int smothWidth;
    int smothHeight;
    bool hasData;
    QTime time;


public slots:
    void E128_detect();
     void disp_img();
     void zoomIn();
     void zoomOut();
    void read_img(QString str);
    void getImagebyPointer1(double *pdValueZ,int width,int height);
     void getImagebyPointer3(double *x,double *y,double *z,int width,int height);
    void close_the_window();
signals:
    void detectFinish();
    void stopMove();
    void sumResult(int type,int num);
    void badResult(int type,int x,int y,int width,int height,int length);
    void dispImg();
    void sendHeightSub(double x,double y,double x2,double y2,double min,double max);

};

#endif // HALCONCLASS_H

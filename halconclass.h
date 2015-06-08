﻿#ifndef HALCONCLASS_H
#define HALCONCLASS_H
#include "HalconCpp.h"
#include "HIOStream.h"
#include <QWindow>
#include <QDebug>
#include <QThread>
#include <QSettings>
#include <QTime>
#include <QFile>
#include <fstream>
#include <QTextCodec>
#include <iostream>



using namespace std;
using namespace Halcon;
void CPPExpDefaultExceptionHandler(const Halcon::HException& except);
typedef struct Roi{
    double x;
    double y;
    double endX;
    double endY;
    double Phi;
    double Length1;
    double Length2;
    int func;
    int index;
    int team;
    double min;
    double max;
    int color;
    int drawType;
    char* name;
}Roi;
Q_DECLARE_METATYPE(Roi)


class halconClass:public QThread
{
    Q_OBJECT
public:

    halconClass(QObject *parent = 0);
    struct VectorInfo{
        float _ratioX;
        float _ratioY;
        float _ratioZ;
        float _constant;
        float _curvature;
        float _reserve;
    };

    struct pointXYZ
    {
        float _PointX;
        float _PointY;
        float _PointZ;
    };


    typedef int (*CT)(Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,HTuple hv_mode,HTuple hv__min,HTuple hv__max,HTuple *hv_TemplateID);
    typedef int (*byteMapperTable)(Halcon::Hobject ho_inImage,Halcon::Hobject *ho_outImage,HTuple hv__min,HTuple hv__max);
    typedef int (*compute_PointNormal)(float iX[],float iY[],float iZ[],int length,VectorInfo* _vectorInfo);
    /*使用网友改编的算法 返回平面方程，Z值永远为1*/
    typedef int (*compute_PointNormal2)(float iX[],float iY[],float iZ[],int length,VectorInfo* _vectorInfo);

    /*用第一种方法计算平面度*/
    typedef int (*Calculate_Flatness)(float iX[],float iY[],float iZ[],int length, double &_result);
    /*用第二种方法计算平面度*/
    typedef int (*Calculate_Flatness2)(float iX[],float iY[],float iZ[],int length, double &_result);
    /*计算点到面的距离*/
    typedef int (*Distance_point2plane)(pointXYZ _point,VectorInfo _vectorInfo,double &_result);

    void startThread();
    void readMTX(QString str);

    void stopThread();
    void open_the_window(int handle,int width,int height);
    HTuple WindowHandle;
    void threedControl(double lastRow, double lastCol, double Row, double Column,QString mode);
    void reset();
    void moveImg(int x,int y);
    void setUseDefault(bool def);
    void set_pos(int x,int y);
    void readSettings();
    void setMode(QString str);
    void clearRect();
    void resizePart();
    HINSTANCE hInstance;
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
    double xScale,yScale,scale;
    int win_width,win_height;
    bool useDefault;
    bool is3D;
    double *imgData;
    int recvCount;

    Hobject result_img,Image,RGBImage,tmpImage;

    QList<QPointF> basePointList;
    bool hasData;
    bool isLoadFile;
    int index;
    HTuple locateRow;
    HTuple locateColumn;
    HTuple locateAngle;
    HTuple HomMat2D;

    HTuple centerX,centerY;

    QList<Hobject*> imgList;
    QMap<int,QList<Hobject>> unitList;
    QTime time;
    Hobject tmpObj;
    QMap<QString,QVariant> roiList;
    QMap<QString,QVariant> dataList;
    QMap<QString,QList<HTuple>> locateList;
    QMap<QString,HTuple> matList;

public slots:
    void test();
    void clearData();
     void disp_img();
     void zoomIn();
     void zoomOut();
     QPoint getPoint();
     QPointF pointToLine(const QPointF &pt1, const QPointF &pt2, const QPointF &pt3);
     void calculateBasePoint();
     QPointF findTwoPointOneLineBasePoint(QMap<QString,QVariant>);
     QPoint findCenter(Hobject image,HTuple Row,HTuple Column,HTuple Row2,HTuple Column2);
     QPoint findCenter(Hobject image,double Row,double Column,double Row2,double Column2);
     QPointF findRectCenter(QMap<QString,QVariant>);
     void twoPointOneLineBasePoint(QMap<QString,QVariant> map);
     void oneRectBasePoint(QMap<QString,QVariant> map);
     void disp_xld(HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2);
     void disp_xld(double Row,double Column,double Row1,double Column1);
     void disp_xld(HTuple Row,HTuple Column,HTuple Phi,HTuple Length1,HTuple Length2);
     void disp_xld(double Row,double Column,double Phi,double Length1,double Length2);
    void read_img(QString str);
    void getImagebyPointer1(double *pdValueZ,int width,int height);

    void close_the_window();
    void drawRect(QMap<QString,QVariant> map);
    void drawToFindBasePoint(QMap<QString,QVariant> map);
    void calculate();
    void delRect(QString);
    void RectHeightSub(int team);
    void pointToPoint(int team);
    void createTemplate(QMap<QString,QVariant>);
    QPointF matchTemplate(QMap<QString,QVariant>);
    void calculatePlaneness(int team);
    void selectImg(int index);
    void compoundImg(int xOffset,int yOffset);
signals:
    void detectFinish();
    void stopMove();
    void clearMemory();
    void sumResult(int type,int num);
    void badResult(int type,int x,int y,int width,int height,int length);
    void dispImg();
    void sendHeightSub(int,double,double,double);
    void sendHeightSub(QString,double,double,double);
    void flushRoiList(QStringList list);
    void sendPlaneness(int ,double);
    void Error(QString);
    void Warning(QString str);
    void addImg(Hobject *);
    void deleteImg(int index);
    void deleteAllImg();
    void reConnect();
    void reportBasePoint(double x,double y);


};

#endif // HALCONCLASS_H

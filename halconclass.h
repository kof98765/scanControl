#ifndef HALCONCLASS_H
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
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include "pcl/PCL_Library_Dll.h"
#include "calculategroup.h"
using namespace std;
using namespace Halcon;
void CPPExpDefaultExceptionHandler(const Halcon::HException& except);




class halconClass:public QThread
{
    Q_OBJECT
public:

    halconClass(QObject *parent = 0);
    typedef int (*ComputePointNormal2)(PointCloud::Ptr &cloud, Vector4f &normal_vec);
    typedef int (*Dis_point2plane)(PointT &point,Vector4f &normal_vec,double &_result);
    typedef int (*Calculate)(PointCloud::Ptr &, double &);
    typedef int (*CalculateFlatness2) (PointCloud::Ptr &cloud, double &);
    typedef int (*GetChildPoint)(PointCloud::Ptr &inCloud,Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,PointCloud::Ptr outCloud);
    typedef int (*Points2Cloud3)(float* iX,float* iY,float* iZ,int iLength,PointCloud::Ptr inCloud);
    typedef int (*CalculateFlatness)(PointCloud::Ptr &inCloud, double &_result);
    typedef int (*CT)(Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,HTuple hv_mode,HTuple hv__min,HTuple hv__max,HTuple *hv_TemplateID);
    typedef int (*byteMapperTable)(Halcon::Hobject ho_inImage,Halcon::Hobject *ho_outImage,HTuple hv__min,HTuple hv__max);


    void startThread();
    void readMTX(QString str);
    void planePoint(int team);
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
    PointCloud::Ptr *inCloud;
    Hobject result_img,Image,RGBImage,tmpImage;

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
    bool isLoadFile;
    int index;
    HTuple locateRow;
    HTuple locateColumn;
    HTuple locateAngle;
    HTuple HomMat2D;

    HTuple centerX,centerY;

    QList<Hobject*> imgList;

    QTime time;

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
    void read_img(QString str);
    void getImagebyPointer1(double *pdValueZ,int width,int height);
     void getImagebyPointer3(double *x,double *y,double *z,int width,int height);
    void close_the_window();
    void drawRect(QMap<QString,QVariant> map);
    void calculate();
    void delRect(QString);
    void RectHeightSub(int team);
    void pointToPoint(int team);
    void createTemplate(int team);
    void matchTemplate(int team);
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
    void addImg(Hobject *);
    void deleteImg(int index);
    void deleteAllImg();
    void reConnect();


};

#endif // HALCONCLASS_H

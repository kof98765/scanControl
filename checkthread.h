#ifndef CHECKTHREAD_H
#define CHECKTHREAD_H

#include "param.h"
#include <QThread>
#include <QMutex>
#include <HalconCpp.h>
using namespace Halcon;

class checkThread : public QThread
{
    Q_OBJECT
public:
    explicit checkThread(QObject *parent = 0);

    void startThread();
    void stopThread();

    void changeFilePath(HTuple path);

protected:
    void run();

public:    
    HTuple winId1,winId2;
    HTuple hv_ImageFile;

    HTuple m_YM_AreaSmall, m_YM_AreaBig, m_YM_smoothWidth, m_YM_SmoothHeight, m_YM_OffSet;

private:
    void initVision();
    void fillUpData(QString type,int num,int sum,double area,double width,double length);

private:
    bool stopped;
    QMutex locker;
    int count;
    QByteArray recv;
    DATA    sent;

    Hobject ho_ImageAmp, ho_ImageCurv,Image_Base;
    HTuple  AcqHandle;

//    // Local iconic variables
//    Hobject  ho_Region, ho_RegionFillUp;
//    Hobject  ho_ConnectedRegions, ho_ImageReduced, ho_ImageMean;
//    Hobject  ho_RegionDynThresh, ho_SelectedRegions, ho_RegionUnion;
//    Hobject  ho_RegionDilation, ho_RegionErosion, ho_ConnectedRegions1;
//    Hobject  ho_Rectangle, ho_ObjectSelected;

//    // Local control variables
//    HTuple  hv_Mean1, hv_Deviation1, hv_Row, hv_Column;
//    HTuple  hv_Phi, hv_Length1, hv_Length2, hv_Mean, hv_Deviation;
//    HTuple  hv_Number, hv_Dev_Mean, hv_Dev_Deviation;


    // Local iconic variables
    Hobject  ho_Region, ho_RegionFillUp, ho_ConnectedRegions, ho_RegionCheck;
    Hobject  ho_ImageReducedA, ho_ImageMean, ho_ImageReducedM;
    Hobject  ho_RegionDynThresh, ho_SelectedRegions, ho_RegionUnion;
    Hobject  ho_RegionDilation, ho_RegionErosion, ho_ConnectedRegions1;
    Hobject  ho_Rectangle, ho_ObjectSelected, ho_ObjectSelected1;
    Hobject  ho_Rectangle1, ho_RegionCheckCurv, ho_ImageReduced;
    Hobject  ho_Lines, ho_UnionContours, ho_SelectedContours;
    Hobject  ho_Circle, ho_RegionCheckCurv1, ho_Edges, ho_ContoursSplit;
    Hobject  ho_Lines1, ho_RegionXLD, ho_Dilation;


    // Local control variables
    HTuple  hv_k, hv_j, hv_i, hv_Mean1, hv_Deviation1;
    HTuple  hv_Number1, hv_Row, hv_Column, hv_Phi, hv_Length1;
    HTuple  hv_Length2, hv_Mean, hv_Deviation, hv_Number, hv_M;
    HTuple  hv_D, hv_Dev_Mean, hv_Dev_Deviation, hv_Area, hv_Row2;
    HTuple  hv_Column2, hv_Row1, hv_Column1, hv_Phi1, hv_Length11;
    HTuple  hv_Length21, hv_Radius, hv_Mean3, hv_Deviation3;
    HTuple  hv_Number_White, hv_Mean2, hv_Deviation2, hv_Number_Yuanfan,hv_Number2;
    HTuple  hv_AbsoluteHisto, hv_RelativeHisto, hv_MinThresh, hv_MaxThresh;
    HTuple  hv_Length, hv_Length_xld, hv_PointOrder;



signals:
    void sendData(DATA);
    void add_bar(int num);
public slots:

};

#endif // CHECKTHREAD_H

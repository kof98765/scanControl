#ifndef PROFILEGET_H
#define PROFILEGET_H

#include <QObject>

#include <QDebug>
#include <fstream>
#define MAX_INTERFACE_COUNT 5
#define MAX_RESOULUTIONS       6
#include "getProfiles/scanControlDataTypes.h"
#include "getProfiles/InterfaceLLT_2.h"
#include <QSettings>
#include <QFile>
#include <QTime>
#include <QPixmap>
#include <QThread>
#define MAX_INTERFACE_COUNT    5
#define MAX_RESOULUTIONS       6

using namespace std;
static void *object;
void __stdcall newProfile(const unsigned char* pucData, unsigned int uiSize, void* pUserData);
class profileGet : public QThread
{
    Q_OBJECT
public:
    profileGet(QObject *parent = 0);

    ~profileGet();
    void initDevice();

    CInterfaceLLT* m_pLLT;
    unsigned int m_uiResolution;
    TScannerType m_tscanCONTROLType;
    unsigned int m_uiNeededProfileCount;
    unsigned int m_uiRecivedProfileCount;
    unsigned int m_uiProfileDataSize;
    unsigned int m_uiPacketSizeMAX;
    unsigned int m_uiPacketSizeMIN;
    unsigned int uiWidth, uiHeight;
    unsigned long filter;
    unsigned long trigger;
    unsigned long IOConfigure;
    unsigned long Processing;
    unsigned int mode;//0为外部触发,1为内部触发,2为单帧模式,3为视频模式
    std::vector<unsigned char> vucVideoBuffer;
    std::vector<double> vdValueX;
    std::vector<double> vdValueZ;
    std::vector<double> tmp;
    std::vector<unsigned short> vdValueIntensity;
    HANDLE m_hProfileEvent;
    std::vector<unsigned char> m_vucProfileBuffer;
    std::vector<unsigned char> m_vucProfileBuffer2;
    void OnError(const char* szErrorTxt, int iErrorValue);
    void DisplayProfile(unsigned short *pdValueIntensity,double *pdValueX, double *pdValueZ, unsigned int uiResolution);
    void DisplayTimestamp(unsigned char *pucTimestamp);
    string Double2Str(double dValue);
    void preGetDate();
    static void sendSignal(const unsigned char* pucData, unsigned int uiSize, void* pUserData);
    QSettings set;
    QTime time;
    QFile f;
    QList<double> data;
protected:
    void run();
private:
     bool bConnected;
     bool isReady;
     bool isExternalTrigger;
     int index;
     unsigned long uiShutterTime;
     unsigned long uiIdleTime;
     unsigned int uiInterfaceCount;
     unsigned long threshold;
     std::vector<unsigned int> vuiInterfaces;
     std::vector<DWORD> vdwResolutions;

signals:
    void DisplayProfile(double *pdValueX, double *pdValueZ, unsigned int uiResolution);
    void dispZ(QString);
    void Error(QString);
    void putImagebyPointer1(double *pdValueZ,int width,int height);
    void putImagebyPointer3(double *x,double *y,double *z,int width,int height);

    void dispSingleFrame(unsigned short *,unsigned short *,double *x,double *y,int size);
    void setData(double*,int);
    void dispFrame(unsigned char*,int);
    void heartPack();
public slots:
    void getNewProfile(const unsigned char* pucData, unsigned int uiSize, void* pUserData);
    void getSingleFrame();
    void getVideoFrame();
    void startVedio();
    void stopVedio();
    void startTrigger();
    void stopTrigger();
    void startSingleFrame();
    void stopSingleFrame();
    void flushSettings();
    void GetProfiles_Callback();
    void readSettings();
    void selectDevice(int index);
    void setExposeTime(int s,int i);
    void setExternTrigger(int index);
    QList<double> getList();
};

#endif // PROFILEGET_H

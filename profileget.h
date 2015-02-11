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
#define MAX_INTERFACE_COUNT    5
#define MAX_RESOULUTIONS       6

using namespace std;
static void *object;
void __stdcall newProfile(const unsigned char* pucData, unsigned int uiSize, void* pUserData);
class profileGet : public QObject
{
    Q_OBJECT
public:
    profileGet(QObject *parent = 0);

    ~profileGet();
    void initDevice();
    void GetProfiles_Callback();
    CInterfaceLLT* m_pLLT;
    unsigned int m_uiResolution;
    TScannerType m_tscanCONTROLType;
    unsigned int m_uiNeededProfileCount;
    unsigned int m_uiRecivedProfileCount;
    unsigned int m_uiProfileDataSize;
    unsigned int m_uiPacketSizeMAX;
    unsigned int m_uiPacketSizeMIN;
    unsigned int uiWidth, uiHeight;
    std::vector<unsigned char> vucVideoBuffer;
    HANDLE m_hProfileEvent;
    std::vector<unsigned char> m_vucProfileBuffer;
    void OnError(const char* szErrorTxt, int iErrorValue);
    void DisplayProfile(unsigned short *pdValueIntensity,double *pdValueX, double *pdValueZ, unsigned int uiResolution);
    void DisplayTimestamp(unsigned char *pucTimestamp);
    string Double2Str(double dValue);
    static void sendSignal(const unsigned char* pucData, unsigned int uiSize, void* pUserData);
    QSettings set;
    QTime time;

private:
     bool bConnected;
     bool isReady;
     unsigned int uiShutterTime;
     unsigned int uiIdleTime;
     unsigned int uiInterfaceCount;
     std::vector<unsigned int> vuiInterfaces;
     std::vector<DWORD> vdwResolutions;

signals:
    void DisplayProfile(double *pdValueX, double *pdValueZ, unsigned int uiResolution);
    void dispZ(QString);
    void Error(QString);
    void putImagebyPointer1(double *pdValueZ,int width,int height);
    void putImagebyPointer3(double *x,double *y,double *z,int width,int height);
    void dispSingleFrame(double *x,double *y,int size);
    void setData(double*,int);
    void dispFrame(unsigned char*,int);
public slots:
    void getNewProfile(const unsigned char* pucData, unsigned int uiSize, void* pUserData);
    void getSingleFrame();
    void getVideoFrame();
    void startVedio();
    void stopVedio();
    void startSingleFrame();
    void stopSingleFrame();
    void flushSettings();

};

#endif // PROFILEGET_H

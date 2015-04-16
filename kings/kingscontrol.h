#ifndef KINGSCONTROL_H
#define KINGSCONTROL_H
#include <afx.h>
#include "afxcmn.h"
#include "afxwin.h"
#include <QThread>
#include "NativeMethods.h"
#include "laser.h"
#include "resource.h"
#include <math.h>
#include <QSettings>
#include <QDebug>
#include <QTimer>
#define _cdecl
using namespace std;
static void* obj;
void _cdecl _callback(BYTE* buffer, DWORD size, DWORD count, DWORD notify, DWORD user);
class kingsControl : public QThread
{
    Q_OBJECT
public:
    kingsControl(QObject *parent = 0);
    ~kingsControl();
    int commandPort;
    int dataPort;
    unsigned int ipAddress;
    int receiveCount;
    LJV7IF_ETHERNET_CONFIG _ethernetConfig;
    static const int DEVICE_ID = 0;
    static const int MAX_PROFILE_COUNT = 3200;
    DWORD frequency;
    int transferMode;
    int displayMode;
    bool isConnected;
    void new_callback(BYTE* buffer, DWORD size, DWORD count, DWORD notify, DWORD user);
private:
    QSettings set;
    std::vector<double> vdValueZ;
    std::vector<DWORD> profileBuf;
    std::vector<double> x;
    QTimer timer;

signals:
    void heartPack();
    void stopSignal();
    void Error(QString);
    void putImagebyPointer1(double *pdValueZ,int width,int height);
    void putImagebyPointer3(double *x,double *y,double *z,int width,int height);
    void dispSingleFrame(unsigned short *,unsigned short *,double *x,double *y,int size);
public slots:
    void initDevice();
    void usbMode();
    void EthernetMode();
    void startGetEthernetData();
    void startGetUsbData();
    void startGetData();
    void stopGetData();
    void flushSettings();
    void setDispMode(int mode);
    void setTransferMode(int mode);
    void GetBatchProfile();


};

#endif // KINGSCONTROL_H
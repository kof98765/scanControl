#include "kingscontrol.h"

kingsControl::kingsControl(QObject *parent) :
    QThread(parent)
{
    obj=(void *)this;
    commandPort=24691;
    dataPort=24692;
    transferMode=1;
    displayMode=1;
    frequency=10;
    receiveCount=0;
    qDebug()<<"init kings";
    CRc::Rc rc = CRc::Ok;
        // Initialize the DLL.
    rc = (CRc::Rc)LJV7IF_Initialize();
    if (!NativeMethods::CheckReturnCode(rc)) return;
}
kingsControl::~kingsControl()
{

}
void kingsControl::initDevice()
{

    flushSettings();
}
void kingsControl::flushSettings()
{
    int mode=set.value("mode",1).toInt();
    setTransferMode(mode);
    transferMode=mode;
    frequency=set.value("freq",10).toInt();
    commandPort=set.value("commandPort",24691).toInt();
    dataPort=set.value("dataPort",24692).toInt();
    qDebug()<<"mode"<<transferMode;
    qDebug()<<"frequency"<<frequency;
    qDebug()<<"commandPort"<<commandPort;
    qDebug()<<"dataPort"<<dataPort;

}
void kingsControl::usbMode()
{
    LJV7IF_StopHighSpeedDataCommunication(DEVICE_ID);
    LJV7IF_HighSpeedDataCommunicationFinalize(DEVICE_ID);
    CRc::Rc rc = CRc::Ok;
    rc = (CRc::Rc)LJV7IF_UsbOpen(DEVICE_ID);
    if (!NativeMethods::CheckReturnCode(rc)) return;
    qDebug()<<"usb mode is init";
}
void kingsControl::EthernetMode()
{
    CRc::Rc rc = CRc::Ok;
    LJV7IF_StopHighSpeedDataCommunication(DEVICE_ID);
    LJV7IF_HighSpeedDataCommunicationFinalize(DEVICE_ID);
    QStringList str=set.value("kingsIp","0").toStringList();
    qDebug()<<str;
    _ethernetConfig.abyIpAddress[0]=str.at(3).toInt();
    _ethernetConfig.abyIpAddress[1]=str.at(2).toInt();
    _ethernetConfig.abyIpAddress[2]=str.at(1).toInt();
    _ethernetConfig.abyIpAddress[3]=str.at(0).toInt();

    _ethernetConfig.wPortNo = commandPort;

    LJV7IF_ETHERNET_CONFIG *p=&_ethernetConfig;
    rc = (CRc::Rc)(LJV7IF_EthernetOpen(DEVICE_ID,p));
    if (!NativeMethods::CheckReturnCode(rc)) return;
    qDebug()<<"etherneMode is init";
}
void kingsControl::startGetData()
{
    receiveCount=0;
    flushSettings();
    if(transferMode==1)
        startGetEthernetData();
    else
        startGetUsbData();
}
void kingsControl::setTransferMode(int mode)
{
    stopGetData();
    transferMode=mode;
    if(transferMode==0)
       usbMode();
    else
        EthernetMode();
    startGetData();
}/*
    函数名:setDispMode
    参数:mode
    描述:mode=0时,发送单帧
        mode=1时,发送profileCount大小的帧
*/
void kingsControl::setDispMode(int mode)
{
    stopGetData();
    displayMode=mode;
    startGetData();
}
void kingsControl::startGetUsbData()
{
    qDebug()<<"start usb";

    CRc::Rc rc = CRc::Ok;
    LJV7IF_HIGH_SPEED_PRE_START_REQ req;
    DWORD threadId = (DWORD)DEVICE_ID;
    usbMode();
    rc = (CRc::Rc)LJV7IF_HighSpeedDataUsbCommunicationInitalize(DEVICE_ID, &_callback, frequency, threadId);
    if (!NativeMethods::CheckReturnCode(rc))
    {
        qDebug()<<"LJV7IF_HighSpeedDataUsbCommunicationInitalize";
        return;
    }

    req.bySendPos = 0;

    // High-speed data communication start prep
    LJV7IF_PROFILE_INFO profileInfo;
    rc = (CRc::Rc)LJV7IF_PreStartHighSpeedDataCommunication(DEVICE_ID, &req, &profileInfo);
    if (!NativeMethods::CheckReturnCode(rc))
    {
        qDebug()<<"LJV7IF_PreStartHighSpeedDataCommunication";
        return;
    }

    // Start high-speed data communication.
    rc = (CRc::Rc)LJV7IF_StartHighSpeedDataCommunication(DEVICE_ID);
    if (!NativeMethods::CheckReturnCode(rc))
    {
        qDebug()<<"LJV7IF_StartHighSpeedDataCommunication";
        return;
    }
    qDebug()<<"start usb finish";
}
void kingsControl::startGetEthernetData()
{
    qDebug()<<"start ethernet";

    CRc::Rc rc = CRc::Ok;
    LJV7IF_HIGH_SPEED_PRE_START_REQ req;
    DWORD threadId = (DWORD)DEVICE_ID;
    EthernetMode();
    LJV7IF_ETHERNET_CONFIG *p=&_ethernetConfig;
    rc = (CRc::Rc)LJV7IF_HighSpeedDataEthernetCommunicationInitalize(DEVICE_ID,p,dataPort, &_callback, frequency, threadId);
    if (!NativeMethods::CheckReturnCode(rc))
    {
        qDebug()<<"LJV7IF_HighSpeedDataEthernetCommunicationInitalize";
        return;
    }


    req.bySendPos = 2;


    // High-speed data communication start prep
    LJV7IF_PROFILE_INFO profileInfo;
    rc = (CRc::Rc)LJV7IF_PreStartHighSpeedDataCommunication(DEVICE_ID, &req, &profileInfo);

    if (!NativeMethods::CheckReturnCode(rc))
    {
        qDebug()<<"LJV7IF_PreStartHighSpeedDataCommunication";
        return;
    }

    vdValueZ.resize(profileInfo.wProfDataCnt*sizeof(DWORD));
    x.resize(profileInfo.wProfDataCnt);
    qDebug()<<"profDataCnt"<<profileInfo.wProfDataCnt;
    // Start high-speed data communication.
    rc = (CRc::Rc)LJV7IF_StartHighSpeedDataCommunication(DEVICE_ID);
    if (!NativeMethods::CheckReturnCode(rc))
    {
        qDebug()<<"LJV7IF_StartHighSpeedDataCommunication";
        return;
    }
    qDebug()<<"start net finish";
}

void kingsControl::stopGetData()
{
    // Stop high-speed data communication.
    CRc::Rc rc = (CRc::Rc)LJV7IF_StopHighSpeedDataCommunication(DEVICE_ID);
    if (rc != CRc::Ok)
    {

        qDebug("StopHighSpeedDataCommunication,Error: 0x%08x ",rc);

        // Exit high-speed data communication.
        rc = (CRc::Rc)LJV7IF_HighSpeedDataCommunicationFinalize(DEVICE_ID);
        if (rc != CRc::Ok)
            qDebug("HighSpeedDataCommunicationFinalize,Error: 0x%08x ",rc);
    }
    qDebug()<<"stop";
}
void kingsControl::new_callback(BYTE* buffer, DWORD size, DWORD count, DWORD notify, DWORD user)
{
    // Received data is in BYTE units, set as a group of INT units.
    DWORD profileSize = size / sizeof(DWORD);

    //得到每一帧的数据
    // Retain profile data
    //qDebug()<<"recv:"<<count;
    //qDebug()<<"size"<<size;
    emit heartPack();
    for (int i = 0; i < count; i++)
    {

        profileBuf.resize(profileSize);
        memcpy(&profileBuf[0],buffer, profileSize*sizeof(DWORD));
        buffer+=profileSize*sizeof(DWORD);
        //保存到文件
        //LJV7IF_PROFILE_INFO profileInfo;
        ProfileData _profileData;
        _profileData.SetData(&profileBuf[0],profileSize);
        for(int i=0;i<_profileData.profSize;i++)
        {

            vdValueZ[receiveCount*_profileData.profSize+i]=(int)_profileData._profileValue[i]*0.00001;
            double v=vdValueZ[receiveCount*_profileData.profSize+i];
            if(v>200|v<-200)
                vdValueZ[receiveCount*_profileData.profSize+i]=0;

            //qDebug()<<vdValueZ[j][i];

        }

        //_profileData.SaveProfile("filepath");

        if(displayMode==0)
        {
            emit dispSingleFrame(0,0,&x[0],&vdValueZ[0],_profileData.profSize);

        }
        receiveCount++;

        if((receiveCount+1)==set.value("profileCount").toInt())
        {


            for(int i=0;i<_profileData.profSize;i++)
            {
                 x[i]=i*0.01;
            }

            //_profileData.SaveProfile("filepath");

            if(displayMode==1)
            {
                emit putImagebyPointer1(&vdValueZ[0],_profileData.profSize,receiveCount+1);


            }
            receiveCount=0;

        }

    }

    //delete[]bufferArray;
}

void _cdecl _callback(BYTE* buffer, DWORD size, DWORD count, DWORD notify, DWORD user)
{
    kingsControl *_Sample=(kingsControl*)obj;
    _Sample->new_callback( buffer, size, count,  notify,  user);
}


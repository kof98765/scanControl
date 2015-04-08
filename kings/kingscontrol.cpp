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
    isConnected=false;
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
    //setTransferMode(mode);
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

    CRc::Rc rc = CRc::Ok;
    rc = (CRc::Rc)LJV7IF_UsbOpen(DEVICE_ID);
    if (rc!=CRc::Ok)
    {
        qDebug()<<(QString("UsbOpen:0x%1").arg(rc,0,16));
        isConnected=false;
        return;
    }
    qDebug()<<"usb mode is init";

}
void kingsControl::EthernetMode()
{


    QStringList str=set.value("kingsIp","").toStringList();
    if(str.isEmpty())
        str<<"10"<<"0"<<"168"<<"192";
    qDebug()<<str;
    _ethernetConfig.abyIpAddress[0]=str.at(3).toInt();
    _ethernetConfig.abyIpAddress[1]=str.at(2).toInt();
    _ethernetConfig.abyIpAddress[2]=str.at(1).toInt();
    _ethernetConfig.abyIpAddress[3]=str.at(0).toInt();

    _ethernetConfig.wPortNo = commandPort;

    LJV7IF_ETHERNET_CONFIG *p=&_ethernetConfig;
    CRc::Rc rc = (CRc::Rc)(LJV7IF_EthernetOpen(DEVICE_ID,p));
    if (rc!=CRc::Ok)
    {
        qDebug()<<(QString("EthernetOpen:0x%1").arg(rc,0,16));
        isConnected=false;
        return;
    }

    rc = CRc::Ok;

    LJV7IF_TARGET_SETTING settings;
    settings.byType=0x2;
    settings.byCategory=0x0;
    settings.byItem=0x0;
    settings.byTarget1=0x0;
    int i=0;
    DWORD error;
    isConnected=true;
    //rc = (CRc::Rc)LJV7IF_SetSetting(DEVICE_ID,LJV7IF_SETTING_DEPTH_WRITE,settings,&i,4,&error);
    //if (!NativeMethods::CheckReturnCode(rc)) return;
    //rc = (CRc::Rc)LJV7IF_GetSetting(DEVICE_ID,LJV7IF_SETTING_DEPTH_WRITE,settings,&i,4);
   // if (!NativeMethods::CheckReturnCode(rc)) return;
    //qDebug("%x",i);
    //rc=(CRc::Rc)LJV7IF_ReflectSetting(DEVICE_ID,LJV7IF_SETTING_DEPTH_SAVE,&error);
    //if (!NativeMethods::CheckReturnCode(rc)) return;
    //qDebug()<<"etherneMode is init";
}
void kingsControl::startGetData()
{

    receiveCount=0;
    flushSettings();
    if(transferMode==0)
        startGetUsbData();
    else
        startGetEthernetData();

}
void kingsControl::setTransferMode(int mode)
{

    transferMode=mode;
    if(transferMode==0)
       usbMode();
    else
        EthernetMode();

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
    usbMode();
    if(!isConnected)
        return;
    LJV7IF_StopHighSpeedDataCommunication(DEVICE_ID);
    LJV7IF_HighSpeedDataCommunicationFinalize(DEVICE_ID);
    LJV7IF_HIGH_SPEED_PRE_START_REQ req;
    DWORD threadId = (DWORD)DEVICE_ID;

    rc = (CRc::Rc)LJV7IF_HighSpeedDataUsbCommunicationInitalize(DEVICE_ID, &_callback, frequency, threadId);
    if (rc!=CRc::Ok)
    {
        emit Error(QString("HighSpeedDataUsbCommunicationInitalize:0x%1").arg(rc,0,16));
        return;
    }

    req.bySendPos = 1;

    // High-speed data communication start prep
    LJV7IF_PROFILE_INFO profileInfo;
    rc = (CRc::Rc)LJV7IF_PreStartHighSpeedDataCommunication(DEVICE_ID, &req, &profileInfo);
    if (rc!=CRc::Ok)
    {
        emit Error(QString("PreStartHighSpeedDataCommunication:0x%1").arg(rc,0,16));
        return;
    }
    vdValueZ.resize(profileInfo.wProfDataCnt*set.value("profileCount",1000).toInt());
    x.resize(profileInfo.wProfDataCnt);
    qDebug()<<"profDataCnt"<<profileInfo.wProfDataCnt;
    // Start high-speed data communication.
    rc = (CRc::Rc)LJV7IF_StartHighSpeedDataCommunication(DEVICE_ID);
    if (rc!=CRc::Ok)
    {
        emit Error(QString("StartHighSpeedDataCommunication:0x%1").arg(rc,0,16));
        return;
    }
    qDebug()<<"start usb finish";
}
void kingsControl::startGetEthernetData()
{
    qDebug()<<"start ethernet";
    EthernetMode();
    if(!isConnected)
        return;
    LJV7IF_StopHighSpeedDataCommunication(DEVICE_ID);
    LJV7IF_HighSpeedDataCommunicationFinalize(DEVICE_ID);
    CRc::Rc rc = CRc::Ok;
    LJV7IF_HIGH_SPEED_PRE_START_REQ req;
    DWORD threadId = (DWORD)DEVICE_ID;

    LJV7IF_ETHERNET_CONFIG *p=&_ethernetConfig;


    rc = (CRc::Rc)LJV7IF_HighSpeedDataEthernetCommunicationInitalize(DEVICE_ID,p,dataPort, &_callback, frequency, threadId);
    if (rc!=CRc::Ok)
    {
        emit Error(QString("HighSpeedDataEthernetCommunicationInitalize:0x%1").arg(rc,0,16));
        return;
    }
    req.bySendPos = 1;
    // High-speed data communication start prep
    LJV7IF_PROFILE_INFO profileInfo;
    rc = (CRc::Rc)LJV7IF_PreStartHighSpeedDataCommunication(DEVICE_ID, &req, &profileInfo);

    if (rc!=CRc::Ok)
    {
        emit Error(QString("PreStartHighSpeedDataCommunication:0x%1").arg(rc,0,16));
        return;
    }

    vdValueZ.resize(profileInfo.wProfDataCnt*set.value("profileCount",1000).toInt());
    x.resize(profileInfo.wProfDataCnt);
    qDebug()<<"profDataCnt"<<profileInfo.wProfDataCnt;
    // Start high-speed data communication.


    rc = (CRc::Rc)LJV7IF_StartHighSpeedDataCommunication(DEVICE_ID);
    qDebug()<<rc;
    if (rc!=CRc::Ok)
    {
        emit Error(QString("StartHighSpeedDataCommunication:0x%1").arg(rc,0,16));
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


        receiveCount++;

        if((receiveCount+1)==set.value("profileCount").toInt())
        {


            for(int i=0;i<_profileData.profSize;i++)
            {
                 x[i]=i*0.01;
            }
            if(displayMode==0)
            {
                emit dispSingleFrame(0,0,&x[0],&vdValueZ[0],_profileData.profSize);

            }
            //_profileData.SaveProfile("filepath");

            if(displayMode==1)
            {
                emit putImagebyPointer1(&vdValueZ[0],_profileData.profSize,receiveCount+1);


            }
            if(displayMode==2)
            {
                emit putImagebyPointer1(&vdValueZ[0],_profileData.profSize,receiveCount+1);
                stopGetData();
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


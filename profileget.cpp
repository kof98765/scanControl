#include "profileget.h"

profileGet::profileGet(QObject *parent) :
    QThread(parent)
{
    object=(void *)this;
    bool bLoadError;
    m_hProfileEvent = CreateEvent(NULL, true, false, "ProfileEvent");
    bConnected = false;
    mode=1;
    index=0;

    //Creating a LLT-object
    //The LLT-Object will load the LLT.dll automaticly and give us a error if ther no LLT.dll
    m_pLLT = new CInterfaceLLT("LLT.dll", &bLoadError);

    if(bLoadError)
    {
      emit Error("Error loading LLT.dll \n,please restart the program");

      //Wait for a keyboard hit


      //Deletes the LLT-object
      delete m_pLLT;
      return ;
    }
    if(m_pLLT->m_pFunctions->CreateLLTDevice == NULL)
    {
      qDebug() << "Please use a LLT.dll version 3.0.0.0 or higher! \n";
    }
    else
    {
      //Create a Firewire Device
       if(m_pLLT->CreateLLTDevice(INTF_TYPE_ETHERNET))
           qDebug() << "CreateLLTDevice OK \n";
       else
       {
           Error("Error during CreateLLTDevice\n");
           return;
       }
    }
}
profileGet::~profileGet()
{
    int iRetValue;
    if(bConnected)
    {
        qDebug() << "Disconnect the scanCONTROL\n";
        if((iRetValue=m_pLLT->Disconnect()) < GENERAL_FUNCTION_OK)
        {
          OnError("Error during Disconnect", iRetValue);
        }
    }
    //Deletes the LLT-object
    delete m_pLLT;
    CloseHandle(m_hProfileEvent);
}

void profileGet::initDevice()
{
    vuiInterfaces.resize(MAX_INTERFACE_COUNT);
    vdwResolutions.resize(MAX_RESOULUTIONS);
    uiInterfaceCount = 0;
    uiShutterTime = set.value("shutterTime",100).toUInt();
    uiIdleTime = set.value("idleTime",900).toUInt();
    m_uiNeededProfileCount = set.value("profileCount",1000).toUInt();//设置帧数

     m_uiPacketSizeMAX = 0;
     m_uiPacketSizeMIN=0;
     isReady=false;

     m_uiResolution = 0;

     m_uiRecivedProfileCount = 0;
     int iRetValue;
     if(bConnected)
     {
         qDebug() << "Disconnect the scanCONTROL\n";
         if((iRetValue=m_pLLT->Disconnect()) < GENERAL_FUNCTION_OK)
         {
             OnError("Error during Disconnect", iRetValue);
             return;
         }
         bConnected=false;
     }

     readSettings();



}
void profileGet::selectDevice(int index)
{
    int iRetValue;
    this->index=index;
    if(bConnected)
    {
        qDebug() << "Disconnect the scanCONTROL\n";
        if((iRetValue=m_pLLT->Disconnect()) < GENERAL_FUNCTION_OK)
        {
            OnError("Error during Disconnect", iRetValue);
            return;
        }
        bConnected=false;
    }

    qDebug() << "\nSelect the device interface " <<index<< vuiInterfaces[index] << "\n";
    if((iRetValue = m_pLLT->SetDeviceInterface(vuiInterfaces[index], 0)) < GENERAL_FUNCTION_OK)
    {

        OnError("Error during SetDeviceInterface", iRetValue);

    }

    qDebug() << "Connecting to scanCONTROL\n";
    if((iRetValue = m_pLLT->Connect()) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during Connect", iRetValue);

    }
    else
    {
        qDebug()<<"connect succesful";
        bConnected = true;
    }

}
void profileGet::readSettings()
{
    int iRetValue;
    bool bOK = true;
    //获取设备列表
    iRetValue = m_pLLT->GetDeviceInterfacesFast(&vuiInterfaces[0], (unsigned int)vuiInterfaces.size());

    if(iRetValue == ERROR_GETDEVINTERFACES_REQUEST_COUNT)
    {
        qDebug() << "There are more or equal than " << vuiInterfaces.size() << " scanCONTROL connected \n";
        uiInterfaceCount = vuiInterfaces.size();
    }
    else if(iRetValue < 0)
    {
        qDebug() << "A error occured during searching for connected scanCONTROL"<<iRetValue<<"\n";
        uiInterfaceCount = 0;
    }
    else
    {
        uiInterfaceCount = iRetValue;

    }

   if(uiInterfaceCount == 0)
   {
        emit Error("There is no scanCONTROL connected \n");
        return;
   }
   else if(uiInterfaceCount == 1)
        qDebug() << "There is 1 scanCONTROL connected \n";
   else
        qDebug() << "There are " << uiInterfaceCount << " scanCONTROL's connected \n";

   if(uiInterfaceCount >= 1)
   {
       //保存设备列表
        QStringList str1;
        for(unsigned int i=0;i<uiInterfaceCount;i++)
        {
            str1<<QString::number(vuiInterfaces[i]);
        }
        set.setValue("interface",str1);
        qDebug()<<"interface"<<str1;
        //选择当前设备
        selectDevice(index);

        //获取LLT类型
        if((iRetValue = m_pLLT->GetLLTType(&m_tscanCONTROLType)) < GENERAL_FUNCTION_OK)
        {
            OnError("Error during GetLLTType", iRetValue);

        }
        qDebug() << "Get scanCONTROL type"<<m_tscanCONTROLType;

        if(iRetValue == GENERAL_FUNCTION_DEVICE_NAME_NOT_SUPPORTED)
        {
            qDebug() << "Can't decode scanCONTROL type. Please contact Micro-Epsilon for a newer version of the LLT.dll.\n";
        }

        if(m_tscanCONTROLType >= scanCONTROL28xx_25 && m_tscanCONTROLType <= scanCONTROL28xx_xxx)
        {
            qDebug() << "The scanCONTROL is a scanCONTROL28xx\n\n";
        }
        else if(m_tscanCONTROLType >= scanCONTROL27xx_25 && m_tscanCONTROLType <= scanCONTROL27xx_xxx)
        {
            qDebug() << "The scanCONTROL is a scanCONTROL27xx\n\n";
        }
        else
        {
            qDebug() << "The scanCONTROL is a undefined type\nPlease contact Micro-Epsilon for a newer SDK\n\n";
        }
        //获取所有分辨率
        qDebug() << "Get all possible resolutions\n";
        if((iRetValue = m_pLLT->GetResolutions(&vdwResolutions[0], vdwResolutions.size())) < GENERAL_FUNCTION_OK)
        {
            OnError("Error during GetResolutions", iRetValue);

        }
        //保存分辨率列表
        QStringList str2;
        for(unsigned int i=0;i<vdwResolutions.size();i++)
        {
            str2<<QString::number(vdwResolutions[i]);
            set.setValue("resolutions",str2);
        }
        qDebug()<<"resolution"<<str2;
       //读取滤波器属性
        if((iRetValue = m_pLLT->GetFeature(FEATURE_FUNCTION_PROFILE_FILTER,&filter)) < GENERAL_FUNCTION_OK)
        {
            OnError("Error during SetFeature(FEATURE_FUNCTION_TRIGGERPROFILE_FILTER)", iRetValue);

        }
        qDebug("filter set %x",filter);
        //读取触发器属性
        if((iRetValue=m_pLLT->GetFeature(FEATURE_FUNCTION_TRIGGER,&trigger))<GENERAL_FUNCTION_OK)
        {
            OnError("Error during SetFeature(TRIGGER)",iRetValue);
        }
        qDebug("trigger set %x",trigger);

        if((iRetValue=m_pLLT->GetFeature(FEATURE_FUNCTION_RS422_INTERFACE_FUNCTION,&IOConfigure))<GENERAL_FUNCTION_OK)
        {
            OnError("Error during SetFeature(IOConfigure)",iRetValue);
        }
        qDebug("IOConfigure set %x",IOConfigure);

        if((iRetValue = m_pLLT->GetMinMaxPacketSize((unsigned long*)&m_uiPacketSizeMIN, (unsigned long*)&m_uiPacketSizeMAX)) < GENERAL_FUNCTION_OK)
        {
                OnError("Error during GetPacketSize", iRetValue);

        }
        qDebug()<<"minPackSize"<<m_uiPacketSizeMIN<<"maxPackSize"<<m_uiPacketSizeMAX;
        m_uiResolution = vdwResolutions[0];

        set.sync();
        flushSettings();
        isReady=true;


    }

}
/*
    刷新设置
*/
void profileGet::flushSettings()
{

    int iRetValue;
    uiShutterTime = set.value("shutterTime",100).toUInt();
    uiIdleTime = set.value("idleTime",900).toUInt();
    m_uiNeededProfileCount = set.value("profileCount",1000).toUInt();//设置帧数

    qDebug() << "Set resolution to " << m_uiResolution << "\n";
    
    if((iRetValue = m_pLLT->SetResolution(m_uiResolution)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during SetResolution", iRetValue);

    }


    qDebug() << "Profile config set to PROFILE\n";
    if((iRetValue = m_pLLT->SetProfileConfig(PROFILE)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during SetProfileConfig", iRetValue);

    }



    qDebug() << "Set shutter time to " << uiShutterTime << "\n";
    if((iRetValue = m_pLLT->SetFeature(FEATURE_FUNCTION_SHUTTERTIME, uiShutterTime)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during SetFeature(FEATURE_FUNCTION_SHUTTERTIME)", iRetValue);

    }



    qDebug() << "Set idle time to " << uiIdleTime << "\n";
    if((iRetValue = m_pLLT->SetFeature(FEATURE_FUNCTION_IDLETIME, uiIdleTime)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during SetFeature(FEATURE_FUNCTION_IDLETIME)", iRetValue);

    }

    qDebug("filter %x",filter);
    filter&=~(0xf<<8);
    filter&=~(0xf<<4);
    filter&=~(0xf<<0);
    filter|=0xc<<8;
    filter|=set.value("resampleValue",0).toInt()<<4;
    filter|=set.value("median",0).toInt()<<2;
    filter|=set.value("average",0).toInt()<<0;

   qDebug("filter %x",filter);

    if((iRetValue = m_pLLT->SetFeature(FEATURE_FUNCTION_PROFILE_FILTER, filter)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during SetFeature(FEATURE_FUNCTION_PROFILE_FILTER)", iRetValue);

    }
    qDebug("trigger:%x",trigger);
    trigger&=~(0xfff<<0);
    trigger&=~(0xf<<16);
    trigger&=~(0xf<<21);
    trigger&=~(0x1<<24);
    trigger&=~(0x1<<25);
    trigger|=(set.value("encoderDivisor",0).toInt()<<0);
    trigger|=(set.value("triggerMode",0).toInt()<<16);
    trigger|=(set.value("triggerPolarity",0).toInt()<<21);
    trigger|=(set.value("triggerSource",0).toInt()<<24);
    trigger|=(set.value("trigger",0).toInt()<<25);
    qDebug("trigger:%x",trigger);
    int t=(set.value("trigger",0).toInt());
    qDebug()<<"trigger mode"<<t;
    if(t)
        isExternalTrigger=true;
    else
        isExternalTrigger=false;
    if((iRetValue = m_pLLT->SetFeature(FEATURE_FUNCTION_TRIGGER, trigger)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during SetFeature(FEATURE_FUNCTION_TRIGGER)", iRetValue);

    }
    qDebug("IOConfigure:%x",IOConfigure);
    IOConfigure&=~(0xf);
    IOConfigure&=~(0xf<<4);
    IOConfigure&=~(0x1<<11);
    IOConfigure|=(set.value("voltage",0).toInt()<<11);
    IOConfigure|=(set.value("digitalInputs",0).toInt()<<4);
    IOConfigure|=5<<0;
    qDebug("IOConfigure:%x",IOConfigure);
    if((iRetValue = m_pLLT->SetFeature(FEATURE_FUNCTION_RS422_INTERFACE_FUNCTION, IOConfigure)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during SetFeature(FEATURE_FUNCTION_TRIGGER)", iRetValue);

    }

    qDebug() << "Sets the Firewire PacketSize to " << m_uiPacketSizeMAX << "\n";



    qDebug("ready to get %d profile",m_uiNeededProfileCount);


}
void profileGet::preGetDate()
{
    switch(mode)
    {
        case 0:
            this->stopTrigger();
            break;
        case 1:
        break;
        case 2:
            this->stopSingleFrame();
        break;
        case 3:
            this->stopVedio();
        break;
    }
}
void profileGet::getVideoFrame()
{
    int iRetValue;

    if((iRetValue = m_pLLT->SaveProfiles("./frame.bmp",BMP))<GENERAL_FUNCTION_OK)
    {
      OnError("Error during saveProfile", iRetValue);
      return ;
    }

}
void profileGet::getSingleFrame()
{

    int iRetValue;

    std::vector<unsigned char> vucProfileBuffer(m_uiResolution*4+16);
    std::vector<double> vdValueX(m_uiResolution);
    std::vector<double> vdValueZ(m_uiResolution);
    std::vector<unsigned short> vdIntensity(m_uiResolution);
    std::vector<unsigned short> vdReflectionWidth(m_uiResolution);

 //   m_pLLT->SaveProfiles("video.bmp", BMP);
    if((iRetValue = m_pLLT->GetActualProfile(&vucProfileBuffer[0], (unsigned int)vucVideoBuffer.size(), PURE_PROFILE, NULL))
         != vucProfileBuffer.size())
    {
        OnError("Error during GetActualProfile", iRetValue);
        return ;
    }

    iRetValue = m_pLLT->ConvertProfile2Values(&vucProfileBuffer[0], m_uiResolution, PURE_PROFILE, m_tscanCONTROLType,
        0, true, &vdReflectionWidth[0], &vdIntensity[0], NULL, &vdValueX[0], &vdValueZ[0], NULL, NULL);
    if(((iRetValue & CONVERT_X) == 0) || ((iRetValue & CONVERT_Z) == 0))
    {
        OnError("Error during Converting of profile data", iRetValue);
        return;
    }

    emit dispSingleFrame(&vdReflectionWidth[0],&vdIntensity[0],&vdValueX[0],&vdValueZ[0],m_uiResolution);

}
void profileGet::startSingleFrame()
{
    int iRetValue;

    if(!isReady)
    {
        emit Error(QStringLiteral("设备还没准备好,请重新启动激光!"));
        return;
    }
    preGetDate();
    mode=2;
    if((iRetValue = m_pLLT->SetProfileConfig(PURE_PROFILE)) < GENERAL_FUNCTION_OK)
    {
      OnError("Error during SetProfileConfig", iRetValue);

    }

      qDebug() << "\nDemonstrate the SingleFrame mode\n";



     qDebug()<< "Enable the SingleFrame stream\n";
     if((iRetValue = m_pLLT->TransferProfiles(NORMAL_TRANSFER, true)) < GENERAL_FUNCTION_OK)
       {
         OnError("Error during TransferProfiles start", iRetValue);
         return;
       }
}
void profileGet::stopSingleFrame()
{

    mode=1;
     int iRetValue;
    qDebug()<< "Disable the SingleFrame stream\n";
    if((iRetValue = m_pLLT->TransferProfiles(NORMAL_TRANSFER, false)) < GENERAL_FUNCTION_OK)
      {
        OnError("Error during TransferProfiles stop", iRetValue);
        return;
      }
}
void profileGet::startTrigger()
{
    int iRetValue;

    m_uiRecivedProfileCount=0;
    if(!isReady)
    {
        emit Error(QStringLiteral("设备还没准备好,请重新启动激光!"));
        return;
    }
    preGetDate();
    mode=0;
    vdValueX.resize(m_uiResolution*m_uiNeededProfileCount);
    vdValueZ.resize(m_uiResolution*m_uiNeededProfileCount);
    vdValueIntensity.resize(m_uiResolution*m_uiNeededProfileCount);
    m_vucProfileBuffer.resize(m_uiResolution*64*m_uiNeededProfileCount);

    if((iRetValue = m_pLLT->SetProfileConfig(PROFILE)) < GENERAL_FUNCTION_OK)
    {
      OnError("Error during SetProfileConfig", iRetValue);

    }

    if((iRetValue = m_pLLT->RegisterCallback(STD_CALL, newProfile, 0)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during RegisterCallback", iRetValue);
        return;
    }

    if((iRetValue = m_pLLT->TransferProfiles(NORMAL_TRANSFER, true)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during TransferProfiles start ", iRetValue);
        return;
    }
}
void profileGet::stopTrigger()
{
    int iRetValue;
    mode=1;
    qDebug() << "Disable the measurement\n";
    if((iRetValue = m_pLLT->TransferProfiles(NORMAL_TRANSFER, false)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during TransferProfiles stop", iRetValue);
        return;
    }
}
void profileGet::startVedio()
{
    int iRetValue;
    if(!isReady)
    {
        emit Error(QStringLiteral("设备还没准备好,请重新启动激光!"));
        return;
    }

    preGetDate();
    mode=3;
    qDebug() << "Enable the video stream\n";
    if((iRetValue = m_pLLT->SetPacketSize(m_uiPacketSizeMAX)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during SetPacketSize", iRetValue);
        return ;
    }
    if((iRetValue = m_pLLT->SetProfileConfig(VIDEO_IMAGE)) < GENERAL_FUNCTION_OK)
    {
      OnError("Error during SetProfileConfig", iRetValue);

    }
    if((iRetValue = m_pLLT->TransferVideoStream(VIDEO_MODE_1, true, &uiWidth, &uiHeight)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during TransferVideoStream start", iRetValue);
        return ;
    }
    vucVideoBuffer.resize(uiWidth*uiHeight);
    qDebug()<<"video"<<uiWidth<<uiHeight;
}


void profileGet::stopVedio()
{
    int iRetValue;
    mode=1;
    qDebug() << "Disable the video stream\n";
    if((iRetValue = m_pLLT->TransferVideoStream(VIDEO_MODE_1, false, NULL, NULL)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during TransferVideoStream stop", iRetValue);
        return ;
    }

}
void profileGet::GetProfiles_Callback()
{
    int iRetValue;
    QTime time;
    time.start();
    m_uiRecivedProfileCount=0;
    if(!isReady)
    {
        emit Error(QStringLiteral("设备还没准备好,请重新启动激光!"));
        return;
    }
    preGetDate();
    mode=1;
    if((iRetValue = m_pLLT->SetProfileConfig(PROFILE)) < GENERAL_FUNCTION_OK)
    {
      OnError("Error during SetProfileConfig", iRetValue);

    }

    vdValueX.resize(m_uiResolution*m_uiNeededProfileCount);
    vdValueZ.resize(m_uiResolution*m_uiNeededProfileCount);
    vdValueIntensity.resize(m_uiResolution*m_uiNeededProfileCount);

    //Resets the event
    ResetEvent(m_hProfileEvent);

    qDebug() << "\nDemonstrate the profile transfer via callback function\n";


    qDebug() << "Register the callback\n";
    //注册回调函数 newprofile
    if((iRetValue = m_pLLT->RegisterCallback(STD_CALL, newProfile, 0)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during RegisterCallback", iRetValue);
        return;
    }
    //Resize the profile buffer to the estimated profile size
    m_vucProfileBuffer.resize(m_uiResolution*64*m_uiNeededProfileCount);

    qDebug() << "Enable the measurement\n";
    if((iRetValue = m_pLLT->TransferProfiles(NORMAL_TRANSFER, true)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during TransferProfiles", iRetValue);
        return;
    }

    qDebug() << "Wait for one profile\n";

    if(WaitForSingleObject(m_hProfileEvent, 50000) != WAIT_OBJECT_0)
    {
        qDebug() << "Error getting profile over the callback \n\n";
        return;
    }

    qDebug() << "Disable the measurement\n";
    if((iRetValue = m_pLLT->TransferProfiles(NORMAL_TRANSFER, false)) < GENERAL_FUNCTION_OK)
    {
        OnError("Error during TransferProfiles", iRetValue);
        return;
    }

    //Test the size from the profile
    if(m_uiProfileDataSize == m_uiResolution*64)
        qDebug() << "Profile size is OK \n";
    else
    {
        qDebug() << "Profile size is wrong \n\n";
        return;
    }

    qDebug() << m_uiRecivedProfileCount << "profiles have recived \n";

    qDebug() << "Converting of profile data from the first reflection\n";



    iRetValue = m_pLLT->ConvertProfile2Values(&m_vucProfileBuffer[0], m_uiResolution*m_uiNeededProfileCount, PROFILE, m_tscanCONTROLType,
    0, true, NULL, &vdValueIntensity[0], NULL, &vdValueX[0], &vdValueZ[0], NULL, NULL);
    if(((iRetValue & CONVERT_X) == 0) || ((iRetValue & CONVERT_Z) == 0))
    {
        OnError("Error during Converting of profile data", iRetValue);
        return;
    }
    qDebug()<<"convert complete";
    emit putImagebyPointer3(&vdValueX[0],(double *)(&vdValueIntensity[0]),&vdValueZ[0],1280,m_uiNeededProfileCount);

//
    emit putImagebyPointer1(&vdValueZ[0],1280,m_uiNeededProfileCount);

    qDebug()<<QStringLiteral("扫描时间:")<<time.elapsed()<<"msec";
  //}

//  DisplayTimestamp(&m_vucProfileBuffer[m_uiNeededProfileCount*m_uiResolution*64-16]);
}
/*
    获取一帧数据
    
*/
void profileGet::getNewProfile(const unsigned char* pucData, unsigned int uiSize, void* pUserData)
{
    int iRetValue;
    static int num=0;
    std::vector<unsigned char> vucProfileBuffer(m_uiResolution*4+16);
    if(uiSize > 0)
    {
        /*
        if(m_uiRecivedProfileCount < m_uiNeededProfileCount)
        {
            //If the needed profile count not arrived: copy the new Profile in the buffer and increase the recived buffer count
            m_uiProfileDataSize = uiSize;
            memcpy(&m_vucProfileBuffer[m_uiRecivedProfileCount*uiSize], pucData, uiSize);
            m_uiRecivedProfileCount++;
        }
        */
        m_uiProfileDataSize = uiSize;
        memcpy(&m_vucProfileBuffer[m_uiRecivedProfileCount*uiSize], pucData, uiSize);
        m_uiRecivedProfileCount++;
       // qDebug()<<"recv"<<m_uiRecivedProfileCount;
        iRetValue = m_pLLT->ConvertProfile2Values(pucData, m_uiResolution,PROFILE, m_tscanCONTROLType,
            0, true, 0, 0, NULL, &vdValueX[0], &vdValueZ[0], NULL, NULL);
        if(((iRetValue & CONVERT_X) == 0) || ((iRetValue & CONVERT_Z) == 0))
        {
            OnError("Error during Converting of profile data", iRetValue);
            return;
        }

        emit dispSingleFrame(0,0,&vdValueX[0],&vdValueZ[0],m_uiResolution);
        if(isExternalTrigger)
        {

            //emit dispSingleFrame(0,&vdValueIntensity[0],&vdValueX[0],&vdValueZ[0],m_uiResolution);
            if(m_uiRecivedProfileCount>=100)
            {
                QTime time;
                time.start();

                iRetValue = m_pLLT->ConvertProfile2Values(&m_vucProfileBuffer[0], m_uiResolution*m_uiRecivedProfileCount, PROFILE, m_tscanCONTROLType,
                0, true, NULL, &vdValueIntensity[0], NULL, &vdValueX[0], &vdValueZ[0], NULL, NULL);
                if(((iRetValue & CONVERT_X) == 0) || ((iRetValue & CONVERT_Z) == 0))
                {
                    OnError("Error during Converting of profile data", iRetValue);
                    return;
                }
                qDebug()<<QStringLiteral("转换时间")<<time.elapsed();
                emit putImagebyPointer1(&vdValueZ[0],1280,m_uiRecivedProfileCount);
                m_uiRecivedProfileCount=0;

            }
        }
        if(m_uiRecivedProfileCount >= m_uiNeededProfileCount)
        {
            //If the needed profile count is arived: set the event
            SetEvent(m_hProfileEvent);


        }
  }
}
void profileGet::OnError(const char* szErrorTxt, int iErrorValue)
{
  char acErrorString[200];

  qDebug() << szErrorTxt << "\n";
  if(m_pLLT->TranslateErrorValue(iErrorValue, acErrorString, sizeof(acErrorString)) >= GENERAL_FUNCTION_OK)
    qDebug() << acErrorString << "\n\n";
}

//Displays one profile
void profileGet::DisplayProfile(unsigned short *pdValueIntensity,double *pdValueX, double *pdValueZ, unsigned int uiResolution)
{
    //指针2halcon图像

    time.start();
    ofstream outfileZ("Z.mtx");
    ofstream outfileX("X.mtx");
    ofstream outfileI("I.mtx");

    for(unsigned int i=1; i<=uiResolution; i++)
    {
        outfileZ<<*pdValueZ++;
        outfileX<<*pdValueX++;
        outfileI<<*pdValueIntensity++;
             if(i%1280 == 0)
             {
               outfileZ<<endl;
               outfileX<<endl;
               outfileI<<endl;
             }else
             {
                 outfileZ<<" ";
                 outfileX<<" ";
                 outfileI<<" ";
             }
      }

      outfileZ.close();
      outfileX.close();
      outfileI.close();
      qDebug()<<QStringLiteral("矩阵生成时间:")<<time.elapsed()<<"msec";
}

//Displays the timestamp
void profileGet::DisplayTimestamp(unsigned char *pucTimestamp)
{
  double dShutterOpen, dShutterClose;
  unsigned int uiProfileCount;

  //Decode the timestamp
  m_pLLT->Timestamp2TimeAndCount(pucTimestamp, &dShutterOpen, &dShutterClose, &uiProfileCount);
  qDebug() << "\nShutterOpen: " << dShutterOpen << " ShutterClose: " << dShutterClose << "\n";
  qDebug() << "ProfileCount: " << uiProfileCount << "\n";
  qDebug() << "\n";
}

void profileGet::run()
{
    GetProfiles_Callback();
}

void __stdcall newProfile(const unsigned char* pucData, unsigned int uiSize, void* pUserData)
{
    profileGet *o=(profileGet *)object;
    emit o->getNewProfile(pucData,uiSize,pUserData);
}


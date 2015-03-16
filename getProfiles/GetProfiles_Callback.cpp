//   GetProfiles_Callback.cpp: demo-application for using the LLT.dll
//
//   Version 3.0.0.0
//
//   Copyright 2009
// 
//   Sebastian Lueth
//   MICRO-EPSILON Optronic GmbH
//   Lessingstrasse 14
//   01465 Dresden OT Langebrueck
//   Germany
//---------------------------------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "InterfaceLLT_2.h"
#include "GetProfiles_Callback.h"
using namespace std;

int getProfile()
{
//	dealTiff();
  std::vector<unsigned int> vuiInterfaces(MAX_INTERFACE_COUNT);
  std::vector<DWORD> vdwResolutions(MAX_RESOULUTIONS);
  unsigned int uiInterfaceCount = 0;
  unsigned int uiShutterTime = 100;
  unsigned int uiIdleTime = 900;
  bool bLoadError;
  int iRetValue;
  bool bOK = true;
  bool bConnected = false;
  m_uiResolution = 0;
  m_uiNeededProfileCount = 1000;//设置帧数
  m_uiRecivedProfileCount = 0;

  m_hProfileEvent = CreateEvent(NULL, true, false, "ProfileEvent");

  //Creating a LLT-object
  //The LLT-Object will load the LLT.dll automaticly and give us a error if ther no LLT.dll
  m_pLLT = new CInterfaceLLT("LLT.dll", &bLoadError);

  if(bLoadError)
  {
    qDebug() << "Error loading LLT.dll \n";

    //Wait for a keyboard hit
    while(!_kbhit()) {}

    //Deletes the LLT-object
    delete m_pLLT;
    return -1;
  }

  //Test if the LLT.dll supports GetLLTType (Version 3.0.0.0 or higher)
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
      qDebug() << "Error during CreateLLTDevice\n";

    //Gets the available interfaces from the scanCONTROL-device
    iRetValue = m_pLLT->GetDeviceInterfacesFast(&vuiInterfaces[0], (unsigned int)vuiInterfaces.size());
    
    if(iRetValue == ERROR_GETDEVINTERFACES_REQUEST_COUNT)
    {
      qDebug() << "There are more or equal than " << vuiInterfaces.size() << " scanCONTROL connected \n";
      uiInterfaceCount = vuiInterfaces.size();
    }
    else if(iRetValue < 0)
    {
      qDebug() << "A error occured during searching for connected scanCONTROL \n";
      uiInterfaceCount = 0;
    }
    else
    {
      uiInterfaceCount = iRetValue;
    } 

    if(uiInterfaceCount == 0)
      qDebug() << "There is no scanCONTROL connected \n";
    else if(uiInterfaceCount == 1)
      qDebug() << "There is 1 scanCONTROL connected \n";
    else
      qDebug() << "There are " << uiInterfaceCount << " scanCONTROL's connected \n";

    if(uiInterfaceCount >= 1)
    {
      qDebug() << "\nSelect the device interface " << vuiInterfaces[0] << "\n";
      if((iRetValue = m_pLLT->SetDeviceInterface(vuiInterfaces[0], 0)) < GENERAL_FUNCTION_OK)
      {
        OnError("Error during SetDeviceInterface", iRetValue);
        bOK = false;
      }
       
      if(bOK)
      {
        qDebug() << "Connecting to scanCONTROL\n";
        if((iRetValue = m_pLLT->Connect()) < GENERAL_FUNCTION_OK)
        {
          OnError("Error during Connect", iRetValue);
          bOK = false;
        }
        else
          bConnected = true;
      }

      if(bOK)
      {
        qDebug() << "Get scanCONTROL type\n";
        if((iRetValue = m_pLLT->GetLLTType(&m_tscanCONTROLType)) < GENERAL_FUNCTION_OK)
        {
          OnError("Error during GetLLTType", iRetValue);
          bOK = false;
        }
        
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

        qDebug() << "Get all possible resolutions\n";
        if((iRetValue = m_pLLT->GetResolutions(&vdwResolutions[0], vdwResolutions.size())) < GENERAL_FUNCTION_OK)
        {
          OnError("Error during GetResolutions", iRetValue);
          bOK = false;
        }

        m_uiResolution = vdwResolutions[0];
      }

      if(bOK)
      {
        qDebug() << "Set resolution to " << m_uiResolution << "\n";
        if((iRetValue = m_pLLT->SetResolution(m_uiResolution)) < GENERAL_FUNCTION_OK)
        {
          OnError("Error during SetResolution", iRetValue);
          bOK = false;
        }
      }

      if(bOK)
      {
        qDebug() << "Set trigger to internal\n";
        if((iRetValue = m_pLLT->SetFeature(FEATURE_FUNCTION_TRIGGER, 0x00000000)) < GENERAL_FUNCTION_OK)
        {
          OnError("Error during SetFeature(FEATURE_FUNCTION_TRIGGER)", iRetValue);
          bOK = false;
        }
      }

      if(bOK)
      {
        qDebug() << "Profile config set to PROFILE\n";
        if((iRetValue = m_pLLT->SetProfileConfig(PROFILE)) < GENERAL_FUNCTION_OK)
        {
          OnError("Error during SetProfileConfig", iRetValue);
          bOK = false;
        }
      }

      if(bOK)
      {
        qDebug() << "Set shutter time to " << uiShutterTime << "\n";
        if((iRetValue = m_pLLT->SetFeature(FEATURE_FUNCTION_SHUTTERTIME, uiShutterTime)) < GENERAL_FUNCTION_OK)
        {
          OnError("Error during SetFeature(FEATURE_FUNCTION_SHUTTERTIME)", iRetValue);
          bOK = false;
        }
      }

      if(bOK)
      {
        qDebug() << "Set idle time to " << uiIdleTime << "\n";
        if((iRetValue = m_pLLT->SetFeature(FEATURE_FUNCTION_IDLETIME, uiIdleTime)) < GENERAL_FUNCTION_OK)
        {
          OnError("Error during SetFeature(FEATURE_FUNCTION_IDLETIME)", iRetValue);
          bOK = false;
        }
      }

      if(bOK)
      {
        GetProfiles_Callback();
      }

      if(bConnected)
      {
        qDebug() << "Disconnect the scanCONTROL\n";
        if((iRetValue = m_pLLT->Disconnect()) < GENERAL_FUNCTION_OK)
        {
          OnError("Error during Disconnect", iRetValue);
        }
      }
    }
  }

  //Deletes the LLT-object
  delete m_pLLT;

  CloseHandle(m_hProfileEvent);

  //Wait for a keyboard hit
  while(!_kbhit()) {}

  return 0;
}

void GetProfiles_Callback()
{
  int iRetValue;
  std::vector<double> vdValueX(m_uiResolution*m_uiNeededProfileCount);
  std::vector<double> vdValueZ(m_uiResolution*m_uiNeededProfileCount);
  std::vector<unsigned short> vdValueIntensity(m_uiResolution*m_uiNeededProfileCount);  //intensity
  //Resets the event
  ResetEvent(m_hProfileEvent);

  qDebug() << "\nDemonstrate the profile transfer via callback function\n";


  qDebug() << "Register the callback\n";
  //注册回调函数 newprofile
  if((iRetValue = m_pLLT->RegisterCallback(STD_CALL, (void*)NewProfile, 0)) < GENERAL_FUNCTION_OK)
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
  //for (int a=0;a<100;a++)
  //{

  iRetValue = m_pLLT->ConvertProfile2Values(&m_vucProfileBuffer[0], m_uiResolution*m_uiNeededProfileCount, PROFILE, m_tscanCONTROLType,
    0, true, NULL, &vdValueIntensity[0], NULL, &vdValueX[0], &vdValueZ[0], NULL, NULL);
  if(((iRetValue & CONVERT_X) == 0) || ((iRetValue & CONVERT_Z) == 0))
  {
    OnError("Error during Converting of profile data", iRetValue);
    return;
  }


  DisplayProfile(&vdValueIntensity[0],&vdValueX[0], &vdValueZ[0], m_uiResolution*m_uiNeededProfileCount);

  //}
  qDebug() << "\n\nDisplay the timestamp from the profile:";
  DisplayTimestamp(&m_vucProfileBuffer[m_uiNeededProfileCount*m_uiResolution*64-16]);
}

//Callback function
//回调函数主体
void __stdcall NewProfile(const unsigned char* pucData, unsigned int uiSize, void* pUserData)
{
  if(uiSize > 0)
  {
    if(m_uiRecivedProfileCount < m_uiNeededProfileCount)
    {
      //If the needed profile count not arrived: copy the new Profile in the buffer and increase the recived buffer count
      m_uiProfileDataSize = uiSize;
      memcpy(&m_vucProfileBuffer[m_uiRecivedProfileCount*uiSize], pucData, uiSize);
      m_uiRecivedProfileCount++;

      qDebug()<<m_uiRecivedProfileCount<<endl;
    }

    if(m_uiRecivedProfileCount >= m_uiNeededProfileCount)
    {
      //If the needed profile count is arived: set the event
      SetEvent(m_hProfileEvent);
    }
  }
}

//Displaying the error text
void OnError(const char* szErrorTxt, int iErrorValue)
{
  char acErrorString[200];

  qDebug() << szErrorTxt << "\n";
  if(m_pLLT->TranslateErrorValue(iErrorValue, acErrorString, sizeof(acErrorString)) >= GENERAL_FUNCTION_OK)
    qDebug() << acErrorString << "\n\n";
}

//Displays one profile
void DisplayProfile(unsigned short *pdValueIntensity,double *pdValueX, double *pdValueZ, unsigned int uiResolution)
{

	ofstream outfileX("E:\\益德项目\\Scancontrol SDK\\Source\\X.mtx");
	ofstream outfileZ("E:\\益德项目\\Scancontrol SDK\\Source\\Z.mtx");
	ofstream outfileI("E:\\益德项目\\Scancontrol SDK\\Source\\I.mtx");
  size_t tNumberSize;

  for(unsigned int i=1; i<=uiResolution; i++)
  {
//     //Prints the X- and Z-values
//     tNumberSize = Double2Str(*pdValueX).size();
//     qDebug() << "\r" << "Profiledata: X = " << *pdValueX++;
//     for(; tNumberSize<8; tNumberSize++)
//     {
//       qDebug() << " ";
//     }

//     tNumberSize = Double2Str(*pdValueZ).size();
//     //qDebug() << " Z = " << *pdValueZ++;
	outfileX<<*pdValueX++;
	outfileZ<<*pdValueZ++;
	outfileI<<*pdValueIntensity++;
	     if(i%1280 == 0)
	     {
	       outfileX<<endl;
		   outfileZ<<endl;
		   outfileI<<endl;
	     }else
		 {
			 outfileX<<" ";
			 outfileZ<<" ";
			 outfileI<<" ";
		 }
//     for(; tNumberSize<8; tNumberSize++)
//     {
//       qDebug() << " ";
//     }
    
    //Somtimes wait a short time (only for display)
//     if(i%8 == 0)
//     {
//       Sleep(10);
//     }
  }
  outfileX.close();
  outfileZ.close();
  outfileI.close();
}

//Displays the timestamp
void DisplayTimestamp(unsigned char *pucTimestamp)
{
  double dShutterOpen, dShutterClose;
  unsigned int uiProfileCount;

  //Decode the timestamp
  m_pLLT->Timestamp2TimeAndCount(pucTimestamp, &dShutterOpen, &dShutterClose, &uiProfileCount);
  qDebug() << "\nShutterOpen: " << dShutterOpen << " ShutterClose: " << dShutterClose << "\n";
  qDebug() << "ProfileCount: " << uiProfileCount << "\n";
  qDebug() << "\n";
}

//Convert a double value to a string
std::string Double2Str(double dValue)
{
  std::ostringstream NewStreamApp;
  NewStreamApp << dValue;

  return NewStreamApp.str();
}


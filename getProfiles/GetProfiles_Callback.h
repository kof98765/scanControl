//   GetProfiles_Callback.h: demo-application for using the LLT.dll
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
#pragma once
#ifndef LLTGetProfilesCallbackH
#define LLTGetProfilesCallbackH

#include "scanControlDataTypes.h"
#include "InterfaceLLT_2.h"

#define MAX_INTERFACE_COUNT    5
#define MAX_RESOULUTIONS       6

void GetProfiles_Callback();
void OnError(const char* szErrorTxt, int iErrorValue);
//void DisplayProfile(double *pdValueX, double *pdValueZ, unsigned int uiResolution);
void DisplayProfile(unsigned short *pdValueIntensity,double *pdValueX, double *pdValueZ, unsigned int uiResolution);
void DisplayTimestamp(unsigned char *pucTimestamp);
std::string Double2Str(double dValue);


CInterfaceLLT* m_pLLT;
unsigned int m_uiResolution;
TScannerType m_tscanCONTROLType;
unsigned int m_uiNeededProfileCount;
unsigned int m_uiRecivedProfileCount;
unsigned int m_uiProfileDataSize;
HANDLE m_hProfileEvent;
std::vector<unsigned char> m_vucProfileBuffer;

#endif

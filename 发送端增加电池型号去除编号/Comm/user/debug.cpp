#include "StdAfx.h"  
#include <stdio.h>
#include <string.h>
#include <Windows.h>

void OutputDebugPrintf(const char* strOutputString, ...)
{
    char strBuffer[4096]={0};
    va_list vlArgs;
    va_start(vlArgs,strOutputString);
    //_vsnprintf_s(strBuffer,sizeof(strBuffer)-1,strOutputString,vlArgs);
	//sprintf();
    vsprintf_s(strBuffer,sizeof(strBuffer)-1,strOutputString,vlArgs);
    va_end(vlArgs);
    //OutputDebugString(_T(strBuffer));
}
#include "StdAfx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "serialport.h"
#include "xmodem.h"

uint8_t XModemSeq[132];

void XModemFill(bool success)
{
	int i = 0;
	unsigned char checkSum = 0;
	static unsigned char packetCount = 1;
	XModemSeq[i++] = XMODEM_SOH;
	XModemSeq[i++] = packetCount;
	XModemSeq[i++] = ~packetCount;
	memset(XModemSeq+i, 0x1A, 128);
	for(; i<131; ++i)
	{
		XModemSeq[i] = (unsigned char)(255 * sin(i/100.0 * 2*M_PI));
		checkSum += XModemSeq[i];
	}
	XModemSeq[i] = checkSum;
	if(success)
		++packetCount;
}

void XModemSend(bool success)
{
	XModemFill(success);
	SerialSend(XModemSeq, sizeof(XModemSeq));
}
void XModemRecv()
{
}

BYTE stopByte = 0x00;

BOOL XModemStart()
{
	BYTE hostResponse[2] = {0};
	stopByte = 0x00;
	while(!stopByte)
	{
		hostResponse[0] = 0x00;
		BOOL bReadStat = SerialRecv(hostResponse, 1);
		OutputDebugPrintf("接收字节：%02x\n", hostResponse[0]);
		if(bReadStat)
		{
			switch(hostResponse[0])
			{
				case XMODEM_NAK : XModemSend(false); break;
				case XMODEM_ACK : XModemSend(true); break;
				case XMODEM_CAN : return TRUE;
				default : OutputDebugPrintf("指令无效\n", hostResponse[0]); break;
			}
		}
		else
			return FALSE;
		Sleep(3000);
	}
	OutputDebugPrintf("停止通信\n");
	return TRUE;
}

BOOL XModemStop()
{
	int i = 0;
	BYTE hostResponse[2] = {0};
	stopByte = XMODEM_EOT;
	while(++i<20)
	{
		if(SerialSend(&stopByte, 1))
			break;
		BOOL bReadStat = SerialRecv(hostResponse, 1);
		if(bReadStat)
		{
			if(hostResponse[0] == XMODEM_CAN)
				return FALSE;
		}
		Sleep(50);
	}
	return TRUE;
}

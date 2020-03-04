#include "StdAfx.h"
#include "serialport.h" 
  
#include <queue>

static HANDLE hCom = INVALID_HANDLE_VALUE; //ȫ�ֱ��������ھ��  
//HANDLE hComThread;//ȫ�ֱ����������߳�

OVERLAPPED Wol = {0}; 
OVERLAPPED Rol = {0}; 
//OVERLAPPED WRol = {0}; 

static BYTE TxBuff[4096];
static DWORD TxLen;
static BYTE RxBuff[65536];
static DWORD RxLen;

HANDLE hEventTx = INVALID_HANDLE_VALUE;

static DWORD sSerialRecv(BYTE* buffer, DWORD bufMaxSize);
static BOOL sSerialSend(BYTE* buffer, DWORD length);




BOOL SerialSend(BYTE* buffer, DWORD length)
{ 
	memcpy(TxBuff, buffer, length);
	TxLen = length;
	SetEvent(hEventTx);
	return TRUE;
}


DWORD ThreadProcRead(LPVOID lpParam)
{   
	HWND hDlg = (HWND)lpParam;
	static DWORD dwParam = 0;
	static CString str = _T("");
	while(1)
	//while(SerialIsOpen())
	{
		DWORD len = sSerialRecv(RxBuff, sizeof(RxBuff));
		if(len)
		{
			PostMessage(hDlg, WM_ON_COM_RECV, (WPARAM)(RxBuff), len);
			RxLen += len;
			PurgeComm(hCom,PURGE_TXCLEAR);
			//PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR|PURGE_TXABORT|PURGE_RXABORT);
		}
	}

	return 0;
}


DWORD ThreadProcWrite(LPVOID pParam)
{   
	static DWORD dwParam = 0;
	static CString str = _T("");
	while(1)
	//while(SerialIsOpen())
	{
		WaitForSingleObject(hEventTx, INFINITE);   
		sSerialSend(TxBuff, TxLen);
		TxLen = 0;
		ResetEvent(hEventTx);
	}
	return 0;
}

BOOL OpenSerialPort(CString port); 
BOOL SerialConfig(DWORD baudrate=9600, DWORD inQueue=4096, DWORD outQueue=65536);

BOOL SerialOpen(HWND pWND, CString port, DWORD baudrate)
{
	if(!OpenSerialPort(port))
		return FALSE;
	if(!SerialConfig(baudrate))
		return FALSE;
	DWORD    dwThreadID;
    DWORD    dwParam;

	{
		HANDLE hThreadWrite = CreateThread( NULL,
                                0,
                                (LPTHREAD_START_ROUTINE)ThreadProcWrite,
                                &dwParam,
                                0,
                                &dwThreadID);
	

    if(hThreadWrite==NULL)
    {
         //MessageBox(_T("�̴߳���ʧ��!"));
		 return FALSE;
    }
	CloseHandle(hThreadWrite);
	}

	{
	hEventTx = CreateEvent ( NULL,          //����Wol��hEvent��ԱΪ���ź�״̬
                    TRUE,
                    FALSE,
                    NULL);

	HANDLE hThreadRead = CreateThread ( NULL,
                                0,
                                (LPTHREAD_START_ROUTINE)ThreadProcRead,
                                (LPVOID)pWND,
                                0,       //�����̺߳�,����ִ�и��߳�
                                &dwThreadID);
    if(hThreadRead==NULL)
    {
         //MessageBox(_T("���̴߳���ʧ��!"));
		 return FALSE;
    }
	CloseHandle(hThreadRead);
	}

	
	return TRUE;

 
}


BOOL OpenSerialPort(CString port)   //��ʼ������  
{  
	//�򿪲�����port
    hCom = CreateFile(_T("\\\\.\\" + port),
						GENERIC_READ|GENERIC_WRITE, 
						0, 
						NULL, 
						OPEN_EXISTING, 
						0, 
						NULL);

    //�򿪲�����port
    /*hCom = CreateFile(_T("\\\\.\\" + port),
						GENERIC_READ|GENERIC_WRITE, 
						0, 
						NULL, 
						OPEN_EXISTING, 
						FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
						NULL); */ 
	//hCom = CreateFile(port,//COM1��
	//				GENERIC_READ|GENERIC_WRITE, //�������д
	//				0, //��ռ��ʽ
	//				NULL,
	//				OPEN_EXISTING, //�򿪶����Ǵ���
	//				0, //ͬ����ʽ
	//				NULL);
	//hCom = CreateFile(_T("\\\\.\\" + port),       //���ں�
	//				 GENERIC_READ | GENERIC_WRITE, //�����д
	//				 0, //ͨѶ�豸�����Զ�ռ��ʽ��
	//				 NULL, //�ް�ȫ����
	//				 OPEN_EXISTING,       //ͨѶ�豸�Ѵ��ڣ�������ص���ʽ�Ļ���FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED
	//				 FILE_FLAG_OVERLAPPED,//�첽I/O,0��ʾͬ����ʽ
	//				 0); //ͨѶ�豸������ģ���
    if (hCom == INVALID_HANDLE_VALUE)  
    {  
        return FALSE;  
    }  
	
    COMMTIMEOUTS TimeOuts;  
    //�趨����ʱ  
    TimeOuts.ReadIntervalTimeout = MAXDWORD;  //�����ַ�֮�������ʱ
    TimeOuts.ReadTotalTimeoutMultiplier = 100;  //��ȡһ���ֽں͵ȴ���һ���ֽ�����ʱ��
    TimeOuts.ReadTotalTimeoutConstant = 1000;   //һ�ζ�ȡ�������ݵĹ̶���ʱ
    //�ڶ�һ�����뻺���������ݺ���������������أ�  
    //�������Ƿ������Ҫ����ַ���  
  
    //�趨д��ʱ  
    TimeOuts.WriteTotalTimeoutMultiplier = 0;  
    TimeOuts.WriteTotalTimeoutConstant = 0 ;  
    SetCommTimeouts(hCom, &TimeOuts); //���ó�ʱ  

	
    return TRUE;  
}  
BOOL CloseSerialPort()   //
{
	BOOL retVal = CloseHandle(hCom);;
	CloseHandle(hEventTx);
	hCom = INVALID_HANDLE_VALUE;
	hEventTx = INVALID_HANDLE_VALUE;
	return retVal;
}

BOOL SerialConfig(DWORD baudrate, DWORD inQueue, DWORD outQueue)
{
	BOOL retVal = TRUE;
	SetupComm(hCom, inQueue, outQueue); //���뻺�����������������Ĭ�ϴ�С����4096
    DCB wdcb;  
    GetCommState (hCom, &wdcb);  
    wdcb.BaudRate = baudrate;//�����ʣ�9600������������  
    wdcb.ByteSize = 8;   //ÿ���ֽ�8λ  
    wdcb.Parity = NOPARITY;  //����żУ��λ  
	wdcb.StopBits=ONESTOPBIT; //��ֹͣλ
	//wdcb.StopBits=ONE5STOPBITS; //1��ֹͣλ
	//wdcb.StopBits=TWOSTOPBITS;
    retVal = SetCommState (hCom, &wdcb);   
	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR|PURGE_TXABORT|PURGE_RXABORT);
	return retVal;
}


BOOL sSerialSend(BYTE* buffer, DWORD length)
{
	
    DWORD    dwRes;
    DWORD    dwWrite;
    //DWORD    dwRead;
	{
	memcpy(TxBuff, buffer, length);
	TxLen = length;
	SetEvent(hEventTx);
	//return TRUE;


    Wol.Internal = 0;        //����OVERLAPPED�ṹWol
    Wol.InternalHigh = 0;
    Wol.Offset = 0;
    Wol.OffsetHigh = 0;             
    Wol.hEvent = CreateEvent ( NULL,          //����Wol��hEvent��ԱΪ���ź�״̬
                            TRUE,
                            FALSE,
                            NULL);
    if (Wol.hEvent == INVALID_HANDLE_VALUE)
	{
        return -1;
    }
    if (WriteFile (hCom,         //���ھ��
					buffer,     //��Ŵ���������
					length,         //�����͵��ֽ���
					&dwWrite,
					&Wol) )       //ָ�򴴽�hComʱ��Wol��ָ��
    {
        return TRUE;
    }
    else
    {
        dwRes = WaitForSingleObject ( Wol.hEvent , 500);   //500ms��ʱ
        switch(dwRes)
        {
            case   WAIT_OBJECT_0:
                if (!GetOverlappedResult (hCom,
                        &Wol,
                        &dwWrite,   
                        TRUE) )     //TRUE��ʾֱ��������ɺ����ŷ���
                {
                        //����ʧ��,����ʹ��GetLastError()��ȡ������Ϣ
					DWORD dwError = GetLastError();
					switch (dwError)
					{
						case ERROR_IO_PENDING: //GetLastError��������
							{
								
								break;
							}
						default:
							break;
					}
                }
                else
				{
                        //�������ݳɹ�
                        //������뷢�ͳɹ��Ĵ������
                }
            break;
            case   WAIT_TIMEOUT:
				//д����ʧ��,ԭ���ǳ�ʱ
            break;
            default:
				//�������Ĭ�ϴ������
            break;
        }
	}
    CloseHandle(Wol.hEvent);
	Rol.hEvent = INVALID_HANDLE_VALUE;
	return true;
	}

}


BOOL fRes;
DWORD dwError=0;
COMSTAT comstat;
using std::queue;

DWORD sSerialRecv(BYTE* buffer, DWORD bufMaxSize)
{
	DWORD dwRes;
	DWORD dwRead;
	static BYTE rxByte[4096];
	static queue<BYTE> RxQueue;
	ClearCommError(hCom, &dwError, &comstat);
	if (comstat.cbInQue == 0)// COMSTAT�ṹ���ش���״̬��Ϣ,cbInQue��Ա������ֵ�������뻺�������ֽ���
		return 0;
	Rol.hEvent = CreateEvent ( NULL,          //����Rol��hEvent��ԱΪ���ź�״̬
							TRUE,
							FALSE,
							NULL);
	if (Rol.hEvent == INVALID_HANDLE_VALUE) //����ʧ��
	{
		return 0;
	}
	Sleep(500);
	if (ReadFile (hCom,         //���ھ��
				rxByte,     //��Ŷ�ȡ����
				sizeof(rxByte),         //Ҫ��ȡ���ֽ���
				&dwRead,		//ʵ�ʶ�ȡ�����ֽ���
				&Rol) )       //ָ�򴴽�hComʱ��Rol��ָ��
	{
		//���������ʾ�Ѿ�����dwRead���ֽ�
		for(DWORD i=0; i<dwRead; ++i)
			RxQueue.push(rxByte[i]);
	}
	else
	{
		//���������ʾδ�����κ��ֽ�
		dwRes = WaitForSingleObject(Rol.hEvent, 5000);   //5�볬ʱ
		switch(dwRes)
		{
			case   WAIT_OBJECT_0:
				if (!GetOverlappedResult(hCom,
						&Rol,
						&dwRead,    //ʵ�ʶ������ֽ���
						TRUE) )     //TRUE��ʾֱ��������ɺ����ŷ���
				{
					RxQueue.push('\0');
					//����ʧ��,����ʹ��GetLastError()��ȡ������Ϣ
				}
				else
				{
					//�ѳɹ�����dwRead���ֽ�
					for(DWORD i=0; i<dwRead; ++i)
						RxQueue.push(rxByte[i]);
				}
			break;
			case   WAIT_TIMEOUT:
					//������ʧ��,ԭ���ǳ�ʱ
			break;
			default:
					//�������Ĭ�ϴ������
			break;
		}
		CloseHandle(Rol.hEvent);
	}
	DWORD byteRead;
	for(byteRead=0; byteRead<bufMaxSize; ++byteRead)
	{
		if(RxQueue.empty()) break;
		buffer[byteRead] = RxQueue.front();
		RxQueue.pop();
	}
	return byteRead;

}

BOOL SerialIsOpen()
{
	return (hCom !=  INVALID_HANDLE_VALUE);
}



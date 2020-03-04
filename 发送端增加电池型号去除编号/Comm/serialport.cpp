#include "StdAfx.h"
#include "serialport.h" 
  
#include <queue>

static HANDLE hCom = INVALID_HANDLE_VALUE; //全局变量，串口句柄  
//HANDLE hComThread;//全局变量，串口线程

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
         //MessageBox(_T("线程创建失败!"));
		 return FALSE;
    }
	CloseHandle(hThreadWrite);
	}

	{
	hEventTx = CreateEvent ( NULL,          //创建Wol的hEvent成员为无信号状态
                    TRUE,
                    FALSE,
                    NULL);

	HANDLE hThreadRead = CreateThread ( NULL,
                                0,
                                (LPTHREAD_START_ROUTINE)ThreadProcRead,
                                (LPVOID)pWND,
                                0,       //创建线程后,立即执行该线程
                                &dwThreadID);
    if(hThreadRead==NULL)
    {
         //MessageBox(_T("读线程创建失败!"));
		 return FALSE;
    }
	CloseHandle(hThreadRead);
	}

	
	return TRUE;

 
}


BOOL OpenSerialPort(CString port)   //初始化串口  
{  
	//打开并设置port
    hCom = CreateFile(_T("\\\\.\\" + port),
						GENERIC_READ|GENERIC_WRITE, 
						0, 
						NULL, 
						OPEN_EXISTING, 
						0, 
						NULL);

    //打开并设置port
    /*hCom = CreateFile(_T("\\\\.\\" + port),
						GENERIC_READ|GENERIC_WRITE, 
						0, 
						NULL, 
						OPEN_EXISTING, 
						FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
						NULL); */ 
	//hCom = CreateFile(port,//COM1口
	//				GENERIC_READ|GENERIC_WRITE, //允许读和写
	//				0, //独占方式
	//				NULL,
	//				OPEN_EXISTING, //打开而不是创建
	//				0, //同步方式
	//				NULL);
	//hCom = CreateFile(_T("\\\\.\\" + port),       //串口号
	//				 GENERIC_READ | GENERIC_WRITE, //允许读写
	//				 0, //通讯设备必须以独占方式打开
	//				 NULL, //无安全属性
	//				 OPEN_EXISTING,       //通讯设备已存在，如果是重叠方式的话：FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED
	//				 FILE_FLAG_OVERLAPPED,//异步I/O,0表示同步方式
	//				 0); //通讯设备不能用模板打开
    if (hCom == INVALID_HANDLE_VALUE)  
    {  
        return FALSE;  
    }  
	
    COMMTIMEOUTS TimeOuts;  
    //设定读超时  
    TimeOuts.ReadIntervalTimeout = MAXDWORD;  //两个字符之间最大延时
    TimeOuts.ReadTotalTimeoutMultiplier = 100;  //读取一个字节和等待下一个字节所需时间
    TimeOuts.ReadTotalTimeoutConstant = 1000;   //一次读取串口数据的固定超时
    //在读一次输入缓冲区的内容后读操作就立即返回，  
    //而不管是否读入了要求的字符。  
  
    //设定写超时  
    TimeOuts.WriteTotalTimeoutMultiplier = 0;  
    TimeOuts.WriteTotalTimeoutConstant = 0 ;  
    SetCommTimeouts(hCom, &TimeOuts); //设置超时  

	
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
	SetupComm(hCom, inQueue, outQueue); //输入缓冲区和输出缓冲区的默认大小都是4096
    DCB wdcb;  
    GetCommState (hCom, &wdcb);  
    wdcb.BaudRate = baudrate;//波特率：9600，其他：不变  
    wdcb.ByteSize = 8;   //每个字节8位  
    wdcb.Parity = NOPARITY;  //无奇偶校验位  
	wdcb.StopBits=ONESTOPBIT; //无停止位
	//wdcb.StopBits=ONE5STOPBITS; //1无停止位
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


    Wol.Internal = 0;        //设置OVERLAPPED结构Wol
    Wol.InternalHigh = 0;
    Wol.Offset = 0;
    Wol.OffsetHigh = 0;             
    Wol.hEvent = CreateEvent ( NULL,          //创建Wol的hEvent成员为无信号状态
                            TRUE,
                            FALSE,
                            NULL);
    if (Wol.hEvent == INVALID_HANDLE_VALUE)
	{
        return -1;
    }
    if (WriteFile (hCom,         //串口句柄
					buffer,     //存放待发送数据
					length,         //欲发送的字节数
					&dwWrite,
					&Wol) )       //指向创建hCom时的Wol的指针
    {
        return TRUE;
    }
    else
    {
        dwRes = WaitForSingleObject ( Wol.hEvent , 500);   //500ms超时
        switch(dwRes)
        {
            case   WAIT_OBJECT_0:
                if (!GetOverlappedResult (hCom,
                        &Wol,
                        &dwWrite,   
                        TRUE) )     //TRUE表示直到操作完成函数才返回
                {
                        //操作失败,可以使用GetLastError()获取错误信息
					DWORD dwError = GetLastError();
					switch (dwError)
					{
						case ERROR_IO_PENDING: //GetLastError函数返回
							{
								
								break;
							}
						default:
							break;
					}
                }
                else
				{
                        //发送数据成功
                        //这里加入发送成功的处理代码
                }
            break;
            case   WAIT_TIMEOUT:
				//写操作失败,原因是超时
            break;
            default:
				//这里加入默认处理代码
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
	if (comstat.cbInQue == 0)// COMSTAT结构返回串口状态信息,cbInQue成员变量的值代表输入缓冲区的字节数
		return 0;
	Rol.hEvent = CreateEvent ( NULL,          //创建Rol的hEvent成员为无信号状态
							TRUE,
							FALSE,
							NULL);
	if (Rol.hEvent == INVALID_HANDLE_VALUE) //创建失败
	{
		return 0;
	}
	Sleep(500);
	if (ReadFile (hCom,         //串口句柄
				rxByte,     //存放读取数据
				sizeof(rxByte),         //要读取的字节数
				&dwRead,		//实际读取到的字节数
				&Rol) )       //指向创建hCom时的Rol的指针
	{
		//进入这里表示已经读入dwRead个字节
		for(DWORD i=0; i<dwRead; ++i)
			RxQueue.push(rxByte[i]);
	}
	else
	{
		//进入这里表示未读入任何字节
		dwRes = WaitForSingleObject(Rol.hEvent, 5000);   //5秒超时
		switch(dwRes)
		{
			case   WAIT_OBJECT_0:
				if (!GetOverlappedResult(hCom,
						&Rol,
						&dwRead,    //实际读出的字节数
						TRUE) )     //TRUE表示直到操作完成函数才返回
				{
					RxQueue.push('\0');
					//操作失败,可以使用GetLastError()获取错误信息
				}
				else
				{
					//已成功读入dwRead个字节
					for(DWORD i=0; i<dwRead; ++i)
						RxQueue.push(rxByte[i]);
				}
			break;
			case   WAIT_TIMEOUT:
					//读操作失败,原因是超时
			break;
			default:
					//这里加入默认处理代码
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



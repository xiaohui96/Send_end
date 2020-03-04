#ifndef __SERIALPORT_H
#define __SERIALPORT_H
  
#define WM_ON_COM_RECV (WM_USER+100)

#ifndef SERIAL_ERROR_CODE
#define SERIAL_ERROR_CODE
#define SERIAL_SUCCESS 0
#define SERIAL_ERROR_OPEN 1		//打开串口时发生错误
#define SERIAL_ERROR_CONFIG 2	//配置串口时发生错误

//extern HANDLE hCom = INVALID_HANDLE_VALUE; //全局变量，串口句柄  
//extern HANDLE hComThread; //全局变量，串口线程 
//extern DWORD WINAPI SerialPort1ThreadProcess(HWND hWnd);//串口监视线程控制函数

#endif // SERIAL_ERROR_CODE
//打开串口 
//pWND: 对话框指针，用来进行消息传递
//port: 端口号
//baudrate: 波特率
BOOL SerialOpen(HWND pWND, CString port, DWORD baudrate);
//关闭串口
BOOL CloseSerialPort();  
//查询串口是否打开
BOOL SerialIsOpen();


//主动发送，被动接收
BOOL SerialSend(BYTE* buffer, DWORD length);

#endif // __SERIALPORT_H
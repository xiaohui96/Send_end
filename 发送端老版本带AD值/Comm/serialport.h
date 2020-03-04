#ifndef __SERIALPORT_H
#define __SERIALPORT_H
  
#define WM_ON_COM_RECV (WM_USER+100)

#ifndef SERIAL_ERROR_CODE
#define SERIAL_ERROR_CODE
#define SERIAL_SUCCESS 0
#define SERIAL_ERROR_OPEN 1		//�򿪴���ʱ��������
#define SERIAL_ERROR_CONFIG 2	//���ô���ʱ��������

//extern HANDLE hCom = INVALID_HANDLE_VALUE; //ȫ�ֱ��������ھ��  
//extern HANDLE hComThread; //ȫ�ֱ����������߳� 
//extern DWORD WINAPI SerialPort1ThreadProcess(HWND hWnd);//���ڼ����߳̿��ƺ���

#endif // SERIAL_ERROR_CODE
//�򿪴��� 
//pWND: �Ի���ָ�룬����������Ϣ����
//port: �˿ں�
//baudrate: ������
BOOL SerialOpen(HWND pWND, CString port, DWORD baudrate);
//�رմ���
BOOL CloseSerialPort();  
//��ѯ�����Ƿ��
BOOL SerialIsOpen();


//�������ͣ���������
BOOL SerialSend(BYTE* buffer, DWORD length);

#endif // __SERIALPORT_H
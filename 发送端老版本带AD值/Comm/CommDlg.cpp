
// CommDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Comm.h"
#include "CommDlg.h"
#include "afxdialogex.h"

#include "serialport.h"
#include "xmodem.h"
#include "myAlgorithm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SERIAL_RXBUFF_MAX  0x100000ul

BYTE TxBuff[4096];
DWORD TxLen;
BYTE RxBuff[SERIAL_RXBUFF_MAX];
DWORD RxLen;
DWORD RxLenTotal;
CString rstr;
CString Rstr;
int array[2][100];

// 用于应用程序“关于”菜单项的 CAboRxByteArrayutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCommDlg 对话框




CCommDlg::CCommDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCommDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_ON_COM_RECV, &CCommDlg::OnRecvDataHandler)
	ON_BN_CLICKED(IDC_BUTTON_Open, &CCommDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_Send, &CCommDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_Clear, &CCommDlg::OnBnClickedButtonClear)
	ON_CBN_SELCHANGE(IDC_COMBO_Port, &CCommDlg::OnCbnSelchangeComboPort)
	ON_CBN_SELCHANGE(IDC_COMBO_Baudrate, &CCommDlg::OnCbnSelchangeComboBaudrate)
	ON_BN_CLICKED(IDC_BUTTON_Send1, &CCommDlg::OnClickedButtonSend1)
	ON_BN_CLICKED(IDC_BUTTON_Send2, &CCommDlg::OnClickedButtonSend2)
	ON_BN_CLICKED(IDC_BUTTON_Send3, &CCommDlg::OnClickedButtonSend3)
	ON_BN_CLICKED(IDC_BUTTON_Send4, &CCommDlg::OnClickedButtonSend4)
	ON_BN_CLICKED(IDC_BUTTON_Send5, &CCommDlg::OnClickedButtonSend5)
	ON_BN_CLICKED(IDC_BUTTON_Send6, &CCommDlg::OnClickedButtonSend6)
	ON_BN_CLICKED(IDC_BUTTON_Send7, &CCommDlg::OnClickedButtonSend7)
	ON_BN_CLICKED(IDC_BUTTON_Send8, &CCommDlg::OnClickedButtonSend8)
ON_WM_TIMER()
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void UserInit()
{

}

void CCommDlg::OnBnClickedButtonClear()
{
	GetDlgItem(IDC_EDIT_Status)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_RecvLen)->SetWindowText(_T("0"));
	//RxLenTotal = 0;
	//RxLen = 0;
}
// CCommDlg 消息处理程序

// 输出单体桩状态
void  CCommDlg::printRecv_Work_Status(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Work_Status);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Work_Status)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 输出发射端BUCK输入电压
void  CCommDlg::printRecv_Vot_Trans_Buck_In(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Vot_Trans_Buck_In);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Vot_Trans_Buck_In)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障时输出发射端BUCK输入电压
void  CCommDlg::printRecv_Vot_Trans_Buck_In_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Vot_Trans_Buck_In_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Vot_Trans_Buck_In_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 输出发射端BUCK占空比
void  CCommDlg::printRecv_Duty_Trans_Buck(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Duty_Trans_Buck);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Duty_Trans_Buck)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障时输出发射端BUCK占空比
void  CCommDlg::printRecv_Duty_Trans_Buck_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Duty_Trans_Buck_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Duty_Trans_Buck_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 输出发射端BUCK输出电压
void  CCommDlg::printRecv_Vot_Trans_Buck_Out(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu = stu *0.027 * 100;
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Vot_Trans_Buck_Out);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Vot_Trans_Buck_Out)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障时输出发射端BUCK输出电压
void  CCommDlg::printRecv_Vot_Trans_Buck_Out_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu = stu *0.027 * 100;
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Vot_Trans_Buck_Out_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Vot_Trans_Buck_Out_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 输出发射端BUCK输出电流
void  CCommDlg::printRecv_Cur_Trans_Buck(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu = stu *0.00116 * 100;
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Cur_Trans_Buck);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Cur_Trans_Buck)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障时输出发射端BUCK输出电流
void  CCommDlg::printRecv_Cur_Trans_Buck_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu = stu *0.00116 * 100;
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Cur_Trans_Buck_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Cur_Trans_Buck_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 输出发射端功率
void  CCommDlg::printRecv_Power_Trans(CString str)
	{
	CString strn1=str.Mid(0,3);
	CString strn2=str.Mid(3,3);
    char temp[10];
	char temp1[10];
	CString stu1;
	long stu;
	long stu3;
	long stu4;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn1);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	::wsprintfA(temp1, "%ls",(LPCTSTR)strn2);
    const char *str2=temp1;
	stu3=strtol(str2,0,16);
	stu4 = stu3 * stu * 0.0000313;
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu4);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Power_Trans);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Power_Trans)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 输出当前继电器状态
void  CCommDlg::printRecv_Relay(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Relay);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Relay)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 输出发射端逆变区温度
void  CCommDlg::printRecv_Temp_Trans_MOS(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu = stu*stu*5.5067*0.000001 - 0.0538*stu + 106.9495;
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Temp_Trans_MOS);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Temp_Trans_MOS)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障时输出发射端逆变区温度
void  CCommDlg::printRecv_Temp_Trans_MOS_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu = stu*stu*5.5067*0.000001 - 0.0538*stu + 106.9495;
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Temp_Trans_MOS_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Temp_Trans_MOS_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 输出频率
void  CCommDlg::printRecv_Fre_Trans_Inverter(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Fre_Trans_Inverter);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Fre_Trans_Inverter)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障时输出频率
void  CCommDlg::printRecv_Fre_Trans_Inverter_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Fre_Trans_Inverter_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Fre_Trans_Inverter_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 发射端充电电压限值
void  CCommDlg::printRecv_Vot_Limit_Trans(CString str)
		{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Vot_Limit_Trans);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Vot_Limit_Trans)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障时发射端充电电压限值
void  CCommDlg::printRecv_Vot_Limit_Trans_Err(CString str)
		{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Vot_Limit_Trans_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Vot_Limit_Trans_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 发射端充电电流限值
void  CCommDlg::printRecv_Cur_Limit_Trans(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Cur_Limit_Trans);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Cur_Limit_Trans)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障时发射端充电电流限值
void  CCommDlg::printRecv_Cur_Limit_Trans_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Cur_Limit_Trans_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Cur_Limit_Trans_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 红外接收成功计数
void  CCommDlg::printRecv_Infrared_Rec_Succ_Cnt(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Infrared_Rec_Succ_Cnt);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Infrared_Rec_Succ_Cnt)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 红外解码错误计数
void  CCommDlg::printRecv_Infrared_Decode_Error_Cnt(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Infrared_Decode_Error_Cnt);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Infrared_Decode_Error_Cnt)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 红外第一类帧延时计数
void  CCommDlg::printRecv_Infrared_Waiting_First_Cnt(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Infrared_Waiting_First_Cnt);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Infrared_Waiting_First_Cnt)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 红外第二类帧延时计数
void  CCommDlg::printRecv_Infrared_Waiting_Second_Cnt(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Infrared_Waiting_Second_Cnt);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Infrared_Waiting_Second_Cnt)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 红外第三类帧延时计数
void  CCommDlg::printRecv_Infrared_Waiting_Third_Cnt(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Infrared_Waiting_Third_Cnt);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Infrared_Waiting_Third_Cnt)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 红外错误计数
void  CCommDlg::printRecv_Infrared_Rec_Error_Cnt(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Infrared_Rec_Error_Cnt);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Infrared_Rec_Error_Cnt)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障类型
void  CCommDlg::printRecv_Fault_Type(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Fault_Type);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Fault_Type)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 车辆编号
void  CCommDlg::printRecv_Bike_ID(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Bike_ID);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Bike_ID)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 接收端存储的电压限值
void  CCommDlg::printRecv_Vot_Limit_Rec(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Vot_Limit_Rec);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Vot_Limit_Rec)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 接收端充电电压限值
void  CCommDlg::printRecv_Vot_Limit_Rec_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Vot_Limit_Recv_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Vot_Limit_Recv_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 接收端存储的电流限值
void  CCommDlg::printRecv_Cur_Limit_Rec(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Cur_Limit_Rec);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Cur_Limit_Rec)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 接收端充电电流限值
void  CCommDlg::printRecv_Cur_Limit_Rec_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Cur_Limit_Recv_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Cur_Limit_Recv_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 接收端BUCK输入电压
void  CCommDlg::printRecv_Vot_Rec_Buck_In(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Vot_Rec_Buck_In);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Vot_Rec_Buck_In)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障时接收端BUCK输入电压
void  CCommDlg::printRecv_Vot_Rec_Buck_In_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Vot_Rec_Buck_In_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Vot_Rec_Buck_In_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 接收端BUCK占空比
void  CCommDlg::printRecv_Duty_Rec_Buck(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Duty_Rec_Buck);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Duty_Rec_Buck)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障时接收端BUCK占空比
void  CCommDlg::printRecv_Duty_Rec_Buck_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Duty_Rec_Buck_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Duty_Rec_Buck_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 接收端BUCK输出电压
void  CCommDlg::printRecv_Vot_Rec_Buck_Out(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu = stu *0.0245 * 100;
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Vot_Rec_Buck_Out);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Vot_Rec_Buck_Out)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障时接收端BUCK输出电压
void  CCommDlg::printRecv_Vot_Rec_Buck_Out_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu = stu *0.0245 * 100;
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Vot_Rec_Buck_Out_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Vot_Rec_Buck_Out_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 接收端BUCK输出电流
void  CCommDlg::printRecv_Cur_Rec_Buck(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu = stu *0.000673 * 100;
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Cur_Rec_Buck);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Cur_Rec_Buck)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障时接收端BUCK输出电流
void  CCommDlg::printRecv_Cur_Rec_Buck_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu = stu *0.000673 * 100;
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Cur_Rec_Buck_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Cur_Rec_Buck_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 输出接收端功率
void  CCommDlg::printRecv_Power_Recv(CString str)
	{
	CString strn1=str.Mid(0,3);
	CString strn2=str.Mid(3,3);
    char temp[10];
	char temp1[10];
	CString stu1;
	long stu;
	long stu3;
	long stu4;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn1);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	::wsprintfA(temp1, "%ls",(LPCTSTR)strn2);
    const char *str2=temp1;
	stu3=strtol(str2,0,16);
	stu4 = stu3 * stu * 0.0000165;
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu4);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Power_Recv);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Power_Recv)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 输出效率
void  CCommDlg::printRecv_Effi(CString str)
	{
	CString strn1=str.Mid(0,3);
	CString strn2=str.Mid(3,3);
    char temp[10];
	char temp1[10];
	CString stu1;
	long stu;
	long stu3;
	long stu4;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn1);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	::wsprintfA(temp1, "%ls",(LPCTSTR)strn2);
    const char *str2=temp1;
	stu3=strtol(str2,0,16);
	stu4 = stu3 * stu * 0.0000313;



	CString strn3=str.Mid(6,3);
	CString strn4=str.Mid(9,3);
    char temp3[10];
	char temp4[10];
	CString stu10;
	long stu6;
	long stu7;
	long stu8;
    ::wsprintfA(temp3, "%ls",(LPCTSTR)strn3);
    const char *str3=temp3;
	stu6=strtol(str3,0,16);
	//stu=stu&(0x0F);
	stu10.Format(_T("%ld"),stu6);
	::wsprintfA(temp4, "%ls",(LPCTSTR)strn4);
    const char *str4=temp4;
	stu7=strtol(str4,0,16);
	stu8 = stu7 * stu6 * 0.0000165;

	long stu9;
	if(stu4 == 0){
		stu9 = 0;
	}
	else{
		stu9 = stu8 * 100 / stu4;
	}
	//stu=stu&(0x0F);
	stu10.Format(_T("%ld"),stu9);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Effi);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Effi)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu10); 
}

// 接收端电池区温度
void  CCommDlg::printRecv_Temp_Rec_MOS(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Temp_Rec_MOS);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Temp_Rec_MOS)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// 故障时接收端电池区温度
void  CCommDlg::printRecv_Temp_Rec_MOS_Err(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Temp_Rec_MOS_Err);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Temp_Rec_MOS_Err)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
// BUCK模式
void  CCommDlg::printRecv_BUCK_Mode_Rec(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	CString stu2;
	CString buck1;
	CString buck2;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	while(stu!=0){
		if(stu%2==0)
		{stu2 = _T("0") + stu2;}
		else
		{stu2 = _T("1") + stu2;}
		stu = stu/2;
	}
	buck1 = stu2.Mid(2,2);
	//buck2 = stu2.Mid(0,2);
	if (buck1 =="")
	{
		buck1 =_T("00");}
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_BUCK_Mode_Rec);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_BUCK_Mode_Rec)->SetWindowText(_T(""));
    pEdit->ReplaceSel(buck1); 
}
// 温度模式
void  CCommDlg::printRecv_Temp_Mode_Rec(CString str)
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	CString stu2;
	CString buck1;
	CString buck2;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	while(stu!=0){
		if(stu%2==0)
		{stu2 = _T("0") + stu2;}
		else
		{stu2 = _T("1") + stu2;}
		stu = stu/2;
	}
	buck1 = stu2.Mid(2,2);
	//buck2 = stu2.Mid(0,2);
	if (buck1 =="")
	{
		buck1 =_T("00");}
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Temp_Mode_Rec);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Temp_Mode_Rec)->SetWindowText(_T(""));
    pEdit->ReplaceSel(buck1); 
}


void  CCommDlg::printStatus(CString str)
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Status);
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
    pEdit->ReplaceSel(str); 
}
// 计算单体桩工作状态，是否复位 
void  CCommDlg::printReset_Flag(CString str)
{
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	CString stu2;
	CString buck1;
	CString buck2;
	CString stu3;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	while(stu!=0){
		if(stu%2==0)
		{stu2 = _T("0") + stu2;}
		else
		{stu2 = _T("1") + stu2;}
		stu = stu/2;
	}
	// 补齐二进制数
	int i = 8 - stu2.GetLength();
	for(; i>=1; i--){
		stu3 = _T('0') + stu3;
	}
	stu2 = stu3 + stu2;
	buck1 = stu2.Mid(4,1);
	//buck2 = stu2.Mid(0,2);
	if (buck1 =="")
	{
		buck1 =_T("00");}
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Reset_Flag);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Reset_Flag)->SetWindowText(_T(""));
    pEdit->ReplaceSel(buck1); 
	}
}

// 计算单体桩工作状态，是否检测到车辆 
void  CCommDlg::printDetected_Car(CString str)
{
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	CString stu2;
	CString buck1;
	CString buck2;
	CString stu3;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	while(stu!=0){
		if(stu%2==0)
		{stu2 = _T("0") + stu2;}
		else
		{stu2 = _T("1") + stu2;}
		stu = stu/2;
	}
	// 补齐二进制数
	//int i = 8 - sizeof(stu2);
	int i = 8 - stu2.GetLength();
	for(; i>=1; i--){
		stu3 = _T('0') + stu3;
	}
	stu2 = stu3 + stu2;
	buck1 = stu2.Mid(0,1);
	//buck2 = stu2.Mid(0,2);
	if (buck1 =="")
	{
		buck1 =_T("00");}
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Detected_Car);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Detected_Car)->SetWindowText(_T(""));
    pEdit->ReplaceSel(buck1); 
	}
}
// 计算单体桩工作状态，是否充电完成
void  CCommDlg::printFinish_Charge(CString str)
{
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	CString stu2;
	CString buck1;
	CString buck2;
	CString stu3;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	while(stu!=0){
		if(stu%2==0)
		{stu2 = _T("0") + stu2;}
		else
		{stu2 = _T("1") + stu2;}
		stu = stu/2;
	}
	// 补齐二进制数
	//int i = 8 - sizeof(stu2);
	int i = 8 - stu2.GetLength();
	for(; i>=1; i--){
		stu3 = _T('0') + stu3;
	}
	stu2 = stu3 + stu2;
	buck1 = stu2.Mid(6,1);
	//buck2 = stu2.Mid(0,2);
	if (buck1 =="")
	{
		buck1 =_T("00");}
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Finish_Charge);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Finish_Charge)->SetWindowText(_T(""));
    pEdit->ReplaceSel(buck1); 
	}
}

// 计算单体桩工作状态，单体桩当前工作状态 
void  CCommDlg::printWork_Status(CString str)
{
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	CString stu2;
	CString buck1;
	CString buck2;
	CString stu3;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	while(stu!=0){
		if(stu%2==0)
		{stu2 = _T("0") + stu2;}
		else
		{stu2 = _T("1") + stu2;}
		stu = stu/2;
	}
	// 补齐二进制数
	int i = 8 - stu2.GetLength();
	for(; i>=1; i--){
		stu3 = _T('0') + stu3;
	}
	stu2 = stu3 + stu2;
	buck1 = stu2.Mid(1,2);
	//buck2 = stu2.Mid(0,2);
	if (buck1 =="")
	{
		buck1 =_T("00");}
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Work_Status);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Work_Status)->SetWindowText(_T(""));
    pEdit->ReplaceSel(buck1); 
	}
}
 
// 计算单体桩工作状态，发射端故障
void  CCommDlg::printFault_Trans(CString str)
{
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	CString stu2;
	CString buck1;
	CString buck2;
	CString stu3;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	while(stu!=0){
		if(stu%2==0)
		{stu2 = _T("0") + stu2;}
		else
		{stu2 = _T("1") + stu2;}
		stu = stu/2;
	}
	// 补齐二进制数
	int i = 8 - stu2.GetLength();
	for(; i>=1; i--){
		stu3 = _T('0') + stu3;
	}
	stu2 = stu3 + stu2;
	buck1 = stu2.Mid(3,1);
	//buck2 = stu2.Mid(0,2);
	if (buck1 =="")
	{
		buck1 =_T("00");}
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Fault_Trans);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Fault_Trans)->SetWindowText(_T(""));
    pEdit->ReplaceSel(buck1); 
	}
}
// 计算单体桩工作状态，接收端故障
void  CCommDlg::printFault_Rec(CString str)
{
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	CString stu2;
	CString buck1;
	CString buck2;
	CString stu3;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	while(stu!=0){
		if(stu%2==0)
		{stu2 = _T("0") + stu2;}
		else
		{stu2 = _T("1") + stu2;}
		stu = stu/2;
	}
	// 补齐二进制数
	int i = 8 - stu2.GetLength();
	for(; i>=1; i--){
		stu3 = _T('0') + stu3;
	}
	stu2 = stu3 + stu2;
	buck1 = stu2.Mid(5,1);
	//buck2 = stu2.Mid(0,2);
	if (buck1 =="")
	{
		buck1 =_T("00");}
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Fault_Rec);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Fault_Rec)->SetWindowText(_T(""));
    pEdit->ReplaceSel(buck1); 
	}
}
// 计算单体桩工作状态，问题事件
void  CCommDlg::printFault(CString str)
{
	{
	CString strn=str;
    char temp[10];
	CString stu1;
	CString stu2;
	CString buck1;
	CString buck2;
	CString stu3;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	while(stu!=0){
		if(stu%2==0)
		{stu2 = _T("0") + stu2;}
		else
		{stu2 = _T("1") + stu2;}
		stu = stu/2;
	}
	// 补齐二进制数
	int i = 8 - stu2.GetLength();
	for(; i>=1; i--){
		stu3 = _T('0') + stu3;
	}
	stu2 = stu3 + stu2;
	buck1 = stu2.Mid(7,1);
	//buck2 = stu2.Mid(0,2);
	if (buck1 =="")
	{
		buck1 =_T("00");}
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Fault);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Fault)->SetWindowText(_T(""));
    pEdit->ReplaceSel(buck1); 
	}
}

// 校验函数
void  CCommDlg::printcheck(CString str)
{
	CString stu1;
	long stu;
	long zongshu=0;
	stu1 = str;
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Status);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	for(int i=0;i<=str.GetLength()-3;i+=2)
	{
	CString strn=str.Mid(i,2);
    char temp[10];
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	zongshu+=stu;
	}
	stu1.Format(_T("%lx"),zongshu);
	if((stu1.GetLength()==1)){
		stu1 = _T("0") +stu1;}
	if(stu1.Right(2)==str.Right(2))
	{
	pEdit->ReplaceSel(_T("\n数据校验成功\n"));
	pEdit->ReplaceSel(_T("\n"));
	}
	else
	{
	pEdit->ReplaceSel(_T("    数据校验失败"));
	pEdit->ReplaceSel(_T("\n"));
	}
}

// 输出电流
int  CCommDlg::print_Cur(CString str)
{
	CString strn = str;
	char temp[10];
	CString stu1;
	long stu;
	::wsprintfA(temp, "%ls",(LPCTSTR)strn);
	const char *str1=temp;
	stu=strtol(str1,0,16);
	return stu;
}
BOOL CCommDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_textcolor=RGB(0,255,0);                 // 文本颜色设置为绿色  
	// TODO: 在此添加额外的初始化代码
	//自定义控件初始化
	GetComList_Reg();
	myProCtrl = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS_Status);

	CComboBox* comboBaudrate = (CComboBox*)GetDlgItem(IDC_COMBO_Baudrate);
	((CButton *)GetDlgItem(IDC_CHECK_HexRecv))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_CHECK_HexSend))->SetCheck(TRUE);
	
	
	//((CButton *)GetDlgItem(IDC_CHECK_SEND))->SetCheck(FALSE);

	comboBaudrate->AddString(_T("9600"));
	comboBaudrate->AddString(_T("19200"));
	comboBaudrate->AddString(_T("115200"));
	SetDlgItemText(IDC_COMBO_Baudrate, _T("9600"));  //

	SetDlgItemText(IDC_COMBO_Port, _T("COM3"));
	TCHAR path[255];
	SHGetSpecialFolderPath(0,path,CSIDL_DESKTOPDIRECTORY,0);

	CString binFileName = path;
	binFileName += _T("\\data");
	SYSTEMTIME st; 
	CString strDate,strTime; 
	
	GetLocalTime(&st); 
	binFileName.AppendFormat(_T("_%4d-%2d-%2d"),st.wYear,st.wMonth,st.wDay); 
	binFileName.AppendFormat(_T("_%2d-%2d"),st.wHour,st.wMinute) ; 
	binFileName += strDate + strTime ;

	binFileName += _T(".hex");
	//GetDlgItem(IDC_EDIT_DataFileName)->SetWindowText(binFileName);

	//CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Recv);
	//pEdit->SetLimitText(1000000);

	//用户代码初始化
	//::UserInit();




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCommDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCommDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	
}

// 绘制曲线
void CCommDlg::DrawWave(int brray[2][100])
{
	CFont font;
	font.CreateFont(13,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,NULL);
	CWnd *pWnd=GetDlgItem(IDC_STATIC_POINT);
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	CFont *pOldFont;
	CDC *pDC = pWnd->GetDC();
	pDC->Rectangle(0, 0,600,350);

	pOldFont=pDC->SelectObject(&font);   //换字体

	pDC->TextOut(2,2,_T("扫频曲线"));

	CPen *pPenRed = new CPen(); //创建画笔对象
	CPen *pPenBlackxu=new CPen();
	CPen *pPenBlackshi = new CPen();
	pPenBlackxu->CreatePen(PS_DOT,1,RGB(0,0,0));
	pPenRed ->CreatePen(PS_SOLID, 2, RGB(0, 0,255)); //蓝色画笔
	pPenBlackshi->CreatePen(PS_SOLID, 2, RGB(0, 0,0));
	//选中当前红色画笔,并保存以前的画笔
	CGdiObject *pOldPen = pDC ->SelectObject(pPenRed);

	pDC ->MoveTo(20, 20); //绘制坐标轴
	pDC ->LineTo(20, 290); //竖起轴//20,290是原点
	pDC ->LineTo(590,290); //水平轴

	pDC->MoveTo(17,24);//y画箭头
	pDC->LineTo(20,20);
	pDC->LineTo(23,24);
	pDC->MoveTo(590,287);//x轴画箭头
	pDC->LineTo(593,290);
	pDC->LineTo(589,293);

	pDC->TextOut(27,20,_T("电流 mA"));
	//pDC->TextOut(27,32,_T("(V)"));
	pDC->TextOut(550,320,_T("频率 kHz"));


	CString yText[6]={_T("4096"),_T("3410"),_T("2728"),_T("2016"),_T("1364"),_T("682")};
	pDC->SelectObject(pPenBlackxu);    //换笔
	for (int i=0;i<6;i++)
	{
		pDC->TextOut(5,50+i*40,yText[i]);
		pDC->MoveTo(20,50+i*40);
		pDC->LineTo(590,50+i*40);
	}

	CString sPIText[12]={_T("240"),_T("270"),_T("300"),_T("330"),_T("360"),_T("390"),_T("420"),_T("450"),_T("480"),_T("510"),_T("540"),_T("570")};
	for (int i=0;i<12;i++)
	{
		pDC->TextOut(60+i*40-5,293,sPIText[i]);
		pDC->MoveTo(60+i*40,20);
		pDC->LineTo(60+i*40,290);
	}


	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);

	pOldPen->DeleteObject();
	pPenBlackxu->DeleteObject();

	CRect rectStatic;
	//m_static.GetClientRect(&rectStatic);
	//float fDeltaX; // x轴相邻两个绘图点的坐标距离
	//float fDeltaY; // y轴每个逻辑单位对应的坐标值
	int pX,pY;

	/*fDeltaX = (float)rectStatic.Width() / (POINT_COUNT - 1);
	fDeltaY = (float)rectStatic.Height() / 80;*/
	//显示数据
	pDC->SelectObject(pPenBlackshi);
	
	pDC->MoveTo(20, 290);

	for (int i=0;i<=100 ; i++)
	{
		//pX = (brray[0][i]*57)/16 - 5700/16 + 20;
		pX = (brray[0][i]*57)/34 - 240*57/34 + 20;
		// 剔除异常频率引起曲线报错
		if(pX<20)
		{
			pX=20;
		}
		if(pX>590)
		{
			pX=590;
		}
		//pX = 290;
		pY = 290 - (brray[1][i])*270/4776;
		if(pY>290)
		{
			pX=290;
		}
		if(pY<20)
		{
			pY=20;
		}
		pDC->LineTo(pX, pY);

	}
	pPenBlackshi->DeleteObject();
		
			//输出最大值
			int Cur_Max = 0;
			int Frc = 0;
			// int m = ((rstr.GetLength())/22)-2;
			for(int j=0; j<= 100; j++){
				if((Cur_Max<=brray[1][j])){
					Cur_Max=brray[1][j];
					Frc = brray[0][j];
				}	
			}
			// test
			// 
			CString stu1;
			CString stu2;
			stu1.Format(_T("%ld"),Cur_Max);
			stu2.Format(_T("%ld"),Frc);
			CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Max_Cur);
			int nLength = pEdit->GetWindowTextLength();
			pEdit->SetSel(nLength, nLength);
			GetDlgItem(IDC_EDIT_Max_Cur)->SetWindowText(_T(""));
			pEdit->ReplaceSel(stu1); 

			CEdit* pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT_Frc);
			int nLength2 = pEdit2->GetWindowTextLength();
			pEdit2->SetSel(nLength2, nLength2);
			GetDlgItem(IDC_EDIT_Frc)->SetWindowText(_T(""));
			pEdit2->ReplaceSel(stu2); 
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCommDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CCommDlg::OnRecvDataHandler(WPARAM wParam, LPARAM lParam)
{   
	CString strnum;
	CString str;
	//GetDlgItem(IDC_COMBO_Addr)->GetWindowText(strSend1);
	BYTE* buffer = (BYTE*)wParam; //缓冲区指针
	WORD total = (WORD)lParam; //缓冲区接收到的字节数

	if(RxLen+total > SERIAL_RXBUFF_MAX)
	{
		MessageBox(_T("The Rx Buffer is full!"));
	}
	else
	{  
		memcpy(RxBuff+RxLen, buffer, total);
		RxLen += total;
		RxLenTotal += total;
	}
	//CString str = _T("");
	//rstr += str;
	//((CButton *)GetDlgItem(IDC_CHECK_HexRecv))->SetCheck(TRUE);
	if(IsDlgButtonChecked(IDC_CHECK_HexRecv)) //Hex接收
	{
		for(WORD cur = 0; cur<total; ++cur)
		{
			str.AppendFormat(_T("%02x"), buffer[cur]);
		}
		rstr += str;
	}
	else
	{
		buffer[total] = '\0';
		str = buffer;
		rstr += str;
	}
	strnum.Format(_T("%d"), RxLenTotal);
	GetDlgItem(IDC_STATIC_RecvLen)->SetWindowText(strnum);
	// test rstr
	/*CString test;
	test = rstr;*/

	if(rstr.Mid(0,2)=="aa")
	{
		//指令5
		if((RxLenTotal==58)&&(rstr.Mid(2,2)!="4b"))
			{
				printStatus(rstr);
				printStatus(_T("\n"));

				
			if(rstr.Mid(2,2)=="0f"){
				printReset_Flag(rstr.Mid(8,2));
				printDetected_Car(rstr.Mid(8,2));
				printWork_Status(rstr.Mid(8,2));
				printFault_Trans(rstr.Mid(8,2));
				printFault_Rec(rstr.Mid(8,2));
				printFault(rstr.Mid(8,2));
				printRecv_Vot_Trans_Buck_In(rstr.Mid(16,1)+rstr.Mid(12,2));
				printRecv_Duty_Trans_Buck(rstr.Mid(17,1)+rstr.Mid(14,2));
				printRecv_Vot_Trans_Buck_Out(rstr.Mid(22,1)+rstr.Mid(18,2));
				printRecv_Cur_Trans_Buck(rstr.Mid(23,1)+rstr.Mid(20,2));
				printRecv_Power_Trans(rstr.Mid(22,1)+rstr.Mid(18,2)+rstr.Mid(23,1)+rstr.Mid(20,2));
				printRecv_Relay(rstr.Mid(24,2));
				printRecv_Temp_Trans_MOS(rstr.Mid(33,1)+rstr.Mid(26,2));
				printRecv_Fre_Trans_Inverter(rstr.Mid(32,1)+rstr.Mid(30,2)+rstr.Mid(28,2));
				printRecv_Vot_Limit_Trans(rstr.Mid(78,1)+rstr.Mid(74,2));
				printRecv_Cur_Limit_Trans(rstr.Mid(79,1)+rstr.Mid(76,2));
				printRecv_Infrared_Rec_Succ_Cnt(rstr.Mid(40,2)+rstr.Mid(38,2)+rstr.Mid(36,2)+rstr.Mid(34,2));
				printRecv_Infrared_Decode_Error_Cnt(rstr.Mid(44,2)+rstr.Mid(42,2));
				printRecv_Infrared_Waiting_First_Cnt(rstr.Mid(52,2)+rstr.Mid(50,2)+rstr.Mid(48,2)+rstr.Mid(46,2));
				printRecv_Infrared_Waiting_Second_Cnt(rstr.Mid(60,2)+rstr.Mid(58,2)+rstr.Mid(56,2)+rstr.Mid(54,2));
				printRecv_Infrared_Waiting_Third_Cnt(rstr.Mid(68,2)+rstr.Mid(66,2)+rstr.Mid(64,2)+rstr.Mid(62,2));
				printRecv_Infrared_Rec_Error_Cnt(rstr.Mid(72,2)+rstr.Mid(70,2));
				printRecv_Fault_Type(rstr.Mid(80,2));
				printRecv_Bike_ID(rstr.Mid(88,2)+rstr.Mid(86,2)+rstr.Mid(84,2)+rstr.Mid(82,2));
				printRecv_Vot_Limit_Rec(rstr.Mid(94,1)+rstr.Mid(90,2));
				printRecv_Cur_Limit_Rec(rstr.Mid(95,1)+rstr.Mid(92,2));
				printRecv_Vot_Rec_Buck_In(rstr.Mid(100,1)+rstr.Mid(96,2));
				printRecv_Duty_Rec_Buck(rstr.Mid(101,1)+rstr.Mid(98,2));
				printRecv_Vot_Rec_Buck_Out(rstr.Mid(106,1)+rstr.Mid(102,2));
				printRecv_Cur_Rec_Buck(rstr.Mid(107,1)+rstr.Mid(104,2));
				printRecv_Power_Recv(rstr.Mid(106,1)+rstr.Mid(102,2)+rstr.Mid(107,1)+rstr.Mid(104,2));
				printRecv_Cur_Rec_Buck(rstr.Mid(107,1)+rstr.Mid(104,2));
				printRecv_Temp_Rec_MOS(rstr.Mid(110,1)+rstr.Mid(108,2));
				printRecv_BUCK_Mode_Rec(rstr.Mid(111,1));
				printRecv_Temp_Mode_Rec(rstr.Mid(111,1));
				printRecv_Effi(rstr.Mid(22,1)+rstr.Mid(18,2)+rstr.Mid(23,1)+rstr.Mid(20,2)+rstr.Mid(106,1)+rstr.Mid(102,2)+rstr.Mid(107,1)+rstr.Mid(104,2));


				// 校验未写
				
		}
			else{
				printStatus(_T("数据帧不正常，请重新发送指令"));
				printStatus(_T("\n"));
			}
			rstr ="";
			RxLenTotal =0;
			printStatus(_T("\n数据帧正常"));
			printStatus(_T("\n"));
	}
		// 避免58字节和31字节命令进入
		if((RxLenTotal==11)&&(rstr.Mid(2,2)!="0f")&&(rstr.Mid(2,2)!="1e")&&(rstr.Mid(2,2)!="4b"))
			{
				printStatus(rstr);
				printStatus(_T("\n"));

	// 根据接收数据第二个字节分别写入不同的框
				// 指令1,3,7,8
				if(rstr.Mid(2,2)=="2d"){
				//printRecv_Work_Status(rstr.Mid(8,2));
				printReset_Flag(rstr.Mid(8,2));
				printDetected_Car(rstr.Mid(8,2));
				printWork_Status(rstr.Mid(8,2));
				printFault_Trans(rstr.Mid(8,2));
				printFault_Rec(rstr.Mid(8,2));
				printFault(rstr.Mid(8,2));
				printFinish_Charge(rstr.Mid(8,2));
				printcheck(rstr.Mid(12,10));

				// test
				//CString strn=rstr.Mid(8,2);
			 //   char temp[10];
				//CString stu1;
				//CString stu2;
				//CString buck1;
				//CString buck2;
				//CString stu3;
				//long stu;
			 //   ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
			 //   const char *str1=temp;
				//stu=strtol(str1,0,16);
				//stu1.Format(_T("%ld"),stu);
				//while(stu!=0){
				//	if(stu%2==0)
				//	{stu2 = _T("0") + stu2;}
				//	else
				//	{stu2 = _T("1") + stu2;}
				//	stu = stu/2;
				//}
				//// 补齐二进制数
				////int i = 8 - sizeof(stu2);
				/*CString stu2;
				stu2 ="10000";
				int i =stu2.GetLength();*/
				//for(; i>=1; i--){
				//	stu3 = _T('0') + stu3;
				//}
				//stu2 = stu3 + stu2;
				//buck1 = stu2.Mid(0,1);
				////buck2 = stu2.Mid(0,2);
				//if (buck1 =="")
				//{
				//	buck1 =_T("00");}
			
				// test check
				/*CString stu1;
				stu1 = rstr.Mid(12,10);
				long stu;
				long zongshu=0;
				stu1 = str;
				int j = stu1.GetLength();
				CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Status);
				int nLength = pEdit->GetWindowTextLength();
				pEdit->SetSel(nLength, nLength);
				for(int i=0;i<=stu1.GetLength()-3;i+=2)
				{
				CString strn=str.Mid(i,2);
				char temp[10];
				::wsprintfA(temp, "%ls",(LPCTSTR)strn);
				const char *str1=temp;
				stu=strtol(str1,0,16);
				zongshu+=stu;
				}
				stu1.Format(_T("%lx"),zongshu);
				if((stu1.GetLength()==1)){
					stu1 = _T("0") +stu1;
				}
				if(stu1.Right(2)==str.Right(2))
				{
				pEdit->ReplaceSel(_T("\n数据校验成功\n"));
				pEdit->ReplaceSel(_T("\n"));
				}
				else
				{
				pEdit->ReplaceSel(_T("    数据校验失败"));
				pEdit->ReplaceSel(_T("\n"));
				}*/

		    }
			// 指令2
				else if(rstr.Mid(2,2)=="3c"){
				printRecv_Vot_Limit_Trans(rstr.Mid(10,2)+rstr.Mid(8,2));
				printRecv_Cur_Limit_Trans(rstr.Mid(14,2)+rstr.Mid(12,2));
				printRecv_Relay(rstr.Mid(16,2));
				//printcheck(rstr.Mid(8,10));
				
			}	
			// 指令4
				else if(rstr.Mid(2,2)=="4b"){
				//printRecv_Work_Status(rstr.Mid(8,2));
				/*printReset_Flag(rstr.Mid(8,2));
				printDetected_Car(rstr.Mid(8,2));
				printWork_Status(rstr.Mid(8,2));*/
				printStatus(rstr);

			}
			/*else {
				printStatus(_T("数据帧不正常，请重新发送指令"));
				printStatus(_T("\n"));
			}*/

				else{
					printStatus(_T("数据帧不正常，请重新发送指令"));
				}
			rstr ="";
			RxLenTotal =0;
			printStatus(_T("\n数据帧正常"));
			printStatus(_T("\n"));

		}

		


		//指令6
		if((RxLenTotal==31)&&(rstr.Mid(2,2)!="0f")&&(rstr.Mid(2,2)!="4b"))
			{
				printStatus(rstr);
				printStatus(_T("\n"));

	
			if(rstr.Mid(2,2)=="1e"){
				/*if(rstr.Mid(52,1)=='0'){
					rstr.Mid(36,16)=="00";
				}*/
				printRecv_Fault_Type(rstr.Mid(8,2));
				printRecv_Vot_Limit_Trans_Err(rstr.Mid(14,1)+rstr.Mid(10,2));
				printRecv_Cur_Limit_Trans_Err(rstr.Mid(15,1)+rstr.Mid(12,2));
				printRecv_Vot_Trans_Buck_In_Err(rstr.Mid(20,1)+rstr.Mid(16,2));
				printRecv_Duty_Trans_Buck_Err(rstr.Mid(21,1)+rstr.Mid(18,2));
				printRecv_Vot_Trans_Buck_Out_Err(rstr.Mid(26,1)+rstr.Mid(22,2));
				printRecv_Cur_Trans_Buck_Err(rstr.Mid(27,1)+rstr.Mid(24,2));
				printRecv_Temp_Trans_MOS_Err(rstr.Mid(35,1)+rstr.Mid(28,2));
				printRecv_Fre_Trans_Inverter_Err(rstr.Mid(34,1)+rstr.Mid(32,2)+rstr.Mid(30,2));
				printRecv_Vot_Limit_Rec_Err(rstr.Mid(40,1)+rstr.Mid(36,2));
				printRecv_Cur_Limit_Rec_Err(rstr.Mid(41,1)+rstr.Mid(38,2));
				printRecv_Vot_Rec_Buck_In_Err(rstr.Mid(46,1)+rstr.Mid(42,2));
				printRecv_Duty_Rec_Buck_Err(rstr.Mid(47,1)+rstr.Mid(44,2));
				printRecv_Vot_Rec_Buck_Out_Err(rstr.Mid(52,1)+rstr.Mid(48,2));
				printRecv_Cur_Rec_Buck_Err(rstr.Mid(53,1)+rstr.Mid(50,2));
				printRecv_Temp_Rec_MOS_Err(rstr.Mid(57,1)+rstr.Mid(54,2));

				


		}
			else{
				printStatus(_T("数据帧不正常，请重新发送指令"));
				printStatus(_T("\n"));
				rstr ="";
				RxLenTotal =0;
			}
		rstr ="";
		RxLenTotal =0;
		printStatus(_T("\n数据帧正常"));
		printStatus(_T("\n"));
	}
		//// 扫频 长度不定
		//{
		//	if((RxLenTotal==11)&&(rstr.Mid(2,2)=="4b")){
		//	printStatus(rstr);
		//	//Rstr = Rstr + rstr;
		//	
		//}
		//int array[2][100];
		//int len_rstr = rstr.GetLength();
		//	// 将电流和频率取出转为10进制
		//	for(int i=0; i<=len_rstr/22-1; i++){
		//		array[1][i] = (print_Cur(rstr.Mid(12+i*22,2)+rstr.Mid(10+i*22,2)))/1000;
		//		array[0][i] = (print_Cur(rstr.Mid(18+i*22,2)+rstr.Mid(16+i*22,2)+Rstr.Mid(14+i*22,2)))/1000;
		//	}
		//	rstr ="";
		//	RxLenTotal =0;
		//}

		// 扫频
		// test
		/*CString test;
		CString test2;
		test = rstr.Right(14);
		test2 = test.Mid(0,2);*/

		//if((RxLenTotal==440)){
			if((RxLenTotal==891)&&(rstr.Mid(2,2)=="4b")){
			//if((RxLenTotal%11==0)&&(rstr.Mid(2,2)=="4b")){
			//if((RxLenTotal%17==0)&&(((rstr.Right(14)).Mid(0,2))=="f0")){
			printStatus(rstr);
			int array[2][100];
			int brray[2][100];
			// 将电流和频率取出转为10进制
			for(int i=0; i<=((rstr.GetLength())/22)-1; i++){
				array[1][i] = (print_Cur(rstr.Mid(12+i*22,2)+rstr.Mid(10+i*22,2)));
				brray[1][i] = array[1][i];
				array[0][i] = (print_Cur(rstr.Mid(18+i*22,2)+rstr.Mid(16+i*22,2)+rstr.Mid(14+i*22,2)));
				//brray[0][i] = array[0][i]/1000;
				brray[0][i] = array[0][i];
			}
			for(int i = 0; i<=100; i++)
				if((array[1][i]> 4096000)||(array[1][i]< 0)){
					array[1][i] = 0;
					brray[1][i] = 0;
				}

			//输出最大值
			/*int Cur_Max = 0;
			int Frc;
			int m = ((rstr.GetLength())/22)-2;
			for(int j=0; j<= 100; j++){
				if((Cur_Max<=array[1][j])){
					Cur_Max=array[1][j];
					Frc = array[0][j];
				}	
			}*/
			// test
			// 
			/*CString stu1;
			CString stu2;
			stu2.Format(_T("%ld"),Frc);*/
			//stu1.Format(_T("%ld"),Cur_Max);
			/*CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Frc);
			int nLength = pEdit->GetWindowTextLength();
			pEdit->SetSel(nLength, nLength);
			GetDlgItem(IDC_EDIT_Frc)->SetWindowText(_T(""));
			pEdit->ReplaceSel(stu2); */
			DrawWave(brray);
			rstr ="";
			RxLenTotal =0;
			
			
			
			
	}
	
	}
	else
	{
		printStatus(_T("数据帧不正常，请重新发送指令"));
		printStatus(_T("\n"));
		rstr ="";
	    RxLenTotal =0;
	}
	/*rstr ="";
	RxLenTotal =0;*/
	return 0;
}

void CCommDlg::toggleButtonStatus(BOOL isopen)
{
	GetDlgItem(IDC_BUTTON_Send)->EnableWindow(isopen);
	//GetDlgItem(IDC_BUTTON_Start)->EnableWindow(isopen);
	//GetDlgItem(IDC_BUTTON_Stop)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BUTTON_Start2)->EnableWindow(isopen);
	//GetDlgItem(IDC_BUTTON_Stop)->EnableWindow(FALSE);
}

//***********************
// 枚举所有的串口，以及名称
//***********************
int CCommDlg::GetComList_Reg()
{
    HKEY hkey;  
    int result;
    int count = 0;

	CComboBox * CCombox  = (CComboBox*)GetDlgItem(IDC_COMBO_Port);

    CString strComName;//串口名称
	CString strDrName;//串口详细名称

	result = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
							_T( "Hardware\\DeviceMap\\SerialComm" ),
							NULL,
							KEY_READ,
							&hkey );

	if(result == ERROR_SUCCESS)   //   打开串口注册表   
	{   
		TCHAR portName[ 0x100 ], commName[ 0x100 ];
		DWORD dwLong, dwSize;

		CCombox->ResetContent();
		do
		{   
			dwSize = sizeof( portName ) / sizeof( TCHAR );
			dwLong = dwSize;
			result = RegEnumValue( hkey, count, portName, &dwLong, NULL, NULL, ( LPBYTE )commName, &dwSize );
			if( ERROR_NO_MORE_ITEMS == result )
			{
				//   枚举串口
				break;   //   commName就是串口名字"COM2"
			}
			strComName=commName;
			strDrName = portName;

			// 从右往左边开始查找第一个'\\'，获取左边字符串的长度
			int len = strDrName.ReverseFind( '\\');
			// 获取'\\'左边的字符串
			CString strFilePath = strDrName.Left( len+1 );
			// 获取'\\'右边的字符串
			CString fileName = strDrName.Right(strDrName.GetLength() - len-1);
			fileName = strComName + _T(": ")+fileName;

			CCombox->AddString(strComName);
			count++;   
		} while ( 1 );

		RegCloseKey( hkey );   
	}

	CCombox->SetCurSel(0);
    return count;
}




void CCommDlg::OffsetProgress()
{
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC_Progress);
	CString str;
	myProCtrl->OffsetPos(1);
	int pos = myProCtrl->GetPos();
	int lower,upper;
	myProCtrl->GetRange(lower, upper);
	
	str.Format(_T("%2d%%"), pos*100/upper);
	pStatic->SetWindowText(str);
}

/**
  * @brief: 串口打开函数
  */
void CCommDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPort;
	GetDlgItem(IDC_COMBO_Port)->GetWindowText(strPort);
	CString strBaudrate;
	GetDlgItem(IDC_COMBO_Baudrate)->GetWindowText(strBaudrate);
	CString strButtonOpen;
	GetDlgItem(IDC_BUTTON_Open)->GetWindowText(strButtonOpen);
	if(!strButtonOpen.CompareNoCase(_T("Close")))
	{
		GetDlgItem(IDC_BUTTON_Open)->SetWindowText(_T("Open"));
		toggleButtonStatus(FALSE);
		if(CloseSerialPort())
			printStatus(_T("关闭") + strPort + _T("成功\n"));  
		else
			MessageBox(_T("关闭") + strPort + _T("失败\n"));  
		return;
	}
	
	if(!SerialOpen(this->GetSafeHwnd(), strPort, _ttoi(strBaudrate)))
	{
		MessageBox(strPort +"打开失败");
		return;
	}
	GetDlgItem(IDC_BUTTON_Open)->SetWindowText(_T("Close"));
	printStatus(strPort + _T("打开成功\n")); 
	toggleButtonStatus();
	
	
}
// 获取反码
CString CCommDlg::printInv(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
	long stu_Inv;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,10);
	//stu=stu&(0x0F);
	stu_Inv = 255 - stu;
	stu1.Format(_T("%x"),stu_Inv);
	return stu1;
}

// 获取16进制的单体桩编号
CString CCommDlg::print16(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,10);
	//stu=stu&(0x0F);
	stu1.Format(_T("%x"),stu);
	return stu1;
}
void CCommDlg::OnBnClickedButtonSend()
{
	CString strSend;
	GetDlgItem(IDC_EDIT_Send)->GetWindowText(strSend);
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
}

// 读取单体桩状态
void CCommDlg::OnClickedButtonSend1()
{
	CString strSend;
	CString Cnum;
	CString Cnum_Inv;
	strSend="55 ";
	// 获取单体桩编码
	GetDlgItemText(IDC_EDIT_Num,Cnum);
	// 计算单体桩编码的反码
	Cnum_Inv = printInv(Cnum);
	// 计算16进制单体桩编号
	Cnum = print16(Cnum);
	//Cnum_Inv ="e6";
	if(Cnum.GetLength()==1){
		Cnum = '0' + Cnum;
	}
	strSend = strSend + Cnum +" " + Cnum_Inv;
	strSend += " 0f 00 00 00 00 00";
	
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
	
}


// 开启充电
void CCommDlg::OnClickedButtonSend2()
{
	CString strSend;
	CString Cnum;
	CString Cnum_Inv;
	CString updVoltage;
	CString updCurrent;
	CString relay;
	CString buffer;
	CString sum;
	strSend="55 ";
	// 获取单体桩编码
	GetDlgItemText(IDC_EDIT_Num,Cnum);
	// 计算单体桩编码的反码
	Cnum_Inv = printInv(Cnum);
	// 计算16进制单体桩编号
	Cnum = print16(Cnum);
	// 获取电压限值
	GetDlgItemText(IDC_EDIT_Update_Voltage,updVoltage);
	// 计算16进制电压限值
	updVoltage = print16(updVoltage);
	// 获取电流限值
	GetDlgItemText(IDC_EDIT_Update_Current,updCurrent);
	// 计算16进制电压限值
	updCurrent = print16(updCurrent);
	// 获取继电器值
	GetDlgItemText(IDC_EDIT_Relay_Charge,relay);
	// 计算16进制继电器值
	relay = print16(relay);
	// 解决继电器值为一位时的bug
	// 计算字节7的值
	buffer =updVoltage.Mid(0,1)+updCurrent.Mid(0,1);
	// 计算校验值
	sum=updVoltage.Mid(1,2)+updCurrent.Mid(1,2)+buffer+relay;
	CString stu1;
	long stu;
	long zongshu=0;
	for(int i=0;i<=6;i+=2)
	{
	CString strn=sum.Mid(i,2);
    char temp[10];
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	zongshu+=stu;
	}
	stu1.Format(_T("%lx"),zongshu);
	if((stu1.GetLength()>2)){
		stu1 = stu1.Mid(1,2);
	}
	if(Cnum.GetLength()==1){
		Cnum = '0' + Cnum;
	}
	// 拼接字符串
	strSend = strSend + Cnum +" " + Cnum_Inv;
	//strSend += " 0f 00 00 00 00 00";
	strSend += " 1E ";
	strSend = strSend + updVoltage.Mid(1,2);
	strSend = strSend + " "+ updCurrent.Mid(1,2) + " " + buffer +" " + relay + " " + stu1;
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}

// 停止充电
void CCommDlg::OnClickedButtonSend3()
{
	CString strSend;
	CString Cnum;
	CString Cnum_Inv;
	strSend="55 ";
	// 获取单体桩编码
	GetDlgItemText(IDC_EDIT_Num,Cnum);
	// 计算单体桩编码的反码
	Cnum_Inv = printInv(Cnum);
	// 计算16进制单体桩编号
	Cnum = print16(Cnum);
	if(Cnum.GetLength()==1){
		Cnum = '0' + Cnum;
	}
	strSend = strSend + Cnum +" " + Cnum_Inv;
	strSend += " 2D 00 00 00 00 00";
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}
//
//扫频
void CCommDlg::OnClickedButtonSend4()
{
	CString strSend;
	CString Cnum;
	CString Cnum_Inv;
	CString Relay_Sweep;
	CString Relay_Sweep_Inv;
	CString Duty;
	CString Duty_Low;
	CString Duty_Hig;
	CString sum;
	strSend="55 ";
	// 获取单体桩编码
	GetDlgItemText(IDC_EDIT_Num,Cnum);
	// 计算单体桩编码的反码
	Cnum_Inv = printInv(Cnum);
	// 计算16进制单体桩编号
	Cnum = print16(Cnum);
	if(Cnum.GetLength()==1){
		Cnum = '0' + Cnum;
	}
	strSend = strSend + Cnum +" " + Cnum_Inv;
	strSend += " 3C ";
	// 获取继电器值
	GetDlgItemText(IDC_EDIT_Relay_Sweep,Relay_Sweep);
	// 获取继电器反码
	Relay_Sweep_Inv = printInv(Relay_Sweep);
	// 计算16进制继电器值
	Relay_Sweep = print16(Relay_Sweep);
	// 获取占空比值
	GetDlgItemText(IDC_EDIT_Duty,Duty);
	// 计算16进制占空比值
	Duty = print16(Duty);
	Duty_Low = Duty.Mid(1,2);
	Duty_Hig = '0' + Duty.Mid(0,1);

	// 计算校验值
	sum=Duty_Low+Duty_Hig;
	CString stu1;
	long stu;
	long zongshu=0;
	for(int i=0;i<=6;i+=2)
	{
	CString strn=sum.Mid(i,2);
    char temp[10];
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	zongshu+=stu;
	}
	stu1.Format(_T("%lx"),zongshu);

	// 拼接字符串
	strSend = strSend + Relay_Sweep + " "+ Relay_Sweep_Inv + " " + Duty_Low + " " + Duty_Hig + " " + stu1;
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}
//
// 读取全部信息
void CCommDlg::OnClickedButtonSend5()
{
	if(IsDlgButtonChecked(IDC_CHECK2))//按钮被按下
	{
		SetTimer(1,1000,NULL);
	}
	else
	{
		KillTimer(1);
	}
	CString strSend;
	CString Cnum;
	CString Cnum_Inv;
	strSend="55 ";
	// 获取单体桩编码
	GetDlgItemText(IDC_EDIT_Num,Cnum);
	// 计算单体桩编码的反码
	Cnum_Inv = printInv(Cnum);
	// 计算16进制单体桩编号
	Cnum = print16(Cnum);
	if(Cnum.GetLength()==1){
		Cnum = '0' + Cnum;
	}
	strSend = strSend + Cnum +" " + Cnum_Inv;
	strSend += " 4B 00 00 00 00 00";
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}
//
//读取故障信息
void CCommDlg::OnClickedButtonSend6()
{
	CString strSend;
	CString Cnum;
	CString Cnum_Inv;
	strSend="55 ";
	// 获取单体桩编码
	GetDlgItemText(IDC_EDIT_Num,Cnum);
	// 计算单体桩编码的反码
	Cnum_Inv = printInv(Cnum);
	// 计算16进制单体桩编号
	Cnum = print16(Cnum);
	if(Cnum.GetLength()==1){
		Cnum = '0' + Cnum;
	}
	strSend = strSend + Cnum +" " + Cnum_Inv;
	strSend += " 5A 00 00 00 00 00";
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					//MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}
//
//清零复位标志
void CCommDlg::OnClickedButtonSend7()
{
	CString strSend;
	CString Cnum;
	CString Cnum_Inv;
	strSend="55 ";
	// 获取单体桩编码
	GetDlgItemText(IDC_EDIT_Num,Cnum);
	// 计算单体桩编码的反码
	Cnum_Inv = printInv(Cnum);
	// 计算16进制单体桩编号
	Cnum = print16(Cnum);
	//Cnum_Inv ="e6";
	if(Cnum.GetLength()==1){
		Cnum = '0' + Cnum;
	}
	strSend = strSend + Cnum +" " + Cnum_Inv;
	strSend += " 69 00 00 00 00 00";
	//GetDlgItem(IDC_COMBO_Order4)->GetWindowText(strSend);
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}
//
//设定单体桩编号
void CCommDlg::OnClickedButtonSend8()
{
	CString strSend;
	CString Cnum;
	CString Cnum_Inv;
	strSend="55 ff 00 ";
	// 获取单体桩编码
	GetDlgItemText(IDC_EDIT_Num,Cnum);
	// 计算单体桩编码的反码
	Cnum_Inv = printInv(Cnum);
	// 计算16进制单体桩编号
	Cnum = print16(Cnum);
	//Cnum_Inv ="e6";
	strSend = strSend + Cnum +" " + Cnum_Inv;
	strSend += " 00 00 00 00";
	//GetDlgItem(IDC_COMBO_Order4)->GetWindowText(strSend);
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}


void CCommDlg::OnCbnSelchangeComboPort()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCommDlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: 在此添加控件通知处理程序代码
}




void CCommDlg::OnEnChangeEditSend()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	//#1015

	// TODO:  在此添加控件通知处理程序代码
}




void CCommDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
	OnClickedButtonSend5();
}
//



HBRUSH CCommDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	CString strr1;
	CString strr2;
	CString strr3;
	CString strr4;
	CString strr5;
	CString strr6;
	GetDlgItemText(IDC_EDIT_Reset_Flag,strr1);//判断Flag_Infrary值
	GetDlgItemText(IDC_EDIT_Fault_Trans,strr2);//判断Flag_Infrary值
	GetDlgItemText(IDC_EDIT_Detected_Car,strr3);//判断Flag_Infrary值
	GetDlgItemText(IDC_EDIT_Work_Status,strr4);//判断Flag_Infrary值
	GetDlgItemText(IDC_EDIT_Fault_Rec,strr5);//判断Flag_Infrary值
	GetDlgItemText(IDC_EDIT_Fault,strr6);
	switch (nCtlColor) //对所有同一类型的控件进行判断  
	{
	case CTLCOLOR_EDIT:  
	case CTLCOLOR_MSGBOX://假设控件是文本框或者消息框，则进入下一个switch  
	switch (pWnd->GetDlgCtrlID())//对某一个特定控件进行判断  
   {      
   case IDC_EDIT_Reset_Flag:         // 复位  
	   if((strr1 == "1")){
	m_textcolor1=RGB(255,0,0);;//红色
	}
	   else{m_textcolor1=RGB(0,255,0);}
    //pDC->SetBkColor(m_color);    // change the background  
    pDC->SetTextColor(m_textcolor1); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break;    
   
	case IDC_EDIT_Fault_Trans:         // 发射端故障 
		if((strr2 == "1")){
	m_textcolor2=RGB(255,0,0);;//红色
	}
		else{m_textcolor2=RGB(0,255,0);}
    //pDC->SetBkColor(m_color);    // change the background  
    pDC->SetTextColor(m_textcolor2); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break;  

	case IDC_EDIT_Detected_Car:         // 是否检测到车辆
		if((strr3 == "0")){
	m_textcolor3=RGB(255,0,0);;//红色
	}
		else{m_textcolor3=RGB(0,255,0);}
    //pDC->SetBkColor(m_color);    // change the background  
    pDC->SetTextColor(m_textcolor3); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break; 

	// 无车辆时接收端和红外数据全部变红
	case IDC_EDIT_Bike_ID:         
		if((strr3 == "0")){
	m_textcolor7=RGB(255,0,0);;//红色
	}
		else{m_textcolor7=RGB(0,255,0);}
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break; 

	case IDC_EDIT_Vot_Limit_Rec:            
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break; 

	case IDC_EDIT_Cur_Limit_Rec:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break; 

	case IDC_EDIT_Vot_Rec_Buck_In:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break; 

	case IDC_EDIT_Vot_Rec_Buck_Out:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break; 

	case IDC_EDIT_Power_Recv:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break; 

	case IDC_EDIT_Cur_Rec_Buck:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break;

	case IDC_EDIT_Duty_Rec_Buck:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break;

	case IDC_EDIT_Temp_Rec_MOS:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break;

	case IDC_EDIT_BUCK_Mode_Rec:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break;

	case IDC_EDIT_Temp_Mode_Rec:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break;

	case IDC_EDIT_Infrared_Rec_Succ_Cnt:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break;

	case IDC_EDIT_Infrared_Decode_Error_Cnt:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break;

	case IDC_EDIT_Infrared_Waiting_First_Cnt:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break;

	case IDC_EDIT_Infrared_Waiting_Second_Cnt:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break;

	case IDC_EDIT_Infrared_Waiting_Third_Cnt:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break;

	case IDC_EDIT_Infrared_Rec_Error_Cnt:         
    //pDC->SetBkColor(m_color);    
    pDC->SetTextColor(m_textcolor7); 
    hbr = (HBRUSH) m_brush;     
    break;

	case IDC_EDIT_Work_Status:         // 工作状态 
		if((strr4 == "00")){
	m_textcolor4=RGB(255,0,0);;//红色
	}
		else{m_textcolor4=RGB(0,255,0);}
    //pDC->SetBkColor(m_color);    // change the background  
    pDC->SetTextColor(m_textcolor4); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break; 

	case IDC_EDIT_Fault_Rec:         // 接收端故障  
		if((strr5 == "1")){
	m_textcolor5=RGB(255,0,0);;//红色
	}
		else{m_textcolor5=RGB(0,255,0);}
    //pDC->SetBkColor(m_color);    // change the background  
    pDC->SetTextColor(m_textcolor5); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break; 

	case IDC_EDIT_Fault:         // 故障类型  
		if((strr6 == "1")){
	m_textcolor6=RGB(255,0,0);;//红色
	}
		else{m_textcolor6=RGB(0,255,0);}
    //pDC->SetBkColor(m_color);    // change the background  
    pDC->SetTextColor(m_textcolor6); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break; 

   default:  
    hbr=CDialogEx::OnCtlColor(pDC,pWnd,nCtlColor);  
    break;  
   
   }  
	     
   
   break;  
}  
 //TODO: Return a different brush if the default is not desired  
	return hbr;

}



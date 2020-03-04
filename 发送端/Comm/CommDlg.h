
// CommDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#define POINT_COUNT 50

// CCommDlg 对话框
class CCommDlg : public CDialogEx
{
// 构造
public:
	CCommDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COMM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	CBrush m_brush;  
    COLORREF m_color,m_textcolor1,m_textcolor,m_textcolor2,m_textcolor3,m_textcolor4,m_textcolor5,m_textcolor6;
	COLORREF m_textcolor7;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnRecvDataHandler(WPARAM wParam, LPARAM lParam);  
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSend();
	void CCommDlg::DrawWave(int brray[2][100]);
private:
	HBRUSH CCommDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void toggleButtonStatus(BOOL isopen=TRUE);
	int GetComList_Reg();
	void printStatus(CString str);
	void printRecvStatus(CString str);
	CString CCommDlg::printInv(CString str);
	CString CCommDlg::print16(CString str);
	void  CCommDlg::printReset_Flag(CString str);
	void  CCommDlg::printDetected_Car(CString str);
	void  CCommDlg::printFinish_Charge(CString str);
	void  CCommDlg::printWork_Status(CString str);
	void  CCommDlg::printFault_Trans(CString str);
	void  CCommDlg::printFault_Rec(CString str);
	void  CCommDlg::printFault(CString str);
	void  CCommDlg::printRecv_Work_Status(CString str);
	void  CCommDlg::printRecv_Vot_Trans_Buck_In(CString str);
	void  CCommDlg::printRecv_Vot_Trans_Buck_In_Err(CString str);
	void  CCommDlg::printRecv_Duty_Trans_Buck(CString str);
	void  CCommDlg::printRecv_Duty_Trans_Buck_Err(CString str);
	void  CCommDlg::printRecv_Vot_Trans_Buck_Out(CString str);
	void  CCommDlg::printRecv_Vot_Trans_Buck_Out_Err(CString str);
	void  CCommDlg::printRecv_Cur_Trans_Buck(CString str);
	void  CCommDlg::printRecv_Cur_Trans_Buck_Err(CString str);
	void  CCommDlg::printRecv_Power_Trans(CString str);
	void  CCommDlg::printRecv_Relay(CString str);
	void  CCommDlg::printRecv_Temp_Trans_MOS(CString str);
	void  CCommDlg::printRecv_Temp_Trans_MOS_Err(CString str);
	void  CCommDlg::printRecv_Fre_Trans_Inverter(CString str);
	void  CCommDlg::printRecv_Fre_Trans_Inverter_Err(CString str);
	void  CCommDlg::printRecv_Vot_Limit_Trans(CString str);
	void  CCommDlg::printRecv_Vot_Limit_Trans_Err(CString str);
	void  CCommDlg::printRecv_Cur_Limit_Trans(CString str);
	void  CCommDlg::printRecv_Cur_Limit_Trans_Err(CString str);
	void  CCommDlg::printRecv_Infrared_Rec_Succ_Cnt(CString str);
	void  CCommDlg::printRecv_Infrared_Decode_Error_Cnt(CString str);
	void  CCommDlg::printRecv_Infrared_Waiting_First_Cnt(CString str);
	void  CCommDlg::printRecv_Infrared_Waiting_Second_Cnt(CString str);
	void  CCommDlg::printRecv_Infrared_Waiting_Third_Cnt(CString str);
	void  CCommDlg::printRecv_Infrared_Rec_Error_Cnt(CString str);
	void  CCommDlg::printRecv_Fault_Type(CString str);
	void  CCommDlg::printRecv_Bike_ID(CString str);
	void  CCommDlg::printRecv_Vot_Limit_Rec(CString str);
	void  CCommDlg::printRecv_Vot_Limit_Rec_Err(CString str);
	void  CCommDlg::printRecv_Cur_Limit_Rec(CString str);
	void  CCommDlg::printRecv_Cur_Limit_Rec_Err(CString str);
	void  CCommDlg::printRecv_Vot_Rec_Buck_In(CString str);
	void  CCommDlg::printRecv_Vot_Rec_Buck_In_Err(CString str);
	void  CCommDlg::printRecv_Duty_Rec_Buck(CString str);
	void  CCommDlg::printRecv_Duty_Rec_Buck_Err(CString str);
	void  CCommDlg::printRecv_Vot_Rec_Buck_Out(CString str);
	void  CCommDlg::printRecv_Vot_Rec_Buck_Out_Err(CString str);
	void  CCommDlg::printRecv_Cur_Rec_Buck(CString str);
	void  CCommDlg::printRecv_Cur_Rec_Buck_Err(CString str);
	void  CCommDlg::printRecv_Power_Recv(CString str);
	void  CCommDlg::printRecv_Effi(CString str);
	void  CCommDlg::printRecv_Temp_Rec_MOS(CString str);
	void  CCommDlg::printRecv_Temp_Rec_MOS_Err(CString str);
	void  CCommDlg::printRecv_BUCK_Mode_Rec(CString str);
	void  CCommDlg::printRecv_Temp_Mode_Rec(CString str);
	void  CCommDlg::printcheck(CString str);
	int  CCommDlg::print_Cur(CString str);

	void CCommDlg::OnClickedTimer();
	void OffsetProgress();
private:
	CProgressCtrl *myProCtrl;
public:
	CStatic m_static;
	int m_nzValues[POINT_COUNT];
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonOpenfile();
	afx_msg void OnBnClickedButtonDatatofile();
	//afx_msg void OnBnClickedCheckHexSend();
	afx_msg void OnBnClickedCheckHexRecv();
	afx_msg void OnCbnSelchangeComboPort();
	afx_msg void OnCbnSelchangeComboBaudrate();
	afx_msg void OnEnChangeEditSend();
	afx_msg void OnCbnSelchangeComboCmd();
	afx_msg void OnEnChangeEditDatafilename();
	afx_msg void OnCbnSelchangeComboAddr();
	afx_msg void OnCbnSelchangeComboEcc();
	afx_msg void OnCbnSelchangeComboData();
	//afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickedButtonSend1();
	afx_msg void OnClickedButtonSend2();
	afx_msg void OnClickedButtonSend3();
	afx_msg void OnClickedButtonSend4();
	afx_msg void OnClickedButtonSend5();
	afx_msg void OnClickedButtonSend6();
	afx_msg void OnClickedButtonSend7();
	afx_msg void OnClickedButtonSend8();
	afx_msg void OnEnChangeEditUpdateVoltage();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
 
};

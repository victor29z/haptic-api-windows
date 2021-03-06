// USBDevControlDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
//#include "DeltaUSBControl.h"		// test for the dll 
#include "DeltaControl.h"

#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")

#define TIMER_SEQ	1
#define	FORCE_SCALE	3			// 原用来定义临界点位的不用了
#define	F2DOUBLE	0.1			// The scale of the actual force to the gui control int value.  
#define	T2DOUBLE	0.001		// torque to gui int.
#define	REFRESH_RATE	1		// ratio of haptic loop to graphic loop	one for step testing
#define	ANGLE_RANGE		1		// angle range
#define	SCALAR_SERVO	100		// SERVO slid scalar

#define WM_UPDATE_IN_MESSAGE (WM_USER+200)

#define	TIMER1		1


// CUSBDevControlDlg 对话框
class CUSBDevControlDlg : public CDialog
{
// 构造
public:
	CUSBDevControlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_USBDEVCONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	CSliderCtrl m_slidMotor1;
	/*CSpinButtonCtrl m_spinMotor1;
	CSpinButtonCtrl m_spinMotor2;
	CSpinButtonCtrl m_spinMotor3;*/
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_slidMotor2;
	CSliderCtrl m_slidMotor3;	
	afx_msg void OnBnClickedBtnConnectDev();
	afx_msg LRESULT OnUpdateInMessage(WPARAM wParam, LPARAM lParam); 

	CDeltaUSBControl m_usbDev;			// dev control member
	//int m_nMotor1Dir;
	//int m_nMotor2Dir;
	//int m_nMotor3Dir;
	afx_msg void OnBnClickedBtnIoMsg();	
	//afx_msg void OnBnClickedBtnIoMsg2();

	bool m_blSeqCommu;
	//afx_msg void OnBnClickedBtnSeqCommu();	
	bool ChkPosIO(UINT16  threshold[3]);		// check the position. If the positon is bigger than the threshold the SetMotorGetPosStatues will called 
												// to setup the PWM as a feedback
	//void static CALLBACK SendFun(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);
	//void MMTimerHandler(UINT nIDEvent); // called every elTime milliseconds
	void MMTimerHandler(UINT nIDEvent);
	bool CreateTimer();
	void DestroyTimer();
	//void static STGetChk(CUSBDevControlDlg* );

	afx_msg void OnBnClickedBtnMmTimer();
	afx_msg void OnBnClickedRadMotor1();
	afx_msg void OnBnClickedRadMotor1b();
	afx_msg void OnBnClickedRadMotor2();
	afx_msg void OnBnClickedRadMotor2b();
	afx_msg void OnBnClickedRadMotor3();
	afx_msg void OnBnClickedRadMotor3b();
	afx_msg void OnBnClickedChkMotor1();
	//BOOL m_blMotor1;
	//BOOL m_blMotor2;
	//BOOL m_blMotor3;
	afx_msg void OnBnClickedChkMotor2();
	afx_msg void OnBnClickedChkMotor3();
	afx_msg void OnBnClickedBtnTest1();

	// void TestIo();
	


	double m_dHX[3];				// 手柄位置
	double m_dHDConfig[4];		// 手柄构型
	double m_dF[3];			 // 力
	double m_dT[6];			// 力矩
	double m_dTest[6];		// test the thread communication
	double m_dRadServo[6];
	
	// PID parameters
	double	m_kp;
	double	m_ki;
	double	m_up;
	double	m_ui[6];
	double	m_outpre[6];
	double	m_outnow[6];
	double	m_outmax;


	// Encoder is in rad unit;
	/*int m_nEncoder1;
	int m_nEncoder2;
	int m_nEncoder3;*/
	BYTE m_statu;

	CWinThread* m_pThread;
	HANDLE hThread1;

	double m_dRad[6];
	afx_msg void OnBnClickedChkFor();
	afx_msg void OnBnClickedBtnSetf();
	afx_msg void OnBnClickedBtnClearF();
	CListCtrl m_listDev;
	CListCtrl m_listForce;
	CSliderCtrl m_slidFX;
	CSliderCtrl m_slidFY;
	CSliderCtrl m_slidFZ;
	CSliderCtrl m_slidMotor4;
	CSliderCtrl m_slidMotor5;
	CSliderCtrl m_slidMotor6;
	int			 m_nForceCtrl;
	afx_msg void OnBnClickedRadF();
	afx_msg void OnBnClickedRadAct();
	afx_msg void OnBnClickedBtnTimer1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	


	/*************************************************
	Function: // GetServoTorque
	Description: // according to the serv rad and feedback, get the torque needed.
	Calls: // 被本函数调用的函数清单
	Called By: // 调用本函数的函数清单
	Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
	Table Updated: // 被修改的表（此项仅对于牵扯到数据库操作的程序）
	Input: // 输入参数说明，包括每个参数的作// 用、取值说明及参数间关系。
			servoRad:	the target radian value of 6 axes. range: [-1 1]. 
			fdbRad:		the feedback radian of 6 axes. range [-1.2 1.2];
	Output: torque:		torque needed in this loop to get the setting point.
	Return: // 函数返回值的说明
	Others: // 其它说明
	*************************************************/
	void GetServoTorque(double servoRad[6], double fdbRad[6],double torque[6]);	
	
};

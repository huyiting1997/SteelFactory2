
// MFCApplication3Dlg.h: 头文件
//

#pragma once
#include<vector>
#include<string>
#include "afxdialogex.h"
#include"GeneralDef.h"
#include"PreviewStatic.h"
#include"LogicControl.h"
#include"../../include/cameraCtrl/HCNetSDK.h"
#include"../../include/sensor/ModbusRtuHandler.h"
#include"../../include/sensor/WirelessRangingHandler.h"

// CMFCApplication3Dlg 对话框
class CMFCApplication3Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication3Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	std::vector<PAIR_IP2CAMERA> m_cameras; //实现摄像头IP到ID的映射（登录时返回的ID）
	//ID的作用判断是否登陆成功，登陆失败返回值为-1
	CPreviewStatic		m_previewTopLeft;
	CPreviewStatic		m_previewTopRight;
	CPreviewStatic		m_previewBottomLeft;
	CPreviewStatic		m_previewBottomMid;
	CPreviewStatic		m_previewBottomRight;
	std::vector<std::string>IPMuster;//用于储存全部IP，登录摄像头


    // 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
	
	bool DoLogin(std::string& devIP, int& devPort, std::string& user, std::string& password);//对摄像头设备进行登录
	void ScreenSwitching();//实现画面切换
	void AlarmLightSwitching(BOOL sitution);//实现警灯切换
	void ChangeColor(HICON icon1,HICON icon2);//设置指示灯颜色
	void DistanceDisplay();//在界面上显示距离
public:
	//实现指示灯切换
	CStatic m_iconL;
	CStatic m_iconR;
	HICON m_hIconRed;
	HICON m_hIconYellow;
	HICON m_hIconGreen;
	double  disL;//左边距
	double	disR;//右边距
	double  carDis;//小车距离
	double  baseStationPosition;//基站位置
	double  nearestTagPosition;//最近的标签距离
	int     tagID;//最近的标签ID

	LogicControl m_logicControl;//控制层对象

	ModbusRtuHandler rtuHandler;//激光串口读取
	WirelessRangingHandler rangingHandler;//基站读取
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//控件变量
	CStatic m_disL;
	CStatic m_disR;
	afx_msg void OnClose();
};




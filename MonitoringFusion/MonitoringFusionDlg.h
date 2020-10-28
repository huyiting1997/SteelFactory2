
// MonitoringFusionDlg.h: 头文件
//

#pragma once

#include "./include/database/CAR.h"
#include "./include/database/stationDlg.h"
#include "./include/database/Alarm_WarnDlg.h"
#include "./include/database/CONSTANT.h"

// CMonitoringFusionDlg 对话框
class CMonitoringFusionDlg : public CDialogEx
{
// 构造
public:
	CMonitoringFusionDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONITORINGFUSION_DIALOG };
#endif

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
	CTabCtrl m_tabCtrl1;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);

public:
	CAR m_carDlg;
	Alarm_WarnDlg m_awDlg;
	CONSTANT m_constantDlg;
	stationDlg m_statDlg;
};

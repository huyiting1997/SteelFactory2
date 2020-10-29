#pragma once


// login 对话框
#include "../logicalCtrl/MFCApplication3Dlg.h"

class login : public CDialogEx
{
	DECLARE_DYNAMIC(login)

public:
	login(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~login();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_username;
	CString m_password;
	virtual BOOL OnInitDialog();
	CComboBox m_selectRoleCombo;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CFont m_editFont;
	CStatic m_static_title;

	CMFCApplication3Dlg m_MFCApplication3Dlg;

};

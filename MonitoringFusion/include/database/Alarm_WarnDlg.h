#pragma once


// Alarm_WarnDlg 对话框

class Alarm_WarnDlg : public CDialogEx
{
	DECLARE_DYNAMIC(Alarm_WarnDlg)

public:
	Alarm_WarnDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Alarm_WarnDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Alarm_Warn_DIALOG  };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list_alarm_warn;
	CEdit m_edit_aw;
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString m_selnum_aw;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

};

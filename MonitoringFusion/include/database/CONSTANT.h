#pragma once


// CONSTANT 对话框

class CONSTANT : public CDialogEx
{
	DECLARE_DYNAMIC(CONSTANT)

public:
	CONSTANT(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CONSTANT();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_constant;
	virtual BOOL OnInitDialog();
	CEdit m_edit_constant;
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

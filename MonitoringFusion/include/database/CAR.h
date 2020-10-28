#pragma once


// CAR 对话框

class CAR : public CDialogEx
{
	DECLARE_DYNAMIC(CAR)

public:
	CAR(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAR();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Car_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list_car;
	afx_msg void OnBnClickedButton1();
	CEdit m_edit;
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CString m_num_car_select;
	afx_msg void OnBnClickedButton4();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

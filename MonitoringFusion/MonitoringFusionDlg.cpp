
// MonitoringFusionDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MonitoringFusion.h"
#include "MonitoringFusionDlg.h"
#include "afxdialogex.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMonitoringFusionDlg 对话框



CMonitoringFusionDlg::CMonitoringFusionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MONITORINGFUSION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMonitoringFusionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl1);
}

BEGIN_MESSAGE_MAP(CMonitoringFusionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMonitoringFusionDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CMonitoringFusionDlg 消息处理程序

BOOL CMonitoringFusionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//CAR m_carDlg;
	//Alarm_WarnDlg m_awDlg;
	//CONSTANT m_constantDlg;
	//stationDlg m_statDlg;

	// TODO: 在此添加额外的初始化代码
	m_tabCtrl1.InsertItem(0, _T("行车表"));
	m_tabCtrl1.InsertItem(1, _T("工位表"));
	m_tabCtrl1.InsertItem(2, _T("预警、报警表"));
	m_tabCtrl1.InsertItem(3, _T("常量表"));

	// 创建三个子对话框
	m_awDlg.Create(IDD_Alarm_Warn_DIALOG, &m_tabCtrl1);
	m_carDlg.Create(IDD_Car_DIALOG, &m_tabCtrl1);
	m_constantDlg.Create(IDD_CONSTANT_DIALOG, &m_tabCtrl1);
	m_statDlg.Create(IDD_STATION_DIALOG, &m_tabCtrl1);

	// 调整子对话框大小及位置
	CRect rc;
	m_tabCtrl1.GetClientRect(&rc);
	CRect rcTabItem;
	m_tabCtrl1.GetItemRect(0, rcTabItem);
	rc.top += rcTabItem.Height() + 4;
	rc.left += 4;
	rc.bottom -= 4;
	rc.right -= 4;
	m_awDlg.MoveWindow(&rc);
	m_carDlg.MoveWindow(&rc);
	m_constantDlg.MoveWindow(&rc);
	m_statDlg.MoveWindow(&rc);

	// 默认标签选中
	m_carDlg.ShowWindow(SW_SHOW);
	m_tabCtrl1.SetCurFocus(0);
	int a = m_tabCtrl1.GetCurSel();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}



void CMonitoringFusionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMonitoringFusionDlg::OnPaint()
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMonitoringFusionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CMonitoringFusionDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	switch (m_tabCtrl1.GetCurSel())
	{
	case 0:
		m_carDlg.ShowWindow(SW_SHOW);
		m_statDlg.ShowWindow(SW_HIDE);
		m_awDlg.ShowWindow(SW_HIDE);
		m_constantDlg.ShowWindow(SW_HIDE);
		m_carDlg.SetFocus();
		break;
	case 1:
		m_carDlg.ShowWindow(SW_HIDE);
		m_statDlg.ShowWindow(SW_SHOW);
		m_awDlg.ShowWindow(SW_HIDE);
		m_constantDlg.ShowWindow(SW_HIDE);
		m_statDlg.SetFocus();
		break;
	case 2:
		m_carDlg.ShowWindow(SW_HIDE);
		m_statDlg.ShowWindow(SW_HIDE);
		m_awDlg.ShowWindow(SW_SHOW);
		m_constantDlg.ShowWindow(SW_HIDE);
		m_awDlg.SetFocus();
		break;
	case 3:
		m_carDlg.ShowWindow(SW_HIDE);
		m_statDlg.ShowWindow(SW_HIDE);
		m_awDlg.ShowWindow(SW_HIDE);
		m_constantDlg.ShowWindow(SW_SHOW);
		m_constantDlg.SetFocus();
		break;
	case 4:
		m_carDlg.ShowWindow(SW_HIDE);
		m_statDlg.ShowWindow(SW_HIDE);
		m_awDlg.ShowWindow(SW_HIDE);
		m_constantDlg.ShowWindow(SW_HIDE);
		break;
	default:
		break;
	}
	*pResult = 0;
}

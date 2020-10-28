
// MFCApplication3Dlg.cpp: 实现文件
//

#include "../../pch.h"
//#include "../../resource.h"
//#include "../../resource.h"
#include "../../resource.h"
#include "../../framework.h"
#include "../../include/logicalCtrl/MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "Winuser.h"

#include<fstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
//
//class CAboutDlg : public CDialogEx
//{
//public:
//	CAboutDlg();
//
//// 对话框数据
//#ifdef AFX_DESIGN_TIME
//	enum { IDD = IDD_ABOUTBOX };
//#endif
//
//	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
//
//// 实现
//protected:
//	DECLARE_MESSAGE_MAP()
//};
//
//CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
//{
//}
//
//void CAboutDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//}
//
//BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//END_MESSAGE_MAP()
//
//
//// CMFCApplication3Dlg 对话框

IMPLEMENT_DYNAMIC(CMFCApplication3Dlg, CDialogEx)

CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
	//m_previewTopLeft(this),
	//m_previewTopRight(this),
	//m_previewBottomLeft(this),
	//m_previewBottomMid(this),
	//m_previewBottomRight(this),
	//rtuHandler(this),
	//rangingHandler(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_previewTopLeft.SetParentWnd(this);
	//m_previewTopRight.SetParentWnd(this);
	//m_previewBottomLeft.SetParentWnd(this);
	//m_previewBottomMid.SetParentWnd(this);
	//m_previewBottomRight.SetParentWnd(this);
//m_previewTopLeft.Set
//m_previewTopLeft(this);
//m_previewTopRight(this),
//m_previewBottomLeft(this),
//m_previewBottomMid(this),
//m_previewBottomRight(this),
//rtuHandler(this),
//rangingHandler(this)
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LEFT, m_iconL);
	DDX_Control(pDX, IDC_STATIC_RIGHT, m_iconR);
	DDX_Control(pDX, IDC_STATIC_DISL, m_disL);
	DDX_Control(pDX, IDC_STATIC_DISR, m_disR);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMFCApplication3Dlg 消息处理程序

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	//m_previewTopLeft.SetParentWnd(this);
	//m_previewTopRight.SetParentWnd(this);
	//m_previewBottomLeft.SetParentWnd(this);
	//m_previewBottomMid.SetParentWnd(this);
	//m_previewBottomRight.SetParentWnd(this);
	// IDM_ABOUTBOX 必须在系统命令范围内。
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//if (pSysMenu != nullptr)
	//{
	//	BOOL bNameValid;
	//	CString strAboutMenu;
	//	bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
	//	ASSERT(bNameValid);
	//	if (!strAboutMenu.IsEmpty())
	//	{
	//		pSysMenu->AppendMenu(MF_SEPARATOR);
	//		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//	}
	//}

	//// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	////  执行此操作
	//SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标
	////开激光串口
	//rtuHandler.Create(AfxRegisterWndClass(0), _T(""), WS_CHILD, CRect(0, 0, 2, 2), this, 0, nullptr);		//2020_10_26，刘钢修改，参数L""函数改为_T("")
	//rtuHandler.openPort(7, 9600, 8, ONESTOPBIT, _T('N'));
	////开基站串口
	//rangingHandler.Create(AfxRegisterWndClass(0),_T(""), WS_CHILD, CRect(0, 0, 2, 2), this, 0, nullptr);	//2020_10_26，刘钢修改，参数L""函数改为_T("")
	//rangingHandler.SetTagPosition();
	//rangingHandler.openPort(5, 115200, 8, ONESTOPBIT, _T('N'));

	//// TODO: 在此添加额外的初始化代码
	////实现指示灯变化
	//m_hIconRed = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_RED), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	//m_hIconGreen = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_GREEN), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	//m_hIconYellow = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_YELLOW), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	//m_iconL.SetIcon(m_hIconGreen);
	//m_iconR.SetIcon(m_hIconGreen);
	//
	////播放控制对象绑定控件
	//m_previewTopLeft.SetControlID(IDC_STATIC_TOPLEFT);
	//m_previewTopRight.SetControlID(IDC_STATIC_TOPRIGHT);
	//m_previewBottomLeft.SetControlID(IDC_STATIC_BOTTOMLEFT);
 //   m_previewBottomMid.SetControlID(IDC_STATIC_BOTTOMMID);
 //   m_previewBottomRight.SetControlID(IDC_STATIC_BOTTOMRIGHT);
	////使用IP对每一个设备进行登录
	//std::string user = "admin";
	//std::string password = "123456abc";
	//int port = 8000;
	//for (int i = 0; i < logic.StationIPArray.size(); i++) {
	//	DoLogin(logic.StationIPArray[i].leftIP, port, user, password);
	//	DoLogin(logic.StationIPArray[i].rightIP, port, user, password);
	//}
	//for (int i = 0; i < logic.CarIPArray.size(); i++) {
	//	DoLogin(logic.CarIPArray[i].leftDownIP, port, user, password);
	//	DoLogin(logic.CarIPArray[i].leftIP, port, user, password);
	//	DoLogin(logic.CarIPArray[i].panoramicIP, port, user, password);
	//	DoLogin(logic.CarIPArray[i].rightDownIP, port, user, password);
	//	DoLogin(logic.CarIPArray[i].rightIP, port, user, password);
	//}
	////将全景摄像头进行播放
	//m_previewBottomMid.StartPlay(logic.globalIP, m_cameras, 1);

	////判断当前处于什么情况
	//DistanceDisplay();
	//ScreenSwitching();
	//SetTimer(1, 500, nullptr);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		//CAboutDlg dlgAbout;
		//dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication3Dlg::OnPaint()
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
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CMFCApplication3Dlg::DoLogin(std::string& devIP, int& devPort, std::string& user, std::string& password)
{
	NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;
	memset(&DeviceInfoTmp, 0, sizeof(NET_DVR_DEVICEINFO_V30));
	LONG lLoginID;
	if (!devIP.compare("404")) {
		lLoginID = -1;//刚刚是==逻辑判断语句，现在改为赋值1027AM
	}
	else {
		lLoginID = NET_DVR_Login_V30((char*)devIP.c_str(), devPort, (char*)user.c_str(), (char*)password.c_str(), &DeviceInfoTmp);
		if (lLoginID == -1) {
			DWORD err = NET_DVR_GetLastError();
			MessageBox(_T("Login to Device failed!\n"));
			return FALSE;
		}
	}

	m_cameras.push_back(std::make_pair(devIP, lLoginID));//存储设备IP和登录ID
}
std::ofstream RTU_LOG("../rtu.txt");
std::ofstream DIS_LOG("../dis.txt");
void CMFCApplication3Dlg::ScreenSwitching()
{
	//停止播放
	m_previewTopLeft.StopPlay();
	m_previewTopRight.StopPlay();
	m_previewBottomLeft.StopPlay();
	m_previewBottomRight.StopPlay();
	std::vector<std::string>CameraIP;//定义数组
	//获取数据
	rtuHandler.getLaserDistance(disL, disR, carDis);
	DIS_LOG << disL << "   " << disR << std::endl;
	rangingHandler.GetRangingInfo(baseStationPosition, nearestTagPosition);
    AlarmLightSwitching( logic.judegSitution(CameraIP,disL,disR,carDis,tagID));
	//画面切换
	m_previewTopLeft.StartPlay(CameraIP[0], m_cameras, 1);
	m_previewTopRight.StartPlay(CameraIP[1], m_cameras, 1);
	m_previewBottomLeft.StartPlay(CameraIP[2], m_cameras, 1);
	m_previewBottomRight.StartPlay(CameraIP[3], m_cameras, 1);


}

void CMFCApplication3Dlg::AlarmLightSwitching(BOOL sitution)
{
	RTU_LOG << sitution << std::endl;
	switch (sitution) {//对于左右距离判断实现指示灯的切换
	case 0:
		ChangeColor(m_hIconGreen, m_hIconGreen);
		break;
	case 1:
		ChangeColor(m_hIconYellow, m_hIconGreen);
		break;
	case 2:
		ChangeColor(m_hIconRed, m_hIconGreen);
		break;
	case 3:
		ChangeColor(m_hIconGreen, m_hIconYellow);
		break;
	case 4:
		ChangeColor(m_hIconGreen, m_hIconRed);
		break;
	case 5:
		ChangeColor(m_hIconYellow, m_hIconRed);
		break;
	case 6:
		ChangeColor(m_hIconRed, m_hIconYellow);
		break;
	case 7:
		ChangeColor(m_hIconYellow, m_hIconYellow);
		break;
	case 8:
		ChangeColor(m_hIconRed, m_hIconRed);
		break;
	default:

		break;
	}
}

void CMFCApplication3Dlg::ChangeColor(HICON icon1, HICON icon2)//将指示灯设置为相应的颜色
{
	m_iconL.SetIcon(icon1);
	m_iconR.SetIcon(icon2);
}
void CMFCApplication3Dlg::DistanceDisplay()//在界面上显示距离
{
	
	
	
	rtuHandler.getLaserDistance(disL, disR, carDis);
	
	CString disLeft; CString disRight;
	disLeft.Format(_T("%1f"), disL);
	disRight.Format(_T("%1f"), disR);
	m_disL.SetWindowText(disLeft);		//2020_10_26，刘钢修改，SetWindowTextW函数改为SetWindowText函数
	m_disR.SetWindowText(disRight);		//2020_10_26，刘钢修改，SetWindowTextW函数改为SetWindowText函数
	
}


void CMFCApplication3Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DistanceDisplay();
	ScreenSwitching();
	CDialogEx::OnTimer(nIDEvent);
}


void CMFCApplication3Dlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	rangingHandler.closePort();
	rtuHandler.closePort();
	CDialogEx::OnClose();
}

// login.cpp: 实现文件
//

#include "../../pch.h"
#include "../../resource.h"
#include "../database/login.h"

#include "afxdialogex.h"
//#include "../../MonitoringFusionDlg.h"
#include <winsock.h> //注意顺序，要放在mysql.h前
#include <mysql.h>//控制台项目中要在mysql.h之前include <winsock.h>


// login 对话框

IMPLEMENT_DYNAMIC(login, CDialogEx)

login::login(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
	, m_username(_T(""))
	, m_password(_T(""))

{

}

login::~login()
{
}

void login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LOGIN_EDIT_username, m_username);
	DDX_Text(pDX, IDC_LOGIN_EDIT_password, m_password);

	DDX_Control(pDX, IDC_LOGIN_COMBO_ROLE, m_selectRoleCombo);
	DDX_Control(pDX, IDC_LOGIN_STATIC_TITLE, m_static_title);
}


BEGIN_MESSAGE_MAP(login, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN_BUTTON_login, &login::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()

END_MESSAGE_MAP()


// login 消息处理程序


//登录按钮：管理员和操作员分别进入不同的窗口
void login::OnBnClickedButton1() //登录按钮
{
	// TODO: 在此添加控件通知处理程序代码

	//判断是否输入了用户名和密码
	UpdateData(TRUE);
	if (m_username == "" || m_password == "")
	{
		AfxMessageBox(_T("请输入用户名和密码"));
		UpdateData(FALSE);
		return;
	}
	int index = m_selectRoleCombo.GetCurSel();//获得当前选项的序号
	CString strC;
	m_selectRoleCombo.GetLBText(index, strC);//将当前选项赋给strC

	MYSQL mysql;
	MYSQL* connect;

	connect = mysql_init(&mysql);
	if (connect == NULL)
	{
		AfxMessageBox(_T("初始化数据库失败"));
		return;
	}
	connect = mysql_real_connect(connect, "localhost", "root", "123456", "steel_mill", 3306, NULL, 0);
	if (connect == NULL)
	{
		AfxMessageBox(_T("连接数据库失败"));
		return;
	}
	char sql[1000] = { 0 };
	//将编码设置为gbk
	strcpy_s(sql, "set names gbk");
	if (mysql_query(connect, sql))
	{
		AfxMessageBox(_T("设置字符编码gbk失败"));
		return;
	}
	//设置编码格式utf8
	strcpy_s(sql, "set names utf8");
	int ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox(_T("初始化数据库失败"));
		return;
	}

	if (strC == "管理员")
	{	
		char* role = (char*)strC.GetBuffer();
		char* username = (char*)m_username.GetBuffer();
		CString password = m_password.GetBuffer();//这里不能强转成char*类型，因为要和后面数据库里的密码进行比对，必须是CString类型
		sprintf_s(sql, "select * from user where Role = \'%s\' and UserName = \'%s\'", role, username);
		mysql_query(connect, "SET NAMES GB2312");
		ret = mysql_query(connect, sql);
		if (ret)
		{
			AfxMessageBox(_T("查询用户表失败"));
			return;
		}
		else
		{
			
			//获取结果集
			MYSQL_RES* res = mysql_store_result(connect);
			//获取查询总数
			my_ulonglong rows = mysql_num_rows(res);
			if (rows == 0)
			{
				AfxMessageBox(_T("用户不存在"));
				CEdit* Grade = (CEdit*)GetDlgItem(IDC_LOGIN_EDIT_username);
				Grade->SetWindowText(_T(""));
				CEdit* Grade1 = (CEdit*)GetDlgItem(IDC_LOGIN_EDIT_password);
				Grade1->SetWindowText(_T(""));
				return;
			}
			// 遍历结果集的每一行数据
			MYSQL_ROW row;
			row = mysql_fetch_row(res);
			if (row[2] == password)
			{
				mysql_free_result(res);
				mysql_close(connect);
				CDialog::EndDialog(IDC_LOGIN_BUTTON_login);//点击登录按钮后关闭登录对话框
				/*CMonitoringFusionDlg MonitoringFusionDlg;*/ //这个最好是成员变量，不能做局部变量 1027AM
				m_dlgMonitoringFusion.DoModal();
			}
			else
			{
				mysql_free_result(res);
				mysql_close(connect);
				AfxMessageBox(_T("用户名或密码错误"));
				CEdit* Grade = (CEdit*)GetDlgItem(IDC_LOGIN_EDIT_username);
				Grade->SetWindowText(_T(""));
				CEdit* Grade1 = (CEdit*)GetDlgItem(IDC_LOGIN_EDIT_password);
				Grade1->SetWindowText(_T(""));
			}
		}
	}
	else if (strC == "操作员")
	{
		char* role = (char*)strC.GetBuffer();
		char* username = (char*)m_username.GetBuffer();
		CString password = m_password.GetBuffer();
		sprintf_s(sql, "select * from user where Role = \'%s\' and UserName = \'%s\'", role, username);
		mysql_query(connect, "SET NAMES GB2312");
		ret = mysql_query(connect, sql);
		if (ret)
		{
			AfxMessageBox(_T("查询用户失败"));
			return;
		}
		else
		{
			//获取结果集
			MYSQL_RES* res = mysql_store_result(connect);
			//获取查询总数
			my_ulonglong rows = mysql_num_rows(res);
			if (rows == 0)
			{
				AfxMessageBox(_T("用户不存在"));
				CEdit* Grade = (CEdit*)GetDlgItem(IDC_LOGIN_EDIT_username);
				Grade->SetWindowText(_T(""));
				CEdit* Grade1 = (CEdit*)GetDlgItem(IDC_LOGIN_EDIT_password);
				Grade1->SetWindowText(_T(""));
				return;
			}
			// 遍历结果集的每一行数据
			MYSQL_ROW row;
			row = mysql_fetch_row(res);
			if (row[2] == password)
			{
				mysql_free_result(res);
				mysql_close(connect);
				CDialog::EndDialog(IDC_LOGIN_BUTTON_login);//点击登录按钮后关闭登录对话框
				//AfxMessageBox(_T("操作员登录成功"));
				//m_dlgMFCApplication3.DoModal();
				m_dlgMFCApplication3 = new CMFCApplication3Dlg;
			}
			else
			{
				mysql_free_result(res);
				mysql_close(connect);
				AfxMessageBox(_T("用户名或密码错误"));
				CEdit* Grade = (CEdit*)GetDlgItem(IDC_LOGIN_EDIT_username);
				Grade->SetWindowText(_T(""));
				CEdit* Grade1 = (CEdit*)GetDlgItem(IDC_LOGIN_EDIT_password);
				Grade1->SetWindowText(_T(""));
			}
		}
	}
}




BOOL login::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(_T("登录"));
	m_selectRoleCombo.AddString(_T("管理员"));
	m_selectRoleCombo.AddString(_T("操作员"));
	m_selectRoleCombo.SetCurSel(1);//将管理员设置为默认值

	//设置字体
	m_editFont.CreatePointFont(180, _T("宋体"));
	m_static_title.SetFont(&m_editFont);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL login::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		// 如果消息是键盘按下事件，且是Entert键，执行以下代码（什么都不做，你可以自己添加想要的代码）
		OnBnClickedButton1();//按下回车执行登录按钮
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void login::OnPaint()
{
	//注释该语句：防止重复调用重画函数
	//CDialogEx::OnPaint();
	//添加代码对话框背景贴图

	//背景
	CPaintDC   dc(this);
	CRect   rect;
	GetClientRect(&rect);    //获取对话框长宽      
	CDC   dcBmp;             //定义并创建一个内存设备环境
	dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP1);    //载入资源中图片
	BITMAP   m_bitmap;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
	//将位图选入临时内存设备环境
	CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);//长，宽

	//logo
	CPaintDC   dc1(this);
	CRect   rect1;
	GetClientRect(&rect1);    //获取对话框长宽      
	CDC   dcBmp1;             //定义并创建一个内存设备环境
	dcBmp1.CreateCompatibleDC(&dc1);             //创建兼容性DC
	CBitmap   bmpBackground1;
	bmpBackground1.LoadBitmap(IDB_BITMAP2);    //载入资源中图片
	BITMAP   m_bitmap1;                         //图片变量               
	bmpBackground1.GetBitmap(&m_bitmap1);       //将图片载入位图中
	//将位图选入临时内存设备环境
	CBitmap* pbmpOld1 = dcBmp1.SelectObject(&bmpBackground1);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(200, 0, rect1.Width(), rect1.Height(), &dcBmp1, 0, 0, 1000, 800, SRCCOPY);//长，宽
}


HBRUSH login::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		//pDC->SetBkColor(RGB(255,0,0));  //需要指定背景色的时候用
		//pDC->SetTextColor(RGB(255, 255, 255));    //文字前景色
		pDC->SetBkMode(TRANSPARENT);    //设置透明
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //获取画笔颜色混合后的画笔，完成透明
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}





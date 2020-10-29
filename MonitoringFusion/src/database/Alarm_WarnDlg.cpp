// Alarm_WarnDlg.cpp: 实现文件

#include "afxdialogex.h"
#include <winsock.h> //注意顺序，要放在mysql.h前
#include <mysql.h>//控制台项目中要在mysql.h之前include <winsock.h>
#include "../../pch.h"
#include "../../resource.h"
#include "../../include/database/Alarm_WarnDlg.h"

// Alarm_WarnDlg 对话框

IMPLEMENT_DYNAMIC(Alarm_WarnDlg, CDialogEx)

Alarm_WarnDlg::Alarm_WarnDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Alarm_Warn_DIALOG, pParent)
	, m_selnum_aw(_T(""))
{

}

Alarm_WarnDlg::~Alarm_WarnDlg()
{
}

void Alarm_WarnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_alarm_warn);
	DDX_Control(pDX, IDC_EDIT1, m_edit_aw);
	DDX_Text(pDX, IDC_EDIT4, m_selnum_aw);
}


BEGIN_MESSAGE_MAP(Alarm_WarnDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &Alarm_WarnDlg::OnNMDblclkList1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &Alarm_WarnDlg::OnEnKillfocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &Alarm_WarnDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Alarm_WarnDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Alarm_WarnDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Alarm_WarnDlg::OnBnClickedButton4)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()


// Alarm_WarnDlg 消息处理程序


BOOL Alarm_WarnDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(_T("预警报警距离信息表"));
	m_list_alarm_warn.DeleteAllItems();	//清空所有表项
	while (m_list_alarm_warn.DeleteColumn(0));	//清空所有表头
	// TODO: 在此添加控件通知处理程序代码
	MYSQL mysql;
	MYSQL* connect;
	MYSQL_FIELD* fields;
	connect = mysql_init(&mysql);
	if (connect == NULL)
	{
		AfxMessageBox(_T("初始化数据库失败"));
		return false;
	}
	connect = mysql_real_connect(connect, "localhost", "root", "123456", "steel_mill", 3306, NULL, 0);
	if (connect == NULL)
	{
		AfxMessageBox(_T("连接数据库失败"));
		return false;
	}
	char sql[1000] = { 0 };
	//将编码设置为gbk
	strcpy_s(sql, "set names gbk");
	if (mysql_query(connect, sql))
	{
		AfxMessageBox(_T("设置字符编码gbk失败"));
		return false;
	}
	//设置编码格式utf8
	strcpy_s(sql, "set names utf8");
	int ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox(_T("设置字符编码utf8失败"));
		return false;
	}
	strcpy_s(sql, "SELECT DB_ID AS '序号',DB_CarNum AS '行车号',DB_AlarmDis AS '报警距离',DB_WarnDis AS '预警距离' FROM alarm_warn ORDER BY DB_ID+0 DESC");
	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox(_T("查询预警、报警信息表失败"));
		return false;
	}
	else
	{
		//获取结果集
		MYSQL_RES* res = mysql_use_result(connect);
		int nfieldNum = mysql_num_fields(res);


		fields = mysql_fetch_fields(res);
		// 字段数量
		int field_count = mysql_field_count(connect);
		// 查询总数
		my_ulonglong rows = mysql_num_rows(res);
		// 获取所有字段
		for (int i = 0; i < field_count; i++)
		{
			if (i == 0)
			{
				m_list_alarm_warn.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 50);
			}
			else
			{
				m_list_alarm_warn.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 120);
			}
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_alarm_warn.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_alarm_warn.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	mysql_close(connect);

	m_edit_aw.ShowWindow(SW_HIDE);
	m_edit_aw.ShowWindow(SW_HIDE);
	SetWindowLong(m_list_alarm_warn.m_hWnd, GWL_EXSTYLE, WS_EX_CLIENTEDGE);
	m_list_alarm_warn.SetExtendedStyle(LVS_EX_GRIDLINES);
	::SendMessage(m_list_alarm_warn.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


int m_Row_aw;//行
int m_Col_aw;//列
void Alarm_WarnDlg::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;

	m_Row_aw = pNMListView->iItem;//获得选中的行
	m_Col_aw = pNMListView->iSubItem;//获得选中列
	int n = m_list_alarm_warn.GetItemCount();//获取当前一共多少行
	if (pNMListView->iSubItem != 0) //如果选择的是子项;
	{
		m_list_alarm_warn.GetSubItemRect(m_Row_aw, m_Col_aw, LVIR_LABEL, rc);//获得子项的RECT；
		m_edit_aw.SetParent(&m_list_alarm_warn);//转换坐标为列表框中的坐标
		m_edit_aw.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_edit_aw.SetWindowText(m_list_alarm_warn.GetItemText(m_Row_aw, m_Col_aw));//将该子项中的值放在Edit控件中；
		m_edit_aw.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edit_aw.SetFocus();//设置Edit焦点
		m_edit_aw.ShowCaret();//显示光标
		m_edit_aw.SetSel(-1);//将光标移动到最后
	}
	else if (pNMListView->iItem != 0) //如果选择的是父项;
	{
		m_list_alarm_warn.GetSubItemRect(m_Row_aw, m_Col_aw, LVIR_LABEL, rc);//获得子项的RECT；
		m_edit_aw.SetParent(&m_list_alarm_warn);//转换坐标为列表框中的坐标
		m_edit_aw.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_edit_aw.SetWindowText(m_list_alarm_warn.GetItemText(m_Row_aw, m_Col_aw));//将该子项中的值放在Edit控件中；
		m_edit_aw.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edit_aw.SetFocus();//设置Edit焦点
		m_edit_aw.ShowCaret();//显示光标
		m_edit_aw.SetSel(-1);//将光标移动到最后
	}
	else
	{
		m_list_alarm_warn.GetSubItemRect(m_Row_aw, m_Col_aw, LVIR_LABEL, rc);//获得子项的RECT；
		m_edit_aw.SetParent(&m_list_alarm_warn);//转换坐标为列表框中的坐标
		m_edit_aw.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_edit_aw.SetWindowText(m_list_alarm_warn.GetItemText(m_Row_aw, m_Col_aw));//将该子项中的值放在Edit控件中；
		m_edit_aw.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edit_aw.SetFocus();//设置Edit焦点
		m_edit_aw.ShowCaret();//显示光标
		m_edit_aw.SetSel(-1);//将光标移动到最后
	}
	*pResult = 0;
}


void Alarm_WarnDlg::OnEnKillfocusEdit1()
{
	// TODO: 在此添加控件通知处理程序代码

	//获取原来的第一列某一行的值
	CString oldstr;
	oldstr = m_list_alarm_warn.GetItemText(m_Row_aw, 0);
	char* oldstr_char = (char*)oldstr.GetBuffer();

	CString tem;
	m_edit_aw.GetWindowText(tem); //得到用户输入的新的内容
	m_list_alarm_warn.SetItemText(m_Row_aw, m_Col_aw, tem); //设置编辑框的新内容
	m_edit_aw.ShowWindow(SW_HIDE); //应藏编辑框

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
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		UpdateData(true);

		//设置数据库字符格式，解决中文乱码问题
		mysql_query(connect, "set names 'gb2312'");

		char* tem_char = (char*)tem.GetBuffer();
		//CString m_Row_str;
		//m_Row_str.Format("%d", m_Row_s+1);
		//char* m_Row_char = (char*)m_Row_str.GetBuffer();

		//获取列名
		CString Col_Name;
		if (m_Col_aw == 1)
		{
			Col_Name = _T("DB_CarNum");
		}
		else if (m_Col_aw == 2)
		{
			Col_Name = _T("DB_AlarmDis");
		}
		else if (m_Col_aw == 3)
		{
			Col_Name = _T("DB_WarnDis");
		}
		else if (m_Col_aw == 0)
		{
			Col_Name = _T("DB_ID");
			//AfxMessageBox(Col_Name);
			char* Col_Name_char1 = (char*)Col_Name.GetBuffer();
			char update1[1000];
			sprintf_s(update1, "UPDATE alarm_warn SET %s=\'%s\' WHERE DB_ID=\'%s\'", Col_Name_char1, tem_char, oldstr_char);
			// 执行 sql 语句。  
			// mysql_query() 的返回值份很多情形， 进行判断使要注意。  
			if (mysql_query(connect, update1) == 0)
			{
				//AfxMessageBox(_T("修改数据成功!"));
			}
			else {
				AfxMessageBox(_T("修改数据失败!"));
			}
			UpdateData(false);
			mysql_close(connect);//关闭Mysql连接
			return;
		}

		char* Col_Name_char = (char*)Col_Name.GetBuffer();


		//获取第一列某一行的值
		CString str;
		str = m_list_alarm_warn.GetItemText(m_Row_aw, 0);
		//AfxMessageBox(str);
		char* str_char = (char*)str.GetBuffer();

		char update[1000];
		sprintf_s(update, "UPDATE alarm_warn SET %s=\'%s\' WHERE DB_ID=\'%s\'", Col_Name_char, tem_char, str_char);


		// 执行 sql 语句。  
		// mysql_query() 的返回值份很多情形， 进行判断使要注意。  
		if (mysql_query(connect, update) == 0)
		{
			//AfxMessageBox(_T("修改数据成功!"));
		}
		else {
			AfxMessageBox(_T("修改数据失败!"));
		}
	}
	UpdateData(false);
	mysql_close(connect);//关闭Mysql连接
}



//删除信息
void Alarm_WarnDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	MYSQL m_sqlCon;
	//初始化数据库对象
	mysql_init(&m_sqlCon);

	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"123456", "steel_mill", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		UpdateData(true);
		//设置数据库字符格式，解决中文乱码问题
		mysql_query(&m_sqlCon, "set names 'gb2312'");
		int selectRow = m_list_alarm_warn.GetSelectionMark();
		CString str;
		str = m_list_alarm_warn.GetItemText(selectRow, 0);
		//AfxMessageBox(str);
		char* str_char = (char*)str.GetBuffer();
		char del[1000];
		sprintf_s(del, "delete from alarm_warn where DB_ID=\'%s\'", str_char);

		// 执行 sql 语句。  
		// mysql_query() 的返回值份很多情形， 进行判断使要注意。  
		if (mysql_query(&m_sqlCon, del) == 0)
		{
			//AfxMessageBox(_T("删除数据成功!"));
		}
		else {
			AfxMessageBox(_T("删除数据失败!"));
		}
	}
	UpdateData(false);
	mysql_close(&m_sqlCon);//关闭Mysql连接

	m_list_alarm_warn.DeleteAllItems();	//清空所有表项
	while (m_list_alarm_warn.DeleteColumn(0));	//清空所有表头


	//此处待优化
	//重新打开数据库进行查询
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
		AfxMessageBox(_T("设置字符编码utf8失败"));
		return;
	}
	strcpy_s(sql, "SELECT DB_ID AS '序号',DB_CarNum AS '行车号',DB_AlarmDis AS '报警距离',DB_WarnDis AS '预警距离' FROM alarm_warn ORDER BY DB_ID+0 DESC");
	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox(_T("查询预警、报警信息失败"));
		return;
	}
	else
	{
		//获取结果集
		MYSQL_RES* res = mysql_use_result(connect);
		int nfieldNum = mysql_num_fields(res);
		MYSQL_FIELD* fields;

		fields = mysql_fetch_fields(res);
		// 字段数量
		int field_count = mysql_field_count(connect);
		// 查询总数
		my_ulonglong rows = mysql_num_rows(res);
		// 获取所有字段
		for (int i = 0; i < field_count; i++)
		{
			if (i == 0)
			{
				m_list_alarm_warn.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 50);
			}
			else
			{
				m_list_alarm_warn.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 120);
			}
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_alarm_warn.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_alarm_warn.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	mysql_close(connect);

}


//添加信息
void Alarm_WarnDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	MYSQL m_sqlCon;
	//初始化数据库对象
	mysql_init(&m_sqlCon);

	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"123456", "steel_mill", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		UpdateData(true);
		int totalRowNum = m_list_alarm_warn.GetItemCount();//列表的行数
		int expectNum = 1;//第一列期望的序号
		int realNum;//第一列实际的序号
		char insert[1000];
		if (totalRowNum == 0)
		{
			CString expectNum_CStr;
			expectNum_CStr.Format("%d", expectNum);
			char* expectNum_char = (char*)expectNum_CStr.GetBuffer();
			sprintf_s(insert, "insert into alarm_warn(DB_ID) values (\'%s\')", expectNum_char);
		}
		for (int i = 0; i < totalRowNum; i++)
		{
			//获取第一列某一行的值
			CString str;
			str = m_list_alarm_warn.GetItemText(i, 0);

			CString str1;
			str1.Format("%d", expectNum);
			realNum = _ttoi(str);
			if (totalRowNum == 1)
			{
				CString expectNum_CStr;
				expectNum_CStr.Format("%d", expectNum + 1);
				char* expectNum_char = (char*)expectNum_CStr.GetBuffer();
				sprintf_s(insert, "insert into alarm_warn(DB_ID) values (\'%s\')", expectNum_char);
			}
			else {
				if (expectNum == realNum)
				{
					expectNum++;
					realNum++;
				}
				else if (expectNum != realNum)
				{
					CString expectNum_CStr;
					expectNum_CStr.Format("%d", expectNum);
					char* expectNum_char = (char*)expectNum_CStr.GetBuffer();
					sprintf_s(insert, "insert into alarm_warn(DB_ID) values (\'%s\')", expectNum_char);
					break;
				}
				if (expectNum == totalRowNum)
				{
					CString expectNum_CStr;
					expectNum_CStr.Format("%d", expectNum + 1);
					char* expectNum_char = (char*)expectNum_CStr.GetBuffer();
					sprintf_s(insert, "insert into alarm_warn(DB_ID) values (\'%s\')", expectNum_char);
				}
			}
		}

		// 执行 sql 语句。  
		// mysql_query() 的返回值份很多情形， 进行判断使要注意。  
		if (mysql_query(&m_sqlCon, insert) == 0)
		{
			//AfxMessageBox(_T("添加数据成功!"));
		}
		else {
			AfxMessageBox(_T("添加失败!"));
		}
	}
	UpdateData(false);
	mysql_close(&m_sqlCon);//关闭Mysql连接


	m_list_alarm_warn.DeleteAllItems();	//清空所有表项
	while (m_list_alarm_warn.DeleteColumn(0));	//清空所有表头


	//此处待优化
	//重新打开数据库进行查询
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
		AfxMessageBox(_T("设置字符编码utf8失败"));
		return;
	}
	strcpy_s(sql, "SELECT DB_ID AS '序号',DB_CarNum AS '行车号',DB_AlarmDis AS '报警距离',DB_WarnDis AS '预警距离' FROM alarm_warn ORDER BY DB_ID+0 DESC");
	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox(_T("查询预警、报警信息表失败"));
		return;
	}
	else
	{
		//获取结果集
		MYSQL_RES* res = mysql_use_result(connect);
		int nfieldNum = mysql_num_fields(res);
		MYSQL_FIELD* fields;

		fields = mysql_fetch_fields(res);
		// 字段数量
		int field_count = mysql_field_count(connect);
		// 查询总数
		my_ulonglong rows = mysql_num_rows(res);
		// 获取所有字段
		for (int i = 0; i < field_count; i++)
		{
			if (i == 0)
			{
				m_list_alarm_warn.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 50);
			}
			else
			{
				m_list_alarm_warn.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 120);
			}
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_alarm_warn.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_alarm_warn.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	mysql_close(connect);

}


//根据行车号查询
void Alarm_WarnDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	MYSQL mysql;
	MYSQL* connect;
	MYSQL_FIELD* fields;
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
		AfxMessageBox(_T("设置字符编码utf8失败"));
		return;
	}
	UpdateData(true);
	if (m_selnum_aw == "")
	{
		AfxMessageBox(_T("请输入所要查询的行车号"));
		UpdateData(false);
		return;
	}
	char* num = (char*)m_selnum_aw.GetBuffer();

	sprintf_s(sql, "SELECT DB_ID AS '序号',DB_CarNum AS '行车号',DB_AlarmDis AS '报警距离',DB_WarnDis AS '预警距离' FROM alarm_warn WHERE DB_CarNum=\'%s\'", num);
	m_list_alarm_warn.DeleteAllItems();	//清空所有表项
	while (m_list_alarm_warn.DeleteColumn(0));	//清空所有表头
	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox(_T("查询预警、报警信息表失败"));
		return;
	}
	else
	{
		//获取结果集
		MYSQL_RES* res = mysql_use_result(connect);
		int nfieldNum = mysql_num_fields(res);


		fields = mysql_fetch_fields(res);
		// 字段数量
		int field_count = mysql_field_count(connect);
		// 查询总数
		my_ulonglong rows = mysql_num_rows(res);
		// 获取所有字段
		for (int i = 0; i < field_count; i++)
		{
			if (i == 0)
			{
				m_list_alarm_warn.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 50);
			}
			else
			{
				m_list_alarm_warn.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 120);
			}
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_alarm_warn.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_alarm_warn.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	UpdateData(false);
	mysql_close(connect);
}

//升序排列（刷新）
void Alarm_WarnDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list_alarm_warn.DeleteAllItems();	//清空所有表项
	while (m_list_alarm_warn.DeleteColumn(0));	//清空所有表头
	// TODO: 在此添加控件通知处理程序代码
	MYSQL mysql;
	MYSQL* connect;
	MYSQL_FIELD* fields;
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
		AfxMessageBox(_T("设置字符编码utf8失败"));
		return;
	}
	strcpy_s(sql, "SELECT DB_ID AS '序号',DB_CarNum AS '行车号',DB_AlarmDis AS '报警距离',DB_WarnDis AS '预警距离' FROM alarm_warn ORDER BY DB_ID+0 DESC");
	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox(_T("查询预警、报警信息表失败"));
		return;
	}
	else
	{
		//获取结果集
		MYSQL_RES* res = mysql_use_result(connect);
		int nfieldNum = mysql_num_fields(res);


		fields = mysql_fetch_fields(res);
		// 字段数量
		int field_count = mysql_field_count(connect);
		// 查询总数
		my_ulonglong rows = mysql_num_rows(res);
		// 获取所有字段
		for (int i = 0; i < field_count; i++)
		{
			if (i == 0)
			{
				m_list_alarm_warn.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 50);
			}
			else
			{
				m_list_alarm_warn.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 120);
			}
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_alarm_warn.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_alarm_warn.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	mysql_close(connect);
}


BOOL Alarm_WarnDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		// 如果消息是键盘按下事件，且是Entert键，执行以下代码（什么都不做，你可以自己添加想要的代码）
		GetDlgItem(IDC_BUTTON4)->SetFocus();
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


//void Alarm_WarnDlg::OnPaint()
//{
//	CPaintDC   dc(this);
//	CRect   rect;
//	GetClientRect(&rect);    //获取对话框长宽      
//	CDC   dcBmp;             //定义并创建一个内存设备环境
//	dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
//	CBitmap   bmpBackground;
//	bmpBackground.LoadBitmap(IDB_BITMAP2);    //载入资源中图片
//	BITMAP   m_bitmap;                         //图片变量               
//	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
//	//将位图选入临时内存设备环境
//	CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackground);
//	//调用函数显示图片StretchBlt显示形状可变
//	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);//长，宽
//}


HBRUSH Alarm_WarnDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	//if (CTLCOLOR_STATIC == nCtlColor)
	//{
	//	//pDC->SetBkColor(RGB(255,0,0));  //需要指定背景色的时候用
	//	//pDC->SetTextColor(RGB(255, 255, 255));    //文字前景色
	//	pDC->SetBkMode(TRANSPARENT);    //设置透明
	//	hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //获取画笔颜色混合后的画笔，完成透明
	//}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	//return hbr;
	return (HBRUSH)::GetStockObject(WHITE_BRUSH);
}






// stationDlg.cpp: 实现文件

#include "afxdialogex.h"
#include <winsock.h> //注意顺序，要放在mysql.h前
#include <mysql.h>//控制台项目中要在mysql.h之前include <winsock.h>
#include "../../pch.h"
#include "../../resource.h"
#include "../../include/database/stationDlg.h"

// stationDlg 对话框

IMPLEMENT_DYNAMIC(stationDlg, CDialogEx)

stationDlg::stationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STATION_DIALOG, pParent)
	, m_num_station_select(_T(""))
{

}

stationDlg::~stationDlg()
{
}

void stationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_station);
	DDX_Control(pDX, IDC_EDIT2, m_edit_s);
	DDX_Text(pDX, IDC_EDIT4, m_num_station_select);
}


BEGIN_MESSAGE_MAP(stationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &stationDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &stationDlg::OnNMDblclkList1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &stationDlg::OnEnKillfocusEdit2)
	ON_BN_CLICKED(IDC_BUTTON2, &stationDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &stationDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &stationDlg::OnBnClickedButton4)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// stationDlg 消息处理程序


BOOL stationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(_T("工位信息表"));

	m_list_station.DeleteAllItems();	//清空所有表项
	while (m_list_station.DeleteColumn(0));	//清空所有表头
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
	strcpy_s(sql, "SELECT DB_ID AS '工位空间序号',DB_StaNum AS '工位号',DB_TagNum AS '标签号',DB_Height AS '落差高度',DB_IPLeft AS '左摄像头IP',DB_IPRight AS '右摄像头IP',DB_Enlarge AS '特写镜头放大倍数',DB_BluetoothDis AS '蓝牙范围' FROM `station` ORDER BY DB_ID+0 DESC");
	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox(_T("查询工位信息表失败"));
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
			m_list_station.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 150);
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_station.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_station.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	mysql_close(connect);

	m_edit_s.ShowWindow(SW_HIDE);
	m_edit_s.ShowWindow(SW_HIDE);
	SetWindowLong(m_list_station.m_hWnd, GWL_EXSTYLE, WS_EX_CLIENTEDGE);
	m_list_station.SetExtendedStyle(LVS_EX_GRIDLINES);
	::SendMessage(m_list_station.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//删除按钮
void stationDlg::OnBnClickedButton1()
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
		int selectRow = m_list_station.GetSelectionMark();
		CString str;
		str = m_list_station.GetItemText(selectRow, 0);
		//AfxMessageBox(str);
		char* str_char = (char*)str.GetBuffer();
		char del[1000];
		sprintf_s(del, "delete from station where DB_ID=\'%s\'", str_char);

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


	m_list_station.DeleteAllItems();	//清空所有表项
	while (m_list_station.DeleteColumn(0));	//清空所有表头

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
	strcpy_s(sql, "SELECT DB_ID AS '工位空间序号',DB_StaNum AS '工位号',DB_TagNum AS '标签号',DB_Height AS '落差高度',DB_IPLeft AS '左摄像头IP',DB_IPRight AS '右摄像头IP',DB_Enlarge AS '特写镜头放大倍数',DB_BluetoothDis AS '蓝牙范围' FROM `station` ORDER BY DB_ID+0 DESC");
	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox(_T("查询工位信息表失败"));
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
			m_list_station.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 150);
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_station.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_station.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	mysql_close(connect);
}

int m_Row_s;//行
int m_Col_s;//列
void stationDlg::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;

	m_Row_s = pNMListView->iItem;//获得选中的行
	m_Col_s = pNMListView->iSubItem;//获得选中列
	int n = m_list_station.GetItemCount();//获取当前一共多少行
	if (pNMListView->iSubItem != 0) //如果选择的是子项;
	{
		m_list_station.GetSubItemRect(m_Row_s, m_Col_s, LVIR_LABEL, rc);//获得子项的RECT；
		m_edit_s.SetParent(&m_list_station);//转换坐标为列表框中的坐标
		m_edit_s.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_edit_s.SetWindowText(m_list_station.GetItemText(m_Row_s, m_Col_s));//将该子项中的值放在Edit控件中；
		m_edit_s.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edit_s.SetFocus();//设置Edit焦点
		m_edit_s.ShowCaret();//显示光标
		m_edit_s.SetSel(-1);//将光标移动到最后
	}
	else if (pNMListView->iItem != 0)
	{
		m_list_station.GetSubItemRect(m_Row_s, m_Col_s, LVIR_LABEL, rc);//获得子项的RECT；
		m_edit_s.SetParent(&m_list_station);//转换坐标为列表框中的坐标
		m_edit_s.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_edit_s.SetWindowText(m_list_station.GetItemText(m_Row_s, m_Col_s));//将该子项中的值放在Edit控件中；
		//AfxMessageBox(_T("222"));
		m_edit_s.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edit_s.SetFocus();//设置Edit焦点
		m_edit_s.ShowCaret();//显示光标
		m_edit_s.SetSel(-1);//将光标移动到最后
	}
	else
	{
		m_list_station.GetSubItemRect(m_Row_s, m_Col_s, LVIR_LABEL, rc);//获得子项的RECT；
		m_edit_s.SetParent(&m_list_station);//转换坐标为列表框中的坐标
		m_edit_s.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_edit_s.SetWindowText(m_list_station.GetItemText(m_Row_s, m_Col_s));//将该子项中的值放在Edit控件中；
		//AfxMessageBox(_T("222"));
		m_edit_s.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edit_s.SetFocus();//设置Edit焦点
		m_edit_s.ShowCaret();//显示光标
		m_edit_s.SetSel(-1);//将光标移动到最后
	}

	*pResult = 0;
}


void stationDlg::OnEnKillfocusEdit2()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取原来的第一列某一行的值
	CString oldstr;
	oldstr = m_list_station.GetItemText(m_Row_s, 0);
	char* oldstr_char = (char*)oldstr.GetBuffer();

	CString tem;
	m_edit_s.GetWindowText(tem); //得到用户输入的新的内容
	m_list_station.SetItemText(m_Row_s, m_Col_s, tem); //设置编辑框的新内容
	m_edit_s.ShowWindow(SW_HIDE); //应藏编辑框

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
		if (m_Col_s == 1)
		{
			Col_Name = _T("DB_StaNum");
		}
		else if (m_Col_s == 2)
		{
			Col_Name = _T("DB_TagNum");
		}
		else if (m_Col_s == 3)
		{
			Col_Name = _T("DB_Height");
		}
		else if (m_Col_s == 4)
		{
			Col_Name = _T("DB_IPLeft");
		}
		else if (m_Col_s == 5)
		{
			Col_Name = _T("DB_IPRight");
		}
		else if (m_Col_s == 6)
		{
			Col_Name = _T("DB_Enlarge");
		}
		else if (m_Col_s == 7)
		{
			Col_Name = _T("DB_BluetoothDis");
		}
		else if (m_Col_s == 0)
		{
			Col_Name = _T("DB_ID");
			//AfxMessageBox(Col_Name);
			char* Col_Name_char1 = (char*)Col_Name.GetBuffer();
			char update1[1000];
			sprintf_s(update1, "UPDATE station SET %s=\'%s\' WHERE DB_ID=\'%s\'", Col_Name_char1, tem_char, oldstr_char);
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
		str = m_list_station.GetItemText(m_Row_s, 0);
		//AfxMessageBox(str);
		char* str_char = (char*)str.GetBuffer();

		char update[1000];
		//sprintf_s(update, "UPDATE station SET %s=\'%s\' WHERE StationNo=\'%s\'", Col_Name_char, tem_char, m_Row_char);
		sprintf_s(update, "UPDATE station SET %s=\'%s\' WHERE DB_ID=\'%s\'", Col_Name_char, tem_char, str_char);


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

//添加按钮
void stationDlg::OnBnClickedButton2()
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
		int totalRowNum = m_list_station.GetItemCount();//列表的行数
		int expectNum = 1;//第一列期望的序号
		int realNum;//第一列实际的序号
		char insert[1000];
		if (totalRowNum == 0)
		{
			CString expectNum_CStr;
			expectNum_CStr.Format("%d", expectNum);
			char* expectNum_char = (char*)expectNum_CStr.GetBuffer();
			sprintf_s(insert, "insert into station(DB_ID) values (\'%s\')", expectNum_char);
		}
		for (int i = 0; i < totalRowNum; i++)
		{
			//获取第一列某一行的值
			CString str;
			str = m_list_station.GetItemText(i, 0);

			CString str1;
			str1.Format("%d", expectNum);
			realNum = _ttoi(str);
			if (totalRowNum == 1)
			{
				CString expectNum_CStr;
				expectNum_CStr.Format("%d", expectNum + 1);
				char* expectNum_char = (char*)expectNum_CStr.GetBuffer();
				sprintf_s(insert, "insert into station(DB_ID) values (\'%s\')", expectNum_char);
			}
			else
			{
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
					sprintf_s(insert, "insert into station(DB_ID) values (\'%s\')", expectNum_char);
					break;
				}
				if (expectNum == totalRowNum)
				{
					CString expectNum_CStr;
					expectNum_CStr.Format("%d", expectNum + 1);
					char* expectNum_char = (char*)expectNum_CStr.GetBuffer();
					sprintf_s(insert, "insert into station(DB_ID) values (\'%s\')", expectNum_char);
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


	m_list_station.DeleteAllItems();	//清空所有表项
	while (m_list_station.DeleteColumn(0));	//清空所有表头


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
	strcpy_s(sql, "SELECT DB_ID AS '工位空间序号',DB_StaNum AS '工位号',DB_TagNum AS '标签号',DB_Height AS '落差高度',DB_IPLeft AS '左摄像头IP',DB_IPRight AS '右摄像头IP',DB_Enlarge AS '特写镜头放大倍数',DB_BluetoothDis AS '蓝牙范围' FROM `station` ORDER BY DB_ID+0 DESC");
	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox(_T("查询工位表失败"));
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
			m_list_station.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 150);
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_station.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_station.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	mysql_close(connect);

}



//升序排列（刷新）
void stationDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list_station.DeleteAllItems();	//清空所有表项
	while (m_list_station.DeleteColumn(0));	//清空所有表头
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
		AfxMessageBox(_T("连接化数据库失败"));
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
	strcpy_s(sql, "SELECT DB_ID AS '工位空间序号',DB_StaNum AS '工位号',DB_TagNum AS '标签号',DB_Height AS '落差高度',DB_IPLeft AS '左摄像头IP',DB_IPRight AS '右摄像头IP',DB_Enlarge AS '特写镜头放大倍数',DB_BluetoothDis AS '蓝牙范围' FROM `station` ORDER BY DB_ID+0 DESC");
	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox(_T("查询工位信息表失败"));
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
			m_list_station.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 150);
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_station.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_station.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	mysql_close(connect);
}





//根据工位号查询
void stationDlg::OnBnClickedButton4()
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
	if (m_num_station_select == "")
	{
		AfxMessageBox(_T("请输入所要查询的工位号"));
		UpdateData(false);
		return;
	}
	char* num = (char*)m_num_station_select.GetBuffer();


	m_list_station.DeleteAllItems();	//清空所有表项
	while (m_list_station.DeleteColumn(0));	//清空所有表头
	sprintf_s(sql, "SELECT DB_ID AS '工位空间序号',DB_StaNum AS '工位号',DB_TagNum AS '标签号',DB_Height AS '落差高度',DB_IPLeft AS '左摄像头IP',DB_IPRight AS '右摄像头IP',DB_Enlarge AS '特写镜头放大倍数',DB_BluetoothDis AS '蓝牙范围' FROM `station` WHERE DB_StaNum=\'%s\'", num);

	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox(_T("查询工位信息表失败"));
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
			m_list_station.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 150);
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_station.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_station.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	UpdateData(false);
	mysql_close(connect);
}


BOOL stationDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		// 如果消息是键盘按下事件，且是Entert键，执行以下代码（什么都不做，你可以自己添加想要的代码）
		GetDlgItem(IDC_BUTTON3)->SetFocus();
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void stationDlg::OnPaint()
{
	CPaintDC   dc(this);
	//CRect   rect;
	//GetClientRect(&rect);    //获取对话框长宽      
	//CDC   dcBmp;             //定义并创建一个内存设备环境
	//dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
	//CBitmap   bmpBackground;
	//bmpBackground.LoadBitmap(IDB_BITMAP2);    //载入资源中图片
	//BITMAP   m_bitmap;                         //图片变量               
	//bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
	////将位图选入临时内存设备环境
	//CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackground);
	////调用函数显示图片StretchBlt显示形状可变
	//dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);//长，宽
}


HBRUSH stationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

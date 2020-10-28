// CAR.cpp: 实现文件
//

#include "../../pch.h"
#include "../../include/database/CAR.h"
#include "../../resource.h"
#include "afxdialogex.h"
#include <winsock.h> //注意顺序，要放在mysql.h前
#include <mysql.h>//控制台项目中要在mysql.h之前include <winsock.h>

// CAR 对话框

IMPLEMENT_DYNAMIC(CAR, CDialogEx)

CAR::CAR(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Car_DIALOG, pParent)
	, m_num_car_select(_T(""))
{

}

CAR::~CAR()
{
}

void CAR::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAR_LIST_SHOW_DATA, m_list_car);
	DDX_Control(pDX, IDC_CAR_EDIT_EDITDATA, m_edit);
	DDX_Text(pDX, IDC_CAR_EDIT_CARNUM, m_num_car_select);
}


BEGIN_MESSAGE_MAP(CAR, CDialogEx)
	ON_BN_CLICKED(IDC_CAR_BUTTON_DELETE, &CAR::OnBnClickedButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_CAR_LIST_SHOW_DATA, &CAR::OnNMDblclkList1)
	ON_EN_KILLFOCUS(IDC_CAR_EDIT_EDITDATA, &CAR::OnEnKillfocusEdit2)
	ON_BN_CLICKED(IDC_CAR_BUTTON_INSERT, &CAR::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CAR_BUTTON_FRUSH, &CAR::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CAR_BUTTON_SELECT, &CAR::OnBnClickedButton4)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAR 消息处理程序


BOOL CAR::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText("行车信息表");

	m_list_car.DeleteAllItems();	//清空所有表项
	while (m_list_car.DeleteColumn(0));	//清空所有表头
	// TODO: 在此添加控件通知处理程序代码
	MYSQL mysql;
	MYSQL* connect;
	MYSQL_FIELD* fields;
	connect = mysql_init(&mysql);
	if (connect == NULL)
	{
		AfxMessageBox("初始化数据库失败");
		return false;
	}
	connect = mysql_real_connect(connect, "localhost", "root", "123456", "steel_mill", 3306, NULL, 0);
	if (connect == NULL)
	{
		AfxMessageBox("连接数据库失败");
		return false;
	}
	char sql[1000] = { 0 };
	//将编码设置为gbk
	strcpy_s(sql, "set names gbk");
	if (mysql_query(connect, sql))
	{
		AfxMessageBox("设置字符编码gbk失败");
		return false;
	}
	//设置编码格式utf8
	strcpy_s(sql, "set names utf8");
	int ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox("设置字符编码utf8失败");
		return false;
	}
	strcpy_s(sql, "SELECT DB_ID AS '序号',DB_CarNum AS '行车号',DB_IPLeftDown AS '左下方摄像头IP',DB_IPRightDown AS '右下方摄像头IP',DB_IPLeft AS '左边摄像头IP',DB_IPRight AS '右边摄像头IP',DB_IPGlobal AS '全景摄像头IP',DB_ChannelNum AS '通道号',DB_SidewaysDis AS '侧偏距离',DB_CorrectionAngle AS '矫正角',DB_232PortNo AS '232端口号',DB_232PortSamplingFrequency AS '232端口采样频率',DB_485PortNo AS '485端口号',DB_485PortSamplingFrequency AS '485端口采样频率',DB_RopeMargin AS '吊耳距离行车边缘' FROM car ORDER BY DB_ID+0 DESC");
	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox("查询行车表失败");
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
				m_list_car.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 50);
			}
			else
			{
				m_list_car.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 200);
			}
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_car.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_car.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	mysql_close(connect);


	m_edit.ShowWindow(SW_HIDE);
	SetWindowLong(m_list_car.m_hWnd, GWL_EXSTYLE, WS_EX_CLIENTEDGE);
	m_list_car.SetExtendedStyle(LVS_EX_GRIDLINES);
	::SendMessage(m_list_car.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//删除按钮
void CAR::OnBnClickedButton1()
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
		int selectRow = m_list_car.GetSelectionMark();
		CString str;
		str = m_list_car.GetItemText(selectRow, 0);
		//AfxMessageBox(str);
		char* str_char = (char*)str.GetBuffer();
		char del[1000];
		sprintf_s(del, "delete from car where DB_ID=\'%s\'", str_char);

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

	m_list_car.DeleteAllItems();	//清空所有表项
	while (m_list_car.DeleteColumn(0));	//清空所有表头


	//此处待优化
	//重新打开数据库进行查询
	MYSQL mysql;
	MYSQL* connect;
	connect = mysql_init(&mysql);
	if (connect == NULL)
	{
		AfxMessageBox("初始化数据库失败");
		return;
	}
	connect = mysql_real_connect(connect, "localhost", "root", "123456", "steel_mill", 3306, NULL, 0);
	if (connect == NULL)
	{
		AfxMessageBox("连接数据库失败");
		return;
	}
	char sql[1000] = { 0 };

	//将编码设置为gbk
	strcpy_s(sql, "set names gbk");
	if (mysql_query(connect, sql))
	{
		AfxMessageBox("设置字符编码gbk失败");
		return;
	}
	//设置编码格式utf8
	strcpy_s(sql, "set names utf8");
	int ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox("设置字符编码utf8失败");
		return;
	}

	strcpy_s(sql, "SELECT DB_ID AS '序号',DB_CarNum AS '行车号',DB_IPLeftDown AS '左下方摄像头IP',DB_IPRightDown AS '右下方摄像头IP',DB_IPLeft AS '左边摄像头IP',DB_IPRight AS '右边摄像头IP',DB_IPGlobal AS '全景摄像头IP',DB_ChannelNum AS '通道号',DB_SidewaysDis AS '侧偏距离',DB_CorrectionAngle AS '矫正角',DB_232PortNo AS '232端口号',DB_232PortSamplingFrequency AS '232端口采样频率',DB_485PortNo AS '485端口号',DB_485PortSamplingFrequency AS '485端口采样频率',DB_RopeMargin AS '吊耳距离行车边缘',DB_RopeMargin AS '吊耳距离行车边缘' FROM car ORDER BY DB_ID+0 DESC");
	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox("查询行车表失败");
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
				m_list_car.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 50);
			}
			else 
			{
				m_list_car.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 200);
			}
			
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_car.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_car.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	mysql_close(connect);
}

int m_Row;//行
int m_Col;//列
void CAR::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;

	m_Row = pNMListView->iItem;//获得选中的行
	m_Col = pNMListView->iSubItem;//获得选中列
	int n = m_list_car.GetItemCount();//获取当前一共多少行
	if (pNMListView->iSubItem != 0) //如果选择的是子项;
	{
		m_list_car.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//获得子项的RECT；
		m_edit.SetParent(&m_list_car);//转换坐标为列表框中的坐标
		m_edit.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_edit.SetWindowText(m_list_car.GetItemText(m_Row, m_Col));//将该子项中的值放在Edit控件中；
		//AfxMessageBox(_T("111"));
		m_edit.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edit.SetFocus();//设置Edit焦点
		m_edit.ShowCaret();//显示光标
		m_edit.SetSel(-1);//将光标移动到最后
	}
	else if (pNMListView->iItem != 0)
	{
		m_list_car.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//获得子项的RECT；
		m_edit.SetParent(&m_list_car);//转换坐标为列表框中的坐标
		m_edit.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_edit.SetWindowText(m_list_car.GetItemText(m_Row, m_Col));//将该子项中的值放在Edit控件中；
		//AfxMessageBox(_T("222"));
		m_edit.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edit.SetFocus();//设置Edit焦点
		m_edit.ShowCaret();//显示光标
		m_edit.SetSel(-1);//将光标移动到最后
	}
	else
	{
		m_list_car.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//获得子项的RECT；
		m_edit.SetParent(&m_list_car);//转换坐标为列表框中的坐标
		m_edit.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_edit.SetWindowText(m_list_car.GetItemText(m_Row, m_Col));//将该子项中的值放在Edit控件中；
		//AfxMessageBox(_T("222"));
		m_edit.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edit.SetFocus();//设置Edit焦点
		m_edit.ShowCaret();//显示光标
		m_edit.SetSel(-1);//将光标移动到最后
	}
	*pResult = 0;
}


void CAR::OnEnKillfocusEdit2()
{
		// TODO: 在此添加控件通知处理程序代码

	
	//获取原来的第一列某一行的值
	CString oldstr;
	oldstr = m_list_car.GetItemText(m_Row, 0);
	char* oldstr_char = (char*)oldstr.GetBuffer();

	CString tem;
	m_edit.GetWindowText(tem); //得到用户输入的新的内容
	m_list_car.SetItemText(m_Row, m_Col, tem); //设置编辑框的新内容
	m_edit.ShowWindow(SW_HIDE); //应藏编辑框


	MYSQL mysql;
	MYSQL* connect;
	connect = mysql_init(&mysql);
	if (connect == NULL)
	{
		AfxMessageBox("初始化数据库失败");
		return;
	}
	connect = mysql_real_connect(connect, "localhost", "root", "123456", "steel_mill", 3306, NULL, 0);
	if (connect == NULL)
	{
		AfxMessageBox("连接数据库失败");
		return;
	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		UpdateData(true);

		//设置数据库字符格式，解决中文乱码问题
		mysql_query(connect, "set names 'gb2312'");


		char* tem_char = (char*)tem.GetBuffer();
		//获取列名
		CString Col_Name;
		if (m_Col == 1)
		{
			Col_Name = _T("DB_CarNum");
		}
		else if (m_Col == 2)
		{
			Col_Name = _T("DB_IPLeftDown");
		}
		else if (m_Col == 3)
		{
			Col_Name = _T("DB_IPRightDown");
		}
		else if (m_Col == 4)
		{
			Col_Name = _T("DB_IPLeft");
		}
		else if (m_Col == 5)
		{
			Col_Name = _T("DB_IPRight");
		}
		else if (m_Col == 6)
		{
			Col_Name = _T("DB_IPGlobal");
		}
		else if (m_Col == 7)
		{
			Col_Name = _T("DB_ChannelNum");
		}
		else if (m_Col == 8)
		{
			Col_Name = _T("DB_SidewaysDis");
		}
		else if (m_Col == 9)
		{
			Col_Name = _T("DB_CorrectionAngle");
		}
		else if (m_Col == 10)
		{
			Col_Name = _T("DB_232PortNo");
		}
		else if (m_Col == 11)
		{
			Col_Name = _T("DB_232PortSamplingFrequency");
		}
		else if (m_Col == 12)
		{
			Col_Name = _T("DB_485PortNo");
		}
		else if (m_Col == 13)
		{
			Col_Name = _T("DB_485PortSamplingFrequency");
		}
		else if (m_Col == 14)
		{
			Col_Name = _T("DB_RopeMargin");
		}
		else if (m_Col == 0)
		{
			Col_Name = _T("DB_ID");
			//AfxMessageBox(Col_Name);
			char* Col_Name_char1 = (char*)Col_Name.GetBuffer();
			char update1[1000];
			sprintf_s(update1, "UPDATE car SET %s=\'%s\' WHERE DB_ID=\'%s\'", Col_Name_char1, tem_char, oldstr_char);
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


		//获取新入输入的第一列某一行的值
		CString str;
		str = m_list_car.GetItemText(m_Row,0);
		char* str_char = (char*)str.GetBuffer();
		char update[1000];
		sprintf_s(update, "UPDATE car SET %s=\'%s\' WHERE DB_ID=\'%s\'", Col_Name_char, tem_char, str_char);


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
void CAR::OnBnClickedButton2()
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
		int totalRowNum = m_list_car.GetItemCount();//列表的行数
		int expectNum = 1;//第一列期望的序号
		int realNum;//第一列实际的序号
		char insert[1000];
		if (totalRowNum == 0)
		{
			CString expectNum_CStr;
			expectNum_CStr.Format("%d", expectNum);
			char* expectNum_char = (char*)expectNum_CStr.GetBuffer();
			sprintf_s(insert, "insert into car(DB_ID) values (\'%s\')", expectNum_char);
		}
		for (int i=0; i < totalRowNum; i++)
		{
			//获取第一列某一行的值
			CString str;
			str = m_list_car.GetItemText(i, 0);

			CString str1;
			str1.Format("%d", expectNum);
			realNum = _ttoi(str);
			if (totalRowNum == 1)
			{
				CString expectNum_CStr;
				expectNum_CStr.Format("%d", expectNum+1);
				char* expectNum_char = (char*)expectNum_CStr.GetBuffer();
				sprintf_s(insert, "insert into car(DB_ID) values (\'%s\')", expectNum_char);
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
					sprintf_s(insert, "insert into car(DB_ID) values (\'%s\')", expectNum_char);
					break;
				}
				if (expectNum == totalRowNum)
				{
					CString expectNum_CStr;
					expectNum_CStr.Format("%d", expectNum + 1);
					char* expectNum_char = (char*)expectNum_CStr.GetBuffer();
					sprintf_s(insert, "insert into car(DB_ID) values (\'%s\')", expectNum_char);
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


	m_list_car.DeleteAllItems();	//清空所有表项
	while (m_list_car.DeleteColumn(0));	//清空所有表头

	//此处待优化
	//重新打开数据库进行查询
	MYSQL mysql;
	MYSQL* connect;
	connect = mysql_init(&mysql);
	if (connect == NULL)
	{
		AfxMessageBox("初始化数据库失败");
		return;
	}
	connect = mysql_real_connect(connect, "localhost", "root", "123456", "steel_mill", 3306, NULL, 0);
	if (connect == NULL)
	{
		AfxMessageBox("连接数据库失败");
		return;
	}
	char sql[1000] = { 0 };
	//将编码设置为gbk
	strcpy_s(sql, "set names gbk");
	if (mysql_query(connect, sql))
	{
		AfxMessageBox("设置字符编码gbk失败");
		return;
	}
	//设置编码格式utf8
	strcpy_s(sql, "set names utf8");
	int ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox("设置字符编码utf8失败");
		return;
	}
	strcpy_s(sql, "SELECT DB_ID AS '序号',DB_CarNum AS '行车号',DB_IPLeftDown AS '左下方摄像头IP',DB_IPRightDown AS '右下方摄像头IP',DB_IPLeft AS '左边摄像头IP',DB_IPRight AS '右边摄像头IP',DB_IPGlobal AS '全景摄像头IP',DB_ChannelNum AS '通道号',DB_SidewaysDis AS '侧偏距离',DB_CorrectionAngle AS '矫正角',DB_232PortNo AS '232端口号',DB_232PortSamplingFrequency AS '232端口采样频率',DB_485PortNo AS '485端口号',DB_485PortSamplingFrequency AS '485端口采样频率',DB_RopeMargin AS '吊耳距离行车边缘' FROM car ORDER BY DB_ID+0 DESC");
	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox("查询行车表失败");
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
				m_list_car.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 50);
			}
			else
			{
				m_list_car.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 200);
			}
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_car.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_car.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	mysql_close(connect);

}

//升序排列（刷新）
void CAR::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list_car.DeleteAllItems();	//清空所有表项
	while (m_list_car.DeleteColumn(0));	//清空所有表头
	// TODO: 在此添加控件通知处理程序代码
	MYSQL mysql;
	MYSQL* connect;
	MYSQL_FIELD* fields;
	connect = mysql_init(&mysql);
	if (connect == NULL)
	{
		AfxMessageBox("初始化数据库失败");
		return;
	}
	connect = mysql_real_connect(connect, "localhost", "root", "123456", "steel_mill", 3306, NULL, 0);
	if (connect == NULL)
	{
		AfxMessageBox("连接数据库失败");
		return;
	}
	char sql[1000] = { 0 };
	//将编码设置为gbk
	strcpy_s(sql, "set names gbk");
	if (mysql_query(connect, sql))
	{
		AfxMessageBox("设置字符编码gbk失败");
		return;
	}
	//设置编码格式utf8
	strcpy_s(sql, "set names utf8");
	int ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox("设置字符编码utf8失败");
		return;
	}
	strcpy_s(sql, "SELECT DB_ID AS '序号',DB_CarNum AS '行车号',DB_IPLeftDown AS '左下方摄像头IP',DB_IPRightDown AS '右下方摄像头IP',DB_IPLeft AS '左边摄像头IP',DB_IPRight AS '右边摄像头IP',DB_IPGlobal AS '全景摄像头IP',DB_ChannelNum AS '通道号',DB_SidewaysDis AS '侧偏距离',DB_CorrectionAngle AS '矫正角',DB_232PortNo AS '232端口号',DB_232PortSamplingFrequency AS '232端口采样频率',DB_485PortNo AS '485端口号',DB_485PortSamplingFrequency AS '485端口采样频率',DB_RopeMargin AS '吊耳距离行车边缘' FROM car ORDER BY DB_ID+0 DESC");
	mysql_query(connect, "SET NAMES GB2312");
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox("查询行车表失败");
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
				m_list_car.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 50);
			}
			else
			{
				m_list_car.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 200);
			}
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_car.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_car.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	mysql_close(connect);
}



//根据行车号查询相关信息
void CAR::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	MYSQL mysql;
	MYSQL* connect;
	MYSQL_FIELD* fields;
	connect = mysql_init(&mysql);
	if (connect == NULL)
	{
		AfxMessageBox("初始化数据库失败");
		return;
	}
	connect = mysql_real_connect(connect, "localhost", "root", "123456", "steel_mill", 3306, NULL, 0);
	if (connect == NULL)
	{
		AfxMessageBox("连接数据库失败");
		return;
	}
	char sql[1000] = { 0 };
	int ret = mysql_query(connect, sql);

	UpdateData(true);
	if (m_num_car_select == "")
	{
		AfxMessageBox("请输入所要查询的行车号");
		UpdateData(false);
		return;
	}
	char* num = (char*)m_num_car_select.GetBuffer();
	sprintf_s(sql, "SELECT DB_ID AS '序号',DB_CarNum AS '行车号',DB_IPLeftDown AS '左下方摄像头IP',DB_IPRightDown AS '右下方摄像头IP',DB_IPLeft AS '左边摄像头IP',DB_IPRight AS '右边摄像头IP',DB_IPGlobal AS '全景摄像头IP',DB_ChannelNum AS '通道号',DB_SidewaysDis AS '侧偏距离',DB_CorrectionAngle AS '矫正角',DB_232PortNo AS '232端口号',DB_232PortSamplingFrequency AS '232端口采样频率',DB_485PortNo AS '485端口号',DB_485PortSamplingFrequency AS '485端口采样频率',DB_RopeMargin AS '吊耳距离行车边缘' FROM car WHERE DB_CarNum=\'%s\'", num);
	
	m_list_car.DeleteAllItems();	//清空所有表项
	while (m_list_car.DeleteColumn(0));	//清空所有表头

	mysql_query(connect, "SET NAMES GB2312");//当编辑框输入中文的时候也可以识别
	ret = mysql_query(connect, sql);
	if (ret)
	{
		AfxMessageBox("查询行车信息表失败");
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
				m_list_car.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 50);
			}
			else
			{
				m_list_car.InsertColumn(i, fields[i].name, LVCFMT_LEFT, 200);
			}
		}

		// 遍历结果集的每一行数据
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < field_count; i++)
			{
				int column = 1;
				m_list_car.InsertItem(i, row[i]);
				for (int j = 1; j < field_count; j++)
				{
					m_list_car.SetItemText(i, column++, row[j]);
				}
				break;
			}

		}
		mysql_free_result(res);
	}
	UpdateData(false);
	mysql_close(connect);
}





BOOL CAR::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		// 如果消息是键盘按下事件，且是Entert键，执行以下代码（什么都不做，你可以自己添加想要的代码）
		GetDlgItem(IDC_CAR_BUTTON_FRUSH)->SetFocus();
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CAR::OnPaint()
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


HBRUSH CAR::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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






#include "../../include/logicalCtrl/Function.h"


//�������ݿ�
MYSQL* Function::Connect(MYSQL* pConn) {
	pConn = mysql_init(NULL);
	if (!mysql_real_connect(pConn, "localhost", "root", "123456", "steel_mill", 3306, NULL, 0))
	{
		printf("�޷��������ݿ�:%s", mysql_error(pConn));
		return pConn;
	}
	return pConn;
}

//�ر����ݿ�
void Function::close(MYSQL* pConn) {
	mysql_close(pConn);
}

//ȡ��������С������λ�ľ���C_workRange
double Function::getConstantWorkRange() {
	double WorkRange;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_workRange from constant"))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	WorkRange = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return WorkRange;
}

//������������ǽ�����
double Function::getConstantReadingDis() {
	double ReadingDis;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_ReadingDis from constant"))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	ReadingDis = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return ReadingDis;
}

//���⵽ǽ�����
double Function::getConstantLaunchDistance() {
	double LaunchDistance;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_LaunchDistance from constant"))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	LaunchDistance = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return LaunchDistance;
}

//С�����浽���ľ���
double Function::getConstantTrolleyDistance() {
	double TrolleyDistance;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_TrolleyDistance from constant"))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	TrolleyDistance = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return TrolleyDistance;
}

//��һ�������ߵ�ǽ��ľ���
double Function::getConstantTrackFirL() {
	double TrackFirL;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_trackFirL from constant"))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	TrackFirL = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return TrackFirL;
}

//��һ������ұߵ�ǽ��ľ���
double Function::getConstantTrackFirR() {
	double C_trackFirR;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_trackFirR from constant"))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	C_trackFirR = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return C_trackFirR;
}

//�ڶ��������ߵ�ǽ��ľ���
double Function::getConstantTrackSecL() {
	double C_trackSecL;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_trackSecL from constant"))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	C_trackSecL = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return C_trackSecL;
}

//�ڶ�������ұߵ�ǽ��ľ���
double Function::getConstantTrackSecR() {
	double C_trackSecR;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_trackSecR from constant"))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	C_trackSecR = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return C_trackSecR;
}

//�����������ߵ�ǽ��ľ���
double Function::getConstantTrackThirdL() {
	double C_trackThirdL;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_trackThirdL from constant"))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	C_trackThirdL = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return C_trackThirdL;
}

//����������ұߵ�ǽ��ľ���
double Function::getConstantTrackThirdR() {
	double C_trackThirdR;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_trackThirdR from constant"))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	C_trackThirdR = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return C_trackThirdR;
}

//ͨ���г��ţ���ȡȫ������ͷIP
std::string Function::getCarIPGlobal(char* CarNum) {
	char* DB_IPGlobal;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_IPGlobal FROM car WHERE DB_CarNum=\'%s\'", CarNum);
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return 0;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	DB_IPGlobal = row[0];
	mysql_free_result(result);
	close(pConn);
	std::string str = DB_IPGlobal;
	return str;
}

//ͨ���г��ţ���ȡȫ������ͷIP    bool
bool Function::getCarIPGlobal(std::string& CarNum, std::string& carIPGlobal) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	if (CarNum == "")
	{
		return false;
	}
	else {
		sprintf_s(sql, "SELECT DB_IPGlobal FROM car WHERE DB_CarNum=\'%s\'", CarNum.c_str());
		if (mysql_query(pConn, sql))
		{
			printf("��ѯʧ��:%s", mysql_error(pConn));
			return 0;
		}
		MYSQL_RES* result = mysql_store_result(pConn);
		MYSQL_ROW row;
		row = mysql_fetch_row(result);
		carIPGlobal = row[0];
		mysql_free_result(result);
		close(pConn);
		return true;
	}

}


//�����г���ȡ�����ͨ����
std::string Function::getCarChannelNum(char* CarNum) {
	std::string DB_ChannelNum;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_ChannelNum FROM car WHERE DB_CarNum=\'%s\'", CarNum);
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return NULL;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	DB_ChannelNum = row[0];
	mysql_free_result(result);
	close(pConn);
	return DB_ChannelNum;
}

//�����г���ȡ�����ͨ����  bool
bool Function::getCarChannelNum(std::string& CarNum, std::string& carChannelNum) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	if (CarNum == "")
	{
		return false;
	}
	else {
		sprintf_s(sql, "SELECT DB_ChannelNum FROM car WHERE DB_CarNum=\'%s\'", CarNum.c_str());
		if (mysql_query(pConn, sql))
		{
			printf("��ѯʧ��:%s", mysql_error(pConn));
			return NULL;
		}
		MYSQL_RES* result = mysql_store_result(pConn);
		MYSQL_ROW row;
		row = mysql_fetch_row(result);
		carChannelNum = row[0];
		mysql_free_result(result);
		close(pConn);
		return true;
	}

}


//�����г���ȡ�������߾�
double Function::getCarRopeMargin(char* CarNum) {
	double DB_RopeMargin;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "select DB_RopeMargin from car where DB_CarNum=\'%s\'", CarNum);
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	DB_RopeMargin = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return DB_RopeMargin;
}


//�����г���ȡ�������߾�  bool
bool Function::getCarRopeMargin(std::string& CarNum, double& carRopeMargin) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	if (CarNum == "")
	{
		return false;
	}
	else {
		sprintf_s(sql, "select DB_RopeMargin from car where DB_CarNum=\'%s\'", CarNum.c_str());
		if (mysql_query(pConn, sql))
		{
			printf("��ѯʧ��:%s", mysql_error(pConn));
			return false;
		}
		MYSQL_RES* result = mysql_store_result(pConn);
		MYSQL_ROW row;
		row = mysql_fetch_row(result);
		carRopeMargin = atof(row[0]);
		mysql_free_result(result);
		close(pConn);
		return carRopeMargin;
	}

}

//���ݹ�λ��ȡ����λ��Ӧ�Ĺ����
int Function::getStationTrackNum(char* staNum) {
	int DB_TrackNum;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "select DB_TrackNum from station where DB_StaNum=\'%s\'", staNum);
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	DB_TrackNum = atoi(row[0]);
	mysql_free_result(result);
	close(pConn);
	return DB_TrackNum;
}

//���ݹ�λ��ȡ����λ��Ӧ�Ĺ����  bool
bool Function::getStationTrackNum(std::string& stationNum, int& stationTrackNum) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	if (stationNum == "")
	{
		return false;
	}
	else {
		sprintf_s(sql, "select DB_TrackNum from station where DB_StaNum=\'%s\'", stationNum.c_str());
		if (mysql_query(pConn, sql))
		{
			printf("��ѯʧ��:%s", mysql_error(pConn));
			return false;
		}
		MYSQL_RES* result = mysql_store_result(pConn);
		MYSQL_ROW row;
		row = mysql_fetch_row(result);
		stationTrackNum = atoi(row[0]);
		mysql_free_result(result);
		close(pConn);
		return true;
	}

}

//���ݹ�λ��ȡ���Ŵ���
std::string Function::getStationEnlarge(char* StaNum) {
	std::string DB_Enlarge;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_Enlarge FROM station WHERE DB_StaNum=\'%s\'", StaNum);
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return 0;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	DB_Enlarge = row[0];
	mysql_free_result(result);
	close(pConn);
	return DB_Enlarge;
}

//���ݹ�λ��ȡ���Ŵ���  bool
bool Function::getStationEnlarge(std::string& stationNum, std::string& stationEnlarge) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	if (stationNum == "")
	{
		return false;
	}
	else {
		sprintf_s(sql, "SELECT DB_Enlarge FROM station WHERE DB_StaNum=\'%s\'", stationNum.c_str());
		if (mysql_query(pConn, sql))
		{
			printf("��ѯʧ��:%s", mysql_error(pConn));
			return false;
		}
		MYSQL_RES* result = mysql_store_result(pConn);
		MYSQL_ROW row;
		row = mysql_fetch_row(result);
		stationEnlarge = row[0];
		mysql_free_result(result);
		close(pConn);
		return true;
	}
}


//���ݹ�λ��ȡ���߶�
double Function::getStationHeight(char* StaNum) {
	double DB_Height;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_Height FROM station WHERE DB_StaNum=\'%s\'", StaNum);
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	DB_Height = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return DB_Height;
}


//���ݹ�λ��ȡ���߶� bool
bool Function::getStationHeight(std::string& stationNum, double& stationHeight) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	if (stationNum == "")
	{
		return false;
	}
	sprintf_s(sql, "SELECT DB_Height FROM station WHERE DB_StaNum=\'%s\'", stationNum.c_str());
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	stationHeight = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return true;
}

//���ݹ�λ��ȡ�����������÷�Χ
double Function::getStationBluetoothDis(char* StaNum) {
	double DB_BluetoothDis;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_BluetoothDis FROM station WHERE DB_StaNum=\'%s\'", StaNum);
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	DB_BluetoothDis = atof(row[0]);
	mysql_free_result(result);
	close(pConn);
	return DB_BluetoothDis;
}

//���ݹ�λ��ȡ�����������÷�Χ bool
bool Function::getStationBluetoothDis(std::string& stationNum, double& stationBluetoothDis) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	if (stationNum == "")
	{
		return false;
	}
	else {
		sprintf_s(sql, "SELECT DB_BluetoothDis FROM station WHERE DB_StaNum=\'%s\'", stationNum.c_str());
		if (mysql_query(pConn, sql))
		{
			printf("��ѯʧ��:%s", mysql_error(pConn));
			return false;
		}
		MYSQL_RES* result = mysql_store_result(pConn);
		MYSQL_ROW row;
		row = mysql_fetch_row(result);
		stationBluetoothDis = atof(row[0]);
		mysql_free_result(result);
		close(pConn);
		return true;
	}

}




//�����г���,ȡ���ĸ�����ͷ��IP
CarCameraIP Function::getCarCameraIP(char* CarNum) {
	CarCameraIP carCameraIP;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_IPLeftDown,DB_IPRightDown,DB_IPLeft,DB_IPRight FROM car WHERE DB_CarNum=\'%s\'", CarNum);
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		carCameraIP.leftDownIP = "";
		carCameraIP.rightDownIP = "";
		carCameraIP.leftIP = "";
		carCameraIP.rightIP = "";
		return carCameraIP;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	carCameraIP.leftDownIP = row[0];
	carCameraIP.rightDownIP = row[1];
	carCameraIP.leftIP = row[2];
	carCameraIP.rightIP = row[3];
	mysql_free_result(result);
	close(pConn);
	return carCameraIP;
}

//�����г���,ȡ���ĸ�����ͷ��IP bool
bool Function::getCarCameraIP(std::string& CarNum, CarCameraIP& carCameraIP) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	if (CarNum == "")
	{
		return false;
	}
	else {
		sprintf_s(sql, "SELECT DB_IPLeftDown,DB_IPRightDown,DB_IPLeft,DB_IPRight FROM car WHERE DB_CarNum=\'%s\'", CarNum.c_str());
		if (mysql_query(pConn, sql))
		{
			printf("��ѯʧ��:%s", mysql_error(pConn));
			//carCameraIP.leftDownIP = "";
			//carCameraIP.rightDownIP = "";
			//carCameraIP.leftIP = "";
			//carCameraIP.rightIP = "";
			return false;
		}
		MYSQL_RES* result = mysql_store_result(pConn);
		MYSQL_ROW row;
		row = mysql_fetch_row(result);
		carCameraIP.leftDownIP = row[0];
		carCameraIP.rightDownIP = row[1];
		carCameraIP.leftIP = row[2];
		carCameraIP.rightIP = row[3];
		mysql_free_result(result);
		close(pConn);
		return true;
	}

}

//���ݹ�λ��ȡ����������ͷIP bool
bool Function::getStationCameraIP(std::string& stationNum, StationCameraIP& stationCameraIP) {
	//StationCameraIP stationCameraIP;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	if (stationNum == "")
	{
		return FALSE;
	}
	else {
		sprintf_s(sql, "SELECT DB_IPLeft,DB_IPRight FROM station WHERE DB_StaNum=\'%s\'", stationNum.c_str());

		if (mysql_query(pConn, sql))
		{
			printf("��ѯʧ��:%s", mysql_error(pConn));
			//stationCameraIP.leftIP = "";
			//stationCameraIP.rightIP = "";
			return false;
		}
		MYSQL_RES* result = mysql_store_result(pConn);
		MYSQL_ROW row;
		row = mysql_fetch_row(result);
		stationCameraIP.leftIP = row[0];
		stationCameraIP.rightIP = row[1];
		mysql_free_result(result);
		close(pConn);
		return true;
	}
}

//���ݹ�λ��ȡ����������ͷIP
StationCameraIP Function::getStationCameraIP(char* StaNum) {
	StationCameraIP stationCameraIP;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_IPLeft,DB_IPRight FROM station WHERE DB_StaNum=\'%s\'", StaNum);
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		stationCameraIP.leftIP = "";
		stationCameraIP.rightIP = "";
		return stationCameraIP;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	stationCameraIP.leftIP = row[0];
	stationCameraIP.rightIP = row[1];
	mysql_free_result(result);
	close(pConn);
	return stationCameraIP;
}

//ȡ����ǩ�ź�������Ϣ
std::vector<std::pair<int,double>> Function::getStationTagInfo() {

	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	//strcpy_s(sql, "SELECT DB_TagNum,DB_Coordinate FROM station GROUP BY DB_TagNum");  2020-10-28 ��λ��޸�  
	strcpy_s(sql, "SELECT DISTINCT DB_TagNum,DB_Coordinate FROM station");
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));

	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	int row_count = mysql_num_rows(result);
	std::vector<std::pair<int, double>> tagInfo(row_count);
	int i = 0;
	int tagNum = 0;
	double coordinate = 0;
	while (row = mysql_fetch_row(result))
	{
		tagNum = atoi(row[0]);
		coordinate = atof(row[1]);
		tagInfo[i].first = tagNum;
		tagInfo[i].second = coordinate;
		i++;
	}
	mysql_free_result(result);
	close(pConn);
	return tagInfo;
}

//ȡ����ǩ�ź�������Ϣ  bool
bool Function::getStationTagInfo(std::vector<std::pair<int, double> >& staTagInfo) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	strcpy_s(sql, "SELECT DB_TagNum,DB_Coordinate FROM station GROUP BY DB_TagNum");
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	int row_count = mysql_num_rows(result);
	//std::vector<std::pair<int, double>> tagInfo(row_count);
	int i = 0;
	int tagNum = 0;
	double coordinate = 0;
	while (row = mysql_fetch_row(result))
	{
		tagNum = atoi(row[0]);
		coordinate = atof(row[1]);
		staTagInfo[i].first = tagNum;
		staTagInfo[i].second = coordinate;
		i++;
	}
	mysql_free_result(result);
	close(pConn);
	return true;
}

//ȡ��ÿһ����λ�ϵ���������ͷIP ��λ�ڶ��Ź�λ������ͷ��ȡ��
std::vector<StationInfoIP> Function::getStationInfoIP() {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	strcpy_s(sql, "SELECT DB_IPLeft,DB_IPRight, DB_StaNum FROM station WHERE DB_TrackNum != 2");
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));

	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	int row_count = mysql_num_rows(result);
	std::vector<StationInfoIP> stationInfoIP(row_count);
	int i = 0;
	while (row = mysql_fetch_row(result))
	{
		stationInfoIP[i].leftIP = row[0];
		stationInfoIP[i].rightIP = row[1];
		stationInfoIP[i].stationNum = row[2];
		i++;
	}
	mysql_free_result(result);
	close(pConn);
	return stationInfoIP;
}

//ȡ��ÿһ����λ�ϵ���������ͷIP ��λ�ڶ��Ź�λ������ͷ��ȡ�� bool
bool Function::getStationInfoIP(std::vector<StationInfoIP>& stationInfoIP) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	strcpy_s(sql, "SELECT DB_IPLeft,DB_IPRight, DB_StaNum FROM station WHERE DB_TrackNum != 2");
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	int row_count = mysql_num_rows(result);
	//std::vector<StationInfoIP> stationInfoIP(row_count);
	int i = 0;
	while (row = mysql_fetch_row(result))
	{
		stationInfoIP[i].leftIP = row[0];
		stationInfoIP[i].rightIP = row[1];
		stationInfoIP[i].stationNum = row[2];
		i++;
	}
	mysql_free_result(result);
	close(pConn);
	return true;
}

//ȡ���г����������ͷIP
std::vector<CarInfoIP> Function::getCarInfoIP() {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	strcpy_s(sql, "SELECT DB_CarNum,DB_IPLeftDown, DB_IPRightDown, DB_IPLeft, DB_IPRight, DB_IPGlobal FROM car");
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));

	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	int row_count = mysql_num_rows(result);
	std::vector<CarInfoIP> carInfoIP(row_count);
	int i = 0;
	while (row = mysql_fetch_row(result))
	{
		carInfoIP[i].carNum = row[0];
		carInfoIP[i].leftDownIP = row[1];
		carInfoIP[i].rightDownIP = row[2];
		carInfoIP[i].leftIP = row[3];
		carInfoIP[i].rightIP = row[4];
		carInfoIP[i].panoramicIP = row[5];
		i++;
	}
	mysql_free_result(result);
	close(pConn);
	return carInfoIP;
}

//ȡ���г����������ͷIP bool
bool Function::getCarInfoIP(std::vector<CarInfoIP>& carInfoIP) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	strcpy_s(sql, "SELECT DB_CarNum,DB_IPLeftDown, DB_IPRightDown, DB_IPLeft, DB_IPRight, DB_IPGlobal FROM car");
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	int row_count = mysql_num_rows(result);
	//std::vector<CarInfoIP> carInfoIP(row_count);
	int i = 0;
	while (row = mysql_fetch_row(result))
	{
		carInfoIP[i].carNum = row[0];
		carInfoIP[i].leftDownIP = row[1];
		carInfoIP[i].rightDownIP = row[2];
		carInfoIP[i].leftIP = row[3];
		carInfoIP[i].rightIP = row[4];
		carInfoIP[i].panoramicIP = row[5];
		i++;
	}
	mysql_free_result(result);
	close(pConn);
	return true;
}

//ȡ����λ�źͶ�Ӧ�Ĺ����
std::vector<std::pair<std::string, int>> Function::getStaNumAndTrackNum() {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	strcpy_s(sql, "SELECT DB_StaNum,DB_TrackNum FROM station");
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));

	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	int row_count = mysql_num_rows(result);
	std::vector<std::pair<std::string, int>> staNumAndTrackNum(row_count);
	int i = 0;
	int trackNum = 0;
	while (row = mysql_fetch_row(result))
	{
		if (row[1] == NULL)
		{
			staNumAndTrackNum[i].first = row[0];
			staNumAndTrackNum[i].second = trackNum;
		}
		else
		{
			trackNum = atof(row[1]);
			staNumAndTrackNum[i].first = row[0];
			staNumAndTrackNum[i].second = trackNum;
		}
		i++;
	}
	mysql_free_result(result);
	close(pConn);
	return staNumAndTrackNum;
}

//ȡ����λ�źͶ�Ӧ�Ĺ����  bool
bool Function::getStaNumAndTrackNum(std::vector<std::pair<std::string, int> >& stationNumAndTrackNum) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	strcpy_s(sql, "SELECT DB_StaNum,DB_TrackNum FROM station");
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));
		return false;
	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	int row_count = mysql_num_rows(result);
	//std::vector<std::pair<std::string, int>> staNumAndTrackNum(row_count);
	int i = 0;
	int trackNum = 0;
	while (row = mysql_fetch_row(result))
	{
		if (row[1] == NULL || row[0] == NULL)
		{
			return false;
		}
		else
		{
			trackNum = atof(row[1]);
			stationNumAndTrackNum[i].first = row[0];
			stationNumAndTrackNum[i].second = trackNum;
		}
		i++;
	}
	mysql_free_result(result);
	close(pConn);
	return true;
}


//���ݱ�ǩ��ȡ����Ӧ��������λ����Ϣ
std::vector<TrackStationNum> Function::getTrackStationNum(char* tagID) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_StaNum,DB_TrackNum FROM station WHERE DB_TagNum=\'%s\'", tagID);
	if (mysql_query(pConn, sql))
	{
		printf("��ѯʧ��:%s", mysql_error(pConn));

	}
	MYSQL_RES* result = mysql_store_result(pConn);
	MYSQL_ROW row;
	int row_count = mysql_num_rows(result);
	std::vector<TrackStationNum> trackStationNum(row_count);
	int i = 0;
	int tracknum = 0;
	while (row = mysql_fetch_row(result))
	{
		trackStationNum[i].stationNum = row[0];
		tracknum = atoi(row[1]);
		trackStationNum[i].trackNum = tracknum;
		i++;
	}
	mysql_free_result(result);
	close(pConn);
	return trackStationNum;
}

//���ݱ�ǩ��ȡ����Ӧ��������λ����Ϣ  bool
bool Function::getTrackStationNum(std::string& tagID, std::vector<TrackStationNum>& trackStationNum) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	if (tagID == "")
	{
		return false;
	}
	else {
		sprintf_s(sql, "SELECT DB_StaNum,DB_TrackNum FROM station WHERE DB_TagNum=\'%s\'", tagID.c_str());
		if (mysql_query(pConn, sql))
		{
			printf("��ѯʧ��:%s", mysql_error(pConn));
			return false;
		}
		MYSQL_RES* result = mysql_store_result(pConn);
		MYSQL_ROW row;
		int row_count = mysql_num_rows(result);
		//std::vector<TrackStationNum> trackStationNum(row_count);
		int i = 0;
		int tracknum = 0;
		while (row = mysql_fetch_row(result))
		{
			trackStationNum[i].stationNum = row[0];
			tracknum = atoi(row[1]);
			trackStationNum[i].trackNum = tracknum;
			i++;
		}
		mysql_free_result(result);
		close(pConn);
		return true;
	}

}
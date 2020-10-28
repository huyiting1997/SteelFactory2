#include "../../include/logicalCtrl/Function.h"


//连接数据库
MYSQL* Function::Connect(MYSQL* pConn) {
	pConn = mysql_init(NULL);
	if (!mysql_real_connect(pConn, "localhost", "root", "123456", "steel_mill", 3306, NULL, 0))
	{
		printf("无法连接数据库:%s", mysql_error(pConn));
		return pConn;
	}
	return pConn;
}

//关闭数据库
void Function::close(MYSQL* pConn) {
	mysql_close(pConn);
}

//取出常量表：小车到工位的距离C_workRange
double Function::getConstantWorkRange() {
	double WorkRange;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_workRange from constant"))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//蓝牙读卡器到墙面距离
double Function::getConstantReadingDis() {
	double ReadingDis;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_ReadingDis from constant"))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//激光到墙面距离
double Function::getConstantLaunchDistance() {
	double LaunchDistance;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_LaunchDistance from constant"))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//小车表面到中心距离
double Function::getConstantTrolleyDistance() {
	double TrolleyDistance;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_TrolleyDistance from constant"))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//第一条轨道左边到墙面的距离
double Function::getConstantTrackFirL() {
	double TrackFirL;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_trackFirL from constant"))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//第一条轨道右边到墙面的距离
double Function::getConstantTrackFirR() {
	double C_trackFirR;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_trackFirR from constant"))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//第二条轨道左边到墙面的距离
double Function::getConstantTrackSecL() {
	double C_trackSecL;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_trackSecL from constant"))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//第二条轨道右边到墙面的距离
double Function::getConstantTrackSecR() {
	double C_trackSecR;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_trackSecR from constant"))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//第三条轨道左边到墙面的距离
double Function::getConstantTrackThirdL() {
	double C_trackThirdL;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_trackThirdL from constant"))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//第三条轨道右边到墙面的距离
double Function::getConstantTrackThirdR() {
	double C_trackThirdR;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	if (mysql_query(pConn, "select C_trackThirdR from constant"))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//通过行车号，获取全景摄像头IP
std::string Function::getCarIPGlobal(char* CarNum) {
	char* DB_IPGlobal;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_IPGlobal FROM car WHERE DB_CarNum=\'%s\'", CarNum);
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));
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


//根据行车号取出球机通道号
std::string Function::getCarChannelNum(char* CarNum) {
	std::string DB_ChannelNum;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_ChannelNum FROM car WHERE DB_CarNum=\'%s\'", CarNum);
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//根据行车号取出吊绳边距
double Function::getCarRopeMargin(char* CarNum) {
	double DB_RopeMargin;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "select DB_RopeMargin from car where DB_CarNum=\'%s\'", CarNum);
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//根据工位号取出工位对应的轨道号
int Function::getStationTrackNum(char* StaNum) {
	int DB_TrackNum;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "select DB_TrackNum from station where DB_StaNum=\'%s\'", StaNum);
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//根据工位号取出放大倍数
std::string Function::getStationEnlarge(char* StaNum) {
	std::string DB_Enlarge;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_Enlarge FROM station WHERE DB_StaNum=\'%s\'", StaNum);
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//根据工位号取出高度
double Function::getStationHeight(char* StaNum) {
	double DB_Height;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_Height FROM station WHERE DB_StaNum=\'%s\'", StaNum);
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//根据工位号取出蓝牙的作用范围
double Function::getStationBluetoothDis(char* StaNum) {
	double DB_BluetoothDis;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_BluetoothDis FROM station WHERE DB_StaNum=\'%s\'", StaNum);
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));
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



//根据行车号,取出四个摄像头的IP
CarCameraIP Function::getCarCameraIP(char* CarNum) {
	CarCameraIP carCameraIP;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_IPLeftDown,DB_IPRightDown,DB_IPLeft,DB_IPRight FROM car WHERE DB_CarNum=\'%s\'", CarNum);
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));
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



//根据工位号取出两个摄像头IP
StationCameraIP Function::getStationCameraIP(char* StaNum) {
	StationCameraIP stationCameraIP;
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_IPLeft,DB_IPRight FROM station WHERE DB_StaNum=\'%s\'", StaNum);
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));
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

//取出标签号和坐标信息
std::vector<std::pair<int,double>> Function::getStationTagInfo() {

	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	strcpy_s(sql, "SELECT DB_TagNum,DB_Coordinate FROM station GROUP BY DB_TagNum");
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));

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

//取出每一个工位上的两个摄像头IP （位于二号工位的摄像头不取）
std::vector<StationInfoIP> Function::getStationInfoIP() {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	strcpy_s(sql, "SELECT DB_IPLeft,DB_IPRight, DB_StaNum FROM station WHERE DB_TrackNum != 2");
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));

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

//取出行车的五个摄像头IP
std::vector<CarInfoIP> Function::getCarInfoIP() {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	strcpy_s(sql, "SELECT DB_CarNum,DB_IPLeftDown, DB_IPRightDown, DB_IPLeft, DB_IPRight, DB_IPGlobal FROM car");
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));

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

std::vector<std::pair<std::string, int>> Function::getStaNumAndTrackNum() {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	strcpy_s(sql, "SELECT DB_StaNum,DB_TrackNum FROM station");
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));

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

std::vector<TrackStationNum> Function::getTrackStationNum(char* tagID) {
	MYSQL* pConn = NULL;
	pConn = Connect(pConn);
	mysql_query(pConn, "set names gbk");
	char sql[1000] = { 0 };
	sprintf_s(sql, "SELECT DB_StaNum,DB_TrackNum FROM station WHERE DB_TagNum=\'%s\'", tagID);
	if (mysql_query(pConn, sql))
	{
		printf("查询失败:%s", mysql_error(pConn));

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
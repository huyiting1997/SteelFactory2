#include "../../pch.h"
#include "../../include/logicalCtrl/LogicControl.h"
#include<string>

LogicControl::LogicControl():
carNum("111")
{
	//从数据库中拿出常量
	C_workRange = data_operate.getConstantWorkRange();
	C_ReadingDis = data_operate.getConstantReadingDis();
	C_LaunchDistance = data_operate.getConstantLaunchDistance();
	C_TrolleyDistance = data_operate.getConstantTrolleyDistance();
	C_trackFirL = data_operate.getConstantTrackFirL();
	C_trackFirR = data_operate.getConstantTrackFirR();
	C_trackSecL = data_operate.getConstantTrackSecL();
	C_trackSecR = data_operate.getConstantTrackSecR();
	C_trackThirdL = data_operate.getConstantTrackThirdL();
	C_trackThirdR = data_operate.getConstantTrackThirdR();
	globalIP = data_operate.getCarIPGlobal(carNum);
	
}
void LogicControl::getCameraIP()
{
	StationIPArray=data_operate.getStationInfoIP();
	CarIPArray = data_operate.getCarInfoIP();
	tagPosition = data_operate.getStationTagInfo();
}

BOOL LogicControl::judegSitution(std::vector<std::string>& CameraIP,  double disL, double disR, double carDis, int tagID)
{
	RfidCam caminfo;
	caminfo = judegStation(carDis,tagID);
	CarCameraIP carIP;
	StationCameraIP stationIP;
	if (caminfo.display) {//切入工位
		
		stationIP = data_operate.getStationCameraIP((char*)caminfo.stationID.c_str());
		//获取工位IP
		carIP=data_operate.getCarCameraIP(carNum);
		//获取行车IP（包含四个值）
		switch (JudgeMargin(disL,disR))
		{
		case 0:
			//向CameraIP中加入工位上的两个以及当前行车的左右防撞
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			return 0;
		case 1:
			//向CameraIP中左边防撞，工位IP，右边防撞
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			return 1;
		case 2:
			//向CameraIP中左边防撞，工位IP，右边防撞
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			return 2;
		case 3:
			//工位右边左边工位
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			return 3;
		case 4:
			//工位右边左边工位
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			return 4;
		case 5:
			//左边右边工位左工位右
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			return 5;
		case 6:
			//左边右边工位左工位右
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			return 6;
		case 7:
			//左边右边工位左工位右
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			return 7;
		case 8:
			//左边右边工位左工位右
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			return 8;
		default:
			return 9;
			break;
		}
	}
	else {//未切入工位
		switch (JudgeMargin(disL, disR))
		{
			//获取行车上的四个IP
			carIP = data_operate.getCarCameraIP(carNum);
		case 0:
			//一次切入行车上的四个摄像头IP
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightDownIP);
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			return 0;
		case 1:
			//向CameraIP中左边防撞，右下IP，左下IP，右边防撞
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightDownIP);
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightIP);
			return 1;
		case 2:
			//左边防撞，右下IP，左下IP，右边防撞
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightDownIP);
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightIP);
			return 2;
		case 3:
			//左下右边防撞左边防撞右下
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightDownIP);
			return 3;
		case 4:
			//左下右边防撞左边防撞右下
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightDownIP);
			return 4;
		case 5:
			//左边防撞右边防撞左下右下球机
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightDownIP);
			return 5;
		case 6:
			//左边防撞右边防撞左下右下球机
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightDownIP);
			return 6;
		case 7:
			//左边防撞右边防撞左下右下球机
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightDownIP);
			return 7;
		case 8:
			//左边防撞右边防撞左下右下球机
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightDownIP);
			return 8;
		default:
			return 9;
			break;
		}
	}
	return 9;
}

int LogicControl::JudgeTrack(double modbusCarDis)
{
	double m_modbusCarDis = modbusCarDis;
	if (C_trackFirL < m_modbusCarDis && m_modbusCarDis < C_trackFirR) {
		return 1;  //返回1，代表轨道1
	}
	else if (C_trackSecL < m_modbusCarDis && m_modbusCarDis < C_trackSecR) {
		return 2; //返回2，代表轨道2
	}
	else if (C_trackThirdL < m_modbusCarDis && m_modbusCarDis < C_trackThirdL) {
		return 3; //返回3，代表轨道3
	}
	else {
		return 0; //返回0，代表没有进入轨道，空白区
	}
}

std::string LogicControl::nearestStationnum(int tagID, double modbusCarDis)
{
	char* a;
	std::vector<TrackStationNum> trackStationNum;
	std::string str;
	while (tagID) {
		str += (tagID % 10 + '0');
		tagID = tagID / 10;
	}
	a =(char*) str.c_str();
	trackStationNum=data_operate.getTrackStationNum(a);
	int track=JudgeTrack(modbusCarDis);
	std::string stationNum;
	if (track) {//进入了轨道
		for (int i = 0; i < trackStationNum.size(); i++) {
			if (trackStationNum[i].trackNum == track) {
				stationNum = trackStationNum[i].stationNum;
				break;
			}
		}
	}
	else {
		stationNum = "###";
	}
	return stationNum;
}

RfidCam LogicControl::judegStation(double modbusCarDis,int tagID)
{
	std::string stationNum;
	RfidCam rfid;
	stationNum = nearestStationnum(tagID, modbusCarDis);
	if (!stationNum.compare("###")) {
		rfid.display = false;
		rfid.stationID = "###";
		return rfid;
	}
	else {
		rfid.display = true;
		rfid.stationID = stationNum;
		return rfid;
	}
}

BOOL LogicControl::JudgeMargin(double disL, double disR)
{

	int L = 0;
	int R = 0;
	if (disL < 3) {
		L = 1;//左报警
	}
	else if (disL > 5) {
		L = -1;//左安全
	}
	else {
		L = 0;//左预警
	}

	if (disR < 3) {
		R = 1;//右报警
	}
	else if (disR > 5) {
		R = -1;
	}
	else {
		R = 0;
	}


	switch (L)
	{
	case -1: {
		switch (R)
		{
		case -1:
			return  ALLSAFE;       //左安全，右安全
			break;
		case 0:
			return  RIGWLEFTSAFE;  //左安全，右预警
			break;
		case 1:
			return  RIGALEFTSAFE;  //左安全，右报警
			break;
		}
		break;
	}
	case 0: {
		switch (R)
		{
		case -1:
			return  LEFTWRIGSAFE;  //左预警，右安全   
			break;
		case 0:
			return  RIGWLEFTW;   //左预警，右预警
			break;
		case 1:
			return  RIGALEFTW;   //左预警 ,右报警，
			break;
		}
		break;
	}
	case 1: {
		switch (R)
		{
		case -1:
			return  LEFTARIGSAFE;  //左报警，右安全 
			break;
		case 0:
			return  RIGWLEFTA;   //左报警,右预警
			break;
		case 1:
			return  RIGALEFTA;   //左报警,右报警
			break;
		}
		break;
	}
	}
}


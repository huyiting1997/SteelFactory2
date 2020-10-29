#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <winsock.h> //注意顺序，要放在mysql.h前
#include <mysql.h>//控制台项目中要在mysql.h之前include <winsock.h>
#include<iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <utility>
#include"global.h"

class Function
{
public:

	static MYSQL* Connect(MYSQL* pConn);//连接数据库
	static void close(MYSQL* pConn);//关闭数据库

	static double getConstantWorkRange();//取出常量表：小车到工位的距离C_workRange
	static double getConstantReadingDis();//基站到墙面距离
	static double getConstantLaunchDistance();//激光到墙面距离
	static double getConstantTrolleyDistance();//小车表面到中心距离
	static double getConstantTrackFirL();//第一条轨道左边到墙面的距离
	static double getConstantTrackFirR();//第一条轨道右边到墙面的距离
	static double getConstantTrackSecL();//第二条轨道左边到墙面的距离
	static double getConstantTrackSecR();//第二条轨道右边到墙面的距离
	static double getConstantTrackThirdL();//第三条轨道左边到墙面的距离
	static double getConstantTrackThirdR();//第三条轨道右边到墙面的距离




	static CarCameraIP getCarCameraIP(char* CarNum);//根据行车号,取出四个摄像头的IP
	bool getCarCameraIP(std::string& CarNum, CarCameraIP& carCameraIP);

	static std::string getCarIPGlobal(char* CarNum);//通过行车号，获取全景摄像头IP
	bool getCarIPGlobal(std::string& CarNum, std::string& carIPGlobal);

	static std::string getCarChannelNum(char* CarNum);//根据行车号取出球机通道号
	bool getCarChannelNum(std::string& CarNum, std::string& carChannelNum);

	static double getCarRopeMargin(char* CarNum);//根据行车号取出吊绳边距
	bool getCarRopeMargin(std::string& CarNum, double& carRopeMargin);



	static int getStationTrackNum(char* staNum);//根据工位号取出工位对应的轨道号
	bool getStationTrackNum(std::string& stationNum, int& stationTrackNum);

	static std::string getStationEnlarge(char* StaNum);//根据工位号取出放大倍数
	bool getStationEnlarge(std::string& stationNum, std::string& stationEnlarge);

	static double getStationHeight(char* StaNum); //根据工位号取出高度
	bool getStationHeight(std::string& stationNum, double& stationHeight);

	static double getStationBluetoothDis(char* StaNum);//根据工位号取出蓝牙的作用范围
	bool getStationBluetoothDis(std::string& stationNum, double& stationBluetoothDis);

	static StationCameraIP getStationCameraIP(char* StaNum);//根据工位号取出两个摄像头IP
	bool getStationCameraIP(std::string& stationNum, StationCameraIP& stationCameraIP);

	static std::vector<std::pair<int, double> > getStationTagInfo();//取出标签号和坐标信息
	bool getStationTagInfo(std::vector<std::pair<int, double> >& stationTagInfo);

	static std::vector<StationInfoIP> getStationInfoIP();//取出每一个工位上的两个摄像头IP （位于二号工位的摄像头不取）
	bool getStationInfoIP(std::vector<StationInfoIP>& stationInfoIP);

	static std::vector<CarInfoIP> getCarInfoIP();//取出行车的五个摄像头IP  返回值为
	bool getCarInfoIP(std::vector<CarInfoIP>& carInfoIP);

	static std::vector<std::pair<std::string, int>> getStaNumAndTrackNum();//取出工位号和对应的轨道号
	bool getStaNumAndTrackNum(std::vector<std::pair<std::string, int> >& stationNumAndTrackNum);

	static std::vector<TrackStationNum> getTrackStationNum(char* tagID);//根据标签号取出对应的三个工位的信息
	bool getTrackStationNum(std::string& tagID, std::vector<TrackStationNum>& trackStationNum);
	
};

#endif
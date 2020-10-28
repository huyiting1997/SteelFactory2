#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <winsock.h> //注意顺序，要放在mysql.h前
#include <mysql.h>//控制台项目中要在mysql.h之前include <winsock.h>
#include<iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include"global.h"
#include <utility>

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
	static std::string getCarIPGlobal(char* CarNum);//通过行车号，获取全景摄像头IP
	static std::string getCarChannelNum(char* CarNum);//根据行车号取出球机通道号
	static double getCarRopeMargin(char* CarNum);//根据行车号取出吊绳边距

	static int getStationTrackNum(char* StaNum);//根据工位号取出工位对应的轨道号
	static std::string getStationEnlarge(char* StaNum);//根据工位号取出放大倍数
	static double getStationHeight(char* StaNum); //根据工位号取出高度
	static double getStationBluetoothDis(char* StaNum);//根据工位号取出蓝牙的作用范围
	static StationCameraIP getStationCameraIP(char* StaNum);//根据工位号取出两个摄像头IP
	//静态取出
	static std::vector<std::pair<int, double>> getStationTagInfo();//取出标签号和坐标信息
	static std::vector<StationInfoIP> getStationInfoIP();//取出每一个工位上的两个摄像头IP （位于二号工位的摄像头不取）
	static std::vector<CarInfoIP> getCarInfoIP();//取出行车的五个摄像头IP  返回值为
	//
	static std::vector<std::pair<std::string, int>> getStaNumAndTrackNum();//根据行车号取出轨道号
	static std::vector<TrackStationNum> getTrackStationNum(char* tagID);//根据标签号取出对应的三个工位的信息
};

#endif
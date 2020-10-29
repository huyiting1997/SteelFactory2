#pragma once

#include<vector>
#include<string>
#include <utility>
#include"Function.h"
#include"global.h"

class LogicControl
{
public:
	LogicControl();
	void getCameraIP();
	//逻辑控制
	BOOL judegSitution(std::vector<std::string>&CameraIP,double disL, double disR, double carDis, int tagID);
	int JudgeTrack(double modbusCarDis);
	std::string  nearestStationnum(int tagID, double modbusCarDis);
	RfidCam judegStation(double modbusCarDis, int tagID);//判断当前位于拿一个工位
	BOOL JudgeMargin(double disL, double disR);//左右防撞逻辑
	void InitParam();
	
	//逻辑判断中使用的常量定义
	double C_workRange;					//小车到工位
	double C_ReadingDis;				//基站到墙面的距离
	double C_LaunchDistance;			//激光到墙面距离
	double C_TrolleyDistance;			//小车表面到中心距离
	double C_trackFirL;					//第一条轨道左边到墙面的距离
	double C_trackFirR;					//第一条轨道右边到墙面的距离
	double C_trackSecL;					// 第二条轨道左边到墙面的距离
	double C_trackSecR;					// 第二条轨道右边到墙面的距离
	double C_trackThirdL;				// 第三条轨道左边到墙面的距离
	double C_trackThirdR;				// 第三条轨道右边到墙面的距离


	//成员变量
	std::vector<StationInfoIP> m_StationIPArray;//工位的全部摄像头IP
	std::vector< CarInfoIP> m_CarIPArray;//行车的五个摄像头IP
	std::vector < std::pair<int, double> > m_tagPosition; //标签号和标签位置
	//char* m_carNum;            //行车号
	std::string m_carNum;
	std::string m_globalIP;   //行车的全景摄像头IP
	//数据库操作对象
	Function m_data_operate;

};


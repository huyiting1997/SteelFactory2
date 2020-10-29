#pragma once
#include<string>
typedef int BOOL;  //定义BOOL类型作为返回值
#define ALLSAFE  0  //左右距离都安全
#define LEFTWRIGSAFE 1 //左边距离预警，右边距离安全
#define LEFTARIGSAFE 2  //左边距离报警，右边距离安全
#define RIGWLEFTSAFE 3 //右边距离预警，左边距离安全
#define RIGALEFTSAFE 4 //右边距离报警，左边距离安全
#define RIGALEFTW    5 //右边距离报警，左边距离预警
#define RIGWLEFTA    6 //右边距离预警，左边距离报警
#define RIGWLEFTW    7//左右边距离同时预警
#define RIGALEFTA    8//左右边距离同时报警


struct RfidCam {
	std::string stationID; //基站ID还是工位ID？？？
	bool display;
};
struct CarCameraIP {
	std::string leftIP;
	std::string rightIP;
	std::string leftDownIP;
	std::string rightDownIP;
};

struct StationCameraIP {
	std::string leftIP;
	std::string rightIP;
};

struct TagInfo {
	int TagNum;
	double Coordinate;
};
struct StationInfoIP {
	std::string stationNum;
	std::string leftIP;
	std::string rightIP;
};
struct CarInfoIP {
	std::string carNum;
	std::string leftIP;
	std::string rightIP;
	std::string leftDownIP;
	std::string rightDownIP;
	std::string panoramicIP;
};
struct TrackStationNum {
	std::string stationNum;
	int trackNum;
};
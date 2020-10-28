#pragma once
#include<string>
typedef int BOOL;  //����BOOL������Ϊ����ֵ
#define ALLSAFE  0  //���Ҿ��붼��ȫ
#define LEFTWRIGSAFE 1 //��߾���Ԥ�����ұ߾��밲ȫ
#define LEFTARIGSAFE 2  //��߾��뱨�����ұ߾��밲ȫ
#define RIGWLEFTSAFE 3 //�ұ߾���Ԥ������߾��밲ȫ
#define RIGALEFTSAFE 4 //�ұ߾��뱨������߾��밲ȫ
#define RIGALEFTW    5 //�ұ߾��뱨������߾���Ԥ��
#define RIGWLEFTA    6 //�ұ߾���Ԥ������߾��뱨��
#define RIGWLEFTW    7//���ұ߾���ͬʱԤ��
#define RIGALEFTA    8//���ұ߾���ͬʱ����


struct RfidCam {
	std::string stationID;
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
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <winsock.h> //ע��˳��Ҫ����mysql.hǰ
#include <mysql.h>//����̨��Ŀ��Ҫ��mysql.h֮ǰinclude <winsock.h>
#include<iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <utility>
#include"global.h"

class Function
{
public:

	static MYSQL* Connect(MYSQL* pConn);//�������ݿ�
	static void close(MYSQL* pConn);//�ر����ݿ�

	static double getConstantWorkRange();//ȡ��������С������λ�ľ���C_workRange
	static double getConstantReadingDis();//��վ��ǽ�����
	static double getConstantLaunchDistance();//���⵽ǽ�����
	static double getConstantTrolleyDistance();//С�����浽���ľ���
	static double getConstantTrackFirL();//��һ�������ߵ�ǽ��ľ���
	static double getConstantTrackFirR();//��һ������ұߵ�ǽ��ľ���
	static double getConstantTrackSecL();//�ڶ��������ߵ�ǽ��ľ���
	static double getConstantTrackSecR();//�ڶ�������ұߵ�ǽ��ľ���
	static double getConstantTrackThirdL();//�����������ߵ�ǽ��ľ���
	static double getConstantTrackThirdR();//����������ұߵ�ǽ��ľ���




	static CarCameraIP getCarCameraIP(char* CarNum);//�����г���,ȡ���ĸ�����ͷ��IP
	bool getCarCameraIP(std::string& CarNum, CarCameraIP& carCameraIP);

	static std::string getCarIPGlobal(char* CarNum);//ͨ���г��ţ���ȡȫ������ͷIP
	bool getCarIPGlobal(std::string& CarNum, std::string& carIPGlobal);

	static std::string getCarChannelNum(char* CarNum);//�����г���ȡ�����ͨ����
	bool getCarChannelNum(std::string& CarNum, std::string& carChannelNum);

	static double getCarRopeMargin(char* CarNum);//�����г���ȡ�������߾�
	bool getCarRopeMargin(std::string& CarNum, double& carRopeMargin);



	static int getStationTrackNum(char* staNum);//���ݹ�λ��ȡ����λ��Ӧ�Ĺ����
	bool getStationTrackNum(std::string& stationNum, int& stationTrackNum);

	static std::string getStationEnlarge(char* StaNum);//���ݹ�λ��ȡ���Ŵ���
	bool getStationEnlarge(std::string& stationNum, std::string& stationEnlarge);

	static double getStationHeight(char* StaNum); //���ݹ�λ��ȡ���߶�
	bool getStationHeight(std::string& stationNum, double& stationHeight);

	static double getStationBluetoothDis(char* StaNum);//���ݹ�λ��ȡ�����������÷�Χ
	bool getStationBluetoothDis(std::string& stationNum, double& stationBluetoothDis);

	static StationCameraIP getStationCameraIP(char* StaNum);//���ݹ�λ��ȡ����������ͷIP
	bool getStationCameraIP(std::string& stationNum, StationCameraIP& stationCameraIP);

	static std::vector<std::pair<int, double> > getStationTagInfo();//ȡ����ǩ�ź�������Ϣ
	bool getStationTagInfo(std::vector<std::pair<int, double> >& stationTagInfo);

	static std::vector<StationInfoIP> getStationInfoIP();//ȡ��ÿһ����λ�ϵ���������ͷIP ��λ�ڶ��Ź�λ������ͷ��ȡ��
	bool getStationInfoIP(std::vector<StationInfoIP>& stationInfoIP);

	static std::vector<CarInfoIP> getCarInfoIP();//ȡ���г����������ͷIP  ����ֵΪ
	bool getCarInfoIP(std::vector<CarInfoIP>& carInfoIP);

	static std::vector<std::pair<std::string, int>> getStaNumAndTrackNum();//ȡ����λ�źͶ�Ӧ�Ĺ����
	bool getStaNumAndTrackNum(std::vector<std::pair<std::string, int> >& stationNumAndTrackNum);

	static std::vector<TrackStationNum> getTrackStationNum(char* tagID);//���ݱ�ǩ��ȡ����Ӧ��������λ����Ϣ
	bool getTrackStationNum(std::string& tagID, std::vector<TrackStationNum>& trackStationNum);
	
};

#endif
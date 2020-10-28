#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <winsock.h> //ע��˳��Ҫ����mysql.hǰ
#include <mysql.h>//����̨��Ŀ��Ҫ��mysql.h֮ǰinclude <winsock.h>
#include<iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include"global.h"
#include <utility>

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
	static std::string getCarIPGlobal(char* CarNum);//ͨ���г��ţ���ȡȫ������ͷIP
	static std::string getCarChannelNum(char* CarNum);//�����г���ȡ�����ͨ����
	static double getCarRopeMargin(char* CarNum);//�����г���ȡ�������߾�

	static int getStationTrackNum(char* StaNum);//���ݹ�λ��ȡ����λ��Ӧ�Ĺ����
	static std::string getStationEnlarge(char* StaNum);//���ݹ�λ��ȡ���Ŵ���
	static double getStationHeight(char* StaNum); //���ݹ�λ��ȡ���߶�
	static double getStationBluetoothDis(char* StaNum);//���ݹ�λ��ȡ�����������÷�Χ
	static StationCameraIP getStationCameraIP(char* StaNum);//���ݹ�λ��ȡ����������ͷIP
	//��̬ȡ��
	static std::vector<std::pair<int, double>> getStationTagInfo();//ȡ����ǩ�ź�������Ϣ
	static std::vector<StationInfoIP> getStationInfoIP();//ȡ��ÿһ����λ�ϵ���������ͷIP ��λ�ڶ��Ź�λ������ͷ��ȡ��
	static std::vector<CarInfoIP> getCarInfoIP();//ȡ���г����������ͷIP  ����ֵΪ
	//
	static std::vector<std::pair<std::string, int>> getStaNumAndTrackNum();//�����г���ȡ�������
	static std::vector<TrackStationNum> getTrackStationNum(char* tagID);//���ݱ�ǩ��ȡ����Ӧ��������λ����Ϣ
};

#endif
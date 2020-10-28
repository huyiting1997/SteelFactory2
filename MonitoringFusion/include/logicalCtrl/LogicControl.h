#pragma once
#include<vector>
#include<string>
#include"global.h"
#include"Function.h"
#include <utility>
class LogicControl
{
public:
	LogicControl();
	void getCameraIP();
	//�߼�����
	BOOL judegSitution(std::vector<std::string>&CameraIP,double disL, double disR, double carDis, int tagID);
	int JudgeTrack(double modbusCarDis);
	std::string  nearestStationnum(int tagID, double modbusCarDis);
	RfidCam judegStation(double modbusCarDis, int tagID);//�жϵ�ǰλ����һ����λ
	BOOL JudgeMargin(double disL, double disR);//���ҷ�ײ�߼�

	
	//�߼��ж���ʹ�õĳ�������
	double C_workRange;					//С������λ
	double C_ReadingDis;				//��վ��ǽ��ľ���
	double C_LaunchDistance;			//���⵽ǽ�����
	double C_TrolleyDistance;			//С�����浽���ľ���
	double C_trackFirL;					//��һ�������ߵ�ǽ��ľ���
	double C_trackFirR;					//��һ������ұߵ�ǽ��ľ���
	double C_trackSecL;					// �ڶ��������ߵ�ǽ��ľ���
	double C_trackSecR;					// �ڶ�������ұߵ�ǽ��ľ���
	double C_trackThirdL;				// �����������ߵ�ǽ��ľ���
	double C_trackThirdR;				// ����������ұߵ�ǽ��ľ���


	//��Ա����
	std::vector<StationInfoIP>StationIPArray;//��λ��ȫ������ͷIP
	std::vector< CarInfoIP>CarIPArray;//�г����������ͷIP
	std::vector<std::pair<int, double> >tagPosition;//��ǩ�źͱ�ǩλ��
	char* carNum;            //�г���
	std::string globalIP;   //�г���ȫ������ͷIP
	//���ݿ��������
	Function data_operate;

};


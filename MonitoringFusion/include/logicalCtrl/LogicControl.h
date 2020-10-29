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
	//�߼�����
	BOOL judegSitution(std::vector<std::string>&CameraIP,double disL, double disR, double carDis, int tagID);
	int JudgeTrack(double modbusCarDis);
	std::string  nearestStationnum(int tagID, double modbusCarDis);
	RfidCam judegStation(double modbusCarDis, int tagID);//�жϵ�ǰλ����һ����λ
	BOOL JudgeMargin(double disL, double disR);//���ҷ�ײ�߼�
	void InitParam();
	
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
	std::vector<StationInfoIP> m_StationIPArray;//��λ��ȫ������ͷIP
	std::vector< CarInfoIP> m_CarIPArray;//�г����������ͷIP
	std::vector < std::pair<int, double> > m_tagPosition; //��ǩ�źͱ�ǩλ��
	//char* m_carNum;            //�г���
	std::string m_carNum;
	std::string m_globalIP;   //�г���ȫ������ͷIP
	//���ݿ��������
	Function m_data_operate;

};


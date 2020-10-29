#include<string>
#include "../../pch.h"
#include "../../include/logicalCtrl/LogicControl.h"

LogicControl::LogicControl():
	m_carNum("111")
{
	//�����ݿ����ó�����
	//C_workRange = m_data_operate.getConstantWorkRange();
	//C_ReadingDis =m_data_operate.getConstantReadingDis();
	//C_LaunchDistance = m_data_operate.getConstantLaunchDistance();
	//C_TrolleyDistance = m_data_operate.getConstantTrolleyDistance();
	//C_trackFirL = m_data_operate.getConstantTrackFirL();
	//C_trackFirR = m_data_operate.getConstantTrackFirR();
	//C_trackSecL = m_data_operate.getConstantTrackSecL();
	//C_trackSecR = m_data_operate.getConstantTrackSecR();
	//C_trackThirdL = m_data_operate.getConstantTrackThirdL();
	//C_trackThirdR = m_data_operate.getConstantTrackThirdR();
	////m_globalIP = m_data_operate.getCarIPGlobal(m_carNum);
	//m_data_operate.getCarIPGlobal(m_carNum, m_globalIP);
	
}
void LogicControl::getCameraIP()
{
	m_StationIPArray= m_data_operate.getStationInfoIP();
	m_CarIPArray = m_data_operate.getCarInfoIP();
	m_tagPosition = m_data_operate.getStationTagInfo();
}

//2020-10-28 ��λ��޸�   �������ݿ⣬��ʼ������
void LogicControl::InitParam() {
	C_workRange = m_data_operate.getConstantWorkRange();
	C_ReadingDis = m_data_operate.getConstantReadingDis();
	C_LaunchDistance = m_data_operate.getConstantLaunchDistance();
	C_TrolleyDistance = m_data_operate.getConstantTrolleyDistance();
	C_trackFirL = m_data_operate.getConstantTrackFirL();
	C_trackFirR = m_data_operate.getConstantTrackFirR();
	C_trackSecL = m_data_operate.getConstantTrackSecL();
	C_trackSecR = m_data_operate.getConstantTrackSecR();
	C_trackThirdL = m_data_operate.getConstantTrackThirdL();
	C_trackThirdR = m_data_operate.getConstantTrackThirdR();
	//m_globalIP = m_data_operate.getCarIPGlobal(m_carNum);
	m_data_operate.getCarIPGlobal(m_carNum, m_globalIP);

	m_StationIPArray = m_data_operate.getStationInfoIP();
	m_CarIPArray = m_data_operate.getCarInfoIP();
	m_tagPosition = m_data_operate.getStationTagInfo();
}


BOOL LogicControl::judegSitution(std::vector<std::string>& CameraIP,  double disL, double disR, double carDis, int tagID)
{
	RfidCam caminfo;
	caminfo = judegStation(carDis,tagID);
	CarCameraIP carIP;
	StationCameraIP stationIP;
	if (caminfo.display) {//���빤λ
		if (m_data_operate.getStationCameraIP(caminfo.stationID, stationIP) == false)
		{
			return false;
		}
		//��ȡ��λIP
		//carIP= m_data_operate.getCarCameraIP(m_carNum);
		if (m_data_operate.getCarCameraIP(m_carNum, carIP) == false)
		{
			return false;
		}
		//��ȡ�г�IP�������ĸ�ֵ��
		switch (JudgeMargin(disL,disR))
		{
		case 0:
			//��CameraIP�м��빤λ�ϵ������Լ���ǰ�г������ҷ�ײ
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			return 0;
		case 1:
			//��CameraIP����߷�ײ����λIP���ұ߷�ײ
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			return 1;
		case 2:
			//��CameraIP����߷�ײ����λIP���ұ߷�ײ
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			return 2;
		case 3:
			//��λ�ұ���߹�λ
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			return 3;
		case 4:
			//��λ�ұ���߹�λ
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			return 4;
		case 5:
			//����ұ߹�λ��λ��
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			return 5;
		case 6:
			//����ұ߹�λ��λ��
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			return 6;
		case 7:
			//����ұ߹�λ��λ��
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(stationIP.leftIP);
			CameraIP.push_back(stationIP.rightIP);
			return 7;
		case 8:
			//����ұ߹�λ��λ��
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
	else {//δ���빤λ
		switch (JudgeMargin(disL, disR))
		{
			//��ȡ�г��ϵ��ĸ�IP
			//carIP = m_data_operate.getCarCameraIP(m_carNum);
			m_data_operate.getCarCameraIP(m_carNum, carIP);
		case 0:
			//һ�������г��ϵ��ĸ�����ͷIP
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightDownIP);
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			return 0;
		case 1:
			//��CameraIP����߷�ײ������IP������IP���ұ߷�ײ
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightDownIP);
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightIP);
			return 1;
		case 2:
			//��߷�ײ������IP������IP���ұ߷�ײ
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightDownIP);
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightIP);
			return 2;
		case 3:
			//�����ұ߷�ײ��߷�ײ����
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightDownIP);
			return 3;
		case 4:
			//�����ұ߷�ײ��߷�ײ����
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightDownIP);
			return 4;
		case 5:
			//��߷�ײ�ұ߷�ײ�����������
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightDownIP);
			return 5;
		case 6:
			//��߷�ײ�ұ߷�ײ�����������
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightDownIP);
			return 6;
		case 7:
			//��߷�ײ�ұ߷�ײ�����������
			CameraIP.push_back(carIP.leftIP);
			CameraIP.push_back(carIP.rightIP);
			CameraIP.push_back(carIP.leftDownIP);
			CameraIP.push_back(carIP.rightDownIP);
			return 7;
		case 8:
			//��߷�ײ�ұ߷�ײ�����������
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
		return 1;  //����1��������1
	}
	else if (C_trackSecL < m_modbusCarDis && m_modbusCarDis < C_trackSecR) {
		return 2; //����2��������2
	}
	else if (C_trackThirdL < m_modbusCarDis && m_modbusCarDis < C_trackThirdL) {
		return 3; //����3��������3
	}
	else {
		return 0; //����0������û�н��������հ���
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
	trackStationNum= m_data_operate.getTrackStationNum(a);
	int track=JudgeTrack(modbusCarDis);
	std::string stationNum;
	if (track) {//�����˹��
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
		L = 1;//�󱨾�
	}
	else if (disL > 5) {
		L = -1;//��ȫ
	}
	else {
		L = 0;//��Ԥ��
	}

	if (disR < 3) {
		R = 1;//�ұ���
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
			return  ALLSAFE;       //��ȫ���Ұ�ȫ
			break;
		case 0:
			return  RIGWLEFTSAFE;  //��ȫ����Ԥ��
			break;
		case 1:
			return  RIGALEFTSAFE;  //��ȫ���ұ���
			break;
		}
		break;
	}
	case 0: {
		switch (R)
		{
		case -1:
			return  LEFTWRIGSAFE;  //��Ԥ�����Ұ�ȫ   
			break;
		case 0:
			return  RIGWLEFTW;   //��Ԥ������Ԥ��
			break;
		case 1:
			return  RIGALEFTW;   //��Ԥ�� ,�ұ�����
			break;
		}
		break;
	}
	case 1: {
		switch (R)
		{
		case -1:
			return  LEFTARIGSAFE;  //�󱨾����Ұ�ȫ 
			break;
		case 0:
			return  RIGWLEFTA;   //�󱨾�,��Ԥ��
			break;
		case 1:
			return  RIGALEFTA;   //�󱨾�,�ұ���
			break;
		}
		break;
	}
	}
}


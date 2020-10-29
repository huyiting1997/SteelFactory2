#pragma once

#include "Windows.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <conio.h>
#include "./HCNetSDK.h"
using namespace std;

#define PI 3.1415926

//ʮ����ת����ʮ������
inline int DEC2HEX_doc(int x) {
	return (x / 1000) * 4096 + ((x % 1000) / 100) * 256 + ((x % 100) / 10) * 16 + x % 10;
}

class CameraControl
{
public:
	CameraControl();

	~CameraControl();

	void InitPTZParam(LONG& leftCameraLoginID, LONG& rightCameraLoginID);  //���������ʼ��

	bool StartCameraControlling(LONG& leftCameraLoginID, LONG& rightCameraLoginID);

	bool ResumeCameraControlling();

	bool SuspendCameraControlling();

	void StopCameraControlling();

	//	��1�������С������   ��2��С�����浽����   ��3������   ��4���Ŵ���   ��5���ؾ�
	 bool PTZSet(double V_TrolleyDistance, double C_TrolleyDistance, double DB_Height, double DB_Enlarge, double DB_RopIntercept);

protected:
	static DWORD WINAPI CameraControlThread(LPVOID pParam);		///�̺߳���

private:
	LONG		m_leftCameraLoginID;
	LONG		m_rightCameraLoginID;

	HANDLE		m_hControlThread;

	HANDLE		m_hShutdownEvent;

	bool		m_bThreadAlive;

	HWND		m_pOwner;

	NET_DVR_PTZPOS ptzPosL;
	NET_DVR_PTZPOS ptzPosR;

	bool         m_PTZSetFinish;
};

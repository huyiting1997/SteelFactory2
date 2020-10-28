#pragma once

#include "Windows.h"
#include "./HCNetSDK.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <conio.h>
using namespace std;

#define PI 3.1415926

//十进制转换成十六进制
inline int DEC2HEX_doc(int x) {
	return (x / 1000) * 4096 + ((x % 1000) / 100) * 256 + ((x % 100) / 10) * 16 + x % 10;
}

class CameraControl
{
public:
	CameraControl();

	~CameraControl();

	void InitPTZParam(LONG& leftCameraLoginID, LONG& rightCameraLoginID);  //球机参数初始化

	bool StartCameraControlling(LONG& leftCameraLoginID, LONG& rightCameraLoginID);

	bool ResumeCameraControlling();

	bool SuspendCameraControlling();

	void StopCameraControlling();

	//	参1：激光测小车表面   参2：小车表面到中心   参3：吊绳   参4：放大倍数   参5：截距
	 bool PTZSet(double V_TrolleyDistance, double C_TrolleyDistance, double DB_Height, double DB_Enlarge, double DB_RopIntercept);

protected:
	static DWORD WINAPI CameraControlThread(LPVOID pParam);		///线程函数

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

//#include "../pch.h"
#include "../../include/cameraCtrl/CameraControl.h"

void CameraControl::InitPTZParam(LONG& leftCameraLoginID, LONG& rightCameraLoginID)
{
	
	NET_DVR_INITIALPOSITIONCTRL InitPositionCtrl;
	InitPositionCtrl.byWorkMode = 1;
	InitPositionCtrl.dwChan = 0;   //通道号

	NET_DVR_RemoteControl(leftCameraLoginID, NET_DVR_PTZ_INITIALPOSITIONCTRL, &InitPositionCtrl, sizeof(NET_DVR_INITIALPOSITIONCTRL));
	NET_DVR_RemoteControl(rightCameraLoginID, NET_DVR_PTZ_INITIALPOSITIONCTRL, &InitPositionCtrl, sizeof(NET_DVR_INITIALPOSITIONCTRL));
}

//ptz参数
bool CameraControl::PTZSet(double V_TrolleyDistance, double C_TrolleyDistance, double DB_Height, double DB_Enlarge, double DB_RopIntercept)
{
	double PanDistance = V_TrolleyDistance + C_TrolleyDistance;   //吊绳到球机的水平距离

	double TiltAngle = atan(DB_Height / PanDistance) * 180 / PI;		//竖直实际偏角
	double PanAngle = atan(DB_RopIntercept / sqrt(PanDistance * PanDistance + DB_Height * DB_Height)) * 180 / PI;    //水平实际偏角

	double Tilt1Angle1 = TiltAngle;     //另一个摄像头实际偏角
	double PanAngle1 = 360 - PanAngle;

	ptzPosR.wAction = 1;  //允许设置PTZ三参
	ptzPosR.wPanPos = DEC2HEX_doc(int(PanAngle * 10));  //实际角度乘以10转换成十六进制传参
	ptzPosR.wTiltPos = DEC2HEX_doc(int(TiltAngle * 10));
	ptzPosR.wZoomPos = DEC2HEX_doc(int(DB_Enlarge * 10));

	ptzPosL.wAction = 1;  //允许设置PTZ三参
	ptzPosL.wPanPos = DEC2HEX_doc(int(PanAngle1 * 10));  //实际角度乘以10转换成十六进制传参
	ptzPosL.wTiltPos = DEC2HEX_doc(int(Tilt1Angle1 * 10));
	ptzPosL.wZoomPos = DEC2HEX_doc(int(DB_Enlarge * 10));

	return true;
}

CameraControl::CameraControl() :
	m_leftCameraLoginID(-1),
	m_rightCameraLoginID(-1),
	m_hControlThread(NULL),
	m_hShutdownEvent(NULL),
	m_bThreadAlive(false)
{
}

CameraControl::~CameraControl()
{
	if (m_hShutdownEvent != NULL) {
		::CloseHandle(m_hShutdownEvent);
	}

	if (m_hControlThread != NULL) {
		::CloseHandle(m_hControlThread);
	}
}

DWORD WINAPI CameraControl::CameraControlThread(LPVOID pParam)
{
	//判断是否完成移动
	NET_DVR_PTZPOS Pos_judgeL;
	NET_DVR_PTZPOS Pos_judgeR;
	Pos_judgeL.wAction = 1;
	Pos_judgeR.wAction = 1;
	DWORD tmpL = 0;     //实际接收到的数据长度指针
	DWORD tmpR = 0;

	CameraControl* controller = (CameraControl*)pParam;
	controller->m_bThreadAlive = true;

	controller->InitPTZParam(controller->m_leftCameraLoginID, controller->m_rightCameraLoginID);
	
	controller->m_PTZSetFinish = true;

	while (::WaitForSingleObject(controller->m_hShutdownEvent, 0) != WAIT_OBJECT_0) {

		BOOL SetPTZStaL = NET_DVR_SetDVRConfig(controller->m_leftCameraLoginID, NET_DVR_SET_PTZPOS, 0, &controller->ptzPosL, sizeof(NET_DVR_PTZPOS));
		BOOL SetPTZStaR = NET_DVR_SetDVRConfig(controller->m_rightCameraLoginID, NET_DVR_SET_PTZPOS, 0, &controller->ptzPosR, sizeof(NET_DVR_PTZPOS));

		if (!(SetPTZStaL && SetPTZStaR)) {
			printf("PTZSet error, %d\n", NET_DVR_GetLastError());
		}
		controller->m_PTZSetFinish = false;

		while (!controller->m_PTZSetFinish)
		{
			if (!(NET_DVR_GetDVRConfig(controller->m_leftCameraLoginID, NET_DVR_GET_PTZPOS, 0, &Pos_judgeL, sizeof(NET_DVR_PTZPOS), &tmpL) && NET_DVR_GetDVRConfig(controller->m_rightCameraLoginID, NET_DVR_GET_PTZPOS, 0, &Pos_judgeR, sizeof(NET_DVR_PTZPOS), &tmpR)))
			{
				printf("PTZGet error, %d\n", NET_DVR_GetLastError());
			}
			else if (Pos_judgeL.wPanPos == controller->ptzPosL.wPanPos && Pos_judgeL.wTiltPos == controller->ptzPosL.wTiltPos && Pos_judgeL.wZoomPos == controller->ptzPosL.wZoomPos && Pos_judgeR.wPanPos == controller->ptzPosR.wPanPos && Pos_judgeR.wTiltPos == controller->ptzPosR.wTiltPos && Pos_judgeR.wZoomPos == controller->ptzPosR.wZoomPos)
			{
				controller->m_PTZSetFinish = true;
			}
		}

	}
	controller->m_bThreadAlive = false;
	return 0;
}

bool CameraControl::StartCameraControlling(LONG& leftCameraLoginID, LONG& rightCameraLoginID)
{
	m_leftCameraLoginID = leftCameraLoginID;
	m_rightCameraLoginID = rightCameraLoginID;

	m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (!(m_hControlThread = ::CreateThread(NULL, 0, CameraControlThread, this, 0, NULL)))
		return false;

	return true;
}

bool CameraControl::ResumeCameraControlling()
{
	//TRACE("Thread resumed\n");
	//m_Thread->ResumeThread();
	::ResumeThread(m_hControlThread);
	return true;
}

//
// Suspend the comm thread
///挂起监视线程
//
bool CameraControl::SuspendCameraControlling()
{
	//TRACE("Thread suspended\n");
	//m_Thread->SuspendThread();
	::SuspendThread(m_hControlThread);
	return true;
}

void CameraControl::StopCameraControlling()
{
	do {
		::SetEvent(m_hShutdownEvent);
	} while (m_bThreadAlive);

	if (m_hShutdownEvent != NULL) {
		::ResetEvent(m_hShutdownEvent);
	}
}



#pragma once
#include <afxwin.h>
#include <vector>
#include <string>
#include <map>
#include "../../include/cameraCtrl/HCNetSDK.h"
#include "GeneralDef.h"

typedef std::pair<std::string, LONG> PAIR_IP2CAMERA;

class CPreviewStatic :
	public CStatic
{
private:
	LONG m_lControlID;//绑定的控件ID

	LONG m_lRealPlayHandle;

	CWnd* m_pParentWnd;//父句柄

	bool m_bIsPlaying;//是否在播放

	LONG m_lPlayHandle;

	//std::vector<PAIR_IP2CAMERA> m_cameras;

	LOCAL_DEVICE_INFO m_curDeviceInfo;

public:
	CPreviewStatic(CWnd* pParentWnd);
	//添加一个函数SetParentWnd(CWnd* pParentWnd)
	CPreviewStatic();
	void SetParentWnd(CWnd* pParentWnd);
	void SetControlID(LONG controlID);

	//bool DoLogin(std::string& devIP, int& devPort, std::string& user, std::string& password);

	void StartPlay(std::string& devIP, std::vector<PAIR_IP2CAMERA>& cameras, int iChanIndex);

	void StopPlay();
};


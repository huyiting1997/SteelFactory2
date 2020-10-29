#pragma once
#include <afxwin.h>
#include <vector>
#include <string>
#include <map>
#include "GeneralDef.h"
#include "../../include/cameraCtrl/HCNetSDK.h"

typedef std::pair<std::string, LONG> PAIR_IP2CAMERA;

class CPreviewStatic :
	public CStatic
{
private:
	LONG m_lControlID;//�󶨵Ŀؼ�ID

	LONG m_lRealPlayHandle;

	CWnd* m_pParentWnd;//�����

	bool m_bIsPlaying;//�Ƿ��ڲ���

	LONG m_lPlayHandle;

	//std::vector<PAIR_IP2CAMERA> m_cameras;

	LOCAL_DEVICE_INFO m_curDeviceInfo;

public:
	CPreviewStatic(CWnd* pParentWnd);

	void SetControlID(LONG controlID);

	//bool DoLogin(std::string& devIP, int& devPort, std::string& user, std::string& password);

	void StartPlay(std::string& devIP, std::vector<PAIR_IP2CAMERA>& cameras, int iChanIndex);

	bool  StopPlay();
};


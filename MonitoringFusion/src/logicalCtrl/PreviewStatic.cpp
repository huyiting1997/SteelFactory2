#include<algorithm>
#include "../../pch.h"
#include "../../include/logicalCtrl/PreviewStatic.h"

CPreviewStatic::CPreviewStatic(CWnd* pParentWnd) :
	m_lControlID(-1),
	m_lRealPlayHandle(-1),
	m_pParentWnd(pParentWnd),
	m_bIsPlaying(false),
	m_lPlayHandle(-1)
{
}

void CPreviewStatic::SetControlID(LONG controlID)
{
	m_lControlID = controlID;
}

//bool CPreviewStatic::DoLogin(std::string& devIP, int& devPort, std::string& user, std::string& password)
//{
//	NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;
//	memset(&DeviceInfoTmp, 0, sizeof(NET_DVR_DEVICEINFO_V30));
//
//	LONG lLoginID = NET_DVR_Login_V30((char*)devIP.c_str(), devPort, (char*)user.c_str(), (char*)password.c_str(), &DeviceInfoTmp);
//	if (lLoginID == -1) {
//		DWORD err = NET_DVR_GetLastError();
//		MessageBox(_T("Login to Device failed!\n"));
//		return FALSE;
//	}
//
//	m_cameras.push_back(std::make_pair(devIP, lLoginID));
//}

void CPreviewStatic::StartPlay(std::string& devIP, std::vector<PAIR_IP2CAMERA>& cameras, int iChanIndex)
{
	LONG lLoginID = -1;

	NET_DVR_CLIENTINFO ClientInfo;
	ClientInfo.hPlayWnd = m_pParentWnd->GetDlgItem(m_lControlID)->m_hWnd;
	ClientInfo.lChannel = iChanIndex;
	ClientInfo.lLinkMode = 0;
	ClientInfo.sMultiCastIP = NULL;
	TRACE("Channel number:%d\n", ClientInfo.lChannel);
	//获取到登录ID
	for (int i = 0; i < cameras.size(); i++) {
		if (cameras[i].first == devIP) {
			lLoginID = cameras[i].second;
			break;
		}
	}

	if (lLoginID == -1) {
		return;
	}

	m_lPlayHandle = NET_DVR_RealPlay_V30(lLoginID, &ClientInfo, NULL, NULL, TRUE);//播放，并保存播放ID
	if (-1 == m_lPlayHandle) {
		DWORD err = NET_DVR_GetLastError();
		CString m_csErr;
		m_csErr.Format(_T("播放出错，错误代码%d"), (int)err);
		MessageBox(m_csErr);
	}

	m_bIsPlaying = TRUE;
}

bool  CPreviewStatic::StopPlay()
{
	if (m_lPlayHandle != -1) {
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
		m_bIsPlaying = FALSE;
		return true;
	}
	return false;
}


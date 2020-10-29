#pragma once
#include <afxwin.h>
#include <stdint.h>
#include <map>
#include "SerialPort.h"

#define WM_WIRELESS_RX_FRAME            WM_USER + 130
#define WM_WIRELESS_TX_FRAME            WM_USER + 131

#define MAX_TAG_NUMBER                  64
#define MAX_CELL_NUMBER                 1024
#define CELL_LENGTH                     0.5

struct TagRecord
{
    short   tagID;
    double  distance;

    int     cellLocation[2];  
    double  position[2];
};


class WirelessRangingHandler : public CWnd
{
    DECLARE_DYNAMIC(WirelessRangingHandler)

public:
    WirelessRangingHandler(CWnd* pParentWnd);
    virtual ~WirelessRangingHandler();


protected:
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg LRESULT OnCommRxChar(WPARAM ch, LPARAM port);

public:
    int     openPort(UINT portnr = 1, UINT baud = 9600, UINT databits = 8, UINT stopsbits = ONESTOPBIT, TCHAR parity = _T('N'));
    void    closePort();

    void    SetTagPosition(std::vector<std::pair<int, double>>data_tagPosition);

    bool    GetRangingInfo(double& stationPosition, double& nearestTagPosition,int& tagID);

private:
    itas109::CSerialPort m_serialPort;

    //int     deviceAddress;

    //int     readBeginAddress;
    //int     readEndAddress;
    int     m_readPeriod;

    int     m_writeFunctionCode;

    uint8_t m_rxBuff[512];                  // ���ջ�����
    size_t  m_rxLength;                     // ���ջ������е��ַ���

    uint8_t m_frameData[512];               // ֡����
    int     m_frameLength;

    int     m_startPosition;

    TagRecord  m_tagRecord[MAX_TAG_NUMBER];

    int     m_tagCount;  //��ǩ������ ��ע��1020

    CRITICAL_SECTION    m_cs;

    int     m_votingCell[MAX_CELL_NUMBER];                    //Ʊ��

    std::map<int, double> m_mapTag2Position;

    double  m_stationPosition;

    int     m_nearestTagID;

    double  m_nearestTagPosition;

    bool    m_bTagDataUpdate;               // ��ǩ���ݸ��±�ʶ
};



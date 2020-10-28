#pragma once
#include <afxwin.h>


#include <stdint.h>
#include "SerialPort.h"
#include <map>

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
    WirelessRangingHandler();
    virtual ~WirelessRangingHandler();


protected:
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg LRESULT OnCommRxChar(WPARAM ch, LPARAM port);

public:
    int     openPort(UINT portnr = 1, UINT baud = 9600, UINT databits = 8, UINT stopsbits = ONESTOPBIT, TCHAR parity = _T('N'));
    void    closePort();

    void    SetTagPosition();

    bool    GetRangingInfo(double& stationPosition, double& nearestTagPosition);

private:
    itas109::CSerialPort m_serialPort;

    //int     deviceAddress;

    //int     readBeginAddress;
    //int     readEndAddress;
    int     m_readPeriod;

    int     m_writeFunctionCode;

    uint8_t m_rxBuff[512];                  // 接收缓冲区
    size_t  m_rxLength;                     // 接收缓冲区中的字符数

    uint8_t m_frameData[512];               // 帧数据
    int     m_frameLength;

    int     m_startPosition;

    TagRecord  m_tagRecord[MAX_TAG_NUMBER];

    int     m_tagCount;  //标签的数量 胡注释1020

    CRITICAL_SECTION    m_cs;

    int     m_votingCell[MAX_CELL_NUMBER];                    //票箱

    std::map<int, double> m_mapTag2Position;

    double  m_stationPosition;

    int     m_nearestTagID;

    double  m_nearestTagPosition;

    bool    m_bTagDataUpdate;               // 标签数据更新标识
};



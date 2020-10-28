#pragma once
#include <afxwin.h>
#include <stdint.h>
#include "SerialPort.h"


#define WM_MODBUS_RX_FRAME              WM_USER + 132
#define WM_MODBUS_TX_FRAME              WM_USER + 133

// ModbusRtuHandler

class ModbusRtuHandler : public CWnd
{
    DECLARE_DYNAMIC(ModbusRtuHandler)

public:
    ModbusRtuHandler(CWnd* pParentWnd);
    ModbusRtuHandler();
    //void SetParentWnd(CWnd* pParentWnd);
    virtual ~ModbusRtuHandler();


protected:
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg LRESULT OnCommRxChar(WPARAM ch, LPARAM port);

public:
    void    setDeviceAddress(int deviceAddress);
    int     getDeviceAddress() const;
    void    setReadBeginAddress(int readStartAddress);
    int     getReadBeginAddress() const;
    void    setReadEndAddress(int readEndAddress);
    int     getReadEndAddress() const;
    void    setReadPeriod(int readPeriod);
    int     getReadPeriod() const;

    int     openPort(UINT portnr = 1, UINT baud = 9600, UINT databits = 8, UINT stopsbits = ONESTOPBIT, TCHAR parity = _T('N'));
    void    closePort();

    int     receive(uint8_t* buff, size_t buffLength);
    int     send(int functionCode, int registerAddress, int registerValue);

    ///2020_10_13，刘钢修改，读取激光测得距离
    bool    getLaserDistance(double& leftDistance, double& rightDistance, double& carDistance);

private:
    itas109::CSerialPort m_serialPort;

    CRITICAL_SECTION	m_csModbusSync;                 ///2020_10_13，刘钢修改，临界资源
    double              m_leftDistance;                 //2020_10_13，刘钢修改，左行车距离
    double              m_rightDistance;                //2020_10_13，刘钢修改，右行车距离
    double              m_carDistance;                  //2020_10_13，刘钢修改，小车距离

    int     m_deviceAddress;

    int     m_readBeginAddress;
    int     m_readEndAddress;
    int     m_readPeriod;

    int     m_writeFunctionCode;

    uint8_t m_rxBuff[512];                      // 接收缓冲区
    size_t  m_rxLength;                         // 接收缓冲区中的字符数

    uint8_t m_frameData[512];                     // 帧数据
    int     m_frameLength;

    int     m_startPosion;
    bool    m_bMeasureUpdate;
};



#include <fstream>
#include "../../pch.h"
#include "../../include/sensor/ModbusRtuHandler.h"
#include "../../include/sensor/crc16.h"



IMPLEMENT_DYNAMIC(ModbusRtuHandler, CWnd)
ModbusRtuHandler::ModbusRtuHandler(CWnd* pParentWnd)

{
	m_rxLength = 0;
	m_startPosion = -1;
	//Create(AfxRegisterWndClass(0), L"", WS_OVERLAPPED, CRect(0, 0, 2, 2), nullptr, 0, nullptr);

    //2020_10_13，刘钢修改，设置缺省设备地址、寄存器地址、读写周期
    m_deviceAddress = 1;
    m_readBeginAddress = 0;
    m_readEndAddress = 4;
    m_readPeriod = 100;
    m_bMeasureUpdate = false;

    //2020_10_13，刘钢修改，初始化临界资源
    InitializeCriticalSection(&m_csModbusSync);
}

ModbusRtuHandler::~ModbusRtuHandler()
{
    //KillTimer(0);

    //2020_10_13，刘钢修改，释放临界资源
    DeleteCriticalSection(&m_csModbusSync);
}
BEGIN_MESSAGE_MAP(ModbusRtuHandler, CWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_MESSAGE(WM_COMM_RXCHAR, ModbusRtuHandler::OnCommRxChar)
END_MESSAGE_MAP()

int ModbusRtuHandler::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码
    //MessageBox(L"ModbusRtuHandler::OnCreate");

    return 0;
}

void ModbusRtuHandler::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (m_serialPort.IsOpened()) {
        uint16_t registerCount = m_readEndAddress - m_readBeginAddress + 1;
        uint8_t  txBuff[16];
        txBuff[0] = m_deviceAddress;
        txBuff[1] = 0x03;
        txBuff[2] = (m_readBeginAddress & 0xFF00) >> 8;
        txBuff[3] = (m_readBeginAddress & 0x00FF);
        txBuff[4] = (uint8_t)(registerCount >> 8);
        txBuff[5] = (uint8_t)registerCount;
        uint16_t crc = getCRC16(txBuff, 6);
        txBuff[6] = (uint8_t)crc;
        txBuff[7] = (uint8_t)(crc >> 8);
        m_serialPort.WriteToPort(txBuff, 8);
        
        //2020_10_13，刘钢修改，不向主界面发送Modbus写数据消息
        //::SendMessage(GetParent()->GetSafeHwnd(), WM_MODBUS_TX_FRAME, (WPARAM)txBuff, 8);
    }

    CWnd::OnTimer(nIDEvent);
}

//  2020_10_15,刘钢修改
std::ofstream Modbus_LOG("../modbus_log.txt");

afx_msg LRESULT ModbusRtuHandler::OnCommRxChar(WPARAM ch, LPARAM port) {

    m_rxBuff[m_rxLength++] = (uint8_t)ch;

    if (m_rxLength < 5) return 1;

    // 寻找帧起始位置
    //int startPosion = -1;
    if (m_startPosion < 0) {
        for (int i = 0; i < m_rxLength; ++i) {
            if (m_rxBuff[i] == m_deviceAddress) {
                m_startPosion = i;
            }
        }
        if (m_startPosion < 0) {
            m_rxLength = 0;
            m_startPosion = -1;
            return 1;
        }
    }

    // 
    int length = 0;
    switch (m_rxBuff[m_startPosion + 1]) {
    case 0x03:
        length = m_rxBuff[m_startPosion + 2] + 5;
        break;

    case 0x83:
        length = 5;
        break;

    case 0x06:
        length = 8;
        break;

    case 0x86:
        length = 5;
        break;

    case 0x10:
        length = 8;
        break;

    case 0x90:
        length = 5;
        break;

    default:
        memcpy(m_rxBuff, m_rxBuff + 1, m_rxLength - 1);
        m_rxLength -= 1;
        m_startPosion = -1;
        break;
    }

    for (int i = 0; i < length; i++) {
        Modbus_LOG << "0x" << std::hex << (int)m_frameData[i] << "  ";
    }
    Modbus_LOG << std::endl << std::endl;

    if (length > (m_rxLength - m_startPosion)) {
        return 2;
    }

    uint16_t crc = getCRC16(m_rxBuff + m_startPosion, length - 2);
    uint16_t crc2 = (m_rxBuff[m_startPosion + length - 1] << 8) + m_rxBuff[m_startPosion + length - 2];

    if (crc != crc2) {
        memcpy(m_rxBuff, m_rxBuff + m_startPosion + 2, m_rxLength - m_startPosion - 2);
        //for (int i = startPosion + 2, j = 0; i < rxLength; ++i, ++j) {
        //    rxBuff[j] = rxBuff[i];
        //}
        m_rxLength -= (size_t)m_startPosion + 2;
        //loggerView->info(L"OnCommRxStr::3");
        return 3;
    }

    memcpy(m_frameData, m_rxBuff + m_startPosion, length);
    memcpy(m_rxBuff, m_rxBuff + m_startPosion + length, m_rxLength - m_startPosion - length);
    m_rxLength -= (size_t)m_startPosion + length;
    m_startPosion = -1;

    //2020_10_13，刘钢修改，不向主界面发送Modbus读数据消息
    //::SendMessage(GetParent()->GetSafeHwnd(), WM_MODBUS_RX_FRAME, (WPARAM)frameData, (LPARAM)length);

    //2020_10_13，刘钢修改，读取Modbus数据
    short data1 = (m_frameData[3] << 8) | m_frameData[4];
    short data2 = (m_frameData[7] << 8) | m_frameData[8];
    short data3 = (m_frameData[11] << 8) | m_frameData[12];

    //2020_10_13，刘钢修改，数据写入成员变量
    EnterCriticalSection(&m_csModbusSync);
    m_leftDistance = data1 / 100.0;                 
    m_rightDistance = data2 / 100.0;                
    m_carDistance = data3 / 100.0;
    m_bMeasureUpdate = true;//数据被更新
    LeaveCriticalSection(&m_csModbusSync);
    
    return 0;
}

void    ModbusRtuHandler::setDeviceAddress(int deviceAddress)
{
    if (this->m_deviceAddress != deviceAddress) {
        this->m_deviceAddress = deviceAddress;
    }
}

int     ModbusRtuHandler::getDeviceAddress() const
{
    return m_deviceAddress;
}

void    ModbusRtuHandler::setReadBeginAddress(int readBeginAddress)
{
    if (this->m_readBeginAddress != readBeginAddress) {
        this->m_readBeginAddress = readBeginAddress;
    }
}

int     ModbusRtuHandler::getReadBeginAddress() const
{
    return m_readBeginAddress;
}

void    ModbusRtuHandler::setReadEndAddress(int readEndAddress)
{
    if (this->m_readEndAddress != readEndAddress) {
        this->m_readEndAddress = readEndAddress;
    }
}

int     ModbusRtuHandler::getReadEndAddress() const
{
    return m_readEndAddress;
}

void    ModbusRtuHandler::setReadPeriod(int readPeriod)
{
    if (this->m_readPeriod == readPeriod) {
        return;
    }

    KillTimer(0);
    this->m_readPeriod = readPeriod;
    if (readPeriod <= 0) {
        return;
    }

    SetTimer(0, readPeriod, nullptr);
}

int ModbusRtuHandler::getReadPeriod() const
{
    return m_readPeriod;
}

int ModbusRtuHandler::openPort(UINT portnr /*= 1*/, UINT baud /*= 9600*/, UINT databits /*= 8*/, UINT stopsbits /*= ONESTOPBIT*/, TCHAR parity /*= _T('N')*/)
{
    m_rxLength = 0;

    if (GetSafeHwnd() == nullptr) {
        return 1;
    }

    if (!m_serialPort.InitPort(GetSafeHwnd(), portnr, baud, parity, databits, stopsbits)) {
        return 2;
    }

    if (!m_serialPort.StartMonitoring()) {
        return 3;
    }

    //if (!serialPort.IsOpened()) {
    //    return 2;
    //}

    if (m_readPeriod > 0) {
        SetTimer(0, m_readPeriod, nullptr);
    }

    return 0;
}

void    ModbusRtuHandler::closePort()
{
    KillTimer(0);
    m_serialPort.ClosePort();
}


int     ModbusRtuHandler::receive(uint8_t* buff, size_t buffLength)
{
    int length = buffLength < m_rxLength ? buffLength : m_rxLength;
    memcpy(buff, m_frameData, length);
    return length;
}

int ModbusRtuHandler::send(int functionCode, int registerAddress, int registerValue)
{
    if (!m_serialPort.IsOpened()) {
        return 1;
    }

    uint8_t  txBuff[16];
    uint16_t crc;
    switch (functionCode)
    {
    case 0x06:
        txBuff[0] = m_deviceAddress;
        txBuff[1] = 0x06;
        txBuff[2] = (registerAddress & 0xFF00) >> 8;
        txBuff[3] = (registerAddress & 0x00FF);
        txBuff[4] = (registerValue & 0xFF00) >> 8;
        txBuff[5] = (registerValue & 0x00FF);
        crc = getCRC16(txBuff, 6);
        txBuff[6] = (uint8_t)crc;
        txBuff[7] = (uint8_t)(crc >> 8);
        m_serialPort.WriteToPort(txBuff, 8);

        ::SendMessage(GetParent()->GetSafeHwnd(), WM_MODBUS_TX_FRAME, (WPARAM)txBuff, (LPARAM)8);
        break;

    case 0x10:
        txBuff[0] = m_deviceAddress;
        txBuff[1] = 0x10;
        txBuff[2] = (registerAddress & 0xFF00) >> 8;
        txBuff[3] = (registerAddress & 0x00FF);
        txBuff[4] = 0x00;
        txBuff[5] = 0x01;
        txBuff[6] = 0x02;
        txBuff[7] = (registerValue & 0xFF00) >> 8;
        txBuff[8] = (registerValue & 0x00FF);
        crc = getCRC16(txBuff, 9);
        txBuff[9] = (uint8_t)crc;
        txBuff[10] = (uint8_t)(crc >> 8);
        m_serialPort.WriteToPort(txBuff, 11);
        ::SendMessage(GetParent()->GetSafeHwnd(), WM_MODBUS_TX_FRAME, (WPARAM)txBuff, (LPARAM)11);
        break;

    default:
        break;
    }
    return 0;
}


bool ModbusRtuHandler::getLaserDistance(double& leftDistance, double& rightDistance, double& carDistance)
{
    // 2020_10_13，刘钢修改，增加串口是否打开条件判断
    if (m_serialPort.IsOpened()&& m_bMeasureUpdate) {
        EnterCriticalSection(&m_csModbusSync);
        leftDistance = m_leftDistance;
        rightDistance = m_rightDistance;
        carDistance = m_carDistance;
        m_bMeasureUpdate = false;
        LeaveCriticalSection(&m_csModbusSync);
    }
    else
        return false;
    
    return true;
}
#include "../../pch.h"
//#include "../../include/sensor/WirelessRangingHandler.h"
#include "../../include/sensor/WirelessRangingHandler.h"
#include <limits>
#include <algorithm>
#include <fstream>

#define MAX_PACK_LEN            20
#define FRAME_LENGTH            21

IMPLEMENT_DYNAMIC(WirelessRangingHandler, CWnd)

#define D       1.6              //


WirelessRangingHandler::WirelessRangingHandler(CWnd* pParentWnd) :
    m_readPeriod(500),
    m_rxLength(0),
    m_frameLength(-1),
    m_startPosition(-1),
    m_tagCount(0),
    m_stationPosition(-1),
    m_nearestTagPosition(-1),
    m_bTagDataUpdate(false)
{
}
WirelessRangingHandler::WirelessRangingHandler() :
    m_readPeriod(500),
    m_rxLength(0),
    m_frameLength(-1),
    m_startPosition(-1),
    m_tagCount(0),
    m_stationPosition(-1),
    m_nearestTagPosition(-1),
    m_bTagDataUpdate(false)
{
}


WirelessRangingHandler::~WirelessRangingHandler()
{
}

BEGIN_MESSAGE_MAP(WirelessRangingHandler, CWnd)
    ON_WM_CREATE()
    ON_WM_TIMER()
    ON_MESSAGE(WM_COMM_RXCHAR, WirelessRangingHandler::OnCommRxChar)
END_MESSAGE_MAP()

int WirelessRangingHandler::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码
    //MessageBox(L"ModbusRtuHandler::OnCreate");

    return 0;
}

//std::ofstream TAG_LOG("../tag_log.txt");
//std::ofstream TAG_RE("../1022_log.txt");
void WirelessRangingHandler::OnTimer(UINT_PTR nIDEvent)
{
    TagRecord tagRecord[MAX_TAG_NUMBER];
    int currentTagNumber;
    std::map<int, double>::iterator iter;
    double tagPosition;

    // TODO: 在此添加消息处理程序代码和/或调用默认值
    switch (nIDEvent) {
    case 0:
    {
        if (m_serialPort.IsOpened()) {
            // 票箱的投票值置零
            memset(m_votingCell, 0, MAX_CELL_NUMBER * sizeof(int)); //把m_votingCell中所有字节换做字符“0”，常用来对指针或字符串的初始化
            

            if (m_tagCount) {  
                //2020
                EnterCriticalSection(&m_cs);
                memcpy(tagRecord, m_tagRecord, m_tagCount * sizeof(TagRecord));  //把m_tagRecord复制到tagRecord
                currentTagNumber = m_tagCount;
                m_tagCount = 0;
                LeaveCriticalSection(&m_cs);

                //for (int i = 0; i < currentTagNumber; i++) {
                //    TAG_LOG << "tagID = " << tagRecord[i].tagID << ", distance = " << tagRecord[i].distance << std::endl;
                //}
                //TAG_LOG << std::endl;
                           
                for (int i = 0; i < currentTagNumber; i++) {             
                    //根据标签ID，查找标签位置
                    std::map<int, double>::iterator iter = m_mapTag2Position.find(tagRecord[i].tagID);
                    if (iter != m_mapTag2Position.end())
                        tagPosition = iter->second;
                    else
                        continue;

                    // 计算基站与标签水平距离
                    double l = sqrt(tagRecord[i].distance * tagRecord[i].distance - D * D);
                    tagRecord[i].position[0] = tagPosition + l;
                    tagRecord[i].position[1] = tagPosition - l;
                    
                    //tagRecord[i].position[1] = tagRecord[i].position[1] > 0 ? tagRecord[i].position[1] : 0;//1020PM胡改
                    // 确定投票区间.
                    int cellLocation0 = int((tagRecord[i].position[0]) / CELL_LENGTH);
                    int cellLocation1 = int((tagRecord[i].position[1]) / CELL_LENGTH);
                    cellLocation1 = cellLocation1 > 0 ? cellLocation1 : 0; 
                    m_votingCell[cellLocation0]++;
                    m_votingCell[cellLocation1]++;

                    // 每个标签记录自身投票区间
                    tagRecord[i].cellLocation[0] = cellLocation0;
                    tagRecord[i].cellLocation[1] = cellLocation1;
                }

                int maxVotingNumber = -1;
                int maxVotingLocation = -1;
                for (int i = 0; i < MAX_CELL_NUMBER; i++) {    //找出最大投票票数区间i
                    if (m_votingCell[i] > maxVotingNumber) {
                        maxVotingNumber = m_votingCell[i];
                        maxVotingLocation = i;
                    }
                }

                double sum = 0.0;
                double cellMiddlePosition = (maxVotingLocation + 0.5) * CELL_LENGTH;

                for (int i = 0; i < currentTagNumber; i++) {    //查找最小距离的标签ID
                    if (abs(tagRecord[i].position[0] - cellMiddlePosition) < abs(tagRecord[i].position[1] - cellMiddlePosition)) {
                        sum += tagRecord[i].position[0];
                    }
                    else {
                        sum += tagRecord[i].position[1];
                    }
                }

                double averPosition = sum / currentTagNumber;

                std::vector<TagRecord>  tagInCell;
                for (int i = 0; i < currentTagNumber; i++) {          //找出投在该区间的标签
                    if (tagRecord[i].cellLocation[0] == maxVotingLocation || tagRecord[i].cellLocation[1] == maxVotingLocation) {
                        tagInCell.push_back(tagRecord[i]);
                    }
                }

                //double minDistance = std::numeric_limits<double>::max();
                double minDistance = 10000000.0;
                int nearestTagID = -1;
                for (int i = 0; i < tagInCell.size(); i++) {    //查找最小距离的标签ID
                    if (tagInCell[i].distance < minDistance) {
                        minDistance = tagInCell[i].distance;
                        nearestTagID = tagInCell[i].tagID;
                    }
                }

            //根据最近的tagID找到对应的位置
                iter = m_mapTag2Position.find(nearestTagID);
                if (iter != m_mapTag2Position.end())
                    tagPosition = iter->second;
                else
                    break;


                EnterCriticalSection(&m_cs);
                m_stationPosition = CELL_LENGTH * maxVotingLocation;
                m_nearestTagID = nearestTagID;
              //  m_nearestTagPosition = m_mapTag2Position.find(m_nearestTagID)->second;
                m_nearestTagPosition = tagPosition;

                m_bTagDataUpdate = true;
                LeaveCriticalSection(&m_cs);
            }
            else {
                m_bTagDataUpdate = false;
                break;
            }
                
        }

        break;
    }
    default:
        break;
    }

    CWnd::OnTimer(nIDEvent);
}

int WirelessRangingHandler::openPort(UINT portnr /*= 1*/, UINT baud /*= 9600*/, UINT databits /*= 8*/, UINT stopsbits /*= ONESTOPBIT*/, TCHAR parity /*= _T('N')*/)
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

    InitializeCriticalSection(&m_cs);

    return 0;
}

void WirelessRangingHandler::closePort()
{
    KillTimer(0);
    m_serialPort.ClosePort();
}

void WirelessRangingHandler::SetTagPosition() //从数据库读取，待修改1020PM
{
    m_mapTag2Position.insert(std::pair<int, double>(4, 5.0));
    m_mapTag2Position.insert(std::pair<int, double>(3, 10.0));
    m_mapTag2Position.insert(std::pair<int, double>(2, 15.0));
    m_mapTag2Position.insert(std::pair<int, double>(1, 20.0));
}

bool WirelessRangingHandler::GetRangingInfo(double& stationPosition, double& nearestTagPosition)
{
    if (!m_serialPort.IsOpened() || m_bTagDataUpdate == false)
        return false;

    EnterCriticalSection(&m_cs);
    stationPosition = m_stationPosition;
    nearestTagPosition = m_nearestTagPosition;
    LeaveCriticalSection(&m_cs);

    return true;
}

uint16_t Checksum_u16(uint8_t* pdata, uint32_t len)
{
    uint16_t sum = 0;
    uint32_t i;
    for (i = 0; i < len; i++)
        sum += pdata[i];
    sum = ~sum;
    return sum;
}

afx_msg LRESULT WirelessRangingHandler::OnCommRxChar(WPARAM ch, LPARAM port)
{
    m_rxBuff[m_rxLength++] = (uint8_t)ch;
    if (m_rxLength < 2) return 1;

    if (m_startPosition < 0) {
        for (int i = 0; i < m_rxLength; ++i) {
            if (m_rxBuff[i] == 0x55 && m_rxBuff[i+1] == 0xAA) {
                m_startPosition = i;
            }
        }
        if (m_startPosition < 0) {
            m_rxLength = 0;
            m_startPosition = -1;
            return 1;
        }
    }

    if (FRAME_LENGTH > (m_rxLength - m_startPosition)) {
        return 2;
    }

    uint16_t crc = Checksum_u16(m_rxBuff + m_startPosition + 2, FRAME_LENGTH - 4);
    uint16_t crc2 = (m_rxBuff[m_startPosition + FRAME_LENGTH - 1] << 8) + m_rxBuff[m_startPosition + FRAME_LENGTH - 2];

    if (crc != crc2) {
        memcpy(m_rxBuff, m_rxBuff + m_startPosition + 2, m_rxLength - m_startPosition - 2);
        m_rxLength -= (size_t)m_startPosition + 2;
        return 3;
    }

    memcpy(m_frameData, m_rxBuff + m_startPosition, FRAME_LENGTH);
    memcpy(m_rxBuff, m_rxBuff + m_startPosition + FRAME_LENGTH, m_rxLength - m_startPosition - FRAME_LENGTH);
    m_rxLength -= (size_t)m_startPosition + FRAME_LENGTH;
    m_startPosition = -1;

    //::SendMessage(GetParent()->GetSafeHwnd(), WM_WIRELESS_RX_FRAME, (WPARAM)m_frameData, (LPARAM)FRAME_LENGTH);

    uint8_t* data = (uint8_t*)m_frameData;
    unsigned char sequence, electricityQuantity;
    short tagID, stationID;
    int distance;

    memcpy(&sequence, &data[4], 1 * sizeof(unsigned char));
    memcpy(&tagID, &data[5], 2 * sizeof(char));
    memcpy(&stationID, &data[7], 2 * sizeof(char));
    memcpy(&distance, &data[9], 4 * sizeof(char));
    memcpy(&electricityQuantity, &data[13], 1 * sizeof(unsigned char));

    TagRecord newTagData;
    newTagData.tagID = tagID;
    newTagData.distance = distance / 100.0;

    int num = -1;
    for (int i = 0; i < m_tagCount; i++) {  //查找是否保存tagID数据
        if (m_tagRecord[i].tagID == tagID) {
            num = i;
        }
    }

    if (num != -1) { //如果已有tagID，更新数据
        EnterCriticalSection(&m_cs);
        memcpy(m_tagRecord + num, &newTagData, sizeof(TagRecord));
        LeaveCriticalSection(&m_cs);
    }
    else { //没有tagID，插入新数据
        EnterCriticalSection(&m_cs);
        memcpy(m_tagRecord + m_tagCount, &newTagData, sizeof(TagRecord));
        m_tagCount++;
        LeaveCriticalSection(&m_cs);
    }   

    return 0;
}
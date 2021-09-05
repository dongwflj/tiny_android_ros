/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : AiAlgorithm.cpp
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#include <algorithm>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <System.h>
#include <sys/time.h>
#include "common/CommonLog.h"
#include "SlamAlgorithm.h"
#include "MapPoint.h"

using namespace ORB_SLAM2;
CSlamAlgorithm::Object_Creator CSlamAlgorithm::_object_creator;

CSlamAlgorithm::CSlamAlgorithm(): m_pSlamInstance(NULL),
                                  m_bIsInit(false) {
}

CSlamAlgorithm::~CSlamAlgorithm() {
    delete m_pSlamInstance;
}

ERESULT CSlamAlgorithm::Init(const string& strVocFile, const string strCameraSettingFile) {
    LOG_INFO("CSlamAlgorithm::Init Entry\n");
    if (m_bIsInit) {
        LOG_WARN("CSlamAlgorithm::Init reentry, Exit with fail\n");
        return E_FAIL;
    }
    double timeStart, timeEnd, cost; 
    timeStart = (double)cv::getTickCount();
    m_pSlamInstance = new ORB_SLAM2::System(strVocFile, strCameraSettingFile, ORB_SLAM2::System::MONOCULAR, true);
    timeEnd = (double)cv::getTickCount();
    cost = 1000*(timeEnd-timeStart)/cv::getTickFrequency();
    LOG_INFO("Slam init time cost:" << cost);
    m_bIsInit = true;
    LOG_INFO("CSlamAlgorithm::Init Exit\n");
    return E_OK;
}

ERESULT CSlamAlgorithm::Track(const std::string& strFrame, const double timestamp) {
    if (!m_bIsInit) {
        return E_FAIL;
    }
    double timeStart, timeEnd, cost; 
    timeStart = (double)cv::getTickCount();
    std::vector<char> vec_data(strFrame.begin(), strFrame.end()); 
    //cv::Mat matRobotFrame = cv::imdecode(vec_data, CV_LOAD_IMAGE_GRAYSCALE);    
    cv::Mat matRobotFrame = cv::imdecode(vec_data, CV_LOAD_IMAGE_ANYCOLOR);    
    timeEnd = (double)cv::getTickCount();
    cost = 1000*(timeEnd-timeStart)/cv::getTickFrequency();
    LOG_INFO("Decode cost:" << cost);
    //timeStart = (double)cv::getTickCount();
    //static int n = 0;
    //n++;
    //string seq;
    //stringstream ss;  
    //ss<<n;  
    //seq = ss.str();
    //imwrite("/opt/tomato/output/" + seq + ".jpg", matRobotFrame);
    //timeEnd = (double)cv::getTickCount();
    //cost = 1000*(timeEnd-timeStart)/cv::getTickFrequency();
    //LOG_INFO("Write file cost:" << cost);
	//cv::resize(matRobotFrame, matRobotFrame, cv::Size(640, 480), (0,0), (0,0), cv::INTER_LINEAR);
    //imwrite("/opt/tomato/output2/" + seq + ".jpg", matRobotFrame);
//    cv::Mat equalizedImg;  
//    equalizeHist(matRobotFrame, equalizedImg);  
//    m_pSlamInstance->TrackMonocular(equalizedImg, timestamp);
    timeStart = (double)cv::getTickCount();
    m_pSlamInstance->TrackMonocular(matRobotFrame, timestamp);
    timeEnd = (double)cv::getTickCount();
    cost = 1000*(timeEnd-timeStart)/cv::getTickFrequency();
    LOG_INFO("Orb track cost:" << cost);
    return E_OK;
}

ERESULT CSlamAlgorithm::Close() {
    LOG_INFO("CSlamAlgorithm::Close entry\n");
    if (!m_bIsInit) {
        LOG_WARN("CSlamAlgorithm::Close Not init, Exit with fail\n");
        return E_FAIL;
    }
    m_bIsInit = false;
    m_pSlamInstance->Shutdown();
    delete m_pSlamInstance;
    m_pSlamInstance = NULL;
    LOG_INFO("CSlamAlgorithm::Close exit\n");
    return E_OK;
}

void CSlamAlgorithm::drawGL() {
    if(NULL != m_pSlamInstance) {
        m_pSlamInstance->drawGL();
    }
}

ORB_SLAM2::System* CSlamAlgorithm::SystemInstance() {
    return m_pSlamInstance;
}

int CSlamAlgorithm::TrackingState() {
    if(NULL == m_pSlamInstance) {
        return -1;
    }
    return m_pSlamInstance->GetTrackingState();
}

ERESULT CSlamAlgorithm::CameraPos(float& fX, float& fY, float& fAngle) {
    ERESULT ret = E_OK;
    if(NULL == m_pSlamInstance) {
        return E_FAIL;
    }
    if (0 != m_pSlamInstance->GetCameraPos(fX, fY, fAngle)) {
        return E_FAIL;
    }
    return ret;
}

void CSlamAlgorithm::Reset() {
    if(NULL == m_pSlamInstance) {
        return;
    }
    m_pSlamInstance->Reset();
}

ERESULT CSlamAlgorithm::MapPoint(std::vector<float>& vecX, std::vector<float>& vecZ) {
    Map* pMap = m_pSlamInstance->GetMap();
    if (NULL != pMap) {
        const vector<ORB_SLAM2::MapPoint*> &vpMPs = pMap->GetAllMapPoints();
        for(size_t i=0, iend=vpMPs.size(); i<iend;i++)
        {
            if(vpMPs[i]->isBad())  {
                continue;
            }
            cv::Mat pos = vpMPs[i]->GetWorldPos();
            vecX.push_back(pos.at<float>(0));
            vecZ.push_back(pos.at<float>(2));
        }
        return E_OK;
    }
    return E_FAIL;
}

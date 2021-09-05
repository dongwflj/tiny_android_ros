/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : NaviStopped.cpp
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#include "common/CommonLog.h"
#include "NaviStopped.h"
#include "service/motion/MotionService.h"

CNaviStopped::CNaviStopped() {
}

CNaviStopped::~CNaviStopped() {
}

ERESULT CNaviStopped::Init() {
    LOG_INFO("CNaviStopped::Init Entry\n");
    LOG_INFO("CNaviStopped::Init Exit\n");
    return E_OK;
}

ERESULT CNaviStopped::Go() {
    LOG_INFO("CNaviStopped::Go() entry\n");
    ERESULT ret = E_OK;
    // Get IMU data from topic
    //CImuPacket* pPacket = (CImuPacket*)CTopicService::GetInstance()->GetTopicMessageAsync(SYS_IMU);
    ///CMotionService::GetInstance()->Move(90, 0, 127);
    // Motion interface
    CMotionService::GetInstance()->Move(50, 50, true, true);
    m_pContext->ChangeState(EMOVING);
    // Slam interface
    /*CSlamAlgorithm* pSlamAlgorithm = CSlamAlgorithm::GetInstance();
    int nSlamState = pSlamAlgorithm->TrackingState();
    if (nSlamState < 2) {
        LOG_INFO("Stop state, slam is not initialize:" << nSlamState << std::endl);
    }
    else if (nSlamState == 2) {
        LOG_INFO("Slam track ok, try to get navi path and move\n"); 
        float x, y, angle;
        ret = pSlamAlgorithm->CameraPos(x, y, angle);
        if (ret != E_OK) {
            LOG_WARN("No slam camera pos, treat as LOSE\n"); 
            m_pContext->ChangeState(ERECOVERY);
            return ret;
        }
        std::vector<float> vecX, vecZ;
        pSlamAlgorithm->MapPoint(vecX, vecZ);
        for (int i = 0; i < vecX.size(); i++) { 
            mNaviEngine.AddObject(vecX[i]*100, vecZ[i]*100);
        }
        vector<point> vecPath;
        ERESULT ret = mNaviEngine.GetNaviPath(x, y, vecPath);
        if (ret != E_OK) {
            // No path found, need roam
            return ret;
        }
        point p5 = vecPath[vecPath.size() - 5];
        float distance = sqrt((p5.y - y)*(p5.y - y) + (p5.x - x)*(p5.x - x));
        float tan = (p5.y - y) / (p5.x - x);
        float val = 180.0 / 3.14159265;

        float arctan = atan(tan) * val;
        float turnAngle;
        if (ret > 0) {
            turnAngle = arctan - 90.0;
        } 
        else {
            turnAngle = 90.0 + arctan;
        }
//        CMotionService::GetInstance()->Move(turnAngle, 0, 127);
//        CMotionService::GetInstance()->Move(0, distance, 127);
        m_pContext->PutLastAction(turnAngle, 0, 127);
        m_pContext->PutLastAction(0, distance, 127);
        m_pContext->ChangeState(EMOVING);
    }
    else {
        // Lost and recovery
        LOG_INFO("Tracking lost" << std::endl);
        m_pContext->ChangeState(ERECOVERY);
    }*/
    LOG_INFO("CNaviStopped::Go() exit\n");
    return ret;    
}

ERESULT CNaviStopped::TimeOut() {
    LOG_INFO("Stop state, do nothing\n"); 
    return E_OK;    
}

ERESULT CNaviStopped::GetToTarget() {
    LOG_INFO("Stop state, do nothing\n"); 
    return E_OK;    
}

ERESULT CNaviStopped::Finish() {
    LOG_INFO("Stop state, do nothing\n"); 
    return E_OK;    
}

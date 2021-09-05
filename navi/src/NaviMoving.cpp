/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : NaviMoving.cpp
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#include <iomanip>
#include "common/CommonLog.h"
#include "NaviMoving.h"
#include "NaviAlgorithm.h"
#include "../../slam/include/SlamAlgorithm.h"

using namespace std;

ERESULT CNaviMoving::Go() {
    LOG_INFO("CNaviMoving::Go() entry\n");
    ERESULT ret = E_OK;
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
        ///CMotionService::GetInstance()->Move(-angle, 0, 127);
        m_pContext->PutLastAction(-angle, 0, 127);
        m_pContext->ChangeState(ESTOPPED);
    }
    else {
        // Lost and recovery
        LOG_INFO("Tracking lost" << std::endl);
        m_pContext->ChangeState(ERECOVERY);
    }*/
    LOG_INFO("CNaviMoving::Go() exit\n");
    return ret;    
}

ERESULT CNaviMoving::TimeOut() {
//    ExecuteAction(DIR_STOP, 0, 0);
//    m_pContext->ChangeState(m_pContext->m_Stopped);
    return E_OK;    
}

ERESULT CNaviMoving::GetToTarget() {
//    ExecuteAction(DIR_STOP, 0, 0);
//    m_pContext->ChangeState(m_pContext->m_Stopped);
    return E_OK;    
}

ERESULT CNaviMoving::Finish() {
//    ExecuteAction(DIR_STOP, 0, 0);
//    m_pContext->ChangeState(m_pContext->m_Stopped);
    return E_OK;    
}

// -1 Finish, 1 Navi 0 Donothing
int CNaviMoving::DecideNextStep(int nCamX, int nCamY) {
    int ret = 0;
/*    int nNextTargetX = 0;
    int nNextTargetY = 0;
    int nFinalTargetX = 0;
    int nFinalTargetY = 0;
    m_pContext->NextTarget(nNextTargetX, nNextTargetY);
    m_pContext->FinalTarget(nFinalTargetX, nFinalTargetY);
    if (nCamX == nNextTargetX && nCamY == nNextTargetY) {
        ret = 1;
    }
    else if (nCamX == nFinalTargetX && nCamY == nFinalTargetY) {
        ret = -1;
    }
    LOG_INFO("Decide next step camx:" << nCamX << " camy:" << nCamY << 
            " nextX:" << nNextTargetX << " nextY:" << nNextTargetY <<
            " ret:" << ret);*/
    return ret;
}

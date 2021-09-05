/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : NaviRecovery.cpp
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#include "common/CommonLog.h"
#include "NaviRecovery.h"
#include "service/motion/MotionService.h"
#include "../../slam/include/SlamAlgorithm.h"


ERESULT CNaviRecovery::Go() {
    LOG_INFO("Recovery State, do nothing\n");
//    CSlamAlgorithm* pSlamAlgorithm = CSlamAlgorithm::GetInstance();
//    int nSlamState = pSlamAlgorithm->TrackingState();
//    if (nSlamState != 2) {
//        double angle, distance, speed;
//        ERESULT ret = m_pContext->GetLastAction(angle, distance, speed);
//        if (ret == E_OK) {
//            CMotionService::GetInstance()->Move(-angle, -distance, speed);
//        }
//        else {
//            // Random roam
//        }
//    }
//    else {
//        m_pContext->ChangeState(ESTOPPED);
//    }
    return E_OK;    
}

ERESULT CNaviRecovery::TimeOut() {
    LOG_INFO("Recovery State, do nothing\n");
    return E_OK;    
}

ERESULT CNaviRecovery::GetToTarget() {
    LOG_INFO("Recovery State, do nothing\n");
    return E_OK;    
}

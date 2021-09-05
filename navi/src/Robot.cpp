/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : Robot.cpp
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/

#include "Robot.h"
#include "common/CommonLog.h"
#include "common/CommonUtil.h"

CRobot::CRobot() : m_StateStop(*this),
                   m_StateHappy(*this),
                   m_StateHungry(*this),
                   m_StateTired(*this),
                   m_pState(NULL) {
}

ERESULT CRobot::Init() {
    LOG_INFO("CRobot::Init entry\n");
    m_pState = &m_StateStop;
    LOG_INFO("CRobot::Init exit\n");
    return E_OK;
}

ERESULT CRobot::Close() {
    return E_OK;
}
 
ERESULT CRobot::FoundPerson() {
    m_pState->FoundPerson();
    return E_OK;
}

ERESULT CRobot::PowerLow() {
    LOG_INFO("CRobot::PowerLow entry\n");
    m_pState->PowerLow();
    LOG_INFO("CRobot::PowerLow exit\n");
    return E_OK;
}

ERESULT CRobot::NeedCharge() {
    m_pState->NeedCharge();
    return E_OK;
}

void CRobot::Run(void) {
    LOG_INFO("CRobot::Run entry\n");
    while (m_bRunning) {
        int num = CCommonUtil::GetRandomNumber(3);
        switch(num) {
        case 0:
            FoundPerson();
            break;
        case 1:
            PowerLow();
            break;
        case 2:
            NeedCharge();
            break;
        default:
            LOG_INFO("Bad event number\n");
        }
        CCommonUtil::SleepMs(3, 0);
    }
}

/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : NaviRobot.cpp
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/

#include "NaviRobot.h"
#include "common/CommonLog.h"

CNaviRobot::CNaviRobot() {
}

ERESULT CNaviRobot::Init() {
    LOG_INFO("CNaviRobot::Init entry\n"); 
    m_OpticalFlow.Init();
    m_Stopped.SetContext(*this);
    m_Stopped.Init();
    m_Moving.SetContext(*this);
    m_Recovery.SetContext(*this);
    m_Finish.SetContext(*this);
    SetState(m_Finish);
    LOG_INFO("CNaviRobot::Init exit\n"); 
    return E_OK;
}

ERESULT CNaviRobot::Close() {
    SetState(m_Finish);
    m_pState->Go();
    m_OpticalFlow.Close();
    return E_OK;
}

ERESULT CNaviRobot::Start() {
    m_OpticalFlow.Start();
    m_pState->Go();
    return E_OK;
}

ERESULT CNaviRobot::Stop() {
    m_pState->Finish();
    m_OpticalFlow.Stop();
    return E_OK;
}

ERESULT CNaviRobot::ChangeState(STATE state) {
    switch(state) {
        case ESTOPPED: {
            SetState(m_Stopped);
            break;
        }
        case EMOVING: {
            SetState(m_Moving);
            break;
        }
        case ERECOVERY: {
            SetState(m_Recovery);
            break;
        }
        case EFINISH: {
            SetState(m_Finish);
            break;
        }
    } 
    return E_OK; 
}

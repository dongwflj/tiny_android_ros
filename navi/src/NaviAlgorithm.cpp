/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : NaviAlgorithm.cpp
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#include "common/CommonLog.h"
#include "NaviAlgorithm.h"
#include "SlamController.h"

using namespace std;

CNaviAlgorithm::Object_Creator CNaviAlgorithm::_object_creator;

CNaviAlgorithm::CNaviAlgorithm() :
    m_nFinalTargetX(0), m_nFinalTargetY(500),
    m_pSlamController(NULL) {
}

CNaviAlgorithm::~CNaviAlgorithm() {
}

ERESULT CNaviAlgorithm::Init() {
    LOG_INFO("CNaviAlgorithm::Init entry\n"); 
    /*if (NULL == m_pSlamController) {
        m_pSlamController = new CSlamController();

        if (NULL == m_pSlamController) {
            LOG_ERR("Slam controller new fail, no memory\n");
            return E_FAIL;
        }
    }*/
    ///m_pSlamController->Init();
    m_Robot.Init(); 
    LOG_INFO("CNaviAlgorithm::Init exit\n"); 
    return E_OK;
}

ERESULT CNaviAlgorithm::Close() {
    m_Robot.Close();
    //m_pSlamController->Close();
    //delete m_pSlamController;
    //m_pSlamController = NULL;
    return E_OK;
}

ERESULT CNaviAlgorithm::SetNaviTarget(int& nX, int& nY) {
    m_nFinalTargetX = nX;
    m_nFinalTargetY = nY;
    return E_OK;
}

ERESULT CNaviAlgorithm::StartNavigation() {
    LOG_INFO("CNaviAlgorithm::Startnavigation entry\n"); 
    m_Robot.Start();
    ///m_pSlamController->Start();
    LOG_INFO("CNaviAlgorithm::Startnavigation exit\n"); 
    return E_OK;
}

ERESULT CNaviAlgorithm::StopNavigation() {
    m_Robot.Stop();
    ///m_pSlamController->Stop();
    return E_OK;
}

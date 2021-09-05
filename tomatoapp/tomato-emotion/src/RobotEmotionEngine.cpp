/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : RobotEmotionEngine.cpp
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#include "common/CommonLog.h"
#include "RobotEmotionEngine.h"
#include "Robot.h"

using namespace std;

CRobotEmotionEngine::Object_Creator CRobotEmotionEngine::_object_creator;

CRobotEmotionEngine::CRobotEmotionEngine() : m_pRobot(NULL) {
}

CRobotEmotionEngine::~CRobotEmotionEngine() {
}

ERESULT CRobotEmotionEngine::Init() {
    LOG_INFO("CRobotEmotionEngine::Init entry\n"); 
    if (NULL == m_pRobot) {
        m_pRobot = new CRobot();
        m_pRobot->Init();
    }
    LOG_INFO("CRobotEmotionEngine::Init exit\n"); 
    return E_OK;
}

ERESULT CRobotEmotionEngine::Close() {
    if (NULL != m_pRobot) {
        delete m_pRobot;
        m_pRobot = NULL;
    }
    return E_OK;
}

ERESULT CRobotEmotionEngine::Start() {
    LOG_INFO("CRobotEmotionEngine::Start Entry\n");
    if (NULL != m_pRobot) {
        m_pRobot->StartThread();
    }
    LOG_INFO("CRobotEmotionEngine::Start Exit\n");
    return E_OK;
}

ERESULT CRobotEmotionEngine::Stop() {
    LOG_INFO("CRobotEmotionEngine::Stop Entry\n");
    if (NULL != m_pRobot) {
        m_pRobot->CancelThread();
    }
    LOG_INFO("CRobotEmotionEngine::Stop Exit\n");
    return E_OK;
}

/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : RobotStateHappy.cpp
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#include "common/CommonLog.h"
#include "service/motion/MotionService.h"
#include "RobotStateHappy.h"
#include "Robot.h"

CRobotStateHappy::CRobotStateHappy(CRobot& robot) : m_Robot(robot) {
}

CRobotStateHappy::~CRobotStateHappy() {
}

ERESULT CRobotStateHappy::FoundPerson() {
    LOG_INFO("Happy state: found persion, ignore\n");
    //m_Robot.ChangeState(m_Robot.m_StateHappy);
    return E_OK;
}

ERESULT CRobotStateHappy::PowerLow() {
    LOG_INFO("Happy state: Power low, I am tired\n");
    CMotionService::GetInstance()->Move(180, 0, 125);
    m_Robot.ChangeState(m_Robot.m_StateTired);
    return E_OK;
}

ERESULT CRobotStateHappy::NeedCharge() {
    LOG_INFO("Happy state: Need charge, I am hungry\n");
    CMotionService::GetInstance()->Move(-180, 0, 125);
    m_Robot.ChangeState(m_Robot.m_StateHungry);
    return E_OK;
}


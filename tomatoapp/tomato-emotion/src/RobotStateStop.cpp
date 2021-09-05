/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : RobotStateStop.cpp
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#include "common/CommonLog.h"
#include "service/motion/MotionService.h"
#include "RobotStateStop.h"
#include "Robot.h"

CRobotStateStop::CRobotStateStop(CRobot& robot) : m_Robot(robot) {
}

CRobotStateStop::~CRobotStateStop() {
}

ERESULT CRobotStateStop::FoundPerson() {
    LOG_INFO("Stop state: found persion, I am Happy\n");
    CMotionService::GetInstance()->Move(60, 0, 125);
    CMotionService::GetInstance()->Move(-120, 0, 125);
    CMotionService::GetInstance()->Move(0, 50, 125);
    CMotionService::GetInstance()->Move(0, -50, 125);
    m_Robot.ChangeState(m_Robot.m_StateHappy);
    return E_OK;
}

ERESULT CRobotStateStop::PowerLow() {
    LOG_INFO("Stop state: Power low, I am tired\n");
    CMotionService::GetInstance()->Move(180, 0, 100);
    m_Robot.ChangeState(m_Robot.m_StateTired);
    return E_OK;
}

ERESULT CRobotStateStop::NeedCharge() {
    LOG_INFO("Stop state: Need charge, I am hungry\n");
    CMotionService::GetInstance()->Move(-180, 0, 100);
    m_Robot.ChangeState(m_Robot.m_StateHungry);
    return E_OK;
}


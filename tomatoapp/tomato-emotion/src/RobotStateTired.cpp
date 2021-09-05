/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : RobotStateTired.cpp
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#include "common/CommonLog.h"
#include "service/motion/MotionService.h"
#include "RobotStateTired.h"
#include "Robot.h"

CRobotStateTired::CRobotStateTired(CRobot& robot) : m_Robot(robot) {
}

CRobotStateTired::~CRobotStateTired() {
}

ERESULT CRobotStateTired::FoundPerson() {
    LOG_INFO("Tired state: found persion, I am Happy\n");
    CMotionService::GetInstance()->Move(60, 0, 75);
    CMotionService::GetInstance()->Move(-120, 0, 75);
    CMotionService::GetInstance()->Move(0, 50, 75);
    CMotionService::GetInstance()->Move(0, -50, 75);
    m_Robot.ChangeState(m_Robot.m_StateHappy);
    return E_OK;
}

ERESULT CRobotStateTired::PowerLow() {
    LOG_INFO("Tired state: Power low, ignore\n");
    //m_Robot.ChangeState(m_Robot.m_StateTired);
    return E_OK;
}

ERESULT CRobotStateTired::NeedCharge() {
    LOG_INFO("Tired state: Need charge, I am hungry\n");
    CMotionService::GetInstance()->Move(180, 0, 75);
    m_Robot.ChangeState(m_Robot.m_StateHungry);
    return E_OK;
}


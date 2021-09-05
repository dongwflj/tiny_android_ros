/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : RobotStateHungry.cpp
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#include "common/CommonLog.h"
#include "service/motion/MotionService.h"
#include "RobotStateHungry.h"
#include "Robot.h"

CRobotStateHungry::CRobotStateHungry(CRobot& robot) : m_Robot(robot) {
}

CRobotStateHungry::~CRobotStateHungry() {
}

ERESULT CRobotStateHungry::FoundPerson() {
    LOG_INFO("Hungry state: found persion, I am Happy\n");
    CMotionService::GetInstance()->Move(60, 0, 25);
    CMotionService::GetInstance()->Move(-120, 0, 25);
    CMotionService::GetInstance()->Move(0, 50, 25);
    CMotionService::GetInstance()->Move(0, -50, 25);
 
    m_Robot.ChangeState(m_Robot.m_StateHappy);
    return E_OK;
}

ERESULT CRobotStateHungry::PowerLow() {
    LOG_INFO("Hungry state: Power low, I am charging\n");
    return E_OK;
}

ERESULT CRobotStateHungry::NeedCharge() {
    LOG_INFO("Hungry state: Need charge, ignore\n");
    //m_Robot.ChangeState(m_Robot.m_StateHungry);
    return E_OK;
}


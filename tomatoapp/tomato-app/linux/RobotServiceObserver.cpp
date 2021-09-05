/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : dongwflj@163.com
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/
#include "common/CommonLog.h"
#include "RobotServiceObserver.h"

ERESULT CRobotServiceObserver::OnConnected() {
    LOG_INFO("CRobotServiceObserver OnConnected\n");
    return E_OK;
}

ERESULT CRobotServiceObserver::OnDisconnected() {
    LOG_INFO("CRobotServiceObserver OnDisconnected\n");
    return E_OK;
}

ERESULT CRobotServiceObserver::OnData() {
    LOG_INFO("CRobotServiceObserver OnData\n");
    return E_OK;
}

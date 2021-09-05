/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : dongwflj@163.com
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/
#ifndef _ROBOTSERVICEOBSERVER_H_
#define _ROBOTSERVICEOBSERVER_H_

#include "core/interface/IRobotServiceObserver.h"

class CRobotServiceObserver : public IRobotServiceObserver {
public:
    ERESULT OnConnected();
    ERESULT OnDisconnected();
    ERESULT OnData();
};

#endif


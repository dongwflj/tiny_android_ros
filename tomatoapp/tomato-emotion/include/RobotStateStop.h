/********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _ROBOTSTATESTOP_H_
#define _ROBOTSTATESTOP_H_

#include "RobotState.h"

class CRobot;
class CRobotStateStop : public IRobotState {
public:
    CRobotStateStop(CRobot& robot);
    ~CRobotStateStop();

    // IRobotState
    ERESULT FoundPerson();
    ERESULT PowerLow();
    ERESULT NeedCharge();

private:
    CRobot& m_Robot;
};

#endif

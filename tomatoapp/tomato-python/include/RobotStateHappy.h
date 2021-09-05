/********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _ROBOTSTATEHAPPY_H_
#define _ROBOTSTATEHAPPY_H_

#include "RobotState.h"

class CRobot;
class CRobotStateHappy : public IRobotState {
public:
    CRobotStateHappy(CRobot& robot);
    ~CRobotStateHappy();

    // IRobotState
    ERESULT FoundPerson();
    ERESULT PowerLow();
    ERESULT NeedCharge();

private:
    CRobot& m_Robot;
};

#endif

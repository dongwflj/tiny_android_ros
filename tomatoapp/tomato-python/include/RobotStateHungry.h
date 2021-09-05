/********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _ROBOTSTATEHUNGRY_H_
#define _ROBOTSTATEHUNGRY_H_

#include "RobotState.h"

class CRobot;
class CRobotStateHungry : public IRobotState {
public:
    CRobotStateHungry(CRobot& robot);
    ~CRobotStateHungry();

    // IRobotState
    ERESULT FoundPerson();
    ERESULT PowerLow();
    ERESULT NeedCharge();

private:
    CRobot& m_Robot;
};

#endif

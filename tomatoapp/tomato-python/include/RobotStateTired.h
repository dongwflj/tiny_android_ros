/********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _ROBOTSTATETIRED_H_
#define _ROBOTSTATETIRED_H_

#include "RobotState.h"

class CRobot;
class CRobotStateTired : public IRobotState {
public:
    CRobotStateTired(CRobot& robot);
    ~CRobotStateTired();

    // IRobotState
    ERESULT FoundPerson();
    ERESULT PowerLow();
    ERESULT NeedCharge();

private:
    CRobot& m_Robot;
};

#endif

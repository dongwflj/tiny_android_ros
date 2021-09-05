/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : Robot.h
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/

#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "common/CommonDefine.h"
#include "common/CommonThread.h"
#include "RobotStateStop.h"
#include "RobotStateHappy.h"
#include "RobotStateHungry.h"
#include "RobotStateTired.h"

class IRobotState;
class CRobot : public CCommonThread {
public:
    CRobot();

    ERESULT Init();
    ERESULT Close();
    ERESULT ChangeState(IRobotState& state) { m_pState = &state; }

    ERESULT FoundPerson();
    ERESULT PowerLow();
    ERESULT NeedCharge();
    // CCommonThread
    void Run(void);
 
    CRobotStateStop   m_StateStop;
    CRobotStateHappy  m_StateHappy;
    CRobotStateHungry m_StateHungry;
    CRobotStateTired  m_StateTired;
private:
    IRobotState* m_pState;
};

#endif

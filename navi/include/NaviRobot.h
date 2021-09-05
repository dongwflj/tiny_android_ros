/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : NaviRobot.h
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/

#ifndef _NAVIROBOT_H_
#define _NAVIROBOT_H_

#include "common/CommonDefine.h"
#include "OpticalFlow.h"
#include "NaviStopped.h"
#include "NaviMoving.h"
#include "NaviRecovery.h"
#include "NaviFinish.h"
#include "IContext.h"

class CNaviState;
class CNaviRobot : public IContext {
public:
    CNaviRobot();
    ERESULT Init();
    ERESULT Close();
    ERESULT Start();
    ERESULT Stop();
    void SetState(CNaviState& state) {m_pState = &state;}

    // IContext
    ERESULT ChangeState(STATE state);
private:
    CNaviStopped  m_Stopped;
    CNaviMoving   m_Moving;
    CNaviRecovery m_Recovery;
    CNaviFinish   m_Finish;
    CNaviState*   m_pState;
    COpticalFlow  m_OpticalFlow;
};

#endif

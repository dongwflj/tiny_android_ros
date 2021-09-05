/********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : RobotState.h
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _IROBOTSTATE_H_
#define _IROBOTSTATE_H_

#include "common/CommonDefine.h"

class IRobotState {
public:
    virtual  ERESULT FoundPerson() = 0;
    virtual  ERESULT PowerLow() = 0;
    virtual  ERESULT NeedCharge() = 0;
};

#endif

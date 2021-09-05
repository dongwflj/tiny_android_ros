/********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : NaviMoving.h
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _NAVIMOVING_H_
#define _NAVIMOVING_H_

#include "NaviState.h"

class CNaviMoving : public CNaviState {
public:
    virtual ERESULT Go();
    virtual ERESULT TimeOut();
    virtual ERESULT GetToTarget();
    virtual ERESULT Finish();
private:
    int DecideNextStep(int nCamX, int nCamY);
};

#endif

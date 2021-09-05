/********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : NaviFinish.h
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _NAVIFINISH_H_
#define _NAVIFINISH_H_

#include "NaviState.h"

class CNaviFinish : public CNaviState {
public:
    virtual ERESULT Go();
    virtual ERESULT TimeOut();
    virtual ERESULT GetToTarget();
    virtual ERESULT Finish();
};

#endif

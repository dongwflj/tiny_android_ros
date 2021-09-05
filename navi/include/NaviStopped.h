/********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : NaviStopped.h
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _NAVISTOPPED_H_
#define _NAVISTOPPED_H_

#include "NaviState.h"
#include "core/SdkDefine.h"

class CNaviStopped : public CNaviState {
public:
    CNaviStopped();
    ~CNaviStopped();
    ERESULT Init();
    // CNaviState 
    virtual ERESULT Go();
    virtual ERESULT TimeOut();
    virtual ERESULT GetToTarget();
    virtual ERESULT Finish();
};

#endif

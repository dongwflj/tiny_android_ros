/********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : NaviRecovery.h
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _NAVIRECOVERY_H_
#define _NAVIRECOVERY_H_

#include "NaviState.h"

class CNaviRecovery : public CNaviState {
public:
    virtual ERESULT Go();
    virtual ERESULT TimeOut();
    virtual ERESULT GetToTarget();
    virtual ERESULT Finish();
private:
};

#endif

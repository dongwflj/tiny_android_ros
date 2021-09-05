/********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : NaviState.h
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _NAVISTATE_H_
#define _NAVISTATE_H_

#include "common/CommonDefine.h"
#include "IContext.h"

class CNaviState {
public:
    virtual ERESULT Go() = 0;
    virtual ERESULT TimeOut() = 0;
    virtual ERESULT GetToTarget() = 0;
    virtual ERESULT Finish() = 0;

    void SetContext(IContext& pContext) { m_pContext = &pContext; }
protected:
    IContext* m_pContext;
};

#endif

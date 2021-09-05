/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : IContext.h
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _ICONTEXT_H_
#define _ICONTEXT_H_

#include "common/CommonDefine.h"

enum STATE {
    ESTOPPED = 0,
    EMOVING,
    ERECOVERY,
    EFINISH
};

class IContext {
public:
    virtual ERESULT ChangeState(STATE state) = 0;
    ///virtual ERESULT Go(EDIRECTION direction, ESPEED speed) = 0;
};

#endif


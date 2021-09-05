/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : dongwflj@163.com
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/
#ifndef _ROBOTEVENT_H_
#define _ROBOTEVENT_H_

#include "util/topic/ITopicObserver.h"

class CRobotEvent: public ITopicObserver {
public:
    ERESULT Init();
    ERESULT Close();
    ERESULT OnTopicData(void* pMessage, bool bNeedRelease);
};

#endif


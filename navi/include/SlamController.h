/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : dongwflj@163.com
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/
#ifndef _SLAMCONTROLLER_H_
#define _SLAMCONTROLLER_H_

#include "common/CommonDefine.h"
#include "common/CommonThread.h"
#include "util/topic/ITopicObserver.h"

class CSlamController : public CCommonThread {
public:
    CSlamController();
    ERESULT Init();
    ERESULT Close();
    ERESULT Start();
    ERESULT Stop();
    // CCommonThread
    void Run(void);
    class CTopicObserver : public ITopicObserver {
    public:
        ERESULT OnTopicData(void* pMessage, bool bNeedRelease);
    };
private:
    CTopicObserver m_CameraObserver;    
};

#endif

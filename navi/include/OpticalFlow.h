/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/

#ifndef _OPTICALFLOW_H_
#define _OPTICALFLOW_H_

#include "common/CommonDefine.h"
#include "common/CommonThread.h"
#include "util/topic/ITopicObserver.h"

class COpticalFlow : public CCommonThread {
public:
    COpticalFlow();
    ERESULT Init();
    ERESULT Close();
    ERESULT Start();
    ERESULT Stop();
    ERESULT GetNaviDecision(int& nLeft, int& nRight);
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

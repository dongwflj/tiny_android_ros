/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : dongwflj@163.com
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/
#include "common/CommonLog.h"
#include "core/SdkDefine.h"
#include "RobotEvent.h"
#include <iostream>
#include "util/topic/TopicService.h"

using namespace std;

ERESULT CRobotEvent::Init() {
    CTopicService::GetInstance()->Subscribe(SYS_EVENT,
                                            *this);
    return E_OK;
}

ERESULT CRobotEvent::Close() {
    CTopicService::GetInstance()->UnSubscribe(SYS_EVENT,
                                            *this);
    return E_OK;
}

ERESULT CRobotEvent::OnTopicData(void* pMessage, bool bNeedRelease) {
    LOG_INFO("CRobotEvent OnTopicData entry\n");
    CTopicService* pTopicService = CTopicService::GetInstance();
    ESYSEVENT event = reinterpret_cast<ESYSEVENT &>(pMessage);
    if (event == EVT_CONNECTED) {
        cout << "Robot connected" << endl;
    }
    else if (event == EVT_DISCONNECTED) {
        cout << "Robot disconnected" << endl;
    } 
    LOG_INFO("Recv sys event:" << event << std::endl);
    return E_OK;
}

/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : SlamWorker.cpp
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#include <fstream>
#include "common/CommonLog.h"
#include "SlamController.h"
#include "util/topic/TopicService.h"
#include "protocol/CameraPacket.h"
#include "slam/include/SlamAlgorithm.h"

using namespace std;

const std::string  AL_SLAM = "al_slam";

CSlamController::CSlamController() {
}

ERESULT CSlamController::Init() {
    LOG_INFO("CSlamController::Init Entry\n");
#ifndef __ANDROID_NDK__
    const std::string strVocFile = "/opt/tomato/tomatoapp/etc/ORBvoc.bin";
    const std::string strSettingFile = "/opt/tomato/tomatoapp/etc/Tomato.yaml";
#else
    const std::string strVocFile = "/sdcard/Download/ORBvoc.bin";
    const std::string strSettingFile = "/sdcard/Download/Tomato.yaml";
#endif
    CSlamAlgorithm::GetInstance()->Init(strVocFile, strSettingFile);
    CTopicService::GetInstance()->RegisterTopic(AL_SLAM);
    CTopicService::GetInstance()->Subscribe(SYS_CAMERA,
                                            m_CameraObserver);
    LOG_INFO("CSlamController::Init Exit\n");
    return E_OK;
}

ERESULT CSlamController::Close() {
    LOG_INFO("CSlamController::Close Entry\n");
    CSlamAlgorithm::GetInstance()->Close();
    LOG_INFO("CSlamController::Close Exit\n");
    return E_OK;
}

ERESULT CSlamController::Start() {
    LOG_INFO("CSlamController::Start Entry\n");
    StartThread();
    LOG_INFO("CSlamController::Start Exit\n");
    return E_OK;
}

ERESULT CSlamController::Stop() {
    LOG_INFO("CSlamController::Stop Entry\n");
    CancelThread();
    LOG_INFO("CSlamController::Stop Exit\n");
    return E_OK;
}

ERESULT CSlamController::CTopicObserver::OnTopicData(void* pMessage, bool bNeedRelease) {
    LOG_INFO("CSlamController::OnTopicData entry");
    CTopicService* pTopicService = CTopicService::GetInstance();
    CCameraPacket* pPacket = (CCameraPacket*)pMessage;

    if (pTopicService->Size(AL_SLAM) > 0) {
        CCameraPacket* pOld = (CCameraPacket*)(pTopicService->GetTopicMessageAsync(AL_SLAM));
        delete pOld;
        LOG_INFO("Image process slow, replace with lastes data\n");
    }
    LOG_INFO("SYS_IMAGE size:" << pTopicService->Size(AL_SLAM) << std::endl);

    if (bNeedRelease) {
        LOG_DBG("CSlamController::OnTopicData need release\n");
        pTopicService->Publish(AL_SLAM, pPacket);
    }
    else {
        LOG_DBG("CSlamController::OnTopicData copy packet\n");
        CCameraPacket* pNaviPacket = new CCameraPacket();
        pNaviPacket->m_Buffer.Write((const char*)(pPacket->m_Buffer.GetBuffer()), pPacket->m_Buffer.GetWriteOffset());
        pNaviPacket->m_TimeStamp = pPacket->m_TimeStamp;
        pTopicService->Publish(AL_SLAM, pNaviPacket);
    }
    LOG_INFO("CSlamController::OnTopicData exit\n");
    return E_OK;
}

void CSlamController::Run(void) {
    LOG_INFO("CSlamController::Run entry\n");
    CTopicService* pTopicService = CTopicService::GetInstance();
    while (m_bRunning) {
        CCameraPacket* pPacket = (CCameraPacket*)pTopicService->GetTopicMessage(AL_SLAM);
        if (NULL != pPacket) {
            const string strFrame(pPacket->m_Buffer.GetBuffer(), pPacket->m_Buffer.GetWriteOffset());
#ifndef __ANDROID_NDK__
            static int n = 1;
            string seq;
            stringstream ss;  
            ss<<n;  
            seq = ss.str();
            std::string origfile = "/opt/tomato/output/" + seq + ".jpg";
            std::ofstream write;
            write.open(origfile.c_str(), ios::out | ios::binary);
            write << strFrame;
            write.close();
            n++;
#endif
            CSlamAlgorithm::GetInstance()->Track(strFrame, pPacket->m_TimeStamp);
            delete pPacket; //Important
        }
        else {
            LOG_ERR("No data from queue\n");
        }
    }
}

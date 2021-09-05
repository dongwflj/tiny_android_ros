/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : SlamAlgorithm.h
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _SLAMALGORITHM_H_
#define _SLAMALGORITHM_H_

#include <string>
#include <vector>
#include "common/CommonDefine.h"

namespace ORB_SLAM2 {
class System;
}

class CSlamAlgorithm {
public:
    static CSlamAlgorithm* GetInstance() {
        static CSlamAlgorithm instance;
        return &instance;
    }
    // Required
    ERESULT Init(const std::string& strVocFile, const std::string strCameraSettingFile);
    ERESULT Close();
    ERESULT Track(const std::string& strFrame, const double timestamp);

    // Option
    /** 
    SYSTEM_NOT_READY=-1,
    NO_IMAGES_YET=0,
    NOT_INITIALIZED=1,
    OK=2,
    LOST=3
    */ 
    int TrackingState();
    ERESULT CameraPos(float& fX, float& fY, float& fAngle);
    void Reset();
    ERESULT MapPoint(std::vector<float>& vecX, std::vector<float>& vecZ);

    // Only for android ui use to return a Mat
    ORB_SLAM2::System* SystemInstance();
    void drawGL();

private:
    struct Object_Creator {
        Object_Creator() {
            CSlamAlgorithm::GetInstance();
        }
    };
    static Object_Creator _object_creator;
    CSlamAlgorithm();
    ~CSlamAlgorithm();
    ORB_SLAM2::System* m_pSlamInstance;
    bool m_bIsInit;
};

#endif

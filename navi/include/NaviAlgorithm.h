/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : NaviAlgorithm.h
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _NAVIALGORITHM_H_
#define _NAVIALGORITHM_H_

#include "common/CommonDefine.h"
#include "NaviRobot.h"

class CSlamController;
class CNaviAlgorithm {
public:
    static CNaviAlgorithm* GetInstance() {
        static CNaviAlgorithm instance;
        return &instance;
    }
    ERESULT Init();
    ERESULT Close();
    // Navi 
    ERESULT StartNavigation();
    ERESULT StopNavigation();
    ERESULT GetNaviNextPath(int& nStartX, int& nStartY, int& nEndX, int& nEndY);
    ERESULT GetNaviCameraPos(int& nX, int& nY, int& nAngle);
    ERESULT SetNaviTarget(int& nX, int& nY);
private:
    struct Object_Creator {
        Object_Creator() {
            CNaviAlgorithm::GetInstance();
        }
    };
    static Object_Creator _object_creator;

    CNaviAlgorithm();
    ~CNaviAlgorithm();
    int           m_nFinalTargetX;
    int           m_nFinalTargetY;
    int           m_nNextTargetX;
    int           m_nNextTargetY;
    CSlamController* m_pSlamController;
    CNaviRobot    m_Robot;
};

#endif

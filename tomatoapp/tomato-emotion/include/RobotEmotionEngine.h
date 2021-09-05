/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Last modified : 2018-01-25
 * Description   : 
 *********************************************************/

#ifndef _ROBOTEMOTIONENGINE_H_
#define _ROBOTEMOTIONENGINE_H_

#include "common/CommonDefine.h"

class CRobot;
class CRobotEmotionEngine {
public:
    static CRobotEmotionEngine* GetInstance() {
        static CRobotEmotionEngine instance;
        return &instance;
    }
    ERESULT Init();
    ERESULT Close();

    ERESULT Start();
    ERESULT Stop();

private:
    struct Object_Creator {
        Object_Creator() {
            CRobotEmotionEngine::GetInstance();
        }
    };
    static Object_Creator _object_creator;

    CRobotEmotionEngine();
    ~CRobotEmotionEngine();
    CRobot* m_pRobot;
};

extern "C" {  
    void RobotEmotionInit() {
        CRobotEmotionEngine::GetInstance()->Init();   
    }  
    void RobotEmotionStart() {
        CRobotEmotionEngine::GetInstance()->Start();   
    }  
}

#endif

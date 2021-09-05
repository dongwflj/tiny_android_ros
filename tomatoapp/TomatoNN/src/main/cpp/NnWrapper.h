/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         :
 * Filename      : NnWrapper.h
 * Last modified : 2018-01-25
 * Description   :
 *********************************************************/

#ifndef _NNWRAPPER_H_
#define _NNWRAPPER_H_

#include <string>
#include <vector>

namespace caffe2 {
    class NetDef;
    class Predictor;
}

class CNnWrapper {
public:
    static CNnWrapper* GetInstance() {
        static CNnWrapper instance;
        return &instance;
//        return nullptr;
    }
    void InitNn();
    std::string DetectAge(std::vector<float>& inputImg, int width, int height);
    std::string DetectEmotion(std::vector<float>& inputImg, int width, int height);
protected:
    struct Object_Creator {
        Object_Creator() {
            CNnWrapper::GetInstance();
        }
    };
    static Object_Creator _object_creator;
    CNnWrapper();
    ~CNnWrapper();
private:
    caffe2::NetDef* mInitNet;
    caffe2::NetDef* mPredictNet;
    caffe2::Predictor* mPredictor;
    bool mbIsInited;
    std::vector<std::string> mAgeList;
    std::vector<std::string> mEmotionList;
};

#endif


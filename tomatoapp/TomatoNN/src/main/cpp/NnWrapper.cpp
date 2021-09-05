/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         :
 * Filename      : NnWrapper.cpp
 * Last modified : 2018-01-25
 * Description   :
 *********************************************************/
#include "NnWrapper.h"
#include "caffe2/core/init.h"
#include "caffe2/utils/proto_utils.h"
#include "caffe2/core/flags.h"
#include "caffe2/core/operator.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <caffe2/core/predictor.h>


#define PROTOBUF_USE_DLLS 1
#define CAFFE2_USE_LITE_PROTO 1

using namespace caffe2;
using namespace std;

CNnWrapper::Object_Creator CNnWrapper::_object_creator;

CNnWrapper::CNnWrapper() : mbIsInited(false) {
}

CNnWrapper::~CNnWrapper() {
    if (NULL != mPredictor) {
        delete mPredictor;
        delete mPredictNet;
        delete mInitNet;
    }
}

void CNnWrapper::InitNn() {
    ///caffe2::GlobalInit(&argc, &argv);
    mInitNet = new NetDef();
    mPredictNet = new NetDef();
//    CAFFE_ENFORCE(ReadProtoFromFile("/sdcard/caffe2agemodel/init_net.pb", mInitNet));
//    CAFFE_ENFORCE(ReadProtoFromFile("/sdcard/caffe2agemodel/predict_net.pb", mPredictNet));
    CAFFE_ENFORCE(ReadProtoFromFile("/sdcard/caffe2emotion/init_net.pb", mInitNet));
    CAFFE_ENFORCE(ReadProtoFromFile("/sdcard/caffe2emotion/predict_net.pb", mPredictNet));
    //auto predicator = caffe2::make_unique<Predictor>(mInitNet, mPredictNet);
    mPredictor = new caffe2::Predictor(*mInitNet, *mPredictNet);
    mAgeList.push_back("(0, 2)");
    mAgeList.push_back("(2, 6)");
    mAgeList.push_back("(6, 12)");
    mAgeList.push_back("(12, 20)");
    mAgeList.push_back("(20, 32)");
    mAgeList.push_back("(32, 43)");
    mAgeList.push_back("(43, 53)");
    mAgeList.push_back("(53, 100)");

    mEmotionList.push_back("Angry");
    mEmotionList.push_back("Disgust");
    mEmotionList.push_back("Fear");
    mEmotionList.push_back("Happy");
    mEmotionList.push_back("Neutral");
    mEmotionList.push_back("Sad");
    mEmotionList.push_back("Surprise");
    mbIsInited = true;
}

string CNnWrapper::DetectAge(vector<float>& inputImg, int width, int height) {
    string ret;
    if (!mbIsInited) {
        return ret;
    }
    caffe2::TensorCPU input;
    input.Resize(std::vector<int>({1, 3, height, width}));
    input.ShareExternalPointer(inputImg.data());
    Predictor::TensorVector inputVec{ &input };
    Predictor::TensorVector outputVec;
    mPredictor->run(inputVec, &outputVec);
    float max_value = 0;
    int best_match_index = -1;
    // 迭代输出结果，output的大小就是网络输出的大小
    for (auto output : outputVec) {
        for (auto i = 0; i<output->size(); ++i) {
            // val对应的就是每一类的概率值
            float val = output->template data<float>()[i];
            if (val>0.001) {
                if (val>max_value) {
                    max_value = val;
                    best_match_index = i;
                }
            }
        }
    }
    if (0 <= best_match_index && best_match_index < 8) {
        ret = mAgeList[best_match_index];
    }
    return ret;
}

string CNnWrapper::DetectEmotion(vector<float>& inputImg, int width, int height) {
    string ret;
    if (!mbIsInited) {
        return ret;
    }

    caffe2::TensorCPU input;
    input.Resize(std::vector<int>({1, 3, height, width}));
    input.ShareExternalPointer(inputImg.data());
    Predictor::TensorVector inputVec{ &input };
    Predictor::TensorVector outputVec;
    mPredictor->run(inputVec, &outputVec);
    float max_value = 0;
    int best_match_index = -1;
    // 迭代输出结果，output的大小就是网络输出的大小
    for (auto output : outputVec) {
        for (auto i = 0; i<output->size(); ++i) {
            // val对应的就是每一类的概率值
            float val = output->template data<float>()[i];
            if (val>0.001) {
                if (val>max_value) {
                    max_value = val;
                    best_match_index = i;
                }
            }
        }
    }
    if (0 <= best_match_index && best_match_index < 7) {
        ret = mEmotionList[best_match_index];
    }
    return ret;
}
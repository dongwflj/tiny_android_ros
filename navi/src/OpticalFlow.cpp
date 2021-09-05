/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : OpticalFlow.cpp
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/

#include "OpticalFlow.h"
#include "common/CommonLog.h"
#include "util/topic/TopicService.h"
#include "protocol/CameraPacket.h"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

const std::string  AL_OPTICALFLOW = "al_opticalflow";

COpticalFlow::COpticalFlow() {
}

ERESULT COpticalFlow::Init() {
    LOG_INFO("COpticalFlow::Init Entry\n");
    CTopicService::GetInstance()->RegisterTopic(AL_OPTICALFLOW);
    CTopicService::GetInstance()->Subscribe(SYS_CAMERA,
                                            m_CameraObserver);
    LOG_INFO("COpticalFlow::Init Exit\n");
    return E_OK;
}

ERESULT COpticalFlow::Close() {
    return E_OK;
}

ERESULT COpticalFlow::Start() {
    LOG_INFO("COpticalFlow::Start Entry\n");
    StartThread();
    LOG_INFO("COpticalFlow::Start Exit\n");
    return E_OK;
}

ERESULT COpticalFlow::Stop() {
    LOG_INFO("COpticalFlow::Stop Entry\n");
    CancelThread();
    LOG_INFO("COpticalFlow::Stop Exit\n");
    return E_OK;
}

ERESULT COpticalFlow::GetNaviDecision(int& nLeft, int& nRight) {
    return E_OK;
}

ERESULT COpticalFlow::CTopicObserver::OnTopicData(void* pMessage, bool bNeedRelease) {
    LOG_INFO("COpticalFlow::OnTopicData entry");
    CTopicService* pTopicService = CTopicService::GetInstance();
    CCameraPacket* pPacket = (CCameraPacket*)pMessage;

    if (pTopicService->Size(AL_OPTICALFLOW) > 0) {
        CCameraPacket* pOld = (CCameraPacket*)(pTopicService->GetTopicMessageAsync(AL_OPTICALFLOW));
        delete pOld;
        LOG_INFO("Image process slow, replace with lastes data\n");
    }
    LOG_INFO("OPTICALFLOW topic size:" << pTopicService->Size(AL_OPTICALFLOW) << std::endl);

    if (bNeedRelease) {
        LOG_DBG("COpticalFlow::OnTopicData need release\n");
        pTopicService->Publish(AL_OPTICALFLOW, pPacket);
    }
    else {
        LOG_DBG("COpticalFlow::OnTopicData copy packet\n");
        CCameraPacket* pNaviPacket = new CCameraPacket();
        pNaviPacket->m_Buffer.Write((const char*)(pPacket->m_Buffer.GetBuffer()), pPacket->m_Buffer.GetWriteOffset());
        pNaviPacket->m_TimeStamp = pPacket->m_TimeStamp;
        pTopicService->Publish(AL_OPTICALFLOW, pNaviPacket);
    }
    LOG_INFO("COpticalFlow::OnTopicData exit\n");
    return E_OK;
}

void COpticalFlow::Run(void) {
    LOG_INFO("COpticalFlow::Run entry\n");
    CTopicService* pTopicService = CTopicService::GetInstance();
    TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03);
    Size subPixWinSize(10,10), winSize(31,31);

    Mat prevGray, image;
    bool needToInit = true;
    bool bUseViewer = false;
    vector<Point2f> points[3];
    while (m_bRunning) {
        vector<double> Left;
        vector<double> Right;
        vector<Point2f> LeftPoints;
        vector<Point2f> RightPoints;
        double dLeftAvg = 0;
        double dRightAvg = 0;
        int initSize = 0; 
        CCameraPacket* pPacket = (CCameraPacket*)pTopicService->GetTopicMessage(AL_OPTICALFLOW);
        if (NULL != pPacket) {
            const string strFrame(pPacket->m_Buffer.GetBuffer(), pPacket->m_Buffer.GetWriteOffset());
            std::vector<char> vec_data(strFrame.begin(), strFrame.end()); 
            cv::Mat gray = cv::imdecode(vec_data, CV_LOAD_IMAGE_GRAYSCALE); 
            cvtColor(gray, image, COLOR_GRAY2BGR, 3);

            if( needToInit )
            {
                // automatic initialization
                goodFeaturesToTrack(gray, points[1], 500, 0.01, 10, Mat(), 3, 0, 0.04);
                cornerSubPix(gray, points[1], subPixWinSize, Size(-1,-1), termcrit);
                LOG_INFO("Init done, size:" << points[1].size() << endl);
                points[2].clear();
                for(int i=0; i<points[1].size(); i++) {
                    points[2].push_back(points[1][i]);
                } 
                initSize = points[1].size();
                needToInit = false;
            }
            else if( !points[0].empty() )
            {
                vector<uchar> status;
                vector<float> err;
                if(prevGray.empty())
                    gray.copyTo(prevGray);
                calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize, 3, termcrit, 0, 0.001);
                size_t i, k;
                for( i = k = 0; i < points[1].size(); i++ )
                {
                    //circle( image, points[0][i], 2, Scalar(0, 0, 255), 1, 8);
                    if( !status[i] )
                        continue;

                    points[1][k++] = points[1][i];
                    ///line(image, points[2][i], points[1][i], Scalar(0,255,0));
                    double dist;
                    if (points[1][i].x < 160) {
                        dist = norm(points[0][i] - points[1][i]);
                        Left.push_back(dist);
                        LeftPoints.push_back(points[1][i]);
                        dLeftAvg += dist;
                    }
                    else {
                        dist = norm(points[0][i] - points[1][i]);
                        Right.push_back(dist);
                        RightPoints.push_back(points[1][i]);
                        dRightAvg += dist;
                    }
                    //circle( image, points[1][i], 5, Scalar(0,255,0), 1, 8);
                }
                dLeftAvg /= dLeftAvg/Left.size();
                dRightAvg /= dRightAvg/Right.size();
                points[1].resize(k);
                int nLeftObs=0, nRightObs=0;
                for (i=0; i<Left.size(); i++) {
                    if (Left[i] > dRightAvg * 0.5) {
                        circle( image, LeftPoints[i], 5, Scalar(0,0, 255), 1, 8);
                        nLeftObs++;
                    }
                    else {
                        circle( image, LeftPoints[i], 5, Scalar(0,255,0), 1, 8);
                    }
                }
                for (i=0; i<Right.size(); i++) {
                    if (Right[i] > dLeftAvg * 0.5) {
                        circle( image, RightPoints[i], 5, Scalar(0,0, 255), 1, 8);
                        nRightObs++;
                    }
                    else {
                        circle( image, RightPoints[i], 5, Scalar(0,255,0), 1, 8);
                    }
                }
                double scale;
                string direction;
                if (dLeftAvg < dRightAvg) {
                    scale = dLeftAvg / dRightAvg;
                    direction = "Go Left";
                }
                else {
                    scale = dRightAvg / dLeftAvg;
                    direction = "Go Right";
                }
                if (scale < 0.5) {
                    cout << "We should take action:" << direction << endl;
                }
                string txt = "L:" + to_string(nLeftObs) + " R:" + to_string(nRightObs) + " LSize:" + to_string(Left.size()) + " RSize:" + to_string(Right.size());
                cout << txt << endl;
                putText(image, txt, Point(5,15), FONT_HERSHEY_PLAIN, 1,
                        Scalar(255, 255, 0), 1, 8);
            }
            needToInit = false;
            imshow("LK Demo", image);
            if (points[1].size() <= initSize * 0.9) {
                needToInit = true;
            }
            std::swap(points[1], points[0]);
            cv::swap(prevGray, gray);
            delete pPacket; //Important
        }
        else {
            LOG_ERR("No data from queue\n");
        }
    }
}

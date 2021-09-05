/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : dongwflj@163.com
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/
#include <iostream>
#include <signal.h>
#include <cerrno>
#include <iomanip>

#include "common/CommonLog.h"
#include "common/CommonUtil.h"
#include "RobotServiceObserver.h"
#include "RobotEvent.h"

#include "core/RobotService.h"
#include "util/topic/TopicService.h"
#include "protocol/CameraPacket.h"

#include "RobotEmotionEngine.h"

using namespace std;

void
menu()
{
    cout <<
        "usage:\n"
        "g: start navigation\n"
        "h: stop navigation\n"
        "w: forward\n"
        "s: backward\n"
        "a: left\n"
        "d: right\n"
        "q: forwardleft\n"
        "e: forwardright\n"
        "z: backwardleft\n"
        "c: backwardright\n"
        "x: stop\n"
        "l: login\n"
        "v: it\n"
        "m: emotion\n"
        "b: exit\n"
        "?: help\n";
}

void RunTestData(CRobotService& robot) {
    FILE * fpPhoto;
    int    iRead ;
    char   szBuf[1000] ;
    CTopicService* pTopicService = CTopicService::GetInstance();
    for(int i=1; i<408; i++) {
        stringstream ss;
        ss << i; 
        //string file = "/root/work/output_my1/"+ ss.str() +".jpg";
        string file = "/opt/tomato/testdata/"+ ss.str() +".jpg";
        fpPhoto = fopen (file.c_str(), "rb") ;
        if (!fpPhoto) {
            cout << "Open file failed" << endl;
            return;
        }
        string buf;
        while ((iRead = fread (szBuf, 1,sizeof (szBuf), fpPhoto)) > 0) {
            buf.append(szBuf, iRead);
        }
        fclose(fpPhoto);
        CCameraPacket* pTask = new CCameraPacket();
        pTask->m_Buffer.Write((const char*)buf.c_str(), buf.length());
        double timestamp = (double)CCommonUtil::GetCurrentTime();
        pTask->m_TimeStamp = timestamp;
        cout << "Inputfile:" << file << " Buf len:" << buf.length() 
             << " TimeStamp:" << setiosflags(ios::fixed)<<setprecision(4) 
             << timestamp << endl;
        pTopicService->Publish(SYS_CAMERA, pTask);
        CCommonUtil::SleepMs(0, 100);
    }
}

int main(int argc, char **argv) {
    struct sigaction act;
    act.sa_handler = SIG_IGN;
    if(sigaction(SIGPIPE, &act, NULL) < 0) {
        return errno;
    }

    cout << "Start tomato..." << endl;
    /*CCommonLog& logger = CCommonLog::GetInstance();
    string logfile = "/opt/tomato/tomatoapp/etc/log4cplus.properties";
    if(!logger.OpenLogConfig(logfile.c_str(), "tomato")) {
        cerr << "Open log4 property file fail, server quit\n";
        return -1;
    }
    LOG_INFO("Start tomato...\n");*/
    CRobotServiceObserver observer;
    CRobotService robot(observer);
    robot.Init();
    CRobotEvent event;
    event.Init();
    menu();
    char c = 'b';
    do {
        cout << "==> ";
        cin >> c;
        switch (c) {
        case 'g': 
            cout << "Start navigation" << endl;
            robot.StartNavigation();
            break;
        case 'h':
            cout << "Stop navigation" << endl;
            robot.StopNavigation();
        	break;
        case 'w':
            cout << "Forward" << endl;
            robot.Move(0, 10, 127);
        	break;
        case 's':
            cout << "Backward" << endl;
            robot.Move(0, -10, 127);
        	break;
        case 'a':
            cout << "Left" << endl;
            robot.Move(90, 0, 127);
        	break;
        case 'd':
            cout << "Right" << endl;
            robot.Move(-90, 0, 127);
        	break;
        case 'q':
            cout << "ForwardLeft" << endl;
            robot.Move(90, 10, 127);
        	break;
        case 'e':
            cout << "ForwardRight" << endl;
            robot.Move(-90, 10, 127);
        	break;
        case 'z':
            cout << "BackwardLeft" << endl;
            robot.Move(270, 10, 127);
        	break;
        case 'c':
            cout << "BackwardRight" << endl;
            robot.Move(-270, 10, 127);
        	break;
        case 'x':
            cout << "Stop" << endl;
            robot.Move(0, 0, 0);
        	break;
        case 'l':
            robot.Login();
        	break;
        case 'v':
            RunTestData(robot);
            break;
        case 'b':
            break;
        case 'm': {
            CRobotEmotionEngine* pEngine = CRobotEmotionEngine::GetInstance();
            pEngine->Init();
            pEngine->Start();
            break;
        }
        case '?':
            menu();
        	break;
        default:
            cout << "unknown command `" << c << "'" << endl;
            menu();
        }
    }
    while(cin.good() && c != 'b');
    event.Close();
    robot.Close();
    return 0;
}

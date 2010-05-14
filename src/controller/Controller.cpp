/*
 * =====================================================================================
 *
 *       Filename:  Controller.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/09/2010 04:14:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "Controller.h"
#include "Configuration.h"
#include "Log.h"
#include "Database.h"
#include "Judger.h"
#include "CakeManager.h"
#include "../common/Packet.h"
#include "../common/Packet/CJConnectReply.h"
//#include "CakeManager.h"
#include <iostream>
#include <errno.h>
#include <string.h>

using namespace std;
using namespace Network;

int Controller::Init()
{
    if(Configuration::GetInstance().Init("./controller.conf"))
    {
        cerr<<"Configuration init failed!"<<endl;
        return -1;
    }
    Configuration &conf = Configuration::GetInstance();
    if(_log.Init(conf.logFile))
    {
        cerr<<"Log init failed!"<<endl;
        return -1;
    }
    if(Database::GetInstance().Init(conf.dbHost, conf.dbUsername, conf.dbPassword, conf.dbSchema))
    {
        cerr<<"Database init failed!"<<endl;
        return -1;
    }
    if(listener.OpenServerSocket(conf.listenPort))
    {
        cerr<<"Network init failed!"<<endl;
        return -1;
    }
    return 0;
}

int Controller::Loop()
{
    int maxfd;//max fd
    fd_set rset;
    JudgerManager &jm = JudgerManager::GetInstance();
    struct timeval tv;
    
    while(true)
    {
        //phase 1

        FD_ZERO(&rset);
        FD_SET(listener.GetSocketFd(), &rset);
        maxfd = listener.GetSocketFd();
        jm.PrepareFdset(&rset, maxfd);
        
        tv.tv_sec = TIME_PER_TICK / 1000;
        tv.tv_usec = TIME_PER_TICK % 1000;

        int ret = select(maxfd + 1, &rset, NULL, NULL, &tv);
        if(ret == -1)//select error
        {
            if(errno == EINTR)
            {
                Log("Select was interrupted.Continue looping.");
                //continue;
            }
            else//usually this means programing error
            {
                Log("Controller::Loop select error:%s", strerror(errno));
                return -1;
            }
        }
        else if(ret == 0)//timeout
        {
            //continue;
        }
        else
        {
            if(FD_ISSET(listener.GetSocketFd(), &rset))//new judger
            {
                //here we may be tricked
                JudgerManager &jm = JudgerManager::GetInstance();
                Judger *j = jm.NewJudger();
                //for now, we just accept one new judger per loop
                if(listener.Accept(j->GetSocketStream()) < 0)
                {
                    Log("Accept new judger failed.");
                    jm.RemoveJudger(j);
                    //retry
                }
            }
            jm.ProcessInput(&rset);
        }

        //phase 2
        CakeManager::GetInstance().Tick(); //load new cake from db

        //phase 3
        JudgerManager::GetInstance().Tick();//dispatch loaded cakes to judgers
    }

    return 0;
}

int Controller::CleanUp()
{
    listener.Close();
    return 0;
}

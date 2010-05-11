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
//#include "CakeManager.h"
#include <iostream>
#include <errno.h>

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
        FD_ZERO(&rset);
        FD_SET(listener.GetSocketFd(), &rset);
        maxfd = listener.GetSocketFd();
        jm.PrepareFdset(&rset, maxfds);
        
        tv.tv_sec = TIME_PER_TICK / 1000;
        tv.tv_usec = TIME_PER_TICK % 1000;

        int ret = select(maxfd + 1, &rset, NULL, NULL, &tv);
        if(ret == -1)//select error
        {
            if(errno == EINTR)
                continue;
            else
            {
                Log("Controller::Loop select error:%s", strerror(errno));
                return -1;
            }
        }
        else if(ret == 0)//timeout
        {
            continue;
        }
        else
        {
            if(FD_ISSET(listener.GetSocketFd(), &rset))//new judger
            {

            }
            jm.ProcessInput(&rset);
        }
    }

    return 0;
}

int Controller::CleanUp()
{
    return 0;
}

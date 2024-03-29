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
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

using namespace std;
using namespace Network;

int Controller::Init()
{
    cerr<<"Initing config file..."<<endl;
    if(Configuration::GetInstance().Init("./controller.conf"))
    {
        cerr<<"Configuration init failed!"<<endl;
        return -1;
    }
    cerr<<"Init done."<<endl;

    cerr<<"Initing log..."<<endl;
    Configuration &conf = Configuration::GetInstance();
    if(_log.Init(conf.logFile))
    {
        cerr<<"Log init failed!"<<endl;
        return -1;
    }
    cerr<<"Init done."<<endl;

    cerr<<"Initing database..."<<endl;
    if(Database::GetInstance().Init(conf.dbHost, conf.dbUsername, conf.dbPassword, conf.dbSchema))
    {
        cerr<<"Database init failed!"<<endl;
        return -1;
    }
    cerr<<"Init done."<<endl;

    cerr<<"Initing network..."<<endl;
    if(listener.OpenServerSocket(conf.listenPort))
    {
        cerr<<"Network init failed!"<<endl;
        return -1;
    }
    cerr<<"Init done."<<endl;

    return 0;
}

int Controller::Loop()
{
    int maxfd;//max fd
    fd_set rset;
    JudgerManager &jm = JudgerManager::GetInstance();
    struct timeval tv;
    
    while(!bStopped)
    {
        //phase 1

        FD_ZERO(&rset);
        FD_SET(listener.GetSocketFd(), &rset);
        maxfd = listener.GetSocketFd();
        jm.PrepareFdset(&rset, maxfd);
        
        tv.tv_sec = TIME_PER_TICK / 1000;
        tv.tv_usec = TIME_PER_TICK % 1000 * 1000;

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
            //Log("Controller::Loop No new packet arrives.");
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
                else
                {
                    const sockaddr_in &addr = j->GetSocketStream().GetClientAddr();
                    Log("New judger comes.IP=%s Port=%d", inet_ntoa(addr.sin_addr), addr.sin_port);
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
    //handler cakes which are not completely judged
    JudgerManager::GetInstance().OnClose();
    CakeManager::GetInstance().OnClose();

    Database::GetInstance().Close();
    return 0;
}

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
#include <iostream>

using namespace std;
using namespace Network;

int Controller::Init()
{
    if(Configuration::GetInstance().Init())
    {
        cerr<<"Configuration init failed!"<<endl;
        return -1;
    }
    Configuration &conf = Configuration::GetInstance();
    if(_log.Init(conf.LogFile))
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

}

int Controller::CleanUp()
{

}

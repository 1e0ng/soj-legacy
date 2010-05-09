/*
 * =====================================================================================
 *
 *       Filename:  Configuration.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2010 08:00:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "Configuration.h"
#include "../common/IniFile.h"
#include <iostream>
using namespace std;

Configuration::Configuration()
{
    CleanUp();
}

int Configuration::Init()
{
    string conf_path = "./controller.conf";
    IniFile ini;
    if(ini.InitFromFile(conf_path.c_str()))
    {
        char buf[512];
        if(ini.GetStringValue("Controller", "DBHost", buf, sizeof(buf)))
        {
            dbHost = buf;
        }
        else
        {
            cerr<<"Read key Controller::DBHost failed!"<<endl;
            return -1;
        }

        if(ini.GetStringValue("Controller", "DBUsername", buf, sizeof(buf)))
        {
            dbUsername = buf;
        }
        else
        {
            cerr<<"Read key Controller::DBUsername failed!"<<endl;
            return -1;
        }

        if(ini.GetStringValue("Controller", "DBPassword", buf, sizeof(buf)))
        {
            dbPassword = buf;
        }
        else
        {
            cerr<<"Read key Controller::DBPassword failed!"<<endl;
            return -1;
        }

        if(ini.GetStringValue("Controller", "DBSchema", buf, sizeof(buf)))
        {
            dbSchema = buf;
        }
        else
        {
            cerr<<"Read key Controller::DBSchema failed!"<<endl;
            return -1;
        }

        if(ini.GetStringValue("Controller", "LogFile", buf, sizeof(buf)))
        {
            logFile = buf;
        }
        else
        {
            cerr<<"Read key Controller::LogFile failed!"<<endl;
            return -1;
        }

        int val;
        if(ini.GetIntValue("Controller", "ServerPort", val))
        {
            listenPort = (short)val;
        }
        else
        {
            cerr<<"Read key Controller::ServerPort failed!"<<endl;
            return -1;
        }
        return 0;
    }
    else 
    {
        cerr<<"Configuration::Init() failed!"<<endl;
        return -1;
    }
}

void Configuration::CleanUp()
{
    dbHost = "";
    dbUsername = "";
    dbPassword = "";
    dbSchema = "";

    logFile = "";
}

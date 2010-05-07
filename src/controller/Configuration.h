/*
 * =====================================================================================
 *
 *       Filename:  Configuration.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2010 08:00:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

struct Configuration
{
public:
    std::string dbHost;
    std::string dbUsername;
    std::string dbPassword;
    std::string dbSchema;
    
    std::string logFile;

    static Configuration &GetInstance()
    {
        static Configuration instance;
        return instance;
    }
    int Init();
    void CleanUp();
private:
    Configuration();
    Configuration &operator=(const Configuration &);
    Configuration(const Configuration &);
};

#endif

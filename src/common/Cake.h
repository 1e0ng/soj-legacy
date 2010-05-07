/*
 * =====================================================================================
 *
 *       Filename:  Cake.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2010 03:17:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
/* each submit is as a cake */
#ifndef CAKE_H
#define CAKE_H

#ifdef _CONTROLLER
#include "../controller/Database.h"
#endif

struct Cake
{
public:
    const static int MAX_SOURCE_LENGTH = 65536;

    int rid;//run id
    int pid;//problem id
    int language;//code language
    int rtime;//run time usage
    int rmemory;//run memory usage
    int timeLimit;//time limit for rtime
    int memoryLimit;//memory limit for rmemory
    int uid;//user id
    char sourceCode[65536];

    Cake(){CleanUp();}
    void CleanUp();

#ifdef _JUDGER
    //judger need to store the source code
    int storeSourceCode(const char *path);
#endif

#ifdef _CONTROLLER
    int LoadFromDB(Database *db);
    //update judge status, user related data and problem related data such as accepted number
    int UpdateDB(Database *db);
#endif
};

#endif

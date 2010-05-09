/*
 * =====================================================================================
 *
 *       Filename:  CakeManager.h
 *
 *    Description:  Manage  cakes being judged
 *
 *        Version:  1.0
 *        Created:  05/07/2010 06:39:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef CAKE_MANAGER_H
#define CAKE_MANAGER_H

#include "Database.h"
#include <bitset>

//manage cakes just fetched from db and waiting for dispatching to specific judger
//once dispatched, remove it immediately
class CakeManager
{
public:
    const static int MAX_CAKE_NUMBER = 64;

    CakeManager():head(0), tail(0){}
    ~CakeManager();

    //dispatch one, release one
    Cake *GetCakeToJudge();
    void ReleaseCake(Cake *cake);

    void Tick();
private:
    //called by Tick()
    int LoadCakes(Database *db);
private:
    Cake cake[MAX_CAKE_NUMBER];
    size_t head;
    size_t tail;
};

#endif

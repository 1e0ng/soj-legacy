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
#include "../common/Cake.h"

//manage cakes just fetched from db and waiting for dispatching to specific judger
//once dispatched, remove it immediately
class CakeManager
{
public:
    const static int MAX_CAKE_NUMBER = 64;

    static CakeManager &GetInstance()
    {
        static CakeManager instance;
        return instance;
    }
    //dispatch one, release one
    Cake *GetCakeToJudge();
    void ReleaseCake(Cake *cake);
    //no judger for current cake,so return it
    void ReturnCake(Cake *cake);

    //sometime judge exited unexpectedly during judging
    //so we need to restore it and leave it to some other judger
    //here we make it back to status JR_QUEUEING
    void RestoreCake(int rid, Database *db);

    void Tick();

    void OnClose();
private:
    //called by Tick()
    int LoadCakes(Database *db);
private:
    CakeManager():head(0), tail(0){}
    ~CakeManager();
    CakeManager(const CakeManager &);
    CakeManager &operator=(const CakeManager &);

    Cake cake[MAX_CAKE_NUMBER];
    size_t head;
    size_t tail;
};

#endif

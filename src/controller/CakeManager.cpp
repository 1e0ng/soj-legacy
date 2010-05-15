/*
 * =====================================================================================
 *
 *       Filename:  CakeManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2010 06:57:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "CakeManager.h"
#include "Log.h"
#include "../common/OJDefine.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

CakeManager::~CakeManager()
{
    head = tail = 0;
    for(int i = 0; i < MAX_CAKE_NUMBER; i++)
        cake[i].CleanUp();
}

Cake *CakeManager::GetCakeToJudge()
{
    if(tail >= head)//it's empty
    {
        //LoadCakes();
        
        //if(tail >= head)//no new submit?
        return NULL;
    }
    return &cake[tail++];
}

void CakeManager::ReturnCake(Cake *cake)
{
    tail--;
    assert( &cake[tail] == cake );
}

void CakeManager::ReleaseCake(Cake *cake)
{
    assert(cake);
    //maybe we should add some check here
    cake->CleanUp();
}

int CakeManager::LoadCakes(Database *db)
{
    assert(db);

    //reset pointers
    head = tail = 0;

    MYSQL_RES *res;
    if(db->Query("select rid, status.pid, language, sourceCode, uid, timeLimit,memoryLimit\
            from status,problem where judgeStatus=1 and status.pid=problem.pid order by rid", &res) < 0)
    {
        Log("CakeManager::LoadCakes failed!");
        return -1;
    }
    MYSQL_ROW row;
    bool flag = false;

    while((row = mysql_fetch_row(res)))
    {
        if(head >= MAX_CAKE_NUMBER)
        {
            Log("CakeManager::LoadCakes Cake pool is fool.Let me have a rest and wait for those lazy judgers.");
            break;
        }
        flag = true;

        Cake &c = cake[ head++ ];

        c.rid = atoi(row[0]);
        c.pid = atoi(row[1]);
        c.language = atoi(row[2]);
        c.uid = atoi(row[4]);
        c.timeLimit = atoi(row[5]);
        c.memoryLimit = atoi(row[6]);
        strncpy(c.sourceCode, row[3], Cake::MAX_SOURCE_LENGTH);
        Log("CakeManager::Loadcakes load cake with rid = %d successfully.", c.rid);

        char buf[256];
        snprintf(buf, sizeof(buf), "update status set judgeStatus=%d where rid = %d", JR_JUDGING, c.rid);
        if(db->Query(buf, NULL) != 1)
        {
            Log("CakeManager::Loadcakes update cake with rid = %d to status JUDGING failed!", c.rid);
        }
    }
    if(!flag)
    {
        Log("CakeManager::Loadcakes no cakes for present.");
    }
    mysql_free_result(res);

    return head;
}

void CakeManager::RestoreCake(int rid, Database *db)
{
    assert(rid >= 0);
    assert(db);

    Log("CakeManager::RestoreCake Restoring cake with rid = %d", rid);
    char buf[128];
    snprintf(buf, sizeof(buf), "update status set judgeStatus=%d where rid = %d", JR_QUEUEING, rid);
    if(db->Query(buf) != 1)
    {
        Log("CakeManager::RestoreCake update db error.");
    }
    else
    {
        Log("CakeManager::RestoreCake Restore cake with rid = %d successfully", rid);
    }
}

void CakeManager::Tick()
{
    //so we just load new cakes when all cakes are sent out
    if((tail == head) )
        LoadCakes(&Database::GetInstance());
}

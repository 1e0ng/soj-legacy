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
#include <stdlib.h>
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

void CakeManager::ReleaseCake(Cake *cake)
{
    //maybe we should add some check here
    cake->CleanUp();
}

int CakeManager::LoadCakes(Database *db)
{
    assert(db);

    //reset pointers
    head = tail = 0;

    MYSQL_RES *res;
    if(db->Query("select rid,pid,language,sourceCode,uid,timeLimit,memoryLimit\
            from status,problem where judgeStatus=1 and status.pid=prolbem.pid order by rid", &res) < 0)
    {
        Log("CakeManager::LoadCakes failed!");
        return -1;
    }
    MYSQL_ROW *row;

    while(row = mysql_fetch_row(res))
    {
        if(head >= MAX_CAKE_NUMBER)
            break;
        Cake &c = cake[ head++ ];

        c.rid = atoi(row[0]);
        c.pid = atoi(row[1]);
        c.language = atoi(row[2]);
        c.uid = atoi(row[4]);
        c.timeLimit = atoi(row[5]);
        c.memoryLimit = atoi(row[6]);
        strncpy(c.sourceCode, row[3], Cake::MAX_SOURCE_LENGTH);
        Log("CakeManager::Loadcs load cake with rid = %d successfully.", c.rid);

        char buf[256];
        snprintf(buf, sizeof(buf), "update status set judgeStatus=2 where rid = %d", c.rid);
        if(db->Query(buf, NULL) != 1)
        {
            Log("Cake::Loadcs update cake with rid = %d to status JUDGING failed!", c.rid);
        }
    }
    mysql_free_result(res);

    return head;
}

void CakeManager::Tick()
{
    //so we just load new cakes when all cakes are sent out
    if((tail == head) )
        LoadCakes();
}

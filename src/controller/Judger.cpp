/*
 * =====================================================================================
 *
 *       Filename:  Judger.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2010 03:25:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "../common/Packet.h"
#include "Judger.h"
#include <assert.h>

static int JudgerManager::JudgerIndexer = 1;

Judger::Judger()
{
    judgerId = -1;
    status = INVALID;
    lastStartJudgeTime = 0;
    pidJudging = -1;
}

Judger::~Judger()
{
    judgerId = -1;
    status = INVALID;
    lastStartJudgeTime = 0;
    pidJudging = -1;

    stream.Close();
}

int Judger::SendPacket(Packet *packet)
{
    return 0;
}

int Judger::ReceivePacket()
{
    return 0;
}

JudgerManager::JudgerManager()
{
    size = 0;
    nextPos = 0;
    for(int i = 0; i < MAX_JUDGER_NUMBER; i++)
        judger[i] = NULL;
    for(Language i = 0; i < LAN_NUMBER; i++)
        supportedLan[i] = false;
}

JudgerManager::~JudgerManager()
{
    for(int i = 0; i < size; i++)
    {
        if(judger[i])delete judger[i],judger[i] = NULL;
    }
    size = 0;

    for(Language i = 0; i < LAN_NUMBER; i++)
        supportedLan[i] = false;
}

Judger *JudgerManager::NewJudger()
{
    assert(size < MAX_JUDGER_NUMBER);

    Judger *j = (judger[size++] = new Judger);
    assert(j);
    j->SetJudgerId(JudgerIndexer++);
    return j;
}

void JudgerManager::RemoveJudger(int jid)
{
    for(size_t i = 0; i < size; i++)
    {
        if(judger[i].GetJudgerId() == jid)
        {
            delete judger[i];
            if(size >= 2)
                judger[i] = judger[size - 1];
            judger[size - 1] = NULL;
            size--;
            break;
        }
    }
}

void JudgerManager::RemoveJudger(Judger *j)
{
    for(size_t i = 0; i < size; i++)
    {
        if(judger[i] == j)
        {
            delete judger[i];
            if(size >= 2)
                judger[i] = judger[size - 1];
            judger[size - 1] = NULL;
            size--;
            break;
        }
    }
}

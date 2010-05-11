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

int JudgerManager::JudgerIndexer = 1;

Judger::Judger()
{
    judgerId = -1;
    status = INVALID;
    lastStartJudgeTime = 0;
    pidJudging = -1;
    for(int i = 0; i < LAN_NUMBER; i++)
        supportedLan[i] = false;
}

Judger::~Judger()
{
    judgerId = -1;
    status = INVALID;
    lastStartJudgeTime = 0;
    pidJudging = -1;
    for(int i = 0; i < LAN_NUMBER; i++)
        supportedLan[i] = false;

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
    for(int i = 0; i < MAX_JUDGER_NUMBER; i++)
        judger[i] = NULL;
}

JudgerManager::~JudgerManager()
{
    for(size_t i = 0; i < size; i++)
    {
        if(judger[i])delete judger[i],judger[i] = NULL;
    }
    size = 0;
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
    assert(j >= 1);

    for(size_t i = 0; i < size; i++)
    {
        if(judger[i]->GetJudgerId() == jid)
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
    if(j == NULL)
        return;
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

void JudgerManager::PrepareFdset(fd_set *rset, int &maxfd)
{
    if(rset == NULL)
        return;
    for(size_t i = 0; i < size; i++)
    {
        int fd = judger[i]->GetSocketFd();
        FD_SET(fd, rset);
        if(fd > maxfd)
            maxfd = fd;
    }
}


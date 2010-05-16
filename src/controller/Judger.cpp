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
#include "../common/Packet/CJJudgeThis.h"
#include "Judger.h"
#include "Log.h"
#include "CakeManager.h"
#include <assert.h>
#include <stdio.h>
#include <errno.h>

int JudgerManager::JudgerIndexer = 1;

Judger::Judger()
{
    judgerId = -1;
    status = INVALID;
    cake.CleanUp();

    for(int i = 0; i < LAN_NUMBER; i++)
        supportedLan[i] = false;
}

Judger::~Judger()
{
    judgerId = -1;
    status = INVALID;
    cake.CleanUp();

    for(int i = 0; i < LAN_NUMBER; i++)
        supportedLan[i] = false;
}

int Judger::Judge(const Cake &c)
{
    assert(IsAvailable());

    status = BUSY;

    cake.CleanUp();
    cake.rid = c.rid;
    cake.uid = c.uid;
    cake.pid = c.pid;
    cake.beginTime = time(NULL);

    CJJudgeThis packet;
    packet.SetCake(c);
    SendPacket(&packet);
    return 0;
}

int Judger::ProcessInput()
{
    Packet *packet = NULL;
    try
    {
        for(int i = 0; i < MAX_PACKETS_PER_TICK; i++)
        {
            packet = ReceivePacket();
            if(packet)
            {
                packet->Execute(this);
                delete packet;
                packet = NULL;
            }
            else
            {
                break;
            }
        }
    }
    catch(...)
    {
        if(packet)
            delete packet;
        throw;
    }

    return 0;
}

int Judger::ProcessOutput()
{
    return 0;
}

int Judger::SendPacket(Packet *packet)
{
    assert(packet);

    packet->Write(stream);
    Log("Judger::SendPacket Sent packet (type = %d)successfully.", packet->GetPacketType());

    return 0;
}

Packet *Judger::ReceivePacket()
{
    int ret, type;
    Packet *packet = NULL;

    if((ret = stream.PeekInt(type)) != sizeof(int) || type < 0 || type >= MAX_PACKET_ID)
    {
        if(ret == 0)
        {
            throw ConnectionEOFException();
        }
        else if(ret == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
        {
            return NULL;
        }
        else
        {
            Log("Judger::ReceivePacket %s.Type = %d", strerror(errno), type);
            throw NetworkException();
            assert(false);
        }
    }
    else
    {
        packet = PacketFactoryManager::GetInstance().GetPacketFactory(type)->GetPacket();
        assert(packet);
        packet->Read(stream);

        Log("Judger::ReceivePacket Packet (type = %d) received successfully.", type);
    }
    return packet;
}

int Judger::UpdateCakeToDB(const CakeReturn &cr, Database *db)
{
    assert(db);
    //it would be better if we use transaction

    char tmp[512];
	//int acceptedPro,submittedPro;
	if(cr.result == JR_AC || cr.result == JR_WA || cr.result == JR_PE)
    {
        //The code has been AC,or WA, or PE
		snprintf(tmp, sizeof(tmp), "update status set judgeStatus=%d, rtime=%d, rmemory=%d where rid=%d", cr.result, cr.rtime, cr.rmemory, cake.rid);
		if(db->Query(tmp, NULL) != 1)
        {
            Log("Judger::UpdateCakeToDB can't update status where rid = %d", cake.rid);
			return -1;
		}
	}
	else
    {
		snprintf(tmp, sizeof(tmp), "update status set judgeStatus=%d, rtime=null,rmemory=null where rid=%d", cr.result, cake.rid);
		if(db->Query(tmp, NULL) != 1)
        {
            Log("Judger::UpdateCakeToDB can't update status where rid = %d", cake.rid);
			return -1;
		}
	}
	if(cr.result == JR_AC)
    {
        //The code has been accpeted!
		snprintf(tmp, sizeof(tmp), "update problem set accepted=accepted+1 where pid=%d",cake.pid);
		if(db->Query(tmp, NULL) != 1)
        {
            Log("Judger::UpdateCakeToDB can't update problem where pid = %d", cake.pid);
			return -1;
		}
		snprintf(tmp, sizeof(tmp), "update user set accepted=accepted+1 where uid=%d",cake.uid);
		if(db->Query(tmp, NULL) != 1)
        {
            Log("Judger::UpdateCakeToDB can't update user where pid = %d", cake.pid);
			return -1;
		}
	}   
    Log("Judger::UpdateCakeToDB update status with rid = %d successfully.", cake.rid);
    return 0;
}

JudgerManager::JudgerManager()
{
    size = 0;
    indexer = 0;
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
    indexer = 0;
}

int Judger::InitFromPacket(JCConnect *packet)
{
    assert(packet);

    //temporary
    for(int i = 0; i < 3; i++)
        supportedLan[i] = true;
    status = AVAILABLE;
    return 0;
}

Judger *JudgerManager::NewJudger()
{
    assert(size < MAX_JUDGER_NUMBER);

    Judger *j = (judger[size++] = new Judger);
    assert(j);
    j->SetJudgerId(JudgerIndexer++);
    j->SetStatus(Judger::INITIALIZING);
    return j;
}

void JudgerManager::RemoveJudger(int jid)
{
    assert(j >= 1);

    for(size_t i = 0; i < size; i++)
    {
        if(judger[i]->GetJudgerId() == jid)
        {
            DoRemoveJudger(i);
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
            DoRemoveJudger(i);
            break;
        }
    }
}

void JudgerManager::DoRemoveJudger(int index)
{
    delete judger[index];
    if(size >= 2)
        judger[index] = judger[size - 1];
    judger[size - 1] = NULL;
    size--;
}

Judger *JudgerManager::GetAvailableJudgerFor(int lan)
{
    assert(lan <= LAN_MAX_ID && lan >= LAN_MIN_ID);

    for(size_t i = 0; i < size; i++)
    {
        size_t j = indexer + i;
        j = (j >= size? j - size: j);
        if(judger[i]->IsAvailable() && judger[i]->IsLanguageSupported(lan))
            return judger[i];
    }
    return NULL;
}

void JudgerManager::PrepareFdset(fd_set *rset, int &maxfd)
{
    if(rset == NULL)
        return;
    for(size_t i = 0; i < size; i++)
    {
        int fd = judger[i]->GetSocketStream().GetSocketFd();
        FD_SET(fd, rset);
        if(fd > maxfd)
            maxfd = fd;
    }
}

int JudgerManager::ProcessInput(fd_set *rset)
{
    assert(rset);

    for(size_t i = 0; i < size; i++)
    {
        if(FD_ISSET(judger[i]->GetSocketStream().GetSocketFd(), rset))
        {
            try
            {
                judger[i]->ProcessInput();
            }
            catch(NetworkException &e)
            {
                Log("JudgerManager::ProcessInput Network error:%s ,judger id = %d. Remove it now.", 
                        e.What(), judger[i]->GetJudgerId());
                if(judger[i]->GetStatus() == Judger::BUSY)
                    CakeManager::GetInstance().RestoreCake(judger[i]->GetRidJudging(), &Database::GetInstance());
                RemoveJudger(judger[i]);
                //Remove judger will cause size minus 1
                --i;
            }
        }
    }
    return 0;
}

void JudgerManager::Tick()
{
    CakeManager &cm = CakeManager::GetInstance();
    for(size_t i = 0; i < size; i++)
    {
        Cake *c = cm.GetCakeToJudge();
        if(c == NULL)//no cakes
        {
            //Log("JudgerManager::Tick No new cake to judge.");
            break;
        }

        Judger *j = GetAvailableJudgerFor(c->language);
        if( j == NULL)
        {
            Log("JudgerManager::Tick All judgers are busy judging so save for next loop to process.");
            cm.ReturnCake(c);
            break;
        }

        Log("JudgerManager::Tick dispatch cake %d to judger %d", c->rid, j->GetJudgerId());

        try
        {
            j->Judge(*c);
            cm.ReleaseCake(c);
        }
        catch(NetworkException &e)
        {
            Log("JudgerManager::Tick Network error:%s ,judger id = %d. Remove it now.", 
                    e.What(), judger[i]->GetJudgerId());
            if(judger[i]->GetStatus() == Judger::BUSY)
                CakeManager::GetInstance().RestoreCake(judger[i]->GetRidJudging(), &Database::GetInstance());
            RemoveJudger(judger[i]);
        }

    }
    //here add some other stuff such as check how much time each judger has spent and to determine whether they are alive
}

void JudgerManager::OnClose()
{
    CakeManager &cm = CakeManager::GetInstance();
    Database *db = &Database::GetInstance();
    for(size_t i = 0; i < size ; i++)
    {
        if(judger[i]->GetStatus() == Judger::BUSY)
        {
             cm.RestoreCake(judger[i]->GetRidJudging(), db);
        }
    }
}

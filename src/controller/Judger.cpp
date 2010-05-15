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
    cake.CleanUp();
    cake.rid = c.rid;
    cake.uid = c.uid;
    cake.pid = c.pid;
    cake.beginTime = time(NULL);

    CJJudgeThis packet;
    packet.SetCake(c);
    if(SendPacket(&packet) < 0)
    {
        Log("Judger::Judge SendPacket error. JudgerId = %d, SysError: %s", judgerId, strerror(errno));
        return -1;
    }
    return 0;
}

int Judger::ProcessInput()
{
    for(int i = 0; i < MAX_PACKETS_PER_TICK; i++)
    {
        Packet *packet = ReceivePacket();
        if(packet)
        {
            Log("Judger::ProcessInput Judger %d is process packet (type = %d)", judgerId, packet->GetPacketType());
            packet->Execute(this);
            delete packet;
        }
        else
        {
            break;
        }
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

    Log("Judger::SendPacket Sending packet...");
    int ret = packet->Write(stream);
    if(ret < 0)
    {
        Log("Judger::SendPacket Write packet error %s", strerror(errno));
        return -1;
    }
    else
    {
        Log("Judger::SendPacket Sent successfully.");
        return 0;
    }
}

Packet *Judger::ReceivePacket()
{
    int ret, type;
    Packet *packet = NULL;

    if((ret = stream.PeekInt(type)) != sizeof(int) || type < 0 || type >= MAX_PACKET_ID)
    {
        if(ret == 0)
        {
            //we encounter an EOF
            Log("Judger::ReceivePacket Client closed connection.Remove judger %d", judgerId);
            JudgerManager::GetInstance().RemoveJudger(this);
            status = INVALID;
        }
        else if(ret == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
        {
            return NULL;
        }
        else
        {
            Log("Judger::ReceivePacket %s", strerror(errno));
            assert(false);
        }
    }
    else
    {
        Log("Judger::ReceivePacket receiving packet (type = %d)", type);
        packet = PacketFactoryManager::GetInstance().GetPacketFactory(type)->GetPacket();
        assert(packet);
        /*
        char buf[1024];
        if((ret = stream.Peek(buf, packet->GetPacketSize()) != packet->GetPacketSize()))
        {
            //maybe this is because data is still being received.
            //
            Log("Packet size is not as expected.Received: %d, expected: %d, judger: %d", ret, packet->GetPacketSize(), jid);
            break;
        }
        else
        {
        */
        if(packet->Read(stream))
        {
            Log("Judger::ReceivePacket Read error %s", strerror(errno));
            delete packet;
            packet = NULL;
        }
        else
        {
            Log("Judger::ReceivePacket Packet received successfully.");
        }
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
		if(db->Query(tmp, NULL))
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
            judger[i]->ProcessInput();
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
            break;

        Judger *j = GetAvailableJudgerFor(c->language);
        if( j == NULL)
        {
            cm.ReturnCake(c);
            break;
        }

        Log("JudgerManager::Tick dispatch cake %d to judger %d", c->rid, j->GetJudgerId());
        j->Judge(*c);

        cm.ReleaseCake(c);
    }
    //here add some other stuff such as check how much time each judger has spent and to determine whether they are alive
}

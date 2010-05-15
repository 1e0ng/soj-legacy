/*
 * =====================================================================================
 *
 *       Filename:  PacketHandler.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/11/2010 05:12:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "../common/Packet/CJJudgeThis.h"
#include "../common/Packet/CJConnectReply.h"
#include "../common/Packet/JCConnect.h"
#include "../common/Packet/JCJudgeThisReturn.h"
#include "Judger.h"
#include "Log.h"
#include <assert.h>

using namespace Network;

int CJJudgeThis::Execute(PacketPlayer *player)
{
    return PER_PACKET_CONTINUE;
}

int CJConnectReply::Execute(PacketPlayer *player)
{
    return PER_PACKET_CONTINUE;
}

int JCConnect::Execute(PacketPlayer *player)
{
    assert(player);

    Judger *j = dynamic_cast<Judger *>(player);
    if(j)
    {
        Log("JCConnect::Execute Init judger %d", j->GetJudgerId());

        j->InitFromPacket(this);
        CJConnectReply packet;
        packet.SetReply(CJConnectReply::ACCEPTED);
        packet.SetJudgerId(j->GetJudgerId());
        j->SendPacket(&packet);
    }
    else
    {
        Log("JCConnect::Execute Invalid player!");
    }
    return PER_PACKET_CONTINUE;
}

int JCJudgeThisReturn::Execute(PacketPlayer *player)
{
    assert(player);

    Judger *j = dynamic_cast<Judger *>(player);
    if(j)
    {
        int jid = GetJudgerId();
        if(jid != j->GetJudgerId())
        {
            Log("JCJudgeThisReturn::Execute judger ids are not the same.Expected ID = %d, ID from packet = %d", j->GetJudgerId(), jid);
            return PER_PACKET_CONTINUE;
        }
        int rid = GetRid();
        if(rid != j->GetRidJudging())
        {
            Log("JCJudgeThisReturn::Execute run ids are not the same.Expected ID = %d, ID from packet = %d", j->GetRidJudging(), rid);
            return PER_PACKET_CONTINUE;
        }
        int status = GetResult();
        if(status < 0 || status >= JR_RESULT_NUMBER)
        {
            Log("JCJudgeThisReturn::Execute status invalid. value = %d", status);
            return PER_PACKET_CONTINUE;
        }
        Log("Judger %d judges cake %d complete. Result: %d", jid, rid, status);
        j->UpdateCakeToDB(cr, &Database::GetInstance());
        j->SetStatus(Judger::AVAILABLE);
    }
    else
    {
        Log("JCJudgeThisReturn::Execute Invalid player!");
    }
    return PER_PACKET_CONTINUE;
}

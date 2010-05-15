/*
 * =====================================================================================
 *
 *       Filename:  PacketHandler.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/11/2010 05:16:49 PM
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
#include "Log.h"
#include "Judger.h"
#include <assert.h>

using namespace Network;

int CJJudgeThis::Execute(PacketPlayer *player)
{
    assert(player);

    Judger *j = dynamic_cast<Judger *>(player);
    if(j)
    {
        j->DoJudge(cake); 
    }
    else
    {
        log(Log::ERROR)<<"player can't be cast Judger!"<<endlog;
        assert(false);
    }

    return PER_PACKET_CONTINUE;
}

int CJConnectReply::Execute(PacketPlayer *player)
{
    assert(player);

    Judger *j = dynamic_cast<Judger *>(player);
    if(j)
    {
        j->SetJudgerId(judgerId);
    }
    else
    {
        log(Log::ERROR)<<"player can't be cast to Judger!"<<endlog;
        assert(false);
    }
    return PER_PACKET_CONTINUE;
}

int JCConnect::Execute(PacketPlayer *player)
{
    return PER_PACKET_CONTINUE;
}

int JCJudgeThisReturn::Execute(PacketPlayer *player)
{
    return PER_PACKET_CONTINUE;
}

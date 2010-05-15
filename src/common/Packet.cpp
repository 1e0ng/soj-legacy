/*
 * =====================================================================================
 *
 *       Filename:  Packet.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2010 08:42:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "Packet.h"
#include "Packet/JCConnect.h"
#include "Packet/CJConnectReply.h"
#include "Packet/CJJudgeThis.h"
#include "Packet/JCJudgeThisReturn.h"
#include <stdio.h>
#include <assert.h>

int Network::Packet::Read(SocketStream &stream)
{
    if(stream.ReadInt(type) != sizeof(type))
        return -1;
    if(type >= MAX_PACKET_ID || type < 0)
        return -1;
    return 0;
}

int Network::Packet::Write(SocketStream &stream)
{
    return stream.WriteInt(type);
}

size_t Network::Packet::GetPacketSize()const
{
    return sizeof(int);
}

Network::PacketFactoryManager::PacketFactoryManager()
{
    for(int i = 0; i < MAX_PACKET_ID; i++)
        factory[i] = NULL;

    RegisterFactory(new JCConnectPacketFactory, JC_CONNECT_PACKET);
    RegisterFactory(new CJConnectReplyPacketFactory, CJ_CONNECT_REPLY_PACKET);
    RegisterFactory(new CJJudgeThisPacketFactory, CJ_JUDGE_THIS_PACKET);
    RegisterFactory(new JCJudgeThisReturnPacketFactory, JC_JUDGE_THIS_RETURN_PACKET);
}

Network::PacketFactoryManager::~PacketFactoryManager()
{
    for(int i = 0; i < MAX_PACKET_ID; i++)
    {
        if(factory[i])delete factory[i],factory[i] = NULL;
    }
}

Network::PacketFactory *Network::PacketFactoryManager::GetPacketFactory(int type)
{
    assert(type >= 0 && type < MAX_PACKET_ID);

    return factory[type];
}

int Network::PacketPlayer::ProcessInput()
{
    return 0;
}

int Network::PacketPlayer::ProcessOutput()
{
    return 0;
}

int Network::PacketPlayer::SendPacket(Packet *packet)
{
    return 0;
}

Network::Packet *Network::PacketPlayer::ReceivePacket()
{
    return NULL;
}

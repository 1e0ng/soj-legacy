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
#include <stdio.h>

int Network::Packet::Read(SocketStream &stream)
{
    int ty;
    if(stream.ReadInt(ty) != sizeof(ty))
        return -1;
    if(ty >= MAX_PACKET_ID || ty < 0)
        return -1;
    type = (PacketType_t)ty;
    return 0;
}

int Network::Packet::Write(SocketStream &stream)
{
    return stream.WriteInt(ty);
}

size_t Network::Packet::GetPacketSize()const
{
    return sizeof(int);
}

Network::PacketFactoryManager::PacketFactoryManager()
{
    for(int i = 0; i < MAX_PACKET_ID; i++)
        factory[i] = NULL;
}

Network::PacketFactoryManager::~PacketFactoryManager()
{
    for(int i = 0; i < MAX_PACKET_ID; i++)
    {
        if(factory[i])delete factory[i],factory[i] = NULL;
    }
}

Network::PacketFactory *Network::PacketFactoryManager::GetPacketFactory(PacketType_t type)
{
    return factory[type];
}

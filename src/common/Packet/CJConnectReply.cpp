/*
 * =====================================================================================
 *
 *       Filename:  CJConnectReply.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/11/2010 04:10:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "CJConnectReply.h"

using namespace Network;

int CJConnectReply::Read(SocketStream &stream)
{
    if(Packet::Read(stream) < 0)
        return -1;

    if(stream.ReadInt(reply) < 0)
        return -1;
    if(stream.ReadInt(judgerId) < 0)
        return -1;
    return 0;
}

int CJConnectReply::Write(SocketStream &stream)
{
    if(Packet::Write(stream) < 0)
        return -1;

    if(stream.WriteInt(reply) < 0)
        return -1;
    if(stream.WriteInt(judgerId) < 0)
        return -1;
    return 0;
}

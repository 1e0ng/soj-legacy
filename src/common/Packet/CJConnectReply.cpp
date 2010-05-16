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
    Packet::Read(stream); 
    stream.ReadInt(reply);
    stream.ReadInt(judgerId);
    return 0;
}

int CJConnectReply::Write(SocketStream &stream)
{
    Packet::Write(stream);
    stream.WriteInt(reply);
    stream.WriteInt(judgerId);
    return 0;
}

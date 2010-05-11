/*
 * =====================================================================================
 *
 *       Filename:  JCConnect.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/11/2010 03:26:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "JCConnect.h"

using namespace Network;

int JCConnect::Read(SocketStream &stream)
{
    if(Packet::Read(stream) < 0)
        return -1;

    if(stream.ReadInt(supportedLan[0]) < 0)
        return -1;
    if(stream.ReadInt(supportedLan[1]) < 0)
        return -1;
    if(stream.ReadInt(supportedLan[2]) < 0)
        return -1;
    return 0;
}

int JCConnect::Write(SocketStream &stream)
{
    if(Packet::Write(stream) < 0)
        return -1;

    if(stream.WriteInt(supportedLan[0]) < 0)
        return -1;
    if(stream.WriteInt(supportedLan[1]) < 0)
        return -1;
    if(stream.WriteInt(supportedLan[2]) < 0)
        return -1;
    return 0;
}

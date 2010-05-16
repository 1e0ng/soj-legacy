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
    Packet::Read(stream);

    for(int i = 0; i < LAN_NUMBER; i++)
    {
        stream.ReadInt(supportedLan[i]);
    }
    return 0;
}

int JCConnect::Write(SocketStream &stream)
{
    Packet::Write(stream);

    for(int i = 0; i < LAN_NUMBER; i++)
    {
        stream.WriteInt(supportedLan[i]);
    }
    return 0;
}

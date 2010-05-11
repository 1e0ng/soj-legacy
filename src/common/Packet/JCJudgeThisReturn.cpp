/*
 * =====================================================================================
 *
 *       Filename:  JCJudgeThisReturn.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/11/2010 04:40:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "JCJudgeThisReturn.h"
using namespace Network;

int JCJudgeThisReturn::Read(SocketStream &stream)
{
    if(Packet::Read(stream) < 0)
        return -1;
    if(stream.ReadInt(rid) < 0)
        return -1;
    if(stream.ReadInt(result) < 0)
        return -1;
    return 0;
}

int JCJudgeThisReturn::Write(SocketStream &stream)
{
    if(Packet::Write(stream) < 0)
        return -1;

    if(stream.WriteInt(rid) < 0)
        return -1;
    if(stream.WriteInt(result) < 0)
        return -1;
    return 0;
}

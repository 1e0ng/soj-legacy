/*
 * =====================================================================================
 *
 *       Filename:  CJJudgeThis.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/11/2010 04:33:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "CJJudgeThis.h"
#include "../SocketStream.h"
using namespace Network;

int CJJudgeThis::Read(SocketStream &stream)
{
    if(Packet::Read(stream) < 0)
        return -1;

    if(stream.ReadInt(sourceLength) < 0)
        return -1;
    if(sourceLength <= 0 || sourceLength >= Cake::MAX_SOURCE_LENGTH - 1)
        return -1;

    if(stream.ReadInt(cake.rid) < 0)
        return -1;
    if(stream.ReadInt(cake.pid) < 0)
        return -1;
    if(stream.ReadInt(cake.uid) < 0)
        return -1;
    if(stream.ReadInt(cake.language) < 0)
        return -1;
    if(stream.ReadInt(cake.timeLimit) < 0)
        return -1;
    if(stream.ReadInt(cake.memoryLimit) < 0)
        return -1;

    if(stream.Peek(cake.sourceCode, sourceLength + 1) < sourceLength + 1)
        return -1;
    if(stream.Read(cake.sourceCode, sourceLength + 1) < 0)
        return -1;
    cake.sourceCode[sourceLength + 1] = '\0';

    return 0;
}

int CJJudgeThis::Write(SocketStream &stream)
{
    if(Packet::Write(stream) < 0)
        return -1;

    if(stream.WriteInt(sourceLength) < 0)
        return -1;

    if(stream.WriteInt(cake.rid) < 0)
        return -1;
    if(stream.WriteInt(cake.pid) < 0)
        return -1;
    if(stream.WriteInt(cake.uid) < 0)
        return -1;
    if(stream.WriteInt(cake.language) < 0)
        return -1;
    if(stream.WriteInt(cake.timeLimit) < 0)
        return -1;
    if(stream.WriteInt(cake.memoryLimit) < 0)
        return -1;

    if(stream.Write(cake.sourceCode, sourceLength + 1) < 0)
        return -1;
    return 0;
}

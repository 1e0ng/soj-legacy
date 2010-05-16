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
#include <assert.h>
using namespace Network;

int CJJudgeThis::Read(SocketStream &stream)
{
    Packet::Read(stream);
    stream.ReadInt(sourceLength);

    if(sourceLength <= 0 || sourceLength >= Cake::MAX_SOURCE_LENGTH - 1)
        assert(false);

    stream.ReadInt(cake.rid);
    stream.ReadInt(cake.pid);
    stream.ReadInt(cake.uid);
    stream.ReadInt(cake.language);
    stream.ReadInt(cake.timeLimit);
    stream.ReadInt(cake.memoryLimit);
    stream.Read(cake.sourceCode, sourceLength + 1);
    cake.sourceCode[sourceLength + 1] = '\0';

    return 0;
}

int CJJudgeThis::Write(SocketStream &stream)
{
    Packet::Write(stream);
    stream.WriteInt(sourceLength);
    stream.WriteInt(cake.rid);
    stream.WriteInt(cake.pid);
    stream.WriteInt(cake.uid);
    stream.WriteInt(cake.language);
    stream.WriteInt(cake.timeLimit);
    stream.WriteInt(cake.memoryLimit);
    stream.Write(cake.sourceCode, sourceLength + 1);
    return 0;
}

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
    Packet::Read(stream);
    stream.Read((char *)&cr, sizeof(cr));
    return 0;
}

int JCJudgeThisReturn::Write(SocketStream &stream)
{
    Packet::Write(stream);
    stream.Write((const char *)&cr, sizeof(cr));
    return 0;
}

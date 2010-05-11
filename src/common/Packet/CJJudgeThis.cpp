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
using namespace Network;

int CJJudgeThis::Read(SocketStream &stream)
{
    if(Packet::Read(stream) < 0)
        return -1;

    if(stream.Read(&cake, sizeof(cake)) < 0)
        return -1;
    return 0;
}

int CJJudgeThis::Write(SocketStream &stream)
{
    if(Packet::Write(stream) < 0)
        return -1;

   if(stream.Write(&cake, sizeof(cake)) < 0)
       return -1;
   return 0;
}

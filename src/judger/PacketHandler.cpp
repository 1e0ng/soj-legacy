/*
 * =====================================================================================
 *
 *       Filename:  PacketHandler.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/11/2010 05:16:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "../common/Packet/CJJudgeThis.h"
#include "../common/Packet/CJConnectReply.h"
#include "../common/Packet/JCConnect.h"
#include "../common/Packet/JCJudgeThisReturn.h"

using namespace Network;

int CJJudgeThis::Execute()
{
    return 0;
}

int CJConnectReply::Execute()
{
    return 0;
}

int JCConnect::Execute()
{
    return 0;
}

int JCJudgeThisReturn::Execute()
{
    return 0;
}

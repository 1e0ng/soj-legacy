/*
 * =====================================================================================
 *
 *       Filename:  PacketDefine.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2010 02:50:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef PACKET_DEFINE_H
#define PACKET_DEFINE_H

enum PacketType_t
{
    JC_CONNECT_PACKET,
    CJ_CONNECT_REPLY_PACKET,
    CJ_JUDGE_THIS_PACKET,
    JC_JUDGE_THIS_RETURN,

    MAX_PACKET_ID
};

#endif

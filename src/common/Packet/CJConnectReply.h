/*
 * =====================================================================================
 *
 *       Filename:  CJConnectReply.h
 *
 *    Description:  controller to judger.reply to connect request
 *
 *        Version:  1.0
 *        Created:  05/11/2010 04:05:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef CJ_CONNECT_REPLY_H
#define CJ_CONNECT_REPLY_H

#include "../Packet.h"

namespace Network
{
    class CJConnectReply
    {
    public:
        enum ReplyType_t
        {
            ACCEPTED, JUDGER_FULL, REFUSED
        };
        virtual int Read(SocketStream &stream);
        virtual int Write(SocketStream &stream);
        virtual int GetPacketSize()const
        {
            return sizeof(int) + sizeof(int);
        }

        virtual int Execute();

        void SetReply(ReplyType_t rep){reply = rep;}
        int GetReply()const{return reply;}
        void SetJudgerId(int id){judgerId = id;}
        int GetJudgerId()const{return judgerId;}
    private:
        int reply;
        int judgerId;//if accepted, return its id
    };
}

#endif

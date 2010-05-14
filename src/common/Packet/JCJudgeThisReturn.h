/*
 * =====================================================================================
 *
 *       Filename:  JCJudgeThisReturn.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/11/2010 04:30:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef JC_JUDGE_THIS_RETURN_H
#define JC_JUDGE_THIS_RETURN_H
#include "../Cake.h"
#include "../Packet.h"
#include "../OJDefine.h"

namespace Network
{
    class JCJudgeThisReturn: public Packet
    {
    public:
        virtual int Read(SocketStream &stream);
        virtual int Write(SocketStream &stream);
        virtual size_t GetPacketSize()const 
        {
            return Packet::GetPacketSize() + sizeof(int) * 5;
        }

        virtual int Execute(PacketPlayer *player);

        void SetRid(int rid){cr.rid = rid;}
        int GetRid()const{return cr.rid;}
        void SetJudgerId(int jid){cr.jid = jid;}
        int GetJudgerId()const{return cr.jid;}
        void SetResult(JudgeResult res){cr.result = res;}
        int GetResult()const{return cr.result;}
        void SetRtime(int rtime){cr.rtime = rtime;}
        int GetRtime()const{return cr.rtime;}
        void SetRmemory(int rmemory){cr.rmemory = rmemory;}
        int GetRmemory()const{return cr.rmemory;}

    private:
        CakeReturn cr;
    };

    class JCJudgeThisReturnPacketFactory: public PacketFactory
    {
    public:
        virtual Packet *GetPacket()
        {
            return new JCJudgeThisReturn;
        }
    };
}

#endif

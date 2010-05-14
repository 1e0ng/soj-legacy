/*
 * =====================================================================================
 *
 *       Filename:  CJJudgeThis.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/11/2010 04:30:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef CJ_JUDGE_THIS_H
#define CJ_JUDGE_THIS_H
#include "../Packet.h"
#include "../Cake.h"
#include <string.h>

namespace Network
{
    class CJJudgeThis:public Packet
    {
    public:
        virtual int Read(SocketStream &stream);
        virtual int Write(SocketStream &stream);
        virtual size_t GetPacketSize()const
        {
            return Packet::GetPacketSize() + sizeof(int) * 6;
        }

        virtual int Execute(PacketPlayer *player);

        const Cake &GetCake()const{return cake;}
        void SetCake(const Cake &c){cake = c; sourceLength = strlen(cake.sourceCode);}
        int GetSourceLength()const{return sourceLength;}
    private:
        int sourceLength;
        Cake cake;
    };
    class CJJudgeThisPacketFactory: public PacketFactory
    {
    public:
        virtual Packet *GetPacket()
        {
            return new CJJudgeThis;
        }
    };
}

#endif

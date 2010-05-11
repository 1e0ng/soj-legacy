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

namespace Network
{
    class CJJudgeThis
    {
    public:
        virtual int Read(SocketStream &stream);
        virtual int Write(SocketStream &stream);
        virtual int GetPacketSize()const
        {
            return sizeof(cake):
        }

        virtual int Execute();

        const Cake &GetCake()const{return cake;}
        void SetCake(const Cake &c){cake = c;}
    private:
        Cake cake;
    };
}

#endif

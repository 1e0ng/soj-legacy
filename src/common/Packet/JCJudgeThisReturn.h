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
            return sizeof(int) + sizeof(int);
        }

        virtual int Execute();

        void SetRid(int rid){this->rid = rid;}
        int GetRid()const{return rid;}
        void SetResult(JudgeResult res){result = res;}
        int GetResult()const{return result;}
    private:
        int rid;
        int result;
    };
}

#endif

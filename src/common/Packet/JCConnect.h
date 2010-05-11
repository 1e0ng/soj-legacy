/*
 * =====================================================================================
 *
 *       Filename:  JCConnect.h
 *
 *    Description:  from Judger to Controller.request to join
 *
 *        Version:  1.0
 *        Created:  05/11/2010 03:20:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef JCCONNECT_H
#define JCCONNECT_H
#include "../Packet.h"
#include "../OJDefine.h"
#include <assert.h>

namespace Network
{
    class JCConnect
    {
    public:
        virtual int Read(SocketStream &stream);
        virtual int Write(SocketStream &stream);
        virtual size_t GetPacketsize()const
        {
            return sizeof(int) * 3;
        }

        virtual int Execute();

        void SetLanguageSupport(Language lan, bool bOn)
        {
            assert(lan < LAN_NUMBER);

            supportedLan[lan] = bOn? 1: 0;
        }
        void GetLanguageSupport(Language lan)const
        {
            assert(lan <LAN_NUMBER);

            return supported[lan];
        }
    private:
        int supportedLan[3];
    };

    class JCConnectPacketFactory: public PacketFactory
    {
    public:
        virtual Packet *GetPacket()
        {
            return new JCConnect;
        }
    private:
    };
}
#endif

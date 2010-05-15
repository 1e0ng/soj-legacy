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
    class JCConnect: public Packet
    {
    public:
        JCConnect(){SetPacketType(JC_CONNECT_PACKET);}

        virtual int Read(SocketStream &stream);
        virtual int Write(SocketStream &stream);
        virtual size_t GetPacketSize()const
        {
            return Packet::GetPacketSize() + sizeof(int) * LAN_NUMBER;
        }

        virtual int Execute(PacketPlayer *player);

        void SetLanguageSupport(int lan, bool bOn)
        {
            assert(lan <= LAN_MAX_ID && lan >= LAN_MIN_ID);

            supportedLan[lan - LAN_MIN_ID] = bOn? 1: 0;
        }
        bool GetLanguageSupport(int lan)const
        {
            assert(lan <= LAN_MAX_ID && lan >= LAN_MIN_ID);

            return supportedLan[lan - LAN_MIN_ID] == 1;
        }

    private:
        int supportedLan[LAN_NUMBER];
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

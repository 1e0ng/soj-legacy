/*
 * =====================================================================================
 *
 *       Filename:  Packet.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2010 08:41:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef PACKET_H
#define PACKET_H
#include "PacketDefine.h"
#include "SocketStream.h"

namespace Network
{
    class Packet
    {
    public:
        virtual ~Packet(){}

        virtual int Read(SocketStream &stream) = 0;
        virtual int Write(SocketStream &stream) = 0;
        virtual size_t GetPacketSize()const = 0;

        virtual int Execute() = 0;
    private:
        PacketType_t type;
    };

    class PacketFactory
    {
    public:
        virtual ~PacketFactory(){}

        virtual Packet *GetPacket() = 0;
    private:
    };

    class PacketFactoryManager
    {
    public:
        PacketFactoryManager();
        ~PacketFactoryManager();

        PacketFactory *GetPacketFactory(PacketType_t type);
    private:
        inline void RegisterFactory(PacketFactory *pf, PacketType_t type)
        {
            factory[type] = pf;
        }

        PacketFactory *factory[MAX_PACKET_ID];
    };
}

#endif

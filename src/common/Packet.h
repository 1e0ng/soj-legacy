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
    class PacketPlayer;
    class Packet
    {
    public:
        enum PacketExecuteReturn_t
        {
            PER_PACKET_ERROR = -1,
            PER_PACKET_CONTINUE,
            PER_PACKET_BREAK
        };
        virtual ~Packet(){}

        virtual int Read(SocketStream &stream) = 0;
        virtual int Write(SocketStream &stream) = 0;
        virtual size_t GetPacketSize()const = 0;

        virtual int Execute(PacketPlayer *player) = 0;

        int GetPacketType()const{return type;}
        void SetPacketType(int ty){type = ty;}
    private:
        int type;
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
        static PacketFactoryManager &GetInstance()
        {
            static PacketFactoryManager instance;
            return instance;
        }

        PacketFactory *GetPacketFactory(int type);
    private:
        PacketFactoryManager();
        ~PacketFactoryManager();
        PacketFactoryManager(const PacketFactoryManager &);
        PacketFactoryManager &operator=(const PacketFactoryManager &);

        inline void RegisterFactory(PacketFactory *pf, PacketType_t type)
        {
            factory[type] = pf;
        }

        PacketFactory *factory[MAX_PACKET_ID];
    };

    //all classes needing packet process should inherited from me
    class PacketPlayer
    {
    public:
        const static int MAX_PACKETS_PER_TICK = 5;

        PacketPlayer(){}
        virtual ~PacketPlayer(){stream.Close();}

        SocketStream &GetSocketStream(){return stream;}

        virtual int ProcessInput();
        virtual int ProcessOutput();

        int SendPacket(Packet *packet);
        Packet *ReceivePacket();
    protected:
        SocketStream stream;
    private:
    };
}

#endif

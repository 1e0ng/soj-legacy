#ifndef SOCKET_STREAM_H
#define SOCKET_STREAM_H
#include <netinet/in.h>
#include <sys/socket.h>

namespace Network
{
    class SocketStream
    {
    public:
        SocketStream():socketfd(-1),bValid(false), bServer(false){}
        ~SocketStream();

        //socket(),bind(),listen
        int OpenServerSocket(short port);
        int OpenClientSocket(const char *ip, short port);
        int Close();

        int GetSocketFd()const 
        {
            return socketfd;
        }
        void SetClientAddr(const sockaddr_in &addr)
        {
            clientAddr = addr;
        }
        const struct sockaddr_in &GetClientAddr()const
        {
            return clientAddr;
        }

        SocketStream *Accept();
        //return bytes left to send on success otherwise -1
        ssize_t Write(const char *buf, size_t size);
        //return bytes read on success otherwize -1
        ssize_t Read(char *buf, size_t size);
    private:
        int socketfd;
        bool bValid;
        bool bServer;//is server socket
        struct sockaddr_in clientAddr;//used by server
    };
}

#endif

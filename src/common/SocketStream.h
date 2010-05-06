#ifndef SOCKET_STREAM_H
#define SOCKET_STREAM_H
#include <netinet/in.h>
#include <sys/socket.h>

namespace Network
{
    class SocketStream
    {
    public:
        SocketStream():socketfd(-1),bValid(false){}
        ~SocketStream(){}

        //socket(),bind(),listen
        int Open(short port);
        int Close();

        int GetSocketFd()const 
        {
            return socketfd;
        }
        const struct sockaddr_in &GetClientAddr()const
        {
            return clientAddr;
        }

        //return bytes left to send on success otherwise -1
        ssize_t Write(const void *buf, size_t size);
        //return bytes read on success otherwize -1
        ssize_t Read(const void *buf, size_t size);
    private:
        int socketfd;
        bool bValid;
        struct sockaddr_in clientAddr;
    };
}

#endif


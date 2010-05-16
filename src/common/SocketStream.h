#ifndef SOCKET_STREAM_H
#define SOCKET_STREAM_H
#include "Exception.h"
#include <netinet/in.h>
#include <sys/socket.h>

namespace Network
{
    class SocketStream
    {
    public:
        SocketStream():socketfd(-1),bValid(false){}
        ~SocketStream();

        //socket(),bind(),listen
        int OpenServerSocket(short port);
        int OpenClientSocket(const char *ip, short port);
        int Close();

        int GetSocketFd()const 
        {
            return socketfd;
        }
        void SetTimeout(long ms);
#ifdef _CONTROLLER
        void SetClientAddr(const sockaddr_in &addr)
        {
            clientAddr = addr;
        }
        const struct sockaddr_in &GetClientAddr()const
        {
            return clientAddr;
        }
#endif

        int Accept(SocketStream &stream);
        //return bytes left to send on success otherwise -1
        ssize_t Write(const char *buf, size_t size);
        ssize_t WriteInt(int n);
        //return bytes read on success otherwize -1
        ssize_t Read(char *buf, size_t size);
        ssize_t ReadInt(int &n);
        ssize_t Recv(char *buf, size_t size, int flags);
        //peek with MSG_DONTWAIT
        ssize_t Peek(char *buf, size_t size);
        ssize_t PeekInt(int &n);
    private:
        int socketfd;
        bool bValid;
#ifdef _CONTROLLER
        struct sockaddr_in clientAddr;//used by server
#endif
    };

    class NetworkException: public OJException
    {
    public:
        NetworkException()throw(){}
        virtual ~NetworkException()throw(){}

        virtual const char *What()const throw()
        {
            return "network exception";
        }
    };

    class ConnectionResetException: public NetworkException
    {
    public:
        ConnectionResetException()throw(){}
        virtual ~ConnectionResetException()throw(){}

        virtual const char *What()const throw()
        {
            return "connection reset";
        }
    };

    class ConnectionEOFException: public NetworkException
    {
    public:
        ConnectionEOFException()throw(){}
        virtual ~ConnectionEOFException()throw(){}

        virtual const char *What()const throw()
        {
            return "connection closed";
        }
    };

    class ConnectionTimedoutException: public NetworkException
    {
    public:
        ConnectionTimedoutException()throw(){}
        virtual ~ConnectionTimedoutException()throw(){}

        virtual const char *What()const throw()
        {
            return "connction timedout";
        }
    };

}

#endif


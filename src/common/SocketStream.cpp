
#include "SocketStream.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

int Network::SocketStream::OpenServerSocket(short port)
{
    if(bValid)
        return 0;

    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket() failed");
        return -1;
    }
    sockaddr_in servsock;
    memset(&servsock, 0, sizeof(servsock));
    servsock.sin_family = AF_INET;
    servsock.sin_port = htons(port);
    servsock.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(socketfd, (struct sockaddr *)&servsock, sizeof(servsock)) < 0)
    {
        perror("bind() failed");
        return -1;
    }
    listen(socketfd, 5);
    
    bValid = true;
    return 0;
}

int Network::SocketStream::OpenClientSocket(const char *ip, short port)
{
    if(bValid)
        return 0;
    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) <0)
    {
        perror("socket() failed");
        return -1;
    }
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if(inet_aton(ip, &addr.sin_addr) < 0)
    {
        return -1;
    }

    if(connect(socketfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect failed");
        close(socketfd);
        return -1;
    }

    bValid = true;
    return 0;
}

int Network::SocketStream::Close()
{
    close(socketfd);
    bValid = false;
    socketfd = -1;
#ifdef _CONTROLLER
    memset(&clientAddr, 0, sizeof(clientAddr));
#endif
    return 0;
}

Network::SocketStream::~SocketStream()
{
    if(bValid)
        Close();
}

int Network::SocketStream::Accept(SocketStream &stream)
{
    sockaddr_in addr;
    int clientfd;
    socklen_t len = sizeof(addr);
    
    clientfd = accept(socketfd, (struct sockaddr *)&addr, &len);
    if(clientfd != -1)
    {
        stream.Close();

        stream.bValid = true;
#ifdef _CONTROLLER
        stream.SetClientAddr(addr);
#endif
        return 0;
    }
    else
    {
        return -1;
    }
}

ssize_t Network::SocketStream::Write(const char *buf, size_t size)
{
    size_t nLeft = size;
    ssize_t nWritten = 0;

    while(nLeft > 0)
    {
        if((nWritten = write(socketfd, buf, nLeft)) <= 0);
        {
            if(errno == EINTR)
                nWritten = 0;
            else
                return -1;//error occured
        }
        nLeft -= nWritten;
        buf += nWritten;
    }
    return size;
}

ssize_t Network::SocketStream::WriteInt(int n)
{
    return Write((const char *)&n, sizeof(int));
}

ssize_t Network::SocketStream::Read(char *buf, size_t size)
{
    size_t nLeft = size;
    ssize_t nRead = 0;

    while(nLeft > 0)
    {
        if((nRead = read(socketfd, buf, nLeft)) < 0)
        {
            if(errno == EINTR)
                nRead = 0;
            else
                return -1;
        }
        else if(nRead == 0)
        {
            break;//EOF
        }
        nLeft -= nRead;
        buf += nRead;
    }
    return size - nLeft;
}

ssize_t Network::SocketStream::ReadInt(int &n)
{
    return Read((char *)&n, sizeof(int));
}

ssize_t Network::SocketStream::Recv(char *buf, size_t size, int flags)
{
    return recv(socketfd, buf, size, flags);
}

ssize_t Network::SocketStream::Peek(char *buf, size_t size)
{
    return recv(socketfd, buf, size, MSG_PEEK | MSG_DONTWAIT);
}

ssize_t Network::SocketStream::PeekInt(int &n)
{
    return Peek((char *)&n, sizeof(n));
}

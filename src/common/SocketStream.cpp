
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
    bServer = true;
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
        perror("Invalid ip address");
        close(socketfd);
        return -1;
    }

    if(connect(socketfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect failed");
        close(socketfd);
        return -1;
    }

    bValid = true;
    bServer = false;
    return 0;
}

int Network::SocketStream::Close()
{
    close(socketfd);
    bValid = false;
    socketfd = -1;
    memset(&clientAddr, 0, sizeof(clientAddr));
    return 0;
}

Network::SocketStream::~SocketStream()
{
    if(bValid)
        Close();
}

Network::SocketStream *Network::SocketStream::Accept()
{
    sockaddr_in addr;
    int clientfd;
    socklen_t len = sizeof(addr);
    
    clientfd = accept(socketfd, (struct sockaddr *)&addr, &len);
    return NULL;
}

ssize_t Network::SocketStream::Write(const char *buf, size_t size)
{
    size_t nLeft = size;
    ssize_t nWritten = 0;

    while(nLeft > 0)
    {
        if((nWritten = write(socketfd, buf, nLeft)) <= 0);
        {
            if(nWritten == EINTR)
                nWritten = 0;
            else
                return -1;//error occured
        }
        nLeft -= nWritten;
        buf += nWritten;
    }
    return nLeft;
}

ssize_t Network::SocketStream::Read(char *buf, size_t size)
{
    size_t nLeft = size;
    ssize_t nRead = 0;

    while(nLeft > 0)
    {
        if((nRead = read(socketfd, buf, nLeft)) < 0)
        {
            if(nRead == EINTR)
                nRead = 0;
            else
                return -1;
        }
        else
        {
            break;//EOF
        }
        nLeft -= nRead;
        buf += nRead;
    }
    return size - nLeft;
}
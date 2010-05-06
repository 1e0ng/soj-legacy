
#include "SocketStream.h"

int Network::SocketStream::Open(short port)
{
    if(bValid)
        return 0;

    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;
    sockaddr_in servsock;
    bzero(&servsock, sizeof(servsock));
    servsock.sin_family = AF_INET;
    servsock.sin_port = htons(port);
    servsock.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(socketfd, (struct sockaddr *)&servsock, sizeof(servsock)) < 0)
        return -1;
    listen(socketfd, 5);
    
    bValid = true;
    return 0;
}

int Network::SocketStream::Close()
{
    bValid = false;
    socketfd = -1;
    bzero(&clientAddr, sizeof(clientAddr));
}

ssize_t Network::SocketStream::Write(const void *buf, size_t size)
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

ssize_t Network::SocketStream::Read(const void *buf, size_t size)
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

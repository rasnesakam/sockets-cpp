#include<string>
#include<sys/socket.h>
#include<iostream>
#include <netinet/in.h>
#include <cstring>
int main(int ac, std::string av[]){
    int port = 8080;
    int socketOption = 1;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof address;
    // socket(int domain, int type, int protocol)
    // domain:   Defines scope of connection. Socket will be served on local area network, or Internet Protocol V4 or V6
    //           Values are:
    //            - AF_LOCAL -> Local Area Network
    //            - AF_INET  -> Internet Protocol v4
    //            - AF_INET6 -> Internet Protocol v6
    // type:     Defines connection type. Wether TCP or UDP
    //           Values are:
    //            - SOCKET_STREAM -> TCP connection
    //            - SOCKET_DGRAM  -> UDP connection
    // protocol: Defines Protocol value for IP.
    int socketFd = socket(AF_INET,SOCK_STREAM,0);
    if (socketFd < 0) {
        std::cerr << "Socket could not established. " << std::strerror(errno) << std::endl;
        exit(errno);
    }
    int socketOpt = setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &socketOpt, sizeof socketOpt);
    if (socketOpt) {
        std::cerr << "Socket option could not be set: " << std::strerror(errno) << std::endl;
        exit(errno);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(socketFd, (const struct sockaddr *)&address, addrlen) < 0){
        std::cerr << "socket could not be binded. " << std::strerror(errno) << std::endl;
        exit(errno);
    }
    if (listen(socketFd, 3) < 0){
        std::cerr << "listen failed" << std::strerror(errno) << std::endl;
        exit(errno);
    }
    int newSocket = accept(socketFd, (struct sockaddr*) &address, &addrlen);
    if (newSocket < 0){
        std::cerr << "listen failed" << std::strerror(errno) << std::endl;
        exit(errno);
    }
    // poll op. learn whether fd has a data or not
    std::string input;
    int valRead = recv(newSocket, &input, 1024, 0);
    
}
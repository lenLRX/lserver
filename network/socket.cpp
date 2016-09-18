#include "socket.h"
#include "../log/log.h"

Socket::Socket():fd(-1)
{}

Socket::Socket(Socket&& temp):fd(temp.fd){
	temp.fd = -1;
}
Socket& Socket::operator = (Socket& other){
	this.fd = other.fd;
	other.fd = -1;
	return *this;
}

Socket::~Socket(){
	close(fd);
}

ServerSocket::ServerSocket(string ip,int port){
	struct sockaddr_in ServerAddr;
    bzero(&ServerAddr,sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    ServerAddr.sin_port = htons(port);
 
    //创建用于internet的流协议(TCP)socket, fd代表服务器socket
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0)
    {
        LOG << "Create Socket Failed!" << endl;
        throw exception(string("Create Socket Failed!"));
    }

    int opt =1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	//把socket和socket地址结构联系起来
    if(socket_namespace::bind(fd,(struct sockaddr*)&receiver_addr,sizeof(receiver_addr)))
    {
        LOG << "Server Bind Port Failed!" << endl; 
        throw exception(string("Server Bind Port Failed!"));
    }
 
    // fd用于监听
    if ( listen(fd, 5) )
    {
        LOG << "Server Listen Failed!" << endl; 
        throw exception(string("Server Listen Failed!"));
    }
}

ServerSocket::~ServerSocket(){
	;
}
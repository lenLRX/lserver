#include "socket.h"
#include "../log/log.h"

Socket::Socket():fd(-1)
{}

Socket::Socket(int fd):fd(fd)
{}

Socket::Socket(Socket&& temp):fd(temp.fd){
	temp.fd = -1;
}
Socket& Socket::operator = (Socket& other){
	this->fd = other.fd;
	other.fd = -1;
	return *this;
}

Socket::~Socket(){
	socket_namespace::close(fd);
}

Connection::Connection(Connection&& temp):Socket(temp.fd){
	temp.fd = -1;
}

Connection& Connection::operator = (Connection& other){
	this->fd = other.fd;
	other.fd = -1;
	return *this;
}
	
int Connection::read(void *buf,size_t nbytes){
	return socket_namespace::read(fd,buf,nbytes);
}

int Connection::write(const void *buf,size_t nbytes){
	return socket_namespace::write(fd,buf,nbytes);
}

Connection::Connection(int fd,struct sockaddr_in addr)
    :Socket(fd),opp_addr(addr)
{

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
        throw exception();
    }

    int opt =1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	//把socket和socket地址结构联系起来
    if(::bind(fd,(struct sockaddr*)&ServerAddr,sizeof(ServerAddr)))
    {
        LOG << "Server Bind Port Failed!" << endl; 
        throw exception();
    }
 
    // fd用于监听
    if ( listen(fd, 5) )
    {
        LOG << "Server Listen Failed!" << endl; 
        throw exception();
    }
}

Connection ServerSocket::accept(){
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	int conn = ::accept(fd,(struct sockaddr*)&client_addr, &client_addr_len);
	return Connection(fd,client_addr);
}

ServerSocket::~ServerSocket(){
	;
}
#include "socket.h"
#include "../log/log.h"
#include <sys/select.h>

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

Connection::Connection(Connection&& temp):Socket(temp.fd),opp_addr(temp.opp_addr){
	temp.fd = -1;
}

Connection& Connection::operator = (Connection& other){
	this->fd = other.fd;
	other.fd = -1;
	this->opp_addr = other.opp_addr;
	return *this;
}

//read which can be time out
int Connection::read(void* buf,size_t nbytes,int secs,int usec){
	fd_set set;
	struct timeval timeout;
	FD_ZERO(&set);
	FD_SET(fd,&set);
	timeout.tv_sec = secs;
	timeout.tv_usec = usec;

	int ret = select(fd+1,&set,NULL,NULL,&timeout);
	if(ret <=0){
		return ret;
	}else{
		return socket_namespace::read(fd,buf,nbytes);
	}
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

ServerSocket::ServerSocket(int port){
	struct sockaddr_in ServerAddr;
    bzero(&ServerAddr,sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = htons(0);
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
	return Connection(conn,client_addr);
}

Connection ServerSocket::accept(int secs,int usec){
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);

	fd_set set;
	struct timeval timeout;
	FD_ZERO(&set);
	FD_SET(fd,&set);
	timeout.tv_sec = secs;
	timeout.tv_usec = usec;

	int ret = select(fd+1,&set,NULL,NULL,&timeout);
	if(ret <=0){
		LOG << "accept failure or timeout" << endl;
	}else{
		int conn = ::accept(fd,(struct sockaddr*)&client_addr, &client_addr_len);
	    return Connection(conn,client_addr);
	}
	return Connection(-1,client_addr);
}

ServerSocket::~ServerSocket(){
	;
}

ClientSocket::ClientSocket(string ip,int port):ip(ip),port(port){
	struct sockaddr_in ClientAddr;
    bzero(&ClientAddr,sizeof(ClientAddr)); //把一段内存区的内容全部设置为0
    ClientAddr.sin_family = AF_INET;    //internet协议族
    ClientAddr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址
    ClientAddr.sin_port = htons(0);    //0表示让系统自动分配一个空闲端口
    //创建用于internet的流协议(TCP)socket,用fd代表客户机socket
    fd = socket(AF_INET,SOCK_STREAM,0);
    if( fd < 0)
    {
        LOG << "Create Socket Failed!\n" << endl;
        throw exception();
    }
    //把客户机的socket和客户机的socket地址结构联系起来
    if(socket_namespace::bind(fd,(struct sockaddr*)&ClientAddr,sizeof(ClientAddr)))
    {
        LOG << "Client Bind Port Failed!\n" << endl; 
        throw exception();
    }
 
    
}

Connection ClientSocket::getConnection(){
	//设置一个socket地址结构ServerAddr,代表服务器的internet地址, 端口
    struct sockaddr_in ServerAddr;
    bzero(&ServerAddr,sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    ServerAddr.sin_port = htons(port);
    socklen_t ServerAddr_length = sizeof(ServerAddr);
    //向服务器发起连接,连接成功后fd代表了客户机和服务器的一个socket连接
    if(connect(fd,(struct sockaddr*)&ServerAddr, ServerAddr_length) < 0)
    {
        LOG << "Can Not Connect To ServerAddr!\n" << endl;;
        throw exception();
    }
	int connfd = fd;
	fd = -1;
	return Connection(connfd,ServerAddr);
}

ClientSocket::~ClientSocket(){

}
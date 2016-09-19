#ifndef __SOCKET_H__
#define __SOCKET_H__
#include "../utility/socket_header.h"
#include <string>

using namespace std;
using namespace socket_namespace;

//base class of socket
class Socket
{
public:
    Socket();
	Socket(int fd);
	virtual ~Socket();
	//check if Socket is valid
	Socket(Socket&& temp);
	Socket& operator = (Socket& other);
	inline operator bool () const{
		return valid();
	}
	inline bool valid() const{
		return fd >= 0;
	}
	int fd;
};

class Connection:public Socket
{
public:
    ~Connection(){}
	Connection(Connection&& temp);
	Connection& operator = (Connection& other);
	int read(void *buf,size_t nbytes);
	int write(const void *buf,size_t nbytes);
	inline bool isblocking() const{
		int flags = fcntl(fd,F_GETFL,0);
		return flags&O_NONBLOCK;
	}
	inline void setblocking() {
		int flags = fcntl(fd, F_GETFL, 0);
        fcntl(fd, F_SETFL, flags|O_NONBLOCK);
	}
	inline operator bool () const{
		return valid();
	}
	inline bool valid() const{
		return fd >= 0;
	}
private:
    friend class ServerSocket;
	friend class ClientSocket;
    Connection(int fd,struct sockaddr_in addr);
	struct sockaddr_in opp_addr;
};

class ServerSocket:public Socket
{
public:
	ServerSocket(string ip,int port);
	Connection accept();
	~ServerSocket();
};

class ClientSocket:public Socket
{
public:
    ClientSocket(string ip,int port);
	Connection getConnection();
	~ClientSocket();
private:
    string ip;
	int port;
};



#endif//__SOCKET_H__
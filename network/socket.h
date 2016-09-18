#ifndef __SOCKET_H__
#define __SOCKET_H__
#include "../utility/socket_header.h"
#include <string>

using namespace socket_namespace;

//base class of socket
class Socket
{
public:
    Socket();
	virtual ~Socket();
	//check if Socket is valid
	Socket(Socket&& temp);
	Socket& operator = (Socket& other);
	inline operator bool () const{
		return fd >= 0;
	}
	int fd;
};

class ServerConnection:public Socket
{
public:
    ~ServerConnection();
private:
    friend class ServerSocket;
    ServerConnection();
};

class ServerSocket:public Socket
{
public:
	ServerSocket(string ip,int port);
	~ServerSocket();
};



#endif//__SOCKET_H__
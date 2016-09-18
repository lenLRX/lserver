#ifndef __SOCKET_H__
#define __SOCKET_H__
#include "../utility/socket_header.h"

using namespace socket_namespace;

//base class of socket
class Socket
{
public:
    Socket();
	virtual ~Socket();
	//check if Socket is valid
	inline operator bool () const{
		return fd >= 0;
	}
	int fd;
};
#endif//__SOCKET_H__
#include "socket.h"

Socket::Socket():fd(-1)
{}

Socket::~Socket(){
	close(fd);
}
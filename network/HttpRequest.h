#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__
#include <string>
using namespace std;
enum class HttpMethod{
	GET,
	POST,
	HEAD,
	PUT,
	DELETE,
	TRACE,
	CONNECT,
	OPTIONS,
	UNKNOWN
};

class HttpRequest
{
public:
    HttpRequest():method(HttpMethod::UNKNOWN){}
    HttpMethod method;
	string uri;
};
#endif//__HTTP_REQUEST_H__
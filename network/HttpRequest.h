#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__
#include <string>
#include <map>
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
	map<string,string> headers;
	string message_body;
};
#endif//__HTTP_REQUEST_H__
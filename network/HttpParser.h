#ifndef __HTTP_PARSER_H__
#define __HTTP_PARSER_H__
#include <string>
#include "../utility/ByteBuffer.h"
#include "HttpRequest.h"
using namespace std;
class HttpParser
{
public:
    HttpParser();
	HttpParser& put(const void* ptr,int nbytes);
	HttpParser& put(void* ptr,int nbytes);
	HttpRequest parse();
	string str();
private:
    ByteBuffer buffer;
};
#endif//__HTTP_PARSER_H__
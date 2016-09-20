#ifndef __HTTP_PARSER_H__
#define __HTTP_PARSER_H__
#include <sstream>
#include "HttpRequest.h"
using namespace std;
class HttpParser
{
public:
    HttpParser();
	HttpParser& operator << (string str);
	HttpRequest parse();
	string str();
private:
    stringstream ss;
};
#endif//__HTTP_PARSER_H__
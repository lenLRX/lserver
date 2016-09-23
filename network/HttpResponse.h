#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__
#include <string>
#include <map>
#include "../utility/ByteBuffer.h"
using namespace std;
class HttpResponse
{
public:
    HttpResponse();
    ByteBuffer getBuffer();
	string version;
	int StatusCode;
	const static map<int,string> StatusCode2Reason;
	string header();
	void setContent(ByteBuffer buffer);
	void setContentType(string type);
	string getContentType();
	ByteBuffer getContent();
private:
    ByteBuffer content;
	string ContentType;
};
#endif//__HTTP_RESPONSE_H__
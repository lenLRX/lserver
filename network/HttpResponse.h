#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__
#include <string>
#include <map>
using namespace std;
class HttpResponse
{
public:
    HttpResponse();
    string str();
	string version;
	int StatusCode;
	const static map<int,string> StatusCode2Reason;
	string header();
	void setContent(string str);
	void setContentType(string type);
	string getContentType();
	string getContent();
private:
    string content;
	string ContentType;
};
#endif//__HTTP_RESPONSE_H__
#include "HttpResponse.h"
#include "http.h"

const map<int,string> HttpResponse::StatusCode2Reason{{200,"OK"}};
HttpResponse::HttpResponse():StatusCode(200),version("HTTP/1.1"){
    ;
}

string HttpResponse::str(){
	string ret;
	ret += header();
	ret += string("Content-length: ") + to_string(content.size())+crlf;
	ret += string("Content-type: text/html\r\n\r\n");
	ret += content;
	return ret;
}

string HttpResponse::header(){
	string ret;
	ret = version + " " + to_string(StatusCode) + " " + StatusCode2Reason.at(StatusCode) + crlf;
	return ret;
}

void HttpResponse::setContent(string str){
	content = move(str);
}

string HttpResponse::getContent(){
	return content;
}
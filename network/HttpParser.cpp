#include "HttpParser.h"

HttpParser::HttpParser(){

}

HttpRequest HttpParser::parse(){
	HttpRequest request;
	string buffer(ss.str());
	string::iterator it = buffer.begin();
	string::iterator end = buffer.end();
	

	//parsing RequestLine

	//parsing Method
	switch(*it){
		case 'G':
		    request.method = HttpMethod::GET;
		break;
		case 'P':
		    it++;
			if(*it == 'U')
				request.method = HttpMethod::PUT;
			else
				request.method = HttpMethod::POST;
		break;
		case 'H':
		    request.method = HttpMethod::HEAD;
		break;
		case 'D':
		    request.method = HttpMethod::DELETE;
		break;
		case 'T':
		    request.method = HttpMethod::TRACE;
		break;
		case 'C':
		    request.method = HttpMethod::CONNECT;
		break;
		case 'O':
		    request.method = HttpMethod::OPTIONS;
		break;
		default:
		    request.method = HttpMethod::UNKNOWN;
		break;
	}

	for(;it!=end;it++){
		if(*it == ' '){
			it++;
			break;
		}
	}

	//parsing Request-URI

	string uri;

	for(;it!=end;it++){
		if(*it == ' '){
			it++;
			break;
		}else{
			uri.push_back(*it);
		}
	}

    //Ignore HTTP VERSION now,TODO: fixme later
	for(;it!=end;it++){
		if(*it == '\n'){
			it++;
			break;
		}
	}


	
	return request;
}

string HttpParser::str(){
	return ss.str();
}

HttpParser& HttpParser::operator << (string str){
	ss << str;
	return *this;
}
#include "HttpParser.h"
#include "../log/log.h"

HttpParser::HttpParser(){

}

HttpRequest HttpParser::parse(){
	HttpRequest request;
	string _buffer(buffer);
	string::iterator it = _buffer.begin();
	string::iterator end = _buffer.end();
	
	LOG << "debug chrome " << str()<<endl;

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

	request.uri = move(uri);

    //Ignore HTTP VERSION now,TODO: fixme later
	for(;it!=end;it++){
		if(*it == '\n'){
			it++;
			break;
		}
	}

	//parsing header
	while(it!=end && *it != '\r'){
		string request_header;
		string field;
		for(;it!=end;it++){
			if(*it == ':'){
				it++;
				break;
			}else{
				request_header.push_back(*it);
			}
		}

		while(*it == ' '){
			it++;
		}

		for(;it!=end;it++){
			if(*it == '\r'){
				it++;
				it++;
				break;
			}else{
				field.push_back(*it);
			}
		}
		//LOG << "parsed field " << request_header << " " << field << endl;
		request.headers.insert(pair<string,string>(request_header,field));
	}

    //TODO: support message-body
	//https://www.w3.org/Protocols/rfc2616/rfc2616-sec4.html


	
	return request;
}

string HttpParser::str(){
	return string(buffer);
}

HttpParser& HttpParser::put(const void* ptr,int nbytes){
	buffer.put(ptr,nbytes);
	return *this;
}

HttpParser& HttpParser::put(void* ptr,int nbytes){
	buffer.put(ptr,nbytes);
	return *this;
}
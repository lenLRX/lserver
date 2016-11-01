#include "RequestHandler.h"

#include <time.h>

#include "../log/log.h"
#include "../utility/html_reader.h"
#include "../utility/resource_reader.h"
#include "../utility/TimeUtility.h"
#include "vpath.h"

RequestHandler::RequestHandler(){

}

RequestHandler::~RequestHandler(){

}

void RequestHandler::handle(Connection conn,HttpRequest request){
	string path = request.uri;

	LOG << "request.uri: " << path << endl;

	if(request.uri == "/")
	    path = "/web/hello.html";

	HttpResponse response;
	vpath _vpath;
	path = _vpath.translate(path);
	if(access(path.c_str(),F_OK|R_OK) == 0){
		time_t mtime = LastModifiedTIme(path);
		string originTime(ctime(&mtime));
		string rfctime(ctime2rfc822date(originTime));

		if(request.headers.find("If-Modified-Since") != 
		request.headers.end() && 
		rfc822date2time_t(request.headers.at("If-Modified-Since")) == mtime){
			code304(response);
		}else{
			code200(response,rfctime,path);
		}
	}else{
		path = _vpath.translate("/web/404.html");
		code404(response,path);
	}

	LOG << "response.StatusCode = " << to_string(response.StatusCode) << endl;

	ByteBuffer byteBuffer = response.getBuffer();
		
	while(byteBuffer){
		pair<void*,int> ret = byteBuffer.get(256);
		conn.write(ret.first,ret.second);
	}
	
}

void RequestHandler::code200(HttpResponse& response,
const string& rfctime,const string& path){
	response.StatusCode = 200;
	response.addField(string("Cache-Control:public"));
	response.addField(string("Last-Modified:") + rfctime);
	Resource resource = ResourceReader::getResource(path);
	response.setContent(resource.getResouce());
	response.setContentType(resource.getType());
}

void RequestHandler::code304(HttpResponse& response){
	response.StatusCode = 304;
}

void RequestHandler::code404(HttpResponse& response,
const string& path){
	response.StatusCode = 404;
	Resource resource = ResourceReader::getResource(path);
	response.setContent(resource.getResouce());
	response.setContentType(resource.getType());
}
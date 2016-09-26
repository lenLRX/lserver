#include "RequestHandler.h"

#include <time.h>

#include "../log/log.h"
#include "../network/HttpResponse.h"
#include "../utility/html_reader.h"
#include "../utility/resource_reader.h"
#include "../utility/LastModifiedTime.h"
#include "../utility/ctime2rfc822date.h"
#include "vpath.h"

RequestHandler::RequestHandler(){

}

RequestHandler::~RequestHandler(){

}

void RequestHandler::handle(Connection conn,HttpRequest request){
	string path = request.uri;

	if(request.uri == "/")
	    path = "/web/hello.html";

	HttpResponse response;
	vpath _vpath;
	path = _vpath.translate(path);
	if(access(path.c_str(),F_OK|R_OK) == 0){
		time_t mtime = LastModifiedTIme(path);
		string originTime(ctime(&mtime));
		string rfctime(ctime2rfc822date(originTime));
		LOG << rfctime << endl;
		response.StatusCode = 200;
	}else{
		response.StatusCode = 404;
		path = _vpath.translate("/web/404.html");;
	}

	LOG << "response.StatusCode = " << to_string(response.StatusCode) << endl;

	

	Resource resource = ResourceReader::getResource(path);
	response.setContent(resource.getResouce());
	response.setContentType(resource.getType());

	ByteBuffer byteBuffer = response.getBuffer();
		
	while(byteBuffer){
		pair<void*,int> ret = byteBuffer.get(256);
		conn.write(ret.first,ret.second);
	}
	
}
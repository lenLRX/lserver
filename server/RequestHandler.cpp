#include "RequestHandler.h"

#include "../log/log.h"
#include "../network/HttpResponse.h"
#include "../utility/html_reader.h"
#include "../utility/resource_reader.h"

RequestHandler::RequestHandler(){

}

RequestHandler::~RequestHandler(){

}

void RequestHandler::handle(Connection conn,HttpRequest request){
	string path = string(".")+request.uri;

	if(request.uri == "/")
	    path = "./web/hello.html";

	HttpResponse response;
	if(access(path.c_str(),F_OK|R_OK) == 0){
		Resource resource = ResourceReader::getResource(path);
		response.setContent(resource.getResouce());
		response.setContentType(resource.getType());
	}else{
		response.StatusCode = 404;
		string content = html_reader("./web/404.html");
		response.setContent(content);
		response.setContentType(html_type);
	}

	ByteBuffer byteBuffer = response.getBuffer();
		
	while(byteBuffer){
		pair<void*,int> ret = byteBuffer.get(256);
		conn.write(ret.first,ret.second);
	}
	
}
#include "RequestHandler.h"
#include "../network/HttpResponse.h"
#include "../utility/html_reader.h"

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
        string content = html_reader(path);
		response.setContent(content);
	}else{
		response.StatusCode = 404;
		string content = html_reader("./web/404.html");
		response.setContent(content);
		response.setContentType(html_type);
	}
		
	string response_string(response.str());
	conn.write(response_string.c_str(),response_string.size());
}
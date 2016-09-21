#include "log/log.h"
#include "network/http.h"
#include "network/HttpParser.h"
#include "network/HttpResponse.h"
#include "network/HttpRequest.h"
#include "network/socket.h"
#include "utility/html_reader.h"

#include <sstream>

static const int buffersize = 256;
int main(){
	Logger::getInstance().redirectStream("temp/static_server.txt");
	ServerSocket server_sock(http_port);
	while(true){
		Connection conn = server_sock.accept();
		HttpParser parser;
		cout << "connection accepted" << endl;
		while(true){
			char buffer[buffersize];
			bzero(buffer,buffersize);

			int length = conn.read(buffer,buffersize);

			//cout << length << "bytes read" << endl;

			if(length < 0){
				cout << "read failed" << endl;
				cout << strerror(errno) << endl;
				break;
			}else if(length == 0){
				break;
			}



			string frag = string(buffer);
			parser << frag;
			string s = parser.str();
			cout << frag <<flush;
			int len = s.size();
			if(len > 3 && s[len-1] == '\n' && s[len - 3] == '\n'){
				break;
			}
		}
		
		HttpRequest request = parser.parse();

		cout << "uri: " << request.uri << endl << flush;

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
		}
		
		string response_string(response.str());
		conn.write(response_string.c_str(),response_string.size());
	}
	return 0;
}
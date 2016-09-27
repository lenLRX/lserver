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

			int length = conn.read(buffer,buffersize,10,0);

			//cout << length << "bytes read" << endl;

			if(length < 0){
				cout << "read failed" << endl;
				cout << strerror(errno) << endl;
				break;
			}else if(length == 0){
				break;
			}



			parser.put(buffer,length);
			string s = parser.str();
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
			response.setContentType(html_type);
		}

		ByteBuffer byteBuffer = response.getBuffer();
			
		while(byteBuffer){
			pair<void*,int> ret = byteBuffer.get(256);
			conn.write(ret.first,ret.second);
		}
	}
	return 0;
}
#include "SingleThreadServer.h"
#include "../network/HttpResponse.h"
#include "../network/HttpParser.h"
#include "../utility/html_reader.h"
#include "../log/log.h"
#include <iostream>

#include <sstream>

static const int buffersize = 256;

SingleThreadServer::SingleThreadServer(){

}

SingleThreadServer::~SingleThreadServer(){

}

void SingleThreadServer::start(){
	running = true;
	internalThread = thread(bind(&SingleThreadServer::loop,this));
}

void SingleThreadServer::stop(){
	running = false;
	internalThread.join();
}

void SingleThreadServer::loop(){
	ServerSocket server_sock(http_port);
	do{
		try{
			Connection conn = server_sock.accept(5,0);
			HttpParser parser;
			//cout << "connection accepted" << endl;
			while(true){
				char buffer[buffersize];
				bzero(buffer,buffersize);

				int length = conn.read(buffer,buffersize,10,0);

				//cout << length << "bytes read" << endl;

				if(length < 0){
					cout << "read failed" << endl;
					cout << strerror(errno) << endl;
					throw exception();
					break;
				}else if(length == 0){
					throw exception();
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

			requestHandler.handle(move(conn),request);
		}catch(exception e){
			;//ignore
		}
	}while(running);
}
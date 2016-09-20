#include "log/log.h"
#include "network/http.h"
#include "network/socket.h"
static const int buffersize = 256;
int main(){
	Logger::getInstance().redirectStream("temp/cout.txt");
	ServerSocket server_sock(http_port);
	while(true){
		Connection conn = server_sock.accept();
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


			cout << string(buffer)<<flush;
		}
		

	}
	return 0;
}
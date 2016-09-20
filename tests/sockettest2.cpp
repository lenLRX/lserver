#include "../network/socket.h"
#include "test.h"

static const string checkstr = "check same";

static const int buffersize = 256;
static const int port = 2345;

bool class_socket_receiver_test(){
	try{
		ServerSocket server_sock(port);
		Connection conn = server_sock.accept();

		char buffer[buffersize];
	    bzero(buffer,buffersize);

		int length = conn.read(buffer,buffersize);

		LOG << length << "bytes read" << endl;

		if(length < 0){
			LOG << "read failed" << endl;
			LOG << strerror(errno) << endl;
			return false;
		}

		string gotstr = string(buffer);

		if(gotstr == checkstr){
			LOG << "recv test success" << endl;
		}else{
			LOG << "error: got string not equal to the string we sent" << endl;
			LOG << "expected: " << checkstr << endl;
			LOG << "got: " << gotstr << endl;
			return false;
		}

	}catch(exception e){
		LOG << e.what() << endl;
		return false;
	}
	return true;
}

bool class_socket_sender_test(){
	try{
		ClientSocket client_sock("127.0.0.1",port);
		Connection conn = client_sock.getConnection();

		int ret = conn.write(checkstr.c_str(),checkstr.size() + 1);

		if(ret>=0){
			LOG << ret <<" bytes sent" << endl;
		}
		else{
			LOG << "send failed" << endl;
			LOG << strerror(errno) << endl;
			return false;
		}
	}catch(exception e){
		LOG << e.what() << endl;
		return false;
	}
	return true;
}

void class_socket_bunch_test1(){
	DECL_TEST_THREADS
	ADD_A_TEST_TO_BUNCH(class_socket_receiver_test)
	sleep(1);
	ADD_A_TEST_TO_BUNCH(class_socket_sender_test)
	WAIT_ALL_THREADS
}

ADDBUNCHTEST(class_socket_bunch_test1)
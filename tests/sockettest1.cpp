#include "../utility/socket.h"
#include "../log/log.h"
#include <thread>
#include <string>
#include "test.h"
#include <memory.h>



using namespace std;
using namespace socket_namespace;

static const string checkstr = "check same";

static const int buffersize = 256;
static const int port = 2345;

bool socket_sender_test(){
	struct sockaddr_in sender_addr;
    bzero(&sender_addr,sizeof(sender_addr)); //把一段内存区的内容全部设置为0
    sender_addr.sin_family = AF_INET;    //internet协议族
    sender_addr.sin_addr.s_addr = inet_addr("127.0.0.1")//INADDR_ANY表示自动获取本机地址
    sender_addr.sin_port = htons(0);    //0表示让系统自动分配一个空闲端口
    //创建用于internet的流协议(TCP)socket,用senderFD代表客户机socket
    int senderFD = socket(AF_INET,SOCK_STREAM,0);
    if( senderFD < 0)
    {
        LOG << "Create Socket Failed!\n" << endl;
        return false;
    }
    //把客户机的socket和客户机的socket地址结构联系起来
    if(socket_namespace::bind(senderFD,(struct sockaddr*)&sender_addr,sizeof(sender_addr)))
    {
        LOG << "Client Bind Port Failed!\n" << endl; 
        return false;
    }
 
    //设置一个socket地址结构receiver_addr,代表服务器的internet地址, 端口
    struct sockaddr_in receiver_addr;
    bzero(&receiver_addr,sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = inet_addr("127.0.0.1")
    receiver_addr.sin_port = htons(port);
    socklen_t receiver_addr_length = sizeof(receiver_addr);
    //向服务器发起连接,连接成功后senderFD代表了客户机和服务器的一个socket连接
    if(connect(senderFD,(struct sockaddr*)&receiver_addr, receiver_addr_length) < 0)
    {
        LOG << "Can Not Connect To receiver_addr!\n" << endl;;
        return false;
    }

	char buffer[buffersize];
	bzero(buffer,buffersize);
	int ret = send(senderFD,checkstr.c_str(),checkstr.size() + 1,0);
	if(ret>=0){
		LOG << ret <<" bytes sent" << endl;
	}
	else{
		LOG << "send failed" << endl;
		return false;
	}
	return false;
}


bool socket_receiver_test(){
//设置一个socket地址结构receiver_addr,代表服务器internet地址, 端口
    struct sockaddr_in receiver_addr;
    bzero(&receiver_addr,sizeof(receiver_addr)); //把一段内存区的内容全部设置为0
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    receiver_addr.sin_port = htons(port);
 
    //创建用于internet的流协议(TCP)socket, recieverFD代表服务器socket
    int recieverFD = socket(AF_INET,SOCK_STREAM,0);
    if( recieverFD < 0)
    {
        printf("Create Socket Failed!");
        return false;
    }


    int opt =1;
    setsockopt(recieverFD,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
     
    //把socket和socket地址结构联系起来
    if(socket_namespace::bind(recieverFD,(struct sockaddr*)&receiver_addr,sizeof(receiver_addr)))
    {
        LOG << "Server Bind Port Failed!" << endl; 
        return false;
    }
 
    // recieverFD用于监听
    if ( listen(recieverFD, 5) )
    {
        LOG << "Server Listen Failed!" << endl; 
        return false;
    }

	struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

	int conn = accept(recieverFD,(struct sockaddr*)&client_addr,&length);
	if(conn < 0){
		LOG << "server Accept failed" << endl;
		return false;
	}

	char buffer[buffersize];
	length = recv(conn,buffer,buffersize,0);
	if(length < 0){
		LOG << "recv failed" << endl;
		return false;
	}

	string gotstr = string(buffer);

	

	if(gotstr == checkstr)
	{
		LOG << "recv success" << endl;
		return true;
	}else{
		LOG << "error: got string not equal to the string we sent" << endl;
		LOG << "expected: " << checkstr << endl;
		LOG << "got: " << gotstr << endl;
		return false;
	}

	return true;
}

void socketbunchtest1(){
	thread sender_thread(socket_sender_test);
	thread receiver_thread(socket_receiver_test);
	sender_thread.join();
	receiver.join();
}

ADDBUNCHTEST(socketbunchtest1)
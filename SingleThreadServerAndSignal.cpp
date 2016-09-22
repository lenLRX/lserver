#include "server/SingleThreadServer.h"
#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

void handle_signal(int sig){
	cout << "got signal " << sig << endl;
}

int main(){
	SingleThreadServer server;
	server.start();
	signal(SIGINT,handle_signal);
	int sig = pause();
	server.stop();
}
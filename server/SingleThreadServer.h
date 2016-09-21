#ifndef __SINGLE_THREAD_SERVER_H__
#define __SINGLE_THREAD_SERVER_H__
#include "RequestHandler.h"
#include <thread>
#include <functional>
using namespace std;

class ServerThread
{
public:
    
private: 
    thread internalThread;
};

class SingleThreadServer
{
public:
	SingleThreadServer();
	~SingleThreadServer();
	void start();
	void stop();
private:
    void loop();
	bool running;
    RequestHandler requestHandler;
	thread internalThread;
};
#endif//__SINGLE_THREAD_SERVER_H__
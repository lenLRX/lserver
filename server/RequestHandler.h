#ifndef __REQUEST_HANDLER_H__
#define __REQUEST_HANDLER_H__
#include "../network/http.h"
#include "../network/socket.h"
#include "../network/HttpRequest.h"
class RequestHandler
{
public:
    RequestHandler();
	~RequestHandler();
	void handle(Connection conn,HttpRequest request);
};
#endif//__REQUEST_HANDLER_H__
#ifndef __REQUEST_HANDLER_H__
#define __REQUEST_HANDLER_H__
#include "../network/http.h"
#include "../network/socket.h"
#include "../network/HttpRequest.h"
#include "../utility/ByteBuffer.h"
#include "../network/HttpResponse.h"
class RequestHandler
{
public:
    RequestHandler();
	~RequestHandler();
	void handle(Connection conn,HttpRequest request);
private:
    void code200(HttpResponse& response,
	const string& rfctime,const string& path);

	void code304(HttpResponse& response);

	void code404(HttpResponse& response,const string& path);
};
#endif//__REQUEST_HANDLER_H__
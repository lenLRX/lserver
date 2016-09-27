#include "test.h"
#include "../log/log.h"
#include "../utility/TimeUtility.h"
#include <string>
#include <time.h>

using namespace std;

bool time_conversion_test(){
	time_t origin_time = time(NULL);
	LOG << "origin_time: " << origin_time << endl;
	string originTime(ctime(&origin_time));
	string rfctime(ctime2rfc822date(originTime));
	time_t compute = rfc822date2time_t(rfctime);
	LOG << "rfc: " << rfctime << " got: " << compute << endl;

	if(compute == origin_time)
	    return true;
	else
	    return false;

	return true;
}

ADDTEST(time_conversion_test)
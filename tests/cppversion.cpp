#include "test.h"
#include "../log/log.h"

bool getCPPversion(){
	LOG<<__cplusplus<<endl;
}

ADDTEST(getCPPversion)
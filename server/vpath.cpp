#include "vpath.h"

vpath::vpath(){

}

vpath::~vpath(){

}

string vpath::translate(string origin){
	return string("../website/") + origin;
}
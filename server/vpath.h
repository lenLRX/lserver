#ifndef __VPATH_H__
#define __VPATH_H__
#include <string>
using namespace std;

//translate vritual path to real path
class vpath
{
public: 
    vpath();
	~vpath();
	string translate(string origin);
};
#endif//__VPATH_H__
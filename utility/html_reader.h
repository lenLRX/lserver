#ifndef __HTML_READER_H__
#define __HTML_READER_H__
#include <string>
#include <fstream>
#include "../network/http.h"
using namespace std;

string html_reader(string filename){
	string ret;
	ifstream html(filename);
	char buffer[512];
	
	while(html.getline(buffer,512)){
		ret += string(buffer) + crlf;
	}
	html.close();
	return ret;
}
#endif//__HTML_READER_H__
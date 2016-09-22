#include "html_reader.h"

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
#include "resource_reader.h"
#include "html_reader.h"
#include "BinaryReader.h"
#include "../log/log.h"
#include <algorithm>
#include <iostream>
Resource ResourceReader::getResource(string path){
	Resource resource;
	int len = path.length();
	int dotpos = -1;
	string suffix;
	for(int i = len - 1;i >=0; i--){
		if(path[i] == '.'){
			dotpos = i;
			break;
		}
		suffix.push_back(path[i]);
	}
	reverse(suffix.begin(),suffix.end());
	LOG << "type:" << suffix << endl << flush;
	if(suffix == "gif"){
		resource.type = "image/gif";
		resource.byteBuffer = BinaryReader(path);
	}else if(suffix == "html"){
		resource.type = html_type;
		resource.byteBuffer = BinaryReader(path);
		//resource.byteBuffer = html_reader(path);
	}else{
		resource.type = "test/plain";
		resource.byteBuffer = BinaryReader(path);
	}

	return resource;
}
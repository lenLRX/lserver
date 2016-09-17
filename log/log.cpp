#include "log.h"

Logger& Logger::operator << (ostream& (*_Pfn)(ostream&)){
	_Pfn(stream);
	return *this;
}

void Logger::flush(){
	stream.flush();
}

void Logger::redirectStream(string filename){
	_fstream.open(filename, ios::app | ios::out);
	stream.set_rdbuf(_fstream.rdbuf());
	stream.sync_with_stdio(false);
}

Logger& Logger::getInstance(){
	static Logger* theInstance = new Logger();
	return *theInstance;
}

Logger::Logger() :stream(cout.rdbuf())
{
	stream.sync_with_stdio(false);
}

Logger::~Logger()
{
	stream.flush();
}
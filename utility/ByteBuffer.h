#ifndef __BYTEBUFFER_H__
#define __BYTEBUFFER_H__
#include <utility>
#include <cstdlib>
using namespace std;

class ByteBuffer
{
public:
    ByteBuffer();
	ByteBuffer(ByteBuffer&& other);
	ByteBuffer(const ByteBuffer& other) = delete;
	ByteBuffer& operator = (ByteBuffer& other) = delete;
	
	~ByteBuffer();
	inline void rewind(){
		pointer = 0;
	}
	pair<void*,int> get(int nbytes);
	void put(void* ptr,int nbytes);
private:
    inline void increase_capacity(){
		capacity *= incr_factor;
		//didn't check return value (which might be NULL)
		buffer = (char*)realloc(buffer,capacity);
	}

    char* buffer;
	int pointer;
	int size;
	int capacity;
	const static int initial_capacity;
	const static float incr_factor;// capacity *= incr_factor;
};
#endif//__BYTEBUFFER_H__
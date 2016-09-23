#include "ByteBuffer.h"
#include <cstring>

const int ByteBuffer::initial_capacity = 32;
const float ByteBuffer::incr_factor = 1.5f;

ByteBuffer::ByteBuffer():
buffer(nullptr),pointer(0),size(0),capacity(initial_capacity){
	buffer = (char*)malloc(capacity);
}

ByteBuffer::ByteBuffer(ByteBuffer&& other):
buffer(other.buffer),pointer(other.pointer),
size(other.size),capacity(other.capacity){
	other.pointer = 0;
	other.size = 0;
	other.capacity = 0;
	other.buffer = nullptr;
}

ByteBuffer::~ByteBuffer(){
	free(buffer);
}

pair<void*,int> ByteBuffer::get(int nbytes){
	pair<void*,int> p;
	p.first = buffer + pointer;
	if(pointer + nbytes <= size)
	    p.second = nbytes;
	else
	    p.second = size - pointer;
	return p;
}

void ByteBuffer::put(void* ptr,int nbytes){
	while(size + nbytes > capacity){
		increase_capacity();
	}
	memcpy(buffer + size,ptr,nbytes);
}
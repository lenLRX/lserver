CC = g++
LD = g++
export CFLAGS = -g -pthread -std=c++11#order matters
LDFLAGS = -pthread
ROOT_DIR=$(shell pwd)
SUBDIRS=$(shell ls -d */|grep -v "build"|grep -v "temp"|grep -v "web")
SRCS := $(wildcard *.cpp)  
OBJS := $(patsubst %cpp,%o,$(SRCS))
EXES := $(patsubst %.cpp,%,$(SRCS))
COMMONOBJS=$(shell find ./build/obj -name "*.o")
export OBJDIR=$(ROOT_DIR)/build/obj/
BINDIR=$(ROOT_DIR)/build/bin/

.PHONY:all clean

.IGNORE:MKOBJDIR

all:MKOBJDIR $(SUBDIRS) $(OBJS) $(EXES)

$(EXES):
	$(LD) $(LDFLAGS) -o $(BINDIR)$@ $(COMMONOBJS) $@.o

$(SUBDIRS):ECHO
	make -C $@

%.o:%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@




MKOBJDIR:
	-mkdir build/obj/
	-mkdir build/bin/

ECHO:
	@echo $(SUBDIRS)

clean:
	rm -rf build/obj/
	rm -rf build/bin/
	rm *.o
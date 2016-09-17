CC = g++
LD = g++
CFLAGS = -std=c++11
ROOT_DIR=$(shell pwd)
SUBDIRS=$(shell ls -d */|grep -v "build"|grep -v "temp")
SRCS := $(wildcard *.cpp)  
OBJS := $(patsubst %cpp,%o,$(SRCS))
BULIDOBJS=$(shell find ./build/obj -name "*.o")
export OBJDIR=$(ROOT_DIR)/build/obj/

.PHONY: all

.IGNORE:MKOBJDIR

all:MKOBJDIR $(SUBDIRS) $(OBJS) runtests

runtests:
	$(LD) -o runtests $(BULIDOBJS)

$(SUBDIRS):ECHO
	make -C $@

%.o:%.cpp
	$(CC) $(CFLAGS) -c $^ -o $(OBJDIR)$@




MKOBJDIR:
	-mkdir build/obj/

ECHO:
	@echo $(SUBDIRS)


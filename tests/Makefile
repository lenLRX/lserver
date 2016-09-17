CC = g++
LD = g++
CFLAGS = -std=c++11

SRCS := $(wildcard *.cpp)  
OBJS := $(patsubst %cpp,%o,$(SRCS))

.PHONY: all

all:$(OBJS) ECHO

%.o:%.cpp
	$(CC) $(CFLAGS) -c $^ -o $(OBJDIR)$@

ECHO:
	@echo $(OBJDIR)
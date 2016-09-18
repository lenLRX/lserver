CC = g++
LD = g++

SRCS := $(wildcard *.cpp)  
OBJS := $(patsubst %cpp,%o,$(SRCS))

.PHONY: all

all:$(OBJS) ECHO

%.o:%.cpp
	$(CC) $(CFLAGS) -c $^ -o $(OBJDIR)$@

ECHO:
	@echo $(OBJDIR)
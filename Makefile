CC=g++
CFLAGS=-g -Wall
SRCS=fourdoku.cpp FDState.h FDState.cpp FDNode.h FDNode.cpp FDAction.h FDAction.cpp search.h search.cpp
OBJS=fourdoku.o FDState.o FDAction.o FDNode.o search.o

all:fourdoku

fourdoku:fourdoku.o FDAction.o FDState.o FDNode.o search.o
	$(CC) $(LFLAGS) $(OBJS) -o fourdoku

fourdoku.o:fourdoku.cpp
	$(CC) $(CFLAGS) -c fourdoku.cpp

FDAction.o:FDAction.h FDAction.cpp
	$(CC) $(CFLAGS) -c FDAction.cpp

FDState.o:FDState.h FDState.cpp
	$(CC) $(CFLAGS) -c FDState.cpp

FDNode.o:FDNode.h FDNode.cpp
	$(CC) $(CFLAGS) -c FDNode.cpp

search.o:search.h search.cpp
	$(CC) $(CFLAGS) -c search.cpp

clean:
	rm -rf $(OBJS) fourdoku


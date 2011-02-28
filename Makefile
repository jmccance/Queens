CC=g++
CFLAGS=-g -Wall
SRCS=queens.cpp QState.cpp QState.h
OBJS=queens.o QState.o
TARGET=queens

all:queens
	chmod u+x runTrials.sh

queens:queens.o QState.o
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

queens.o:queens.cpp
	$(CC) $(CFLAGS) -c queens.cpp

QState.o:QState.cpp QState.h
	$(CC) $(CFLAGS) -c QState.cpp

clean:
	rm -rf $(OBJS) $(TARGET)


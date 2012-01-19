CC=g++
CFLAGS=-g -Wall
OBJS=queens.o QState.o
TARGET=queens

all:$(TARGET)
	chmod u+x runTrials.sh

queens: QState.o

queens.o: QState.h

QState.o: Qstate.h

clean:
	rm -rf $(OBJS) $(TARGET)


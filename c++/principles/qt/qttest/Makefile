# this makefile is going to be called from one further up

TARGET=$(shell basename `pwd` )
TARGET_OBJS=$(patsubst %.cc, %.o, $(wildcard *.cc))
TARGET_DEPS=$(wildcard *.h)

TARGET_LIBS:=-L/usr/lib/qt-3.3/lib -lqui
TARGET_INCLUDES:=-I/usr/lib/qt-3.3/include

CC=g++ -g


all: $(TARGET)

$(TARGET): $(TARGET_OBJS)
	$(CC) -o $@ $(TARGET_LIBS) $^

$(TARGET_OBJS): $(strip $(TARGET_DEPS))

%.o: %.cc
	$(CC) -c $(TARGET_INCLUDES) -o $@ $*.cc

clean:
	rm -rf *.o *~ $(TARGET)

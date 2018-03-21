# this makefile is going to be called from one further up

TARGET=$(shell basename `pwd` )
TARGET_OBJS=$(patsubst %.c, %.o, $(wildcard *.c))
TARGET_DEPS=$(wildcard *.h)

TARGET_LIBS=
TARGET_INCLUDES=

CC=gcc -g


all: $(TARGET)

$(TARGET): $(TARGET_OBJS)
	$(CC) -o $@ $(TARGET_LIBS) $(TARGET_INCLUDES) $^

$(TARGET_OBJS): $(strip $(TARGET_DEPS))

%.o: %.cc
	$(CC) -c -o $@ $*.cc

%.o: %.c
	$(CC) -c -o $@ $*.c

clean:
	rm -rf *.o *~ $(TARGET)

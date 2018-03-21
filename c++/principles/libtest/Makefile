# this makefile is going to be called from one further up

TARGET=libtest
#TARGET_OBJS=$(patsubst "*.cc", "*.o", $(wildcard *.cc))
TARGET_OBJS=main.o
TARGET_DEPS=$(shell ls *.h)

TARGET_LIBS=-ltestlib -L./lib
TARGET_INCLUDES=-I. -I./lib

CC=g++ -g


all: $(TARGET)

$(TARGET): $(TARGET_OBJS) ./lib/libtestlib.so
	$(CC) -o $@ $(TARGET_LIBS) $^

$(TARGET_OBJS): $(strip $(TARGET_DEPS))

%.o: %.cc
	$(CC) -c $(TARGET_INCLUDES) -o $@ $*.cc

./lib/libtestlib.so: 
	make -C lib

clean:
	rm -rf *.o *~ $(TARGET)
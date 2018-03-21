# this makefile is going to be called from one further up

TARGET=libtestlib.so
TARGET_OBJS=testlib.o
TARGET_DEPS=$(shell ls *.h)

CC=g++ -g


all: $(TARGET)

$(TARGET): $(TARGET_OBJS)
	$(CC) -shared -fpic -o $@ $^

$(TARGET_OBJS): $(strip $(TARGET_DEPS))

%.o: %.cc
	$(CC) -c -fpic $(TARGET_INCLUDES) -o $@ $*.cc

clean:
	rm -rf *.o *~ $(TARGET)
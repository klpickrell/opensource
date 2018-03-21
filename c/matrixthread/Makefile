# this makefile is going to be called from one further up

TARGET=matrixthreads
TARGET_OBJS=$(patsubst %.c, %.o, $(wildcard *.c))
TARGET_DEPS=$(wildcard *.h)

TARGET_LIBS=-lpthread
TARGET_INCLUDES=

CC=gcc -g


all: $(TARGET)

$(TARGET): $(TARGET_OBJS)
	$(CC) -o $@ $(TARGET_LIBS) $(TARGET_INCLUDES) $^

$(TARGET_OBJS): $(strip $(TARGET_DEPS))

%.o: %.c
	$(CC) -c -o $@ $*.c

clean:
	rm -rf *.o *~ $(TARGET)

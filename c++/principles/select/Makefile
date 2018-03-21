# this makefile is going to be called from one further up

TARGET=select
TARGET_OBJS=main.o
TARGET_DEPS=$(shell ls *.h)

TARGET_LIBS=
TARGET_INCLUDES=

CC=g++ -g


all: $(TARGET)

$(TARGET): $(TARGET_OBJS)
	$(CC) -o $@ $(TARGET_LIBS) $(TARGET_INCLUDES) $^

$(TARGET_OBJS): $(strip $(TARGET_DEPS))

%.o: %.cc
	$(CC) -c -o $@ $*.cc

clean:
	rm -rf *.o *~ $(TARGET)
# this makefile is going to be called from one further up

TARGET=$(shell basename `pwd` )
TARGET_OBJS=$(patsubst %.cc, %.o, $(wildcard *.cc))
TARGET_DEPS=$(wildcard *.h)

TARGET_LIBS=
TARGET_INCLUDES=

CC=g++ -g

LOCAL_LD_FLAGS=-lrt


all: $(TARGET)

$(TARGET): $(TARGET_OBJS)
	$(CC) -o $@ $(LOCAL_LD_FLAGS) $(TARGET_LIBS) $(TARGET_INCLUDES) $^

$(TARGET_OBJS): $(strip $(TARGET_DEPS))

%.o: %.cc
	$(CC) -c -o $@ $*.cc

clean:
	rm -rf *.o *~ $(TARGET)

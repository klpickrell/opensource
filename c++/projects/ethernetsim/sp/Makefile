# this makefile is going to be called from one further up

include ../socketslib/Dependencies.make

TARGET=$(shell basename `pwd` )
TARGET_OBJS=$(patsubst %.cc, %.o, $(wildcard *.cc))
TARGET_DEPS=$(wildcard *.h)

LOCAL_LIBS=../socketslib/libsocketslib.a
LOCAL_INCLUDES=-I../socketslib 
TARGET_LIBS := -lboost_program_options

CC=g++ -g


all: libsocketslib.a $(TARGET)

$(TARGET): $(TARGET_OBJS) $(LOCAL_LIBS)
	$(CC) -o $@ $(LOCAL_INCLUDES) $(TARGET_LIBS) $(DEPENDENCIES.socketslib) $^

$(TARGET_OBJS): $(strip $(TARGET_DEPS))

%.o: %.cc
	$(CC) -c $(LOCAL_INCLUDES) -o $@ $*.cc

libsocketslib.a:
	make -C ../socketslib

clean:
	rm -rf *.o *~ $(TARGET)

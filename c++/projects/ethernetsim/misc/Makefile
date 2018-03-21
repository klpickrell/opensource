# this makefile is going to be called from one further up

TARGET=$(shell basename `pwd` )

TARGET_OBJS=$(patsubst %.cc, %.o, $(wildcard *.cc))
TARGET_DEPS=$(wildcard *.h)

TARGET_LIBS=-lboost_signals
TARGET_INCLUDES=

CC=g++ -g

all: lib$(TARGET).a

shared: $(TARGET_OBJS)
	$(CC) -fPIC -shared -o lib$(TARGET).so $(TARGET_LIBS) $(TARGET_INCLUDES) $^

lib$(TARGET).a: $(TARGET_OBJS)
	$(AR) cru lib$(TARGET).a $^

$(TARGET_OBJS): $(strip $(TARGET_DEPS))

%.o: %.cc
	$(CC) -c -o $@ $*.cc

.PHONY: clean
clean:
	rm -rf *.o *~ lib$(TARGET).so lib$(TARGET).a


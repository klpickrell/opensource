# this makefile is going to be called from one further up

TARGET=$(shell basename `pwd` )
TARGET_OBJS=$(patsubst %.cc, %.o, $(wildcard *.cc))
TARGET_DEPS=$(wildcard *.h)

TARGET_LIBS=
TARGET_INCLUDES=-I/work/SNAC/HEAD/HITSCP/uff_rec/include

CC=g++ -g


all: $(TARGET)

$(TARGET): $(TARGET_OBJS)
	$(CC) -o $@ $(TARGET_LIBS) $(TARGET_INCLUDES) $^

$(TARGET_OBJS): $(strip $(TARGET_DEPS))

%.o: %.cc
	$(CC) -c $(TARGET_INCLUDES) -o $@ $*.cc

clean:
	rm -rf *.o *~ $(TARGET)
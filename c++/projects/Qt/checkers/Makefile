# this makefile is going to be called from one further up

TARGET=checkers
TARGET_OBJS=boardwidget.o movevalidator.o engine.o mainframe.o main.o mainwindow.o tilewidget.o board.o newgamedialog.o
TARGET_DEPS=$(wildcard *.h)

TARGET_LIBS:=-L/usr/local/Trolltech/Qt-4.3.4/lib -lQtCore -lQtGui
TARGET_INCLUDES:=-I/usr/local/Trolltech/Qt-4.3.4/include 
TARGET_INCLUDES += -I/usr/local/Trolltech/Qt-4.3.4/include/QtCore \
		   -I/usr/local/Trolltech/Qt-4.3.4/include/QtGui  \
		   -I/usr/local/Trolltech/Qt-4.3.4/include/Qt

MOC=/usr/local/Trolltech/Qt-4.3.4/bin/moc

MOC_INCLUDES=mainwindow.h mainframe.h tilewidget.h boardwidget.h engine.h newgamedialog.h

MOC_FILES := $(patsubst %.h, moc_%.cc, $(MOC_INCLUDES))
MOC_OBJS := $(patsubst %.h, moc_%.o, $(MOC_INCLUDES))

QT_DEBUG=1

ifndef QT_DEBUG
	CC=g++ -g -DQT_NO_DEBUG_OUTPUT
else
	CC=g++ -g
endif

all: $(MOC_FILES) $(TARGET)

$(TARGET): $(TARGET_OBJS) $(MOC_OBJS)
	$(CC) -o $@ $(TARGET_LIBS) $^

$(TARGET_OBJS): $(strip $(TARGET_DEPS))


moc_tilewidget.cc: tilewidget.h
	$(MOC) -o $@ $^

moc_mainwindow.cc: mainwindow.h
	$(MOC) -o $@ $^

moc_boardwidget.cc: boardwidget.h
	$(MOC) -o $@ $^

moc_mainframe.cc: mainframe.h
	$(MOC) -o $@ $^

moc_engine.cc: engine.h
	$(MOC) -o $@ $^

moc_newgamedialog.cc: newgamedialog.h
	$(MOC) -o $@ $^


%.o: %.cc
	$(CC) -c $(TARGET_INCLUDES) -o $@ $*.cc

clean:
	rm -rf *.o *~ $(TARGET) moc_*.cc

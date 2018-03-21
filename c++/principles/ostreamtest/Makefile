ALL_PROGRAMS = test
all : $(ALL_PROGRAMS)
.Phony : all

SOI.o : SOI.h SOI.cc
	g++ -c SOI.cc
	
Signal.o : Signal.h Signal.cc SOI.h
	g++ -c Signal.cc
	
test : main.o Signal.o SOI.o
	g++ -o test main.o SOI.o Signal.o

main.o : main.cc Signal.h
	g++ -c main.cc

clean : 
	rm test main.o SOI.o Signal.o

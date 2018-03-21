PROJECT := yaccproj

.PHONY: grammar scanner clean

all: grammar scanner
	gcc -o $(PROJECT) grammar.c scanner.c

grammar:
	yacc -d -v -o grammar.c grammar.y
scanner:
	lex -oscanner.c scanner.l

clean:
	rm -f *~ scanner.c grammar.c grammar.h *.o $(PROJECT)

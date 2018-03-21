digit [0-9]
letter [a-z|A-Z]

%{
#include <stdio.h>
#include "grammar.h"
%}
%%

     /* comments */
;+.*          { ; }

     /* numbers and parens */
{digit}+     { printf( "NUMBER\n" ); return NUMBER; }
[()]         { return *yytext; }
\.           { return *yytext; }

     /* lispkit keywords */
let        { printf( "LET\n" ); return LET; }
letrec     { printf( "LETREC\n" ); return LETREC; }
lambda     { printf( "LAMBDA\n" ); return LAMBDA; }
defun      { printf( "DEFUN\n" ); return DEFUN; }
quote      { printf( "QUOTE\n" ); return QUOTE; }
add        { printf( "ADD\n" ); return ADD; }
sub        { printf( "SUB\n" ); return SUB; }
mul        { printf( "MUL\n" ); return MUL; }
div        { printf( "DIV\n" ); return DIV; }
rem        { printf( "REM\n" ); return REM; }
sq         { printf( "SQ\n" ); return SQ; }
odd        { printf( "ODD\n" ); return ODD; }
even       { printf( "EVEN\n" ); return EVEN; }
leq        { printf( "LEQ\n" ); return LEQ; }
eq         { printf( "EQ\n" ); return EQ; }
head       { printf( "HEAD\n" ); return HEAD; }
tail       { printf( "TAIL\n" ); return TAIL; }
atom       { printf( "ATOM\n" ); return ATOM; }
null       { printf( "NULL_TOKEN\n" ); return NULL_TOKEN; }
if         { printf( "IF\n" ); return IF; }
not        { printf( "NOT\n" ); return NOT; }
and        { printf( "AND\n" ); return AND; }
or         { printf( "OR\n" ); return OR; }
chr        { printf( "CHR\n" ); return CHR; }
cons       { printf( "CONS\n" ); return CONS; }
nil        { printf( "NIL\n" ); return NIL; }
true       { printf( "TRUE\n" ); return TRUE; }
false      { printf( "FALSE\n" ); return FALSE; }
car        { printf( "CAR\n" ); return CAR; }
cdr        { printf( "CDR\n" ); return CDR; }


     /* names */
{letter}({letter}|{digit})*      { printf( "NAME: %s\n", yytext ); return NAME; }


     /* whitespace and comments */
\n                      /* ignore end of line */;
[ \t]+                  /* ignore whitespace */;
%%


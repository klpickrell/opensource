%{

#include <stdio.h>

%}

/* lispkit keyword tokens */

%token LET LETREC LAMBDA DEFUN QUOTE ADD SUB MUL DIV REM SQ ODD EVEN
%token LEQ EQ HEAD TAIL ATOM NULL_TOKEN IF NOT AND OR CHR CONS NIL
%token TRUE FALSE CAR CDR

/* numbers and names */

%token NUMBER NAME

%union {
    int number;
    char* string;
}

%token <number> NUMBER
%token <string> NAME

%%

program: letrec_clause
       | lambda_clause
       | let_clause
       | defun_clause
       | call_clause
{
    /* code goes here */
    printf( "program\n" );
}
;

op_clause_list: '(' QUOTE NIL ')'
           | '(' one_place_op clause ')'
           | '(' two_place_op clause clause ')'
           | '(' three_place_op clause clause clause ')'
{
    /* code goes here */
    printf( "op_clause_list\n" );
}
;

one_place_op: SQ
            | ODD
            | EVEN
            | HEAD
            | TAIL
            | ATOM
            | NULL_TOKEN
            | NOT
            | CHR
{
    /* code goes here */
    printf( "one_place_op\n" );
}
;

two_place_op: ADD
            | SUB
            | MUL
            | DIV
            | REM
            | LEQ
            | EQ
            | AND
            | OR
            | CONS
{
    /* code goes here */
    printf( "two_place_op\n" );
}
;

three_place_op: IF
{
    /* code goes here */
    printf( "three_place_op\n" );
}
;

clause: letrec_clause
      | let_clause
      | lambda_clause
      | defun_clause
      | call_clause
      | quote_clause
      | op_clause_list
      | atom
{
    /* code goes here */
    printf( "clause\n" );
}
;

letrec_clause: '(' LETREC clause '.' declaration_list ')'
{
    /* code goes here */
    printf( "letrec_clause\n" );
}
;

let_clause: '(' LET clause '.' declaration_list ')'
{
    /* code goes here */
    printf( "let_clause\n" );
}
;

lambda_clause: '(' LAMBDA argument_list clause ')'
{
    /* code goes here */
    printf( "lambda_clause\n" );
}
;

defun_clause: '(' DEFUN name argument_list clause ')'
{
    /* code goes here */
    printf( "defun_clause\n" );
}
;

call_clause: '(' name ')'
           | '(' name clause_sequence ')'
{
    /* code goes here */
    printf( "call_clause\n" );
}
;

clause_sequence: clause
               | clause_sequence clause
{
    /* code goes here */
    printf( "clause_sequence\n" );
}
;

quote_clause: '(' QUOTE s_expression ')'
{
    /* code goes here */
    printf( "quote_clause\n" );
}
;

declaration_list: '(' QUOTE NIL ')'
                | non_empty_declaration_seq
{
    /* code goes here */
    printf( "declaration_list\n" );
}
;

non_empty_declaration_seq: '(' name '.' clause ')'
                         |  non_empty_declaration_seq '(' name '.' clause ')'
{
    /* code goes here */
    printf( "non_empty_declaration_seq\n" );
}
;

argument_list: '(' QUOTE NIL ')'
             | '(' non_empty_argument_seq ')'
{
    /* code goes here */
    printf( "argument_list\n" );
}
;

non_empty_argument_seq: name
                      | non_empty_argument_seq name
{
    /* code goes here */
    printf( "non_empty_argument_seq\n" );
}
;

s_expression: atom
            | '(' s_expression_seq ')'
{
    /* code goes here */
    printf( "s_expression\n" );
}
;

s_expression_seq: s_expression
                | s_expression '.' s_expression
                | s_expression_seq s_expression
{
    /* code goes here */
    printf( "s_expression_seq\n" );
}
;

atom: name
    | numeral
{
    /* code goes here */
    printf( "atom\n" );
}
;

name: NAME
{
    /* code goes here */
    printf( "name\n" );
}
;

numeral: NUMBER
{
    /* code goes here */
    printf( "numeral\n" );
}
;


%%


void yyerror(const char *str)
{
    fprintf(stderr,"error: %s\n",str);
}
 
int yywrap()
{
    return 1;
} 
  
main()
{
    yyparse();
}


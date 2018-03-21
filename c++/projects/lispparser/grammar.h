#ifndef YYERRCODE
#define YYERRCODE 256
#endif

#define LET 257
#define LETREC 258
#define LAMBDA 259
#define DEFUN 260
#define QUOTE 261
#define ADD 262
#define SUB 263
#define MUL 264
#define DIV 265
#define REM 266
#define SQ 267
#define ODD 268
#define EVEN 269
#define LEQ 270
#define EQ 271
#define HEAD 272
#define TAIL 273
#define ATOM 274
#define NULL_TOKEN 275
#define IF 276
#define NOT 277
#define AND 278
#define OR 279
#define CHR 280
#define CONS 281
#define NIL 282
#define TRUE 283
#define FALSE 284
#define CAR 285
#define CDR 286
#define NUMBER 287
#define NAME 288
typedef union {
    int number;
    char* string;
} YYSTYPE;
extern YYSTYPE yylval;

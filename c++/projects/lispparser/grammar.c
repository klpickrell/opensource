#ifndef lint
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
static int yygrowstack();
#define YYPREFIX "yy"
#line 2 "grammar.y"

#include <stdio.h>

#line 17 "grammar.y"
typedef union {
    int number;
    char* string;
} YYSTYPE;
#line 26 "grammar.c"
#define YYERRCODE 256
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
const short yylhs[] = {                                        -1,
    0,    0,    0,    0,    0,    6,    6,    6,    6,    7,
    7,    7,    7,    7,    7,    7,    7,    7,    9,    9,
    9,    9,    9,    9,    9,    9,    9,    9,   10,    8,
    8,    8,    8,    8,    8,    8,    8,    1,    3,    2,
    4,    5,    5,   16,   16,   11,   13,   13,   18,   18,
   14,   14,   19,   19,   17,   17,   20,   20,   20,   12,
   12,   15,   21,
};
const short yylen[] = {                                         2,
    1,    1,    1,    1,    1,    4,    4,    5,    6,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    6,    6,    5,
    6,    3,    4,    1,    2,    4,    4,    1,    5,    6,
    4,    3,    1,    2,    1,    3,    1,    3,    2,    1,
    1,    1,    1,
};
const short yydefred[] = {                                      0,
    0,    0,    1,    2,    3,    4,    5,    0,    0,    0,
    0,   62,    0,   63,    0,   30,   32,   31,   33,   34,
   36,    0,   35,   37,   60,   61,    0,    0,    0,    0,
   42,   44,    0,    0,   19,   20,   21,   22,   23,   10,
   11,   12,   24,   25,   13,   14,   15,   16,   29,   17,
   26,   27,   18,   28,    0,    0,    0,    0,    0,    0,
   53,    0,    0,    0,   43,   45,    0,    0,   55,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   52,   54,
   40,    0,    6,    0,    0,   46,    7,    0,    0,    0,
    0,   39,    0,   38,   51,   41,    0,   56,   59,    8,
    0,    0,    0,    0,   58,    9,   47,    0,    0,   49,
    0,   50,
};
const short yydgoto[] = {                                       2,
   16,   17,   18,   19,   20,   21,   55,   22,   56,   57,
   23,   24,   75,   29,   25,   33,   70,   76,   62,   85,
   26,
};
const short yysindex[] = {                                    -17,
 -240,    0,    0,    0,    0,    0,    0,  -30,  -30,  -16,
 -263,    0,  -40,    0, -145,    0,    0,    0,    0,    0,
    0,  -19,    0,    0,    0,    0,  -18, -248,  -30,  -16,
    0,    0,  -38,  -36,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -30,  -30,  -30,  -11,  -11, -250,
    0,  -27,   -8,  -30,    0,    0,   -7,  -28,    0,   -5,
   -4,  -30,  -30, -239,    1,    4,    5,    6,    0,    0,
    0,   10,    0,   -1,  -34,    0,    0,   11,  -30, -241,
    7,    0, -263,    0,    0,    0,  -28,    0,    0,    0,
   13,   14,  -30,   16,    0,    0,    0,   19,  -30,    0,
   20,    0,
};
const short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   22,    0,    0,    0,    0,
    0,    0,    0,  -32,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,
};
const short yygindex[] = {                                      0,
   64,   65,   67,   69,   70,    0,    0,    2,    0,    0,
    0,  -29,   12,   42,   15,    0,  -47,    0,    0,    0,
    0,
};
#define YYTABLESIZE 261
const short yytable[] = {                                      15,
   31,   15,   65,   68,   69,   68,   98,   57,   57,   15,
   27,   68,   60,   79,   32,   13,    8,    9,   10,   11,
   84,   90,    1,   28,   12,   30,   58,   59,   74,   13,
   63,   78,   81,   83,   66,   86,   87,   99,   69,   12,
  102,   92,   61,   93,   97,   94,   95,   12,   12,  105,
   96,  100,  103,  106,  107,   69,   71,   72,   73,  110,
  112,  109,   48,    3,    4,   82,    5,   69,    6,    7,
   77,   64,    0,   88,   89,    0,   80,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   91,    0,
  101,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  108,    0,    0,  104,    0,    0,
  111,    8,    9,   10,   11,   34,   35,   36,   37,   38,
   39,   40,   41,   42,   43,   44,   45,   46,   47,   48,
   49,   50,   51,   52,   53,   54,    0,    0,    0,    0,
    0,    0,   12,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   67,   14,   12,   14,   12,
   14,   12,   14,   12,   57,   57,   14,   12,   14,   12,
   12,
};
const short yycheck[] = {                                      40,
   41,   40,   41,   40,   34,   40,   41,   40,   41,   40,
    9,   40,  261,   41,   13,    1,  257,  258,  259,  260,
   68,  261,   40,   40,  288,   11,   46,   46,   40,   15,
   29,  282,   41,   41,   33,   41,   41,   85,   68,  288,
  282,   41,   28,   40,   46,   41,   41,  288,  288,   97,
   41,   41,   46,   41,   41,   85,   55,   56,   57,   41,
   41,   46,   41,    0,    0,   64,    0,   97,    0,    0,
   59,   30,   -1,   72,   73,   -1,   62,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   74,   -1,
   89,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  103,   -1,   -1,   93,   -1,   -1,
  109,  257,  258,  259,  260,  261,  262,  263,  264,  265,
  266,  267,  268,  269,  270,  271,  272,  273,  274,  275,
  276,  277,  278,  279,  280,  281,   -1,   -1,   -1,   -1,
   -1,   -1,  288,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  282,  287,  288,  287,  288,
  287,  288,  287,  288,  287,  288,  287,  288,  287,  288,
  288,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 288
#if YYDEBUG
const char * const yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,0,0,"'.'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"LET","LETREC",
"LAMBDA","DEFUN","QUOTE","ADD","SUB","MUL","DIV","REM","SQ","ODD","EVEN","LEQ",
"EQ","HEAD","TAIL","ATOM","NULL_TOKEN","IF","NOT","AND","OR","CHR","CONS","NIL",
"TRUE","FALSE","CAR","CDR","NUMBER","NAME",
};
const char * const yyrule[] = {
"$accept : program",
"program : letrec_clause",
"program : lambda_clause",
"program : let_clause",
"program : defun_clause",
"program : call_clause",
"op_clause_list : '(' QUOTE NIL ')'",
"op_clause_list : '(' one_place_op clause ')'",
"op_clause_list : '(' two_place_op clause clause ')'",
"op_clause_list : '(' three_place_op clause clause clause ')'",
"one_place_op : SQ",
"one_place_op : ODD",
"one_place_op : EVEN",
"one_place_op : HEAD",
"one_place_op : TAIL",
"one_place_op : ATOM",
"one_place_op : NULL_TOKEN",
"one_place_op : NOT",
"one_place_op : CHR",
"two_place_op : ADD",
"two_place_op : SUB",
"two_place_op : MUL",
"two_place_op : DIV",
"two_place_op : REM",
"two_place_op : LEQ",
"two_place_op : EQ",
"two_place_op : AND",
"two_place_op : OR",
"two_place_op : CONS",
"three_place_op : IF",
"clause : letrec_clause",
"clause : let_clause",
"clause : lambda_clause",
"clause : defun_clause",
"clause : call_clause",
"clause : quote_clause",
"clause : op_clause_list",
"clause : atom",
"letrec_clause : '(' LETREC clause '.' declaration_list ')'",
"let_clause : '(' LET clause '.' declaration_list ')'",
"lambda_clause : '(' LAMBDA argument_list clause ')'",
"defun_clause : '(' DEFUN name argument_list clause ')'",
"call_clause : '(' name ')'",
"call_clause : '(' name clause_sequence ')'",
"clause_sequence : clause",
"clause_sequence : clause_sequence clause",
"quote_clause : '(' QUOTE s_expression ')'",
"declaration_list : '(' QUOTE NIL ')'",
"declaration_list : non_empty_declaration_seq",
"non_empty_declaration_seq : '(' name '.' clause ')'",
"non_empty_declaration_seq : non_empty_declaration_seq '(' name '.' clause ')'",
"argument_list : '(' QUOTE NIL ')'",
"argument_list : '(' non_empty_argument_seq ')'",
"non_empty_argument_seq : name",
"non_empty_argument_seq : non_empty_argument_seq name",
"s_expression : atom",
"s_expression : '(' s_expression_seq ')'",
"s_expression_seq : s_expression",
"s_expression_seq : s_expression '.' s_expression",
"s_expression_seq : s_expression_seq s_expression",
"atom : name",
"atom : numeral",
"name : NAME",
"numeral : NUMBER",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 224 "grammar.y"


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

#line 319 "grammar.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 5:
#line 32 "grammar.y"
{
    /* code goes here */
    printf( "program\n" );
}
break;
case 9:
#line 42 "grammar.y"
{
    /* code goes here */
    printf( "op_clause_list\n" );
}
break;
case 18:
#line 57 "grammar.y"
{
    /* code goes here */
    printf( "one_place_op\n" );
}
break;
case 28:
#line 73 "grammar.y"
{
    /* code goes here */
    printf( "two_place_op\n" );
}
break;
case 29:
#line 80 "grammar.y"
{
    /* code goes here */
    printf( "three_place_op\n" );
}
break;
case 37:
#line 94 "grammar.y"
{
    /* code goes here */
    printf( "clause\n" );
}
break;
case 38:
#line 101 "grammar.y"
{
    /* code goes here */
    printf( "letrec_clause\n" );
}
break;
case 39:
#line 108 "grammar.y"
{
    /* code goes here */
    printf( "let_clause\n" );
}
break;
case 40:
#line 115 "grammar.y"
{
    /* code goes here */
    printf( "lambda_clause\n" );
}
break;
case 41:
#line 122 "grammar.y"
{
    /* code goes here */
    printf( "defun_clause\n" );
}
break;
case 43:
#line 130 "grammar.y"
{
    /* code goes here */
    printf( "call_clause\n" );
}
break;
case 45:
#line 138 "grammar.y"
{
    /* code goes here */
    printf( "clause_sequence\n" );
}
break;
case 46:
#line 145 "grammar.y"
{
    /* code goes here */
    printf( "quote_clause\n" );
}
break;
case 48:
#line 153 "grammar.y"
{
    /* code goes here */
    printf( "declaration_list\n" );
}
break;
case 50:
#line 161 "grammar.y"
{
    /* code goes here */
    printf( "non_empty_declaration_seq\n" );
}
break;
case 52:
#line 169 "grammar.y"
{
    /* code goes here */
    printf( "argument_list\n" );
}
break;
case 54:
#line 177 "grammar.y"
{
    /* code goes here */
    printf( "non_empty_argument_seq\n" );
}
break;
case 56:
#line 185 "grammar.y"
{
    /* code goes here */
    printf( "s_expression\n" );
}
break;
case 59:
#line 194 "grammar.y"
{
    /* code goes here */
    printf( "s_expression_seq\n" );
}
break;
case 61:
#line 202 "grammar.y"
{
    /* code goes here */
    printf( "atom\n" );
}
break;
case 62:
#line 209 "grammar.y"
{
    /* code goes here */
    printf( "name\n" );
}
break;
case 63:
#line 216 "grammar.y"
{
    /* code goes here */
    printf( "numeral\n" );
}
break;
#line 668 "grammar.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}

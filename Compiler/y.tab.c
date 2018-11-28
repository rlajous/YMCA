/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 1 "yacc.y"

#include<stdio.h>

int regs[26];
int base;

extern int yylex();

#line 13 "yacc.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  	int a;
    char * text;
  	int value;

  	/* program_node* program_node;*/
  	/* defines_node* defines_node;*/
  	/* define_node* define_node;*/
  	/* functions_node* functions_node;*/
  	/* function_node* function_node;*/
  	/* type_node * type_node;*/
  	/* parameters_node* parameters_node;*/
  	/* sentences_node* sentences_node;*/
  	/* sentence_node* sentence_node;*/
  	/* declaration_node * declaration_node;*/
  	/* variable_opration_node* variable_opration_node;*/
  	/* assignment_node* assignment_node;*/
  	/* queue_stack_node* queue_stack_node;*/
  	/* elements_node* elements_node;*/
  	/* element_node* element_node;*/
  	/* if_node* if_node;*/
  	/* while_node* while_node;*/
  	/* for_node* for_node;*/
  	/* condition_node* condition_node;*/
  	/* expression_node* expression_node;*/
  	/* function_execute_node* function_execute_node;*/
  	/* call_parameters_node* call_parameters_node;*/
  	/* call_parameter_node* call_parameter_node;*/
  	/* return_node* return_node;*/
  } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 68 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define DIGIT 257
#define LETTER 258
#define SEMICOLON 259
#define COLON 260
#define COMMA 261
#define OPEN_CURLY_BRACES 262
#define CLOSE_CURLY_BRACES 263
#define LESS_THAN 264
#define GREATER_THAN 265
#define OPEN_PARENTHESES 266
#define CLOSE_PARENTHESES 267
#define OPEN_BRACKET 268
#define CLOSE_BRACKET 269
#define PLUS 270
#define MINUS 271
#define MULTIPLY 272
#define DIVIDE 273
#define MOD 274
#define EQUAL 275
#define NOT_EQUAL 276
#define GREATER_OR_EQUAL 277
#define LESS_OR_EQUAL 278
#define AND 279
#define OR 280
#define RETURN 281
#define DEFINE 282
#define FOR 283
#define WHILE 284
#define IF 285
#define ELSE 286
#define BOOLEAN_TYPE 287
#define INTEGER_TYPE 288
#define STRING_TYPE 289
#define MAIN 290
#define BOOLEAN 291
#define NAME 292
#define STRING 293
#define INTEGER 294
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    3,    3,    3,    2,    2,    4,    5,
    6,    6,    6,    7,    7,    9,    9,   10,    8,    8,
   11,   11,   12,   12,   12,   12,   12,   12,   12,   14,
   15,   16,   16,   13,   13,   17,   17,   17,   18,   22,
   22,   23,   23,   24,   24,   19,   20,   20,   20,   20,
   20,   20,   20,   20,   20,   20,   21,   21,   25,   25,
   25,   25,   25,   25,   25,   25,   25,
};
static const YYINT yylen[] = {                            2,
    2,    2,    1,    3,    3,    3,    2,    1,    8,    7,
    1,    1,    1,    1,    0,    3,    1,    2,    1,    0,
    2,    1,    2,    1,    1,    1,    2,    2,    2,   11,
    7,    7,   11,    2,    2,    1,    3,    3,    4,    0,
    1,    3,    1,    1,    1,    2,    1,    3,    4,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    1,    1,
    1,    1,    3,    3,    3,    3,    3,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    0,    0,   12,   11,   13,    1,    0,
    8,    0,    2,    4,    6,    5,    7,    0,    0,    0,
    0,    0,    0,    0,   14,    0,    0,   18,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   19,    0,    0,
   24,   25,   26,    0,    0,    0,   36,    0,   16,   59,
    0,   61,   62,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   35,   10,   21,   23,   27,   28,   29,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   45,    0,   41,    0,    0,   37,   38,   58,
    0,    9,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   39,
    0,    0,   48,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   42,    0,    0,    0,    0,    0,   31,
    0,    0,    0,    0,    0,    0,    0,   30,   33,
};
static const YYINT yydgoto[] = {                          2,
    3,    9,    4,   10,   11,   36,   24,   37,   25,   26,
   38,   39,   40,   41,   42,   43,   44,   53,   46,   80,
   47,   84,   85,   86,   81,
};
static const YYINT yysindex[] = {                      -272,
 -279,    0,  -60, -272, -192,    0,    0,    0,    0,  -60,
    0, -270,    0,    0,    0,    0,    0, -249, -241, -235,
  -60, -195, -245, -201,    0, -186,  -36,    0, -165,  -60,
 -206, -145, -142, -137,  -16, -162, -158,    0,  -36, -116,
    0,    0,    0, -114, -113, -107,    0,  -36,    0,    0,
 -102,    0,    0,  -10, -136, -257, -257,  -26,  -98, -118,
  -22, -101,    0,    0,    0,    0,    0,    0,    0,  -82,
 -206, -206, -206, -206, -206, -148,  -84, -257,    0, -215,
  -39, -187,    0,  -85,    0,  -76,  -10,    0,    0,    0,
  -10,    0,  -10,  -10,  -10,  -10,  -10, -257, -185,  -58,
 -257, -257, -206, -206,  -68, -206, -206, -206,  -50,    0,
  -26, -256,    0,  -36, -219, -219,  -10,  -10, -206,  -10,
  -10,  -10,  -36,    0, -136,  -54,  -10,  -48,  -57,    0,
  -46,  -21,  -18,  -36,  -36,  -17,   -6,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,  -14,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   -9,    0,    0,    0,    0,    9,   14,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   15,    0,
    0,    0,    0,    0,    0,    0,    0,   14,    0,    0,
 -161,    0,    0,   20,    0,    0,    0,   13,    0,    0,
    0,   22,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -139,    0,
    0,    0,    0,    0,    0,   16, -231,    0,    0,    0,
 -253,    0, -117, -110,  -88,  -81,  -59,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   14, -252, -251, -240, -211,    0, -196,
  -66,  -56,   14,    0,    0,    0,  -37,    0,    0,    0,
 -230,    0,    0,   14,   14,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  278,  274,    0,    0,    0,    8,    0,  -44,  255,    0,
  247,    0,    0,    0,    0,    0,  -53,  -27,    0,  -52,
  251,    0,  177,    0,  -30,
};
#define YYTABLESIZE 288
static const YYINT yytable[] = {                         45,
   54,   77,  125,   70,   82,   57,   56,   55,   78,    1,
   12,   45,    5,   57,   56,   55,   20,   12,   52,   18,
   45,   19,  101,  102,   21,   99,   52,   87,   23,   44,
   91,   22,   32,   79,   51,   44,   52,   23,   52,   52,
   93,   94,   95,   96,   97,  112,   28,   51,  115,  116,
   32,  100,   32,   32,   32,   51,   32,   32,   32,  101,
  102,   32,   50,  101,  102,   29,   27,   51,   51,  126,
   50,  129,  117,  118,   30,  120,  121,  122,  128,  109,
   87,  113,   50,   50,   50,   51,   45,   52,  127,  136,
  137,  101,  102,  101,  102,   45,   48,   60,   14,   60,
   15,   16,   60,   60,   64,   60,   45,   45,   60,   60,
   60,   60,   60,   60,   60,   60,   60,   60,   60,   47,
   55,   59,   60,   56,   59,   59,   61,   47,   57,   62,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   47,
   47,   63,   66,   63,   67,   68,   63,   63,   64,   63,
   64,   69,   89,   64,   64,   76,   64,   63,   63,   63,
   63,   63,   63,   58,   64,   64,   64,   64,   64,   64,
   67,   88,   67,   61,   98,   67,   67,   66,   67,   66,
   92,  110,   66,   66,  111,   66,   67,   67,   67,   67,
   67,   67,   53,   66,   66,   66,   66,   66,   66,   65,
   53,   65,   54,  114,   65,   65,  119,   65,  130,  132,
   54,  123,   53,   53,  131,   65,   65,   65,   65,   65,
   65,   49,   54,   54,  103,  104,    6,    7,    8,   49,
   71,   72,   73,   74,   75,  105,  106,  107,  108,  133,
  134,   49,   49,  135,   31,  138,   32,   33,   34,   58,
    6,    7,    8,   59,   60,   35,  139,   15,   61,   71,
   72,   73,   74,   75,   50,   51,   83,   52,   50,   51,
   90,   52,    3,    3,    3,   17,   20,   22,   46,   40,
   34,   13,   43,   17,   49,   65,   63,  124,
};
static const YYINT yycheck[] = {                         27,
   31,   55,  259,   48,   57,  259,  259,  259,  266,  282,
    3,   39,  292,  267,  267,  267,  266,   10,  259,  290,
   48,  292,  279,  280,  266,   78,  267,   58,   21,  261,
   61,  267,  263,  291,  292,  267,  294,   30,  279,  280,
   71,   72,   73,   74,   75,   98,  292,  259,  101,  102,
  281,  267,  283,  284,  285,  267,  287,  288,  289,  279,
  280,  292,  259,  279,  280,  267,  262,  279,  280,  114,
  267,  125,  103,  104,  261,  106,  107,  108,  123,  267,
  111,  267,  279,  280,  291,  292,  114,  294,  119,  134,
  135,  279,  280,  279,  280,  123,  262,  259,  291,  261,
  293,  294,  264,  265,  263,  267,  134,  135,  270,  271,
  272,  273,  274,  275,  276,  277,  278,  279,  280,  259,
  266,  270,  271,  266,  264,  265,  275,  267,  266,  292,
  270,  271,  272,  273,  274,  275,  276,  277,  278,  279,
  280,  259,  259,  261,  259,  259,  264,  265,  259,  267,
  261,  259,  271,  264,  265,  292,  267,  275,  276,  277,
  278,  279,  280,  266,  275,  276,  277,  278,  279,  280,
  259,  270,  261,  275,  259,  264,  265,  259,  267,  261,
  263,  267,  264,  265,  261,  267,  275,  276,  277,  278,
  279,  280,  259,  275,  276,  277,  278,  279,  280,  259,
  267,  261,  259,  262,  264,  265,  275,  267,  263,  267,
  267,  262,  279,  280,  263,  275,  276,  277,  278,  279,
  280,  259,  279,  280,  264,  265,  287,  288,  289,  267,
  270,  271,  272,  273,  274,  275,  276,  277,  278,  286,
  262,  279,  280,  262,  281,  263,  283,  284,  285,  266,
  287,  288,  289,  270,  271,  292,  263,  267,  275,  270,
  271,  272,  273,  274,  291,  292,  293,  294,  291,  292,
  293,  294,  287,  288,  289,  267,  263,  263,  259,  267,
  259,    4,  267,   10,   30,   39,   36,  111,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 294
#define YYUNDFTOKEN 322
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"DIGIT","LETTER","SEMICOLON",
"COLON","COMMA","OPEN_CURLY_BRACES","CLOSE_CURLY_BRACES","LESS_THAN",
"GREATER_THAN","OPEN_PARENTHESES","CLOSE_PARENTHESES","OPEN_BRACKET",
"CLOSE_BRACKET","PLUS","MINUS","MULTIPLY","DIVIDE","MOD","EQUAL","NOT_EQUAL",
"GREATER_OR_EQUAL","LESS_OR_EQUAL","AND","OR","RETURN","DEFINE","FOR","WHILE",
"IF","ELSE","BOOLEAN_TYPE","INTEGER_TYPE","STRING_TYPE","MAIN","BOOLEAN","NAME",
"STRING","INTEGER",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : defines functions",
"defines : define defines",
"defines : define",
"define : DEFINE NAME BOOLEAN",
"define : DEFINE NAME INTEGER",
"define : DEFINE NAME STRING",
"functions : function functions",
"functions : main",
"function : type NAME OPEN_PARENTHESES args CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES",
"main : type MAIN OPEN_PARENTHESES CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES",
"type : INTEGER_TYPE",
"type : BOOLEAN_TYPE",
"type : STRING_TYPE",
"args : params",
"args :",
"params : param COMMA params",
"params : param",
"param : type NAME",
"body : sentences",
"body :",
"sentences : sentence sentences",
"sentences : sentence",
"sentence : declaration SEMICOLON",
"sentence : for",
"sentence : while",
"sentence : if",
"sentence : var_operation SEMICOLON",
"sentence : func_call SEMICOLON",
"sentence : return SEMICOLON",
"for : FOR OPEN_PARENTHESES var_operation SEMICOLON condition SEMICOLON var_operation CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES",
"while : WHILE OPEN_PARENTHESES condition CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES",
"if : IF OPEN_PARENTHESES condition CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES",
"if : IF OPEN_PARENTHESES condition CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES ELSE OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES",
"declaration : type NAME",
"declaration : type assignment",
"var_operation : assignment",
"var_operation : NAME PLUS PLUS",
"var_operation : NAME MINUS MINUS",
"func_call : NAME OPEN_PARENTHESES call_args CLOSE_PARENTHESES",
"call_args :",
"call_args : call_params",
"call_params : call_param COMMA call_params",
"call_params : call_param",
"call_param : expresion",
"call_param : STRING",
"return : RETURN expresion",
"condition : BOOLEAN",
"condition : OPEN_PARENTHESES condition CLOSE_PARENTHESES",
"condition : expresion EQUAL EQUAL expresion",
"condition : expresion NOT_EQUAL expresion",
"condition : expresion GREATER_THAN expresion",
"condition : expresion LESS_THAN expresion",
"condition : expresion GREATER_OR_EQUAL expresion",
"condition : expresion LESS_OR_EQUAL expresion",
"condition : condition OR condition",
"condition : condition AND condition",
"assignment : NAME EQUAL expresion",
"assignment : NAME EQUAL STRING",
"expresion : BOOLEAN",
"expresion : NAME",
"expresion : INTEGER",
"expresion : func_call",
"expresion : expresion PLUS expresion",
"expresion : expresion MINUS expresion",
"expresion : expresion MOD expresion",
"expresion : expresion DIVIDE expresion",
"expresion : expresion MULTIPLY expresion",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 209 "yacc.y"

int main()
{
 return(yyparse());
}

void yyerror(s)
char *s;
{
  fprintf(stderr, "%s\n",s);
}

int yywrap()
{
  return(1);
}
#line 428 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
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
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
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

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 89 "yacc.y"
	{}
break;
case 2:
#line 92 "yacc.y"
	{}
break;
case 3:
#line 93 "yacc.y"
	{}
break;
case 4:
#line 95 "yacc.y"
	{}
break;
case 5:
#line 96 "yacc.y"
	{}
break;
case 6:
#line 97 "yacc.y"
	{}
break;
case 7:
#line 100 "yacc.y"
	{}
break;
case 8:
#line 101 "yacc.y"
	{}
break;
case 9:
#line 104 "yacc.y"
	{}
break;
case 10:
#line 107 "yacc.y"
	{}
break;
case 11:
#line 109 "yacc.y"
	{}
break;
case 12:
#line 110 "yacc.y"
	{}
break;
case 13:
#line 111 "yacc.y"
	{}
break;
case 14:
#line 114 "yacc.y"
	{}
break;
case 15:
#line 115 "yacc.y"
	{}
break;
case 16:
#line 118 "yacc.y"
	{}
break;
case 17:
#line 119 "yacc.y"
	{}
break;
case 18:
#line 122 "yacc.y"
	{}
break;
case 19:
#line 125 "yacc.y"
	{}
break;
case 20:
#line 126 "yacc.y"
	{}
break;
case 21:
#line 129 "yacc.y"
	{}
break;
case 22:
#line 130 "yacc.y"
	{}
break;
case 23:
#line 133 "yacc.y"
	{}
break;
case 24:
#line 134 "yacc.y"
	{}
break;
case 25:
#line 135 "yacc.y"
	{}
break;
case 26:
#line 136 "yacc.y"
	{}
break;
case 27:
#line 137 "yacc.y"
	{}
break;
case 28:
#line 138 "yacc.y"
	{}
break;
case 29:
#line 139 "yacc.y"
	{}
break;
case 30:
#line 142 "yacc.y"
	{}
break;
case 31:
#line 145 "yacc.y"
	{}
break;
case 32:
#line 148 "yacc.y"
	{}
break;
case 33:
#line 149 "yacc.y"
	{}
break;
case 34:
#line 152 "yacc.y"
	{}
break;
case 35:
#line 153 "yacc.y"
	{}
break;
case 36:
#line 156 "yacc.y"
	{}
break;
case 37:
#line 157 "yacc.y"
	{}
break;
case 38:
#line 158 "yacc.y"
	{}
break;
case 39:
#line 161 "yacc.y"
	{}
break;
case 40:
#line 164 "yacc.y"
	{}
break;
case 41:
#line 165 "yacc.y"
	{}
break;
case 42:
#line 168 "yacc.y"
	{}
break;
case 43:
#line 169 "yacc.y"
	{}
break;
case 44:
#line 172 "yacc.y"
	{}
break;
case 45:
#line 173 "yacc.y"
	{}
break;
case 46:
#line 176 "yacc.y"
	{}
break;
case 47:
#line 179 "yacc.y"
	{}
break;
case 48:
#line 180 "yacc.y"
	{}
break;
case 49:
#line 181 "yacc.y"
	{}
break;
case 50:
#line 182 "yacc.y"
	{}
break;
case 51:
#line 183 "yacc.y"
	{}
break;
case 52:
#line 184 "yacc.y"
	{}
break;
case 53:
#line 185 "yacc.y"
	{}
break;
case 54:
#line 186 "yacc.y"
	{}
break;
case 55:
#line 187 "yacc.y"
	{}
break;
case 56:
#line 188 "yacc.y"
	{}
break;
case 57:
#line 192 "yacc.y"
	{}
break;
case 58:
#line 193 "yacc.y"
	{}
break;
case 59:
#line 196 "yacc.y"
	{}
break;
case 60:
#line 197 "yacc.y"
	{}
break;
case 61:
#line 198 "yacc.y"
	{}
break;
case 62:
#line 199 "yacc.y"
	{}
break;
case 63:
#line 200 "yacc.y"
	{}
break;
case 64:
#line 201 "yacc.y"
	{}
break;
case 65:
#line 202 "yacc.y"
	{}
break;
case 66:
#line 203 "yacc.y"
	{}
break;
case 67:
#line 204 "yacc.y"
	{}
break;
#line 898 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
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
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}

%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
";"                     {return SEMICOLON;}
":"                     {return COLON;}
","                     {return COMMA;}
"{"                     {return OPEN_CURLY_BRACES;}
"}"                     {return CLOSE_CURLY_BRACES;}
"<"                     {return LESS_THAN;}
">"                     {return GREATER_THAN;}
"("                     {return OPEN_PARENTHESES;}
")"                     {return CLOSE_PARENTHESES;}
"["                     {return OPEN_BRACKET;}
"]"                     {return CLOSE_BRACKET;}
"+"                     {return PLUS;}
"-"                     {return MINUS;}
"*"                     {return MULTIPLY;}
"/"                     {return DIVIDE;}
"%"                     {return MOD;}
"="                     {return EQUAL;}
"!="                    {return NOT_EQUAL;}
">="                    {return GREATER_OR_EQUAL;}
"<="                    { return LESS_OR_EQUAL;}

"||"                    {return OR;}
"&&"                    {return AND;}

"return"                {return RETURN;}
"define"                {return DEFINE;}
"for"                   {return FOR;}
"while"                 {return WHILE;}
"if"                    {return IF;}
"else"                  {return ELSE;}

"boolean"               {return BOOLEAN_TYPE;}
"int"                   {return INTEGER_TYPE;}
"string"                {return STRING_TYPE;}

"main"                  {return MAIN;}

"true"                  {yylval.value = 1; return BOOLEAN;}
"false"                 {yylval.value = 0; return BOOLEAN;}
[0-9]+					{yylval.value = atoi(yytext);
						return INTEGER;}

[a-zA-Z]([a-zA-Z0-9_])*	{yylval.text = malloc(yyleng + 1);
                        memcpy(yylval.text, yytext, yyleng);
                        (yylval.text)[yyleng] = '\0';
					    return NAME;}

\"[^\"]*\"				{yylval.text = malloc(yyleng + 1);
                        memcpy(yylval.text, yytext, yyleng);
                        (yylval.text)[yyleng] = '\0';
						return STRING;}

\/\*[^\*\/]*\*\/    ;
\/\/[^\n]*  ;
[ \t]  ;

\n  {yylineno++;}
%%
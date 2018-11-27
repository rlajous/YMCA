%{
#include <stdio.h>
/*extern void yyerror(char *);*/
%}

%start sentence

%token SEMICOLON COLON COMMA OPEN_CURLY_BRACES CLOSE_CURLY_BRACES LESS_THAN GREATER_THAN 
%token OPEN_PARENTHESES CLOSE_PARENTHESES OPEN_BRACKET CLOSE_BRACKET PLUS MINUS MULTIPLY DIVIDE MOD
%token EQUAL NOT_EQUAL GREATER_OR_EQUAL LESS_OR_EQUAL

%token AND OR RETURN DEFINE FOR WHILE IF ELSE

%token BOOLEAN_TYPE INTEGER_TYPE STRING_TYPE

%token MAIN BOOLEAN INTEGER NAME STRING 
 

%%
 /* Las producciones (o "reglas") de la gramatica
  * que describe nuestro lenguaje
  */

program: defines functions {}
	;

defines: define defines {}
	| define {}
	;
define: DEFINE NAME BOOLEAN {}
	| DEFINE NAME INTEGER {}
	| DEFINE NAME STRING {}
	;

functions: function functions {}
	| main {}
	;

function: type NAME OPEN_PARENTHESES args CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES {}
	;

main: type MAIN OPEN_PARENTHESES CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES {} 

type: INTEGER_TYPE {}
	| BOOLEAN_TYPE {}
	| STRING_TYPE {}
	;

args: params {}
	| {}
	;

params: param COMMA params {}
	| param {}
	;

param: type NAME {}
	;

body: sentences {}
	| {}
	;

sentences: sentence sentences {}
	| sentence {}
	;

sentence: declaration SEMICOLON {}
	| for {}
	| while {}
	| if {}
	| var_operation SEMICOLON {}
	| func_call SEMICOLON {}
	| return SEMICOLON {}
	;

for: FOR OPEN_PARENTHESES var_operation SEMICOLON condition SEMICOLON var_operation CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES {}
	;

while: WHILE OPEN_PARENTHESES condition CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES {}
	;
	
if: IF OPEN_PARENTHESES condition CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES {}
	| IF OPEN_PARENTHESES condition CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES ELSE OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES {}
	;

declaration: type NAME {}
	| type assignment {}
	;

var_operation: assignment {}
	| NAME PLUS PLUS {}
	| NAME MINUS MINUS {}
	;

func_call: NAME OPEN_PARENTHESES call_args CLOSE_PARENTHESES {}
	;

call_args: {}
	| call_params {}
	;

call_params: call_param COMMA call_params {}
	| call_param {}
	;	

call_param: expresion {}
	| STRING {}
	;

return: RETURN expresion {}
	;

condition: BOOLEAN {}
	| OPEN_PARENTHESES condition CLOSE_PARENTHESES {}
	| expresion EQUAL EQUAL expresion {}
	| expresion NOT EQUAL expresion {}
	| expresion GREATER_THAN expresion {}
	| expresion LESS_THAN expresion {}
	| expresion GREATER_OR_EQUAL expresion {}
	| expresion LESS_OR_EQUAL expresion {}
	| condition OR condition {}
	| condition AND condition {}
	;
	
	
assignment: NAME EQUAL expresion {}
	| NAME EQUAL STRING {}
	; 
	
expresion: BOOLEAN {}
	| NAME {}
	| INTEGER {}
	| func_call {}
	| expresion PLUS expresion {}
	| expresion MINUS expresion {}
	| expresion MOD expresion {}
	| expresion DIVIDE expresion {}
	| expresion MULTIPLY expresion {}
	;

%%

  fprintf(stderr, "%s\n",s);
}

yywrap()
{
  return(1);
}
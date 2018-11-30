%{
	#include<stdio.h>
	#include "nodes.h"
	#include "../Utilities/matrix.h"
	#include "../Utilities/typesCheck.h"
	#include "../Utilities/translateNodes.h"

int regs[26];
int base;

extern void yyerror(char *);
extern int yylex();

%}

%start program

%union {
  	int a;
    char * text;
  	int value;

  	program_node* program_node;
  	defines_node* defines_node;
  	define_node* define_node;
  	functions_node* functions_node;
  	function_node* function_node;
  	type_node * type_node;
  	parameters_node* parameters_node;
  	sentences_node* sentences_node;
  	sentence_node* sentence_node;
  	declaration_node * declaration_node;
  	variable_operation_node* variable_operation_node;
  	assignment_node* assignment_node;
  	elements_node* elements_node;
  	element_node* element_node;
  	if_node* if_node;
  	while_node* while_node;
  	for_node* for_node;
  	condition_node* condition_node;
  	expression_node* expression_node;
  	function_execute_node* function_execute_node;
  	call_parameters_node* call_parameters_node;
  	call_parameter_node* call_parameter_node;
  	return_node* return_node;
  }


%token DIGIT LETTER SEMICOLON
%token SEMICOLON COLON COMMA OPEN_CURLY_BRACES CLOSE_CURLY_BRACES LESS_THAN GREATER_THAN 
%token OPEN_PARENTHESES CLOSE_PARENTHESES OPEN_BRACKET CLOSE_BRACKET PLUS MINUS MULTIPLY DIVIDE MOD
%token EQUAL NOT_EQUAL GREATER_OR_EQUAL LESS_OR_EQUAL

%token AND OR RETURN DEFINE FOR WHILE IF ELSE

%token BOOLEAN_TYPE INTEGER_TYPE STRING_TYPE MATRIX_TYPE_START

%token MAIN BOOLEAN NAME STRING

%token <value> BOOLEAN
%token <value> INTEGER
%token <text> NAME
%token <text> STRING


%type <program_node> program
%type <defines_node> defines
%type <define_node> define
%type <functions_node> functions
%type <function_node> function main
%type <type_node> type /*compound_type Ver si va*/
%type <parameters_node> args params
%type <sentences_node> body sentences
%type <sentence_node> sentence
%type <text> /*SentenceEnd*/ assign_operation /*LogicalOperation Increment Decrement*/
%type <declaration_node> declaration
%type <variable_operation_node> var_operation
%type <assignment_node> assignment
 /*%type <elements_node> ElementList Elements va a servir para declarar
 la matriz
 %type <element_node> element*/
%type <if_node> if
%type <while_node> while
%type <for_node> for
%type <condition_node> condition
%type <expression_node> expression
%type <function_execute_node> func_call
%type <call_parameters_node> call_args call_params
%type <call_parameter_node> call_param
%type <return_node> return

 /* terminals go from lowest precedence to highest */
%left PLUS MINUS 		  /* lowest precedence *//* left associative */
%left MULTIPLY DIVIDE MOD /* higher precedence than + and - */
%left EQUAL NOT_EQUAL GREATER_OR_EQUAL GREATER_THAN LESS_THAN LESS_OR_EQUAL
%left OR AND 			  /* highest precedence */

%%                   /* beginning of rules section */

program: defines functions {$$ = new_program_node($1, $2); translateProgramNode($$);}
	;

defines: define defines {$$ = new_defines_node($1, $2);}
	| /* lambda */ {$$ = NULL; createFunction();}
	;
define: DEFINE NAME BOOLEAN {$$ = new_define_node(DEFINE_INTEGER, $2, $3, NULL);}
	| DEFINE NAME INTEGER {$$ = new_define_node(DEFINE_INTEGER, $2, $3, NULL);}
	| DEFINE NAME STRING {$$ = new_define_node(DEFINE_STRING, $2, 0, $3);}
	;

functions: function functions {$$ = new_functions_node($1, $2);}
	| main {$$ = new_functions_node($1, NULL);}
	;

function: type NAME OPEN_PARENTHESES args CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES {$$ = new_function_node($1, $2, $4, $7);}
	;

main: type MAIN OPEN_PARENTHESES CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES {$$ = new_function_node($1, "main", NULL, $6);} 

matrix_type: MATRIX_TYPE_START LESS_THAN INTEGER_TYPE GREATER_THAN
		   | MATRIX_TYPE_START LESS_THAN BOOLEAN_TYPE GREATER_THAN
		   | MATRIX_TYPE_START LESS_THAN STRING_TYPE  GREATER_THAN

type: INTEGER_TYPE {$$ = INTEGER_T;}
	| BOOLEAN_TYPE {$$ = BOOLEAN_T;}
	| STRING_TYPE {$$ = STRING_T;}
	| matrix_type {$$ = MATRIX_T;}
	;

args: params {$$ = $1;}
	| {$$ = NULL;}
	;

params: type NAME COMMA params {$$ = new_parameters_node($1, $2, $4);}
	| type NAME {$$ = new_parameters_node($1, $2, NULL);}
	;

body: sentences {$$ = $1;}
	| {$$ = NULL;}
	;

sentences: sentence sentences {$$ = new_sentences_node($1, $2);}
	| sentence {$$ = new_sentences_node($1, NULL); }
	;

sentence: declaration SEMICOLON {$$ = new_sentence_node(SENTENCE_DECLARATION, $1, NULL, $2, NULL, NULL, NULL, NULL, NULL); }
	| for {$$ = new_sentence_node(SENTENCE_FOR, NULL, NULL, NULL, $1, NULL, NULL, NULL, NULL); }
	| while {$$ = new_sentence_node(SENTENCE_WHILE, NULL, NULL, NULL, NULL, $1, NULL, NULL, NULL);}
	| if {$$ = new_sentence_node(SENTENCE_IF, NULL, NULL, NULL, NULL, NULL, $1, NULL, NULL);}
	| var_operation SEMICOLON {$$ = new_sentence_node(SENTENCE_VARIABLE, NULL, $1, $2, NULL, NULL, NULL, NULL, NULL); }
	| func_call SEMICOLON {$$ = new_sentence_node(SENTENCE_FUNCTION, NULL, NULL, $2, NULL, NULL, NULL, $1, NULL);}
	| return SEMICOLON {$$ = new_sentence_node(SENTENCE_RETURN, NULL, NULL, $2, NULL, NULL, NULL, NULL, $1); }
	;

for: FOR OPEN_PARENTHESES assignment SEMICOLON condition SEMICOLON var_operation CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES {$$ = new_for_node(REGULAR_FOR, $3, $5, $7, $10, NULL, NULL);}
	;

while: WHILE OPEN_PARENTHESES condition CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES {$$ = new_while_node($3, $6);}
	;
	
if: IF OPEN_PARENTHESES condition CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES {$$ = new_if_node($3, $6, NULL);}
	| IF OPEN_PARENTHESES condition CLOSE_PARENTHESES OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES ELSE OPEN_CURLY_BRACES body CLOSE_CURLY_BRACES {$$ = new_if_else_node($3, $6, $10);} /*TODO: capaz falte algo con el else*/
	;

declaration: type NAME {$$ = new_declaration_node($1, $2);}
	| type assignment {}
	;

var_operation: assignment {$$ = new_variable_opration_node(VARIABLE_ASSIGNMENT, $1, NULL);}
	| NAME PLUS PLUS {$$ = new_variable_opration_node(VARIABLE_INCREMENT, NULL, $1);}
	| NAME MINUS MINUS {$$ = new_variable_opration_node(VARIABLE_DECREMENT, NULL, $1);}
	;

func_call: NAME OPEN_PARENTHESES call_args CLOSE_PARENTHESES {$$ = new_function_execute_node($1, $3);}
	;

call_args: {$$ = NULL; }
	| call_params {$$ = $1;}
	;

call_params: call_param COMMA call_params {$$ = new_call_parameters_node($1, $3);}
	| call_param {$$ = new_call_parameters_node($1, NULL);}
	;	

call_param: expression {$$ = new_call_parameter_node(PARAMETER_EXPRESSION, NULL, $1);}
	| STRING {$$ = new_call_parameter_node(PARAMERER_STRING, $1, NULL);}
	;

return: RETURN expression {$$ = new_return_node(RETURN_EXPRESSION, NULL, $2);}
	;

condition: BOOLEAN {}
	| OPEN_PARENTHESES condition CLOSE_PARENTHESES {$$ = new_condition_node(CONDITION_PARENTHESES, NULL, NULL, NULL, $2);}
	| expression EQUAL EQUAL expression {}
	| expression NOT_EQUAL expression {}
	| expression GREATER_THAN expression {}
	| expression LESS_THAN expression {}
	| expression GREATER_OR_EQUAL expression {}
	| expression LESS_OR_EQUAL expression {}
	| condition OR condition {}
	| condition AND condition {}
	;
	
	
assignment: NAME assign_operation expression {$$ = new_assignment_node(ASSIGNMENT_EXPRESSION, $1, NULL, NULL, $2, $3);}
		  | NAME EQUAL STRING {$$ = new_assignment_node(ASSIGNMENT_STRING, $1, $3, NULL, NULL, NULL);}
		  ;

assign_operation: EQUAL {$$ = "=";}
				| PLUS EQUAL {$$ = "+=";}
				| MINUS EQUAL {$$ = "-="; }
				| MULTIPLY EQUAL {$$ = "*=";}
				| DIVIDE EQUAL {$$ = "/=";}
	
expression: BOOLEAN {}
		 | NAME {}
		 | INTEGER {}
		 | matrix {/* no se si esta bien meter matrix aca 
		 			  porque por ej: ¿se puede hacer 
					  if(m == {{1,2,3},{4,5,6},{7,8,9}})??? */}
		 | func_call {}
		 | expression PLUS expression {}
		 | expression MINUS expression {}
		 | expression MOD expression {}
		 | expression DIVIDE expression {}
		 | expression MULTIPLY expression {}
		 | 
		 ;

matrix: OPEN_BRACKET sub_matrix CLOSE_BRACKET {}
	  | OPEN_BRACKET numbers    CLOSE_BRACKET {}

sub_matrix: OPEN_BRACKET numbers CLOSE_BRACKET COMMA sub_matrix {}
		  | OPEN_BRACKET numbers CLOSE_BRACKET COMMA {}
		  | OPEN_BRACKET numbers CLOSE_BRACKET {}

numbers: DIGIT COMMA numbers {}
	   | DIGIT COMMA {}
	   | DIGIT {}

%%
int main()
{
 return(yyparse());
}

int yywrap()
{
  return(1);
}
%{
#include<stdio.h>

int regs[26];
int base;

extern int yylex();

%}

%start program

%union {
  	int a;
    char * text;
  	int value;

  	// program_node* program_node;
  	// defines_node* defines_node;
  	// define_node* define_node;
  	// functions_node* functions_node;
  	// function_node* function_node;
  	// type_node * type_node;
  	// parameters_node* parameters_node;
  	// sentences_node* sentences_node;
  	// sentence_node* sentence_node;
  	// declaration_node * declaration_node;
  	// variable_opration_node* variable_opration_node;
  	// assignment_node* assignment_node;
  	// queue_stack_node* queue_stack_node;
  	// elements_node* elements_node;
  	// element_node* element_node;
  	// if_node* if_node;
  	// while_node* while_node;
  	// for_node* for_node;
  	// condition_node* condition_node;
  	// expression_node* expression_node;
  	// function_execute_node* function_execute_node;
  	// call_parameters_node* call_parameters_node;
  	// call_parameter_node* call_parameter_node;
  	// return_node* return_node;
  }


%token DIGIT LETTER SEMICOLON
%token SEMICOLON COLON COMMA OPEN_CURLY_BRACES CLOSE_CURLY_BRACES LESS_THAN GREATER_THAN 
%token OPEN_PARENTHESES CLOSE_PARENTHESES OPEN_BRACKET CLOSE_BRACKET PLUS MINUS MULTIPLY DIVIDE MOD
%token EQUAL NOT_EQUAL GREATER_OR_EQUAL LESS_OR_EQUAL

%token AND OR RETURN DEFINE FOR WHILE IF ELSE

%token BOOLEAN_TYPE INTEGER_TYPE STRING_TYPE

%token MAIN BOOLEAN NAME STRING

%token <value> BOOLEAN
%token <value> INTEGER
%token <text> NAME
%token <text> STRING


  // %type <program_node> Program
  // %type <defines_node> Defines
  // %type <define_node> Define
  // %type <functions_node> Functions
  // %type <function_node> Function Main
  // %type <type_node> Type CompoundType
  // %type <parameters_node> Arguments Parameters
  // %type <sentences_node> Block Sentences
  // %type <sentence_node> Sentence
  // %type <text> SentenceEnd AssignmentOperation LogicalOperation Increment Decrement
  // %type <declaration_node> Declaration
  // %type <variable_opration_node> VariableOperation
  // %type <assignment_node> Assignment
  // %type <elements_node> ElementList Elements
  // %type <element_node> Element
  // %type <if_node> If Else
  // %type <while_node> While
  // %type <for_node> For
  // %type <condition_node> Condition
  // %type <expression_node> Expression
  // %type <function_execute_node> FunctionExecute
  // %type <call_parameters_node> CallArguments CallParameters
  // %type <call_parameter_node> CallParameter
  // %type <return_node> Return

%%                   /* beginning of rules section */

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
	| expresion NOT_EQUAL expresion {}
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
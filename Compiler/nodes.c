#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "../Utilities/typesCheck.h"

program_node*
new_program_node(defines_node * defines,
				functions_node * functions){

	program_node * node = malloc(sizeof(program_node));

	node->defines = defines;
	node->functions = functions;

	return node;
}

defines_node*
new_defines_node(define_node * define, defines_node * next){

	defines_node * node = malloc(sizeof(defines_node));

	node -> define = define;
	node -> next = next;

	return node;
}

define_node*
new_define_node(enum productions production, char*name, int value, char* string_name){

	char * name_aux = malloc(strlen(name) + 1);
	define_node * node = NULL;
	strcpy(name_aux, name);

	if(existsDefine(name_aux)){
		error(VARIABLE_REPETITION);
	}else{

		node = malloc(sizeof(define_node));
		node -> name = name_aux;
		node -> production = production;
		if(production == DEFINE_INTEGER){
			node -> string_name = NULL;
			node -> value = value;
		}else if(production == DEFINE_STRING){
			node -> value = 0;
			char* string_name_aux = malloc(strlen(string_name) + 1);
			strcpy(string_name_aux, string_name);
			node -> string_name = string_name_aux;
		}else{
			error(INCOMPATIBLE);
		}
	}
	addToDefines(name_aux, production == DEFINE_INTEGER? INTEGER_T : STRING_T);

	return node;
}

type_node*
new_type_node(basicTypes basicType, compoundTypes compoundType){
	type_node * node = malloc(sizeof(type_node));

	node -> basicType = basicType;
	node -> compoundType = compoundType;

	return node;

}

functions_node*
new_functions_node(function_node * function, functions_node * next){
	functions_node * node = malloc(sizeof(functions_node));

	node -> function = function;
	node -> next = next;

	return node;
}

function_node*
new_function_node(type_node * type, char* name, parameters_node * parameters, sentences_node * sentences){

	function_node * node = malloc(sizeof(function_node));
	char * name_aux = malloc(strlen(name) + 1);
	strcpy(name_aux, name);
	addReturn(type->basicType, type->compoundType);
	if(!renameCurrent(name_aux)) {
		error(FUNCTION_REPETITION_ERROR);
	}
	node -> type = type;
	node -> parameters = parameters;
	node -> sentences = sentences;
	node -> name = name_aux;

	return node; /*total la idea es que el error() se encargue de terminar antes si es necesario*/
}

parameters_node*
new_parameters_node(type_node * type, char * name, parameters_node * next){

	parameters_node * node = malloc(sizeof(parameters_node));
	char * name_aux = malloc(strlen(name) + 1);
	strcpy(name_aux, name);

	if(!addParameterToFunction(name_aux, type->basicType, type->compoundType)){
		error(VARIABLE_REPETITION);
	}else{
		node -> type = type;
		node -> name = name_aux;
		if(next != NULL){
			node -> next = next;
		}else{
			node -> next = NULL;
		}
		return node;
	}
	return node;
}

sentences_node*
new_sentences_node(sentence_node * sentence, sentences_node * sentences){

	sentences_node * node = malloc(sizeof(sentences_node));

	node -> sentence = sentence;
	if(sentences != NULL){
		node -> sentences = sentences;
	}else{
		node -> sentences = NULL;
	}

	return node;
}

sentence_node*
new_sentence_node(enum productions production, declaration_node * declaration, variable_operation_node * variable_operation,  char* sentenceEnd,
	for_node * for_node, while_node * while_node, if_node * if_node,
	function_execute_node* function_execute, return_node*return_node){

	sentence_node * node = malloc(sizeof(sentence_node));

	node -> production = production;
	node -> declaration = declaration;
	node -> variable_opration = variable_operation;
	node -> for_node = for_node;
	node -> while_node = while_node;
	node -> if_node = if_node;
	node -> function_execute = function_execute;
	node -> return_node = return_node;

	if(sentenceEnd != NULL && *sentenceEnd !=';'){
		error(INCOMPATIBLE);
	}else{
		if(sentenceEnd == NULL)
			node -> sentenceEnd = '\0';
		else
			node -> sentenceEnd = ';';
	}

	return node;
}

declaration_node *
new_declaration_node(type_node * type, char * name){

	declaration_node * node = malloc(sizeof(declaration_node));
	char * name_aux = malloc(strlen(name) + 1);
	strcpy(name_aux, name);

	if(!addVariable(name, type->basicType, type->compoundType))
		error(VARIABLE_REPETITION);
	node -> type = type;
	node -> name = name_aux;

	return node;
}

variable_operation_node*
new_variable_operation_node(enum productions production, assignment_node * assignment, char * increment_decrement_name){
	variable_operation_node * node = malloc(sizeof(variable_operation_node));
	char * name_aux;

	node -> production = production;
	if(production == VARIABLE_ASSIGNMENT) {
		node -> assignment = assignment;
		node -> increment_decrement_name = NULL;
	}else if(production == VARIABLE_INCREMENT || production == VARIABLE_DECREMENT){
		node -> assignment = NULL;
		name_aux = malloc(strlen(increment_decrement_name) + 1);
		strcpy(name_aux, increment_decrement_name);
		node -> increment_decrement_name = name_aux;
	}else{
		error(INCOMPATIBLE);
	}
	return node;
}

assignment_node*
new_assignment_node(enum productions production, char * name,
	char * string, matrix_node * matrix, char* assignment_operation,
	expression_node * expression){

	assignment_node * node = malloc(sizeof(assignment_node));
	char * name_aux = malloc(strlen(name) + 1);
	strcpy(name_aux, name);

	node -> production = production;
	node -> name = name_aux;

	if(production == ASSIGNMENT_STRING){
		/*solo lo creo si lo necesito, si no directamente, null*/
		char * string_aux = malloc(strlen(string) + 1);
		strcpy(string_aux, string);
		node -> string = string_aux;
		node -> matrix = NULL;
		node -> assignment_operation = NULL;
		node -> expression = NULL;
		int exists = existsVariableTyped(name_aux, STRING_T, NONE);
		if(exists == -1)
			error(INCOMPATIBLE_TYPE);
		else if(exists == 0)
			error(VARIABLE_NOT_DEFINED);
	}else if(production == ASSIGNMENT_MATRIX){

		node -> string = NULL;
		node -> matrix = matrix;
		node -> assignment_operation = NULL;
		node -> expression = NULL;
		if(!existsVariable(name_aux))
			error(VARIABLE_NOT_DEFINED);
	}else if(production == ASSIGNMENT_EXPRESSION){

		node -> string = NULL;
		node -> matrix = NULL;

		char * assignment_operation_aux = malloc(strlen(assignment_operation) + 1);
		strcpy(assignment_operation_aux, assignment_operation);
		node -> assignment_operation = assignment_operation_aux;

		node -> expression = expression;
		if(assignment_operation[0] != '=' && !existsVariable(name_aux)) {
			error(VARIABLE_NOT_DEFINED);
		}
		else if(assignment_operation[0] == '=' && !existsVariable(name_aux))
			error(VARIABLE_NOT_DEFINED);
	}else {
		error(INCOMPATIBLE);
	}

	return node;
}

matrix_node *
new_matrix_node(rows_node * rows){

	matrix_node * node = malloc(sizeof(matrix_node));

	node -> rows = rows;
	node -> cols = rows->cols;
	node -> rowsnum = rows-> rownum; 

	return node;
}

rows_node *
new_rows_node (row_node * row, rows_node * next){
	rows_node * node = malloc(sizeof(rows_node));
	if(next == NULL){
		node->rownum = 1;
	}else{
		node->rownum = next->rownum +1;
		if(row->col != next->cols){
		error(CANT_COLS_ERROR);
	}

	}

	node -> row = row;
	node -> cols = row -> col;
	node -> next = next;

	return node;
}

row_node *
new_row_node (int value, row_node * next){

	row_node * node = malloc(sizeof(row_node));

	node -> value = value;
	node -> next = next;

	if(next == NULL){
		node->col = 1;
	}else{
		node->col = next->col + 1;
	}

	return node;
}


if_node *
new_if_node(condition_node * condition, sentences_node * sentences, if_node * else_branch){

	if_node * node = malloc(sizeof(if_node));

	if(condition != NULL){
		node -> condition = condition;
	}else{
		node -> condition = NULL;
	}

	node -> sentences = sentences;

	if(else_branch !=NULL){
		node -> else_branch = else_branch;
	}else{
		node -> else_branch = NULL;
	}

	return node;
}

while_node*
new_while_node(condition_node * condition, sentences_node * sentences){

	while_node * node = malloc(sizeof(while_node));

	node -> condition = condition;
	node -> sentences = sentences;

	return node;
}

for_node*
new_for_node(enum productions production, assignment_node *assignment, condition_node *condition,
			variable_operation_node *variable_operation, sentences_node *sentences, char * variable,
		char * structure){

	for_node * node = malloc(sizeof(for_node));

	node -> production = production;
	if(production == REGULAR_FOR){
		node -> assignment = assignment;
		node -> condition = condition;
		node -> variable_operation = variable_operation;
		node -> sentences = sentences;
		node -> variable = NULL;
		node -> structure = NULL;
	}else{
		error(INCOMPATIBLE);
	}

	return node;
}

condition_node*
new_condition_node(enum productions production, expression_node *expression_1, char * logical_operation,
	expression_node *expression_2, condition_node *condition){

	condition_node * node = malloc(sizeof(condition_node));

	node -> production = production;

	if(production == CONDITION_LOGICAL){
		node -> expression_1 = expression_1;

		char * logical_operation_aux = malloc(strlen(logical_operation) + 1);
		strcpy(logical_operation_aux, logical_operation);
		node -> logical_operation = logical_operation_aux;

		node -> expression_2 = expression_2;
		node -> condition = NULL;

	}else if(production == CONDITION_EXPRESSION){
		node -> expression_1 = expression_1;
		node -> logical_operation = NULL;
		node -> expression_2 = NULL;
		node -> condition = NULL;

	}else if(production == CONDITION_PARENTHESES){
		node -> expression_1 = NULL;
		node -> logical_operation = NULL;
		node -> expression_2 = NULL;
		node -> condition = condition;
	}else{
		error(INCOMPATIBLE);
	}
	return node;
}

expression_node*
new_expression_node(enum productions production,
		expression_node *expression_1,
		char op, expression_node *expression_2,
		function_execute_node *function_execute,
		int boolean_number, char * name){
	expression_node * node = malloc(sizeof(expression_node));

	node -> production = production;

	if(production == EXPRESSION_OPERATION){
		node -> expression_1 = expression_1;
		node -> expression_2 = expression_2;
		node -> op = op;
		node -> function_execute = NULL;
		node -> boolean_number = 0;
		node -> name = NULL;
	}else if(production == EXPRESSION_BOOLEAN || production == EXPRESSION_VARIABLE || production == EXPRESSION_INTEGER || production == EXPRESSION_FUNCTION){
		node -> expression_1 = NULL;
		node -> expression_2 = NULL;
		node -> function_execute = NULL;
		if(production == EXPRESSION_BOOLEAN || production == EXPRESSION_INTEGER){
			node -> boolean_number = boolean_number;
			node -> name = NULL;
		}else if(production == EXPRESSION_VARIABLE){
			node -> boolean_number = 0;

			char * name_aux = malloc(strlen(name) + 1);
			strcpy(name_aux, name);
			node -> name = name_aux;
		}else{
			node -> boolean_number = 0;
			node -> name = NULL;
			node -> function_execute = function_execute;
		}
	}else{
		error(INCOMPATIBLE);
	}
	return node;
}

function_execute_node*
new_function_execute_node(char * name, call_parameters_node * parameters){

	function_execute_node * node = malloc(sizeof(function_execute_node));
	char * name_aux = malloc(strlen(name) + 1);
	strcpy(name_aux, name);

	node -> name = name_aux;
	node -> parameters = parameters;

	return node;
}

call_parameters_node *
new_call_parameters_node(call_parameter_node * parameter,
	call_parameters_node * next){

	call_parameters_node * node = malloc(sizeof(call_parameters_node));

	node -> parameter = parameter;
	node -> next = next;

	return node;
}

call_parameter_node*
new_call_parameter_node(enum productions production,
	char* string,
	expression_node *expression){

	call_parameter_node * node = malloc(sizeof(call_parameter_node));

	node -> production = production;

	if(production == PARAMETER_STRING){
		char * string_aux = malloc(strlen(string) + 1);
		strcpy(string_aux, string);
		node -> string = string_aux;
		node -> expression = NULL;
	}else if(production == PARAMETER_EXPRESSION){
		node -> string = NULL;
		node -> expression = expression;
	}else{
		error(INCOMPATIBLE);
	}

	return node;
}

return_node *
new_return_node(enum productions production,
		char* string,
		expression_node *expression){

	return_node * node = malloc(sizeof(return_node));

	node -> production = production;
	if(production == RETURN_EXPRESSION){
		node -> string = NULL;
		node -> expression = expression;
	}else if(production == RETURN_STRING){
		char*string_aux = malloc(strlen(string) + 1);
		strcpy(string_aux, string);
		node -> string = string_aux;
		node -> expression = NULL;
	}else{
		error(INCOMPATIBLE);
	}

	return node;
}

void error(errorType type) {
	switch (type) {
		case FUNCTION_REPETITION_ERROR: printf("Error, function defined more than once\n"); break;
		case INCOMPATIBLE: printf("Error, incompatible operation\n"); break;
		case INCOMPATIBLE_TYPE: printf("Error, incompatible types found\n"); break;
		case VARIABLE_REPETITION: printf("Error, variable name used more than once\n"); break;
		case VARIABLE_NOT_DEFINED: printf("Error, variable operation on not assigned variable\n"); break;
		case ERROR_ARGUMENTS: printf("Error, wrong arguments for function\n"); break;
		case FUNCTION_NOT_DEFINED: printf("Error, function not defined\n"); break;
		case NOT_VALID_OPERATION: printf("Error, a non valid operation was performed\n"); break;
		case CANT_COLS_ERROR: printf("Error, the amount of columns in two rows don't match\n"); break;
		case BAD_FOR_ERROR: printf("Error, wrong for declaration \n"); break;
	}
	exit(2);
}

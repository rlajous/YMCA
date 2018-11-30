#ifndef NODES_H
#define NODES_H

enum productions
{
	DEFINE_INTEGER, DEFINE_STRING, SENTENCE_DECLARATION, SENTENCE_VARIABLE, SENTENCE_FOR, SENTENCE_WHILE, SENTENCE_IF, SENTENCE_FUNCTION, SENTENCE_RETURN,
	VARIABLE_ASSIGNMENT, VARIABLE_INCREMENT, VARIABLE_DECREMENT, ASSIGNMENT_STRING, ASSIGNMENT_QUEUE, ASSIGNMENT_STACK, ASSIGNMENT_EXPRESSION,
	ELEMENT_BOOLEAN, ELEMENT_STRING, ELEMENT_VARIABLE, ELEMENT_INTEGER, FOR_EACH, REGULAR_FOR, CONDITION_LOGICAL, CONDITION_EXPRESSION, CONDITION_PARENTHESES,
	EXPRESSION_BOOLEAN, EXPRESSION_VARIABLE, EXPRESSION_INTEGER, EXPRESSION_FUNCTION, EXPRESSION_OPERATION, PARAMERER_STRING, PARAMETER_EXPRESSION,
	RETURN_STRING, RETURN_EXPRESSION
};

typedef enum {INTEGER_T, BOOLEAN_T, STRING_T} basicTypes;

typedef enum {QUEUE_T = 4, STACK_T, NONE} compoundTypes;

typedef enum {FUNCTION_REPETITION_ERROR, VARIABLE_REPETITION, INCOMPATIBLE, INCOMPATIBLE_TYPE, VARIABLE_NOT_DEFINED, ERROR_ARGUMENTS, FUNCTION_NOT_DEFINED, NOT_VALID_OPERATION} errorType;

	typedef struct program_node{
		struct defines_node * defines;
		struct functions_node * functions;
	} program_node;

	typedef struct defines_node{
		struct define_node * define;
		struct defines_node * next;
	} defines_node;

	typedef struct define_node{
		enum productions production;
		char* name;
		char* string_name;
		int value;
	} define_node;

	typedef struct type_node{
		basicTypes basicType;
		compoundTypes compoundType;
	} type_node;

	typedef struct functions_node{
		struct function_node * function;
		struct functions_node * next;
	} functions_node;

	typedef struct function_node{
		struct type_node * type;
		struct parameters_node * parameters;
		struct sentences_node * sentences;
		char * name;
	} function_node;

	typedef struct parameters_node {
		struct type_node * type;
		struct parameters_node * next;
		char* name; /*NAME*/
	} parameters_node;

	typedef struct sentences_node {
		struct sentence_node * sentence;
		struct sentences_node * sentences;
	}sentences_node;

	typedef struct sentence_node{
		enum productions production;
		struct type_node * type;
		struct declaration_node * declaration;
		struct variable_opration_node *variable_opration;
		struct for_node *for_node;
		struct while_node *while_node;
		struct if_node *if_node;
		struct function_execute_node *function_execute;
		struct return_node *return_node;
		char sentenceEnd; //Si es ; o nada.
	}sentence_node;

	typedef struct declaration_node{
		struct type_node * type;
		char * name;
	}declaration_node;

	typedef struct variable_opration_node{
		enum productions production;
		struct assignment_node *assignment;
		char * increment_decrement_name;
	}variable_opration_node;

	typedef struct assignment_node{
		enum productions production;
		char *name;
		char *string;
		struct queue_stack_node *queue_stack;
		char *assignment_operation;
		struct expression_node *expression;
	}assignment_node;

	typedef struct queue_stack_node{
		struct elements_node *elements;
	}queue_stack_node;

	typedef struct elements_node{
		struct element_node *element;
		struct elements_node *next;
	}elements_node;

	/*no es el nombre de la variable si no lo que se le asigna en si */
	typedef struct element_node{
		enum productions production;
		char *string_name;
		int value;
	}element_node;

	typedef struct if_node{
		struct condition_node *condition;
		struct sentences_node *sentences;
		struct if_node *else_branch; /*en else pondrias condition en null & else en null, pero en if_else es lo mismo*/
	}if_node;

	typedef struct while_node{
		struct condition_node *condition;
		struct sentences_node *sentences;
	}while_node;

	typedef struct for_node	{
		enum productions production;
		struct assignment_node *assignment;
		struct condition_node *condition;
		struct variable_opration_node *variable_operation;
		struct sentences_node *sentences;
		char * variable;
		char * structure;
	}for_node;

	typedef struct condition_node{
		enum productions production;
		struct expression_node *expression_1;
		char * logical_operation;
		struct expression_node *expression_2;
		struct condition_node *condition;
	}condition_node;

	typedef struct expression_node{
		enum productions production;
		struct expression_node *expression_1;
		char op;
		struct expression_node *expression_2;
		struct function_execute_node *function_execute;
		int boolean_number;
		char * name;
	}expression_node;

	typedef struct function_execute_node{
		char * name;
		struct call_parameters_node * parameters;
	}function_execute_node;

	typedef struct call_parameters_node{
		struct call_parameter_node * parameter;
		struct call_parameters_node * next;
	} call_parameters_node;

	typedef struct call_parameter_node{
		enum productions production;
		char* string;
		struct expression_node *expression;
	} call_parameter_node;

	typedef struct return_node {
		enum productions production;
		char* string;
		struct expression_node *expression;
	} return_node;

program_node*	new_program_node(defines_node * defines, functions_node * functions);

defines_node*	new_defines_node(define_node * define, defines_node * next);

define_node* new_define_node(enum productions production, char*name, int value, char* string_name);

functions_node*	new_functions_node(function_node * function, functions_node * next);

function_node* new_function_node(type_node * type, char* name, parameters_node * parameters, sentences_node * sentences);

type_node * new_type_node(basicTypes basic, compoundTypes compound);

parameters_node* new_parameters_node(type_node * type, char*name, parameters_node * next);

sentences_node*	new_sentences_node(sentence_node * sentence, sentences_node * sentences);

sentence_node* new_sentence_node(enum productions production, declaration_node * declaration, variable_opration_node * variable_operation,  char* sentenceEnd,
	for_node * for_node, while_node * while_node, if_node * if_node,function_execute_node* function_execute, return_node*return_node);

declaration_node *	new_declaration_node(type_node * type, char * name);

variable_opration_node*	new_variable_opration_node(enum productions production, assignment_node * assignment, char * increment_decrement_name);

assignment_node* new_assignment_node(enum productions production, char * name,
	char * string, queue_stack_node * queue_stack, char* assignment_operation, expression_node * expression);

queue_stack_node * new_queue_stack_node(elements_node * elements);

elements_node *	new_elements_node (element_node * element, elements_node * next);

element_node * new_element_node(enum productions production, int value, char * string_name);

if_node *	new_if_node(condition_node * condition, sentences_node * sentences, if_node * else_branch);

while_node*	new_while_node(condition_node * condition, sentences_node * sentences);

for_node*	new_for_node(enum productions production, assignment_node *assignment, condition_node *condition,
			variable_opration_node *variable_operation, sentences_node *sentences, char * variable,	char * structure);

condition_node*	new_condition_node(enum productions production, expression_node *expression_1, char * logical_operation,
	expression_node *expression_2, condition_node *condition);

expression_node* new_expression_node(enum productions production,	expression_node *expression_1,
		char op, expression_node *expression_2,	function_execute_node *function_execute,
		int boolean_number, char * name);

function_execute_node* new_function_execute_node(char * name, call_parameters_node * parameters);

call_parameters_node * new_call_parameters_node(call_parameter_node * parameter,
	call_parameters_node * next);

call_parameter_node* new_call_parameter_node(enum productions production,	char* string,
	expression_node *expression);

return_node *	new_return_node(enum productions production, char* string,
		expression_node *expression);

void error(errorType type);

#endif

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
extern YYSTYPE yylval;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Compiler/nodes.h"
#include "translateNodes.h"
#include "typesCheck.h"

static FILE* file = NULL;
functionNode* funCurrent = NULL;

void translateProgramNode(program_node * program) {
  file = fopen("Compiler/compiled.c", "w+");
	if (file != NULL)	{
	  fprintf(file,"#include <stdio.h>\n");
	  fprintf(file,"#include <stdlib.h>\n");
	  fprintf(file,"#include <string.h>\n");
	  fprintf(file,"#include \"../Utilities/matrix.h\"\n\n");

    translateDefines(program->defines);
    fprintf(file, "\n");
    translateFunctionDefinitions(getFunctionList());
    fprintf(file, "\n");

    translateFunctions(program->functions);

	  fclose(file);
  } else
    perror("Output file error\n");
}

void translateType(basicTypes basic, compoundTypes compound) {
  if(compound == QUEUE_T || compound == STACK_T) {
    fprintf(file, "listADT ");
    return;
  }
  switch (basic) {
    case BOOLEAN_T: case INTEGER_T: fprintf(file, "int "); break;
    case STRING_T: fprintf(file, "char * "); break;
  }
}

void translateDefines(defines_node * defines) {
  defines_node * next = defines;
  while(next != NULL) {
    define_node * define = next->define;
    fprintf(file, "#define %s ", define->name);
    switch (define->production) {
      case DEFINE_INTEGER: fprintf(file, "%d\n", define->value); break;
      case DEFINE_STRING: fprintf(file, "%s\n", define->string_name); break;
    }
    next = next->next;
  }
}

void translateFunctionDefinitions(functionList * functions) {
  functionList * next = functions;
  while(next != NULL) {
    functionNode * function = next->function;
    translateFunctionDefinition(function);
    fprintf(file, ";\n");
    next = next->next;
  }
}

void translateFunctionDefinition(functionNode * function) {
  translateType(function->basic, function->compound);
  fprintf(file, "%s(", function->name);
  translateParameters(function->arguments);
  fprintf(file, ")");
}

void translateParameters(variableList * arguments) {
  variableList * next = arguments;
  while(next != NULL) {
    variableNode * variable = next->variable;
    translateType(variable->basic, variable->compound);
    fprintf(file, "%s", variable->name);
    next = next->next;
    if(next != NULL)
      fprintf(file, ", ");
  }
}

void translateFunctions(functions_node * functions) {
  functions_node * next = functions;
  while(next != NULL) {
    function_node * function = next->function;
    functionNode * fun = getFunction(function->name);
    funCurrent = fun;
    translateFunctionDefinition(fun);
    fprintf(file, " {\n");
    //declareVariables(fun->variables);
    translateSentences(function->sentences);
    fprintf(file, "}\n\n");
    next = next->next;
  }
}

void declareVariables(variableList * variables) {
  variableList * next = variables;
  while(next != NULL) {
    variableNode * variable = next->variable;
    translateType(variable->basic, variable->compound);
    fprintf(file, "%s;\n", variable->name);
    next = next->next;
  }
}

void translateSentences(sentences_node * sentences) {
  sentences_node * next = sentences;
  while(next != NULL) {
    sentence_node * sentence = next->sentence;
    translateSentence(sentence);
    next = next->sentences;
  }
}

void translateSentence(sentence_node * sentence) {
  switch (sentence->production) {
    case SENTENCE_DECLARATION: translateDeclaration(sentence); break;
    case SENTENCE_IF: translateIf(sentence->if_node); break;
    case SENTENCE_FOR: translateFor(sentence->for_node); break;
    case SENTENCE_WHILE: translateWhile(sentence->while_node); break;
    case SENTENCE_FUNCTION: translateFunctionCall(sentence); break;
    case SENTENCE_VARIABLE: translateVariableOperation(sentence); break;
    case SENTENCE_RETURN: translateReturn(sentence); break;
  }
}

void translateDeclaration(sentence_node * sentence) {
  declaration_node * declaration = sentence->declaration;
  variableNode * variable = getVariable(declaration->name, funCurrent);
  translateType(variable->basic, variable->compound);
  fprintf(file, "%s;\n", variable->name);
  translateSentenceEnd(sentence);
}

void translateIf(if_node * ifNode) {
  fprintf(file, "if(");
  translateCondition(ifNode->condition);
  fprintf(file, ") {\n");
  translateSentences(ifNode->sentences);
  fprintf(file, "}\n");
  translateElse(ifNode->else_branch);
}

void translateElse(if_node * elseNode) {
  if(elseNode == NULL)
    return;

  fprintf(file, "else {\n");

  if(elseNode->condition != NULL) {
    translateIf(elseNode);
  } else {
    translateSentences(elseNode->sentences);
  }
  fprintf(file, "}\n");
  translateElse(elseNode->else_branch);
}

void translateCondition(condition_node * condition) {
  switch (condition->production) {
    case CONDITION_LOGICAL: translateExpression(condition->expression_1);
                            fprintf(file, " %s ", condition->logical_operation);
                            translateExpression(condition->expression_2); break;
    case CONDITION_PARENTHESES: fprintf(file, "(");
                                translateCondition(condition->condition);
                                fprintf(file, ")"); break;
    case CONDITION_EXPRESSION: translateExpression(condition->expression_1); break;
  }
}

void translateExpression(expression_node * expression) {
  type_node * type = getExpressionType(expression);
  switch (expression->production) {
    case EXPRESSION_BOOLEAN: case EXPRESSION_INTEGER: fprintf(file, "%d", expression->boolean_number); break;
    case EXPRESSION_VARIABLE: fprintf(file, "%s", expression->name); break;
    case EXPRESSION_FUNCTION: translateExpressionFunctionCall(expression->function_execute); break;
    case EXPRESSION_OPERATION:translateOperation(expression); break;
  }
}

void translateOperation(expression_node * expression) {
  if(expression->expression_1->production == EXPRESSION_VARIABLE) {
    variableNode * var = getVariable(expression->expression_1->name, funCurrent);
    if(var->compound == QUEUE_T || var->compound == STACK_T) {
      switch (expression->op) {
        case '-': translateQueueStackOperations(var, 0); fprintf(file, ")"); return;
        case '+': translateQueueStackOperations(var, 1); fprintf(file, ")"); return;
        default: error(INCOMPATIBLE);
      }
    }
  }
  translateExpression(expression->expression_1);
  fprintf(file, " %c ", expression->op);
  translateExpression(expression->expression_2);
}

void translateExpressionFunctionCall(function_execute_node * function) {
  fprintf(file, "%s(", function->name);
  functionNode * fun = getFunction(function->name);
  if(fun == NULL) {
    error(FUNCTION_NOT_DEFINED);
  }
  translateCallParameters(function->parameters, fun);
  fprintf(file, ")");
}

void translateFor(for_node * forNode) {
  if(forNode->production == REGULAR_FOR) {
    translateAssignment(forNode->assignment);
    fprintf(file, "for(; ");
    translateCondition(forNode->condition);
    fprintf(file, "; ");
    translateForVariableOperation(forNode->variable_operation);
    fprintf(file, ") {\n");
    translateSentences(forNode->sentences);
    fprintf(file, "}\n");
    return;
  }

  variableNode * variable = getVariable(forNode->structure, funCurrent);
  fprintf(file, "while(!isEmpty(%s)) {\n", forNode->structure);
  fprintf(file, "%s = ", forNode->variable);
  translateQueueStackOperations(variable, 0);
  fprintf(file, ");\n");
  translateSentences(forNode->sentences);
  fprintf(file, "}\n");
}

void translateQueueStackOperations(variableNode * structure, int add) {
  char * aux = "";
  if(structure->basic == BOOLEAN_T || structure->basic == INTEGER_T)
    aux = "Int";
  if(add) {
    if(structure->compound == QUEUE_T) {
      fprintf(file, "queue%s(%s, ", aux, structure->name);
    } else {
      fprintf(file, "push%s(%s, ", aux, structure->name);
    }
  } else {
    if(structure->compound == QUEUE_T) {
      fprintf(file, "dequeue%s(%s", aux, structure->name);
    } else {
      fprintf(file, "pop%s(%s", aux, structure->name);
    }
  }
}

void translateForVariableOperation(variable_operation_node * variableOperation) {
  switch (variableOperation->production) {
    case VARIABLE_INCREMENT:fprintf(file, "%s++", variableOperation->increment_decrement_name);
                            break;
    case VARIABLE_DECREMENT: fprintf(file, "%s--", variableOperation->increment_decrement_name);
                            break;
  }
}

void translateWhile(while_node * whileNode) {
  fprintf(file, "while(");
  translateCondition(whileNode->condition);
  fprintf(file, ") {\n");
  translateSentences(whileNode->sentences);
  fprintf(file, "}\n");
}

void translateFunctionCall(sentence_node * sentence) {
  function_execute_node * function = sentence->function_execute;
  functionNode * fun = getFunction(function->name);
  if(fun == NULL) {
    error(FUNCTION_NOT_DEFINED);
  }
  if(sentence->sentenceEnd != ';') {
    switch (fun->basic) {
      case STRING_T: fprintf(file, "printf(\"%%s\\n\", "); break;
      case BOOLEAN_T: case INTEGER_T: fprintf(file, "printf(\"%%d\\n\", "); break;
    }
  }
  fprintf(file, "%s(", function->name);
  if(translateCallParameters(function->parameters, fun) != getFunctionParameterCount(fun)) {
    error(ERROR_ARGUMENTS);
  }

  fprintf(file, ")");
  if(sentence->sentenceEnd != ';') {
    if(fun->compound == QUEUE_T || fun->compound == STACK_T) {
      switch (fun->compound) {
        case QUEUE_T: fprintf(file, ";\n printf(\"Queue\\n\")"); break;
        case STACK_T: fprintf(file, ";\n printf(\"Stack\\n\")"); break;
      }
    }else {
      fprintf(file, ")");
    }
  }
  fprintf(file, ";\n");
}

int translateCallParameters(call_parameters_node * parameters, functionNode * function) {
  int i = 0;
  call_parameters_node * next = parameters;
  type_node * type = new_type_node(INTEGER_T, NONE);
  variableNode * variable;
  while(next != NULL) {
    variable = getParameterI(function, i);
    type->basicType = variable->basic;
    type->compoundType = variable->compound;
    call_parameter_node * parameter = next->parameter;
    translateCallParameter(parameter, type);
    next = next->next;
    if(next != NULL)
      fprintf(file, ", ");
    i++;
  }
  return i;
}

void translateCallParameter(call_parameter_node * parameter, type_node * expected) {
  if(parameter->production == PARAMERER_STRING) {
    if(expected->basicType != STRING_T || expected->compoundType != NONE) {
      error(INCOMPATIBLE_TYPE);
    }
    fprintf(file, "%s", parameter->string);
  } else {
    type_node * expr = getExpressionType(parameter->expression);
    if(expected->basicType != expr->basicType || expected->compoundType != expr->compoundType)
      error(INCOMPATIBLE_TYPE);
    translateExpression(parameter->expression);
  }
}

void translateVariableOperation(sentence_node * sentence) {
  variable_operation_node * variableOperation = sentence->variable_opration;
  switch (variableOperation->production) {
    case VARIABLE_ASSIGNMENT: translateAssignment(variableOperation->assignment); break;
    case VARIABLE_INCREMENT:fprintf(file, "%s++;\n", variableOperation->increment_decrement_name);
                            break;
    case VARIABLE_DECREMENT: fprintf(file, "%s--;\n", variableOperation->increment_decrement_name);
                            break;
  }
  translateSentenceEnd(sentence);
}

void translateAssignment(assignment_node * assignment) {
  variableNode * variable = getVariable(assignment->name,funCurrent);
  switch (assignment->production) {
    case ASSIGNMENT_STRING: if(variable->basic != STRING_T || variable->compound != NONE) {
                            error(INCOMPATIBLE_TYPE);
                            }fprintf(file, "%s = malloc(strlen(%s) + 1);\n", assignment->name, assignment->string);
                            fprintf(file, "strcpy(%s, %s);\n", assignment->name, assignment->string); break;
    case ASSIGNMENT_QUEUE: case ASSIGNMENT_STACK: translateQueueStack(assignment); break;
    case ASSIGNMENT_EXPRESSION: fprintf(file, "%s %s ", assignment->name, assignment->assignment_operation);
                                translateExpression(assignment->expression);
                                fprintf(file, ";\n"); break;
  }
}

void translateQueueStack(assignment_node * assignment) {
  fprintf(file, "%s = newList();\n", assignment->name);
  translateElementList(assignment);
}

void translateElementList(assignment_node * assignment) {
  elements_node * next = assignment->queue_stack->elements;
  variableNode * variable;
  int isQueue = assignment->production == ASSIGNMENT_QUEUE;
  variableNode * list = getVariable(assignment->name, funCurrent);
  while(next != NULL) {
    element_node * element = next->element;
    char* aux = "";

    if(element->production == ELEMENT_BOOLEAN || element->production == ELEMENT_INTEGER)
      aux = "Int";
    if(isQueue) {
      fprintf(file, "queue%s(%s, ", aux, assignment->name);
    } else {
      fprintf(file, "push%s(%s, ", aux, assignment->name);
    }

    switch (element->production) {
      case ELEMENT_STRING: if(list->basic != STRING_T) {
                            error(INCOMPATIBLE_TYPE);
                          }
                          fprintf(file, "%s, strlen(%s) + 1);\n", element->string_name, element->string_name); break;
      case ELEMENT_VARIABLE: variable = getVariable(element->string_name, funCurrent);
                            if(list->basic != variable->basic) {
                              error(INCOMPATIBLE_TYPE);
                            }
                            if(variable->basic == STRING_T)
                              fprintf(file, "%s, strlen(%s) + 1);\n", element->string_name, element->string_name);
                            else
                              fprintf(file, "%s, sizeof(%s));\n", element->string_name, element->string_name);
                            break;
      case ELEMENT_BOOLEAN: case ELEMENT_INTEGER: if(list->basic != BOOLEAN_T && list->basic != INTEGER_T) {
                                                    error(INCOMPATIBLE_TYPE);
                                                    } fprintf(file, "%d);\n", element->value); break;
    }
    next = next->next;
  }
}

void translateReturn(sentence_node * sentence) {
  fprintf(file, "return ");
  return_node * returnNode = sentence->return_node;
  if(returnNode->production == RETURN_STRING) {
    if(funCurrent->basic != STRING_T || funCurrent->compound != NONE)
      error(INCOMPATIBLE_TYPE);
    fprintf(file, "%s", returnNode->string);
  } else {
    type_node * value = getExpressionType(returnNode->expression);
    if(funCurrent->basic != value->basicType || funCurrent->compound != value->compoundType) {
      error(INCOMPATIBLE_TYPE);
    }
    translateExpression(returnNode->expression);
    free(value);
  }
  fprintf(file, ";\n");
}

void translateSentenceEnd(sentence_node * sentence) {
  if(sentence->sentenceEnd == ';') {
    return;
  }

  if(sentence->production == SENTENCE_VARIABLE || sentence->production == SENTENCE_DECLARATION) {
    variable_operation_node * variableOperation = sentence->variable_opration;
    declaration_node * declaration = sentence->declaration;
    char * var;
    if(variableOperation != NULL) {
      switch (variableOperation->production) {
        case VARIABLE_ASSIGNMENT: var = variableOperation->assignment->name; break;
        case VARIABLE_INCREMENT: var = variableOperation->increment_decrement_name; break;
      }
    } else {
      var = declaration->name;
    }
    variableNode * variable = getVariable(var, funCurrent);

    if(variable->compound == QUEUE_T || variable->compound == STACK_T) {
      switch (variable->compound) {
        case QUEUE_T: fprintf(file, "printf(\"Queue\\n\");\n"); break;
        case STACK_T: fprintf(file, "printf(\"Stack\\n\");\n"); break;
      }
      return;
    }
    switch (variable->basic) {
      case STRING_T: fprintf(file, "printf(\"%%s\\n\", %s);\n", var); break;
      case BOOLEAN_T: case INTEGER_T: fprintf(file, "printf(\"%%d\\n\", %s);\n", var); break;
    }
  }
}

type_node * getExpressionType(expression_node * expression) {
  type_node * t1;
  type_node * t2;
  type_node * aux;
  if(expression->production == EXPRESSION_BOOLEAN) {
    t1 = new_type_node(BOOLEAN_T, NONE);
    return t1;
  }

  if(expression->production == EXPRESSION_INTEGER) {
    t1 = new_type_node(INTEGER_T, NONE);
    return t1;
  }

  if(expression->production == EXPRESSION_VARIABLE) {
    variableNode * var = getVariable(expression->name, funCurrent);
    if(var == NULL)
      error(VARIABLE_NOT_DEFINED);
    t1 = new_type_node(var->basic, var->compound);
    return t1;
  }

  if(expression->production == EXPRESSION_FUNCTION) {
    functionNode * function = getFunction(expression->function_execute->name);
    if(function == NULL)
      error(FUNCTION_NOT_DEFINED);
    t1 = new_type_node(function->basic, function->compound);
    return t1;
  }

  t1 = getExpressionType(expression->expression_1);
  t2 = getExpressionType(expression->expression_2);

  if(isCompatible(t1, t2, expression->op)) {
    aux = new_type_node(t1->basicType, t1->compoundType);
    free(t1);
    free(t2);
    return aux;
  }
  error(NOT_VALID_OPERATION);
  free(t1);
  free(t2);
  return NULL;
}

int isCompatible(type_node * t1, type_node * t2, char op) {
  switch (op) {
    case '+': return isCompatibleAddition(t1, t2);
    case '-': return isCompatibleAddition(t1, t2);
    case '/': return isCompatibleMultMod(t1, t2);
    case '*': return isCompatibleMultMod(t1, t2);
    case '%': return isCompatibleMultMod(t1, t2);
  }
  return 1;
}

int isCompatibleAddition(type_node * t1, type_node * t2) {
  if(t1->compoundType == QUEUE_T || t2->compoundType == STACK_T) {
    return (t2->compoundType == NONE && t2->basicType == INTEGER_T);
  }

  switch (t1->basicType) {
    case INTEGER_T: case BOOLEAN_T: return 1;
    case STRING_T: return 0;
  }
}

int isCompatibleMultMod(type_node * t1, type_node * t2) {
  if(t1->compoundType == QUEUE_T || t2->compoundType == STACK_T) {
    return 0;
  }

  switch (t1->basicType) {
    case INTEGER_T: case BOOLEAN_T: return 1;
    case STRING_T: return 0;
  }
}

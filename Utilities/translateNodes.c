#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Compiler/nodes.h"
#include "translateNodes.h"
#include "typesCheck.h"

static FILE *file = NULL;
functionNode *funCurrent = NULL;

void translateProgramNode(program_node *program)
{
  file = fopen("Compiler/compiled.c", "w+");
  if (file != NULL)
  {
    fprintf(file, "#include <stdio.h>\n");
    fprintf(file, "#include <stdlib.h>\n");
    fprintf(file, "#include <string.h>\n");
    fprintf(file, "#include \"../Utilities/matrix.h\"\n\n");

    translateDefines(program->defines);
    fprintf(file, "\n");
    translateFunctionDefinitions(getFunctionList());
    fprintf(file, "\n");

    translateFunctions(program->functions);

    fclose(file);
  }
  else
    perror("Output file error\n");
}

void translateType(basicTypes basic, compoundTypes compound)
{
  if (compound == MATRIX_T)
  {
    fprintf(file, "matrix ");
    return;
  }
  switch (basic)
  {
  case BOOLEAN_T:
  case INTEGER_T:
    fprintf(file, "int ");
    break;
  case STRING_T:
    fprintf(file, "char * ");
    break;
  }
}

void translateDefines(defines_node *defines)
{
  defines_node *next = defines;
  while (next != NULL)
  {
    define_node *define = next->define;
    fprintf(file, "#define %s ", define->name);
    switch (define->production)
    {
    case DEFINE_INTEGER:
      fprintf(file, "%d\n", define->value);
      break;
    case DEFINE_STRING:
      fprintf(file, "%s\n", define->string_name);
      break;
    default:;
    }
    next = next->next;
  }
}

void translateFunctionDefinitions(functionList *functions)
{
  functionList *next = functions;
  while (next != NULL)
  {
    functionNode *function = next->function;
    translateFunctionDefinition(function);
    fprintf(file, ";\n");
    next = next->next;
  }
}

void translateFunctionDefinition(functionNode *function)
{
  translateType(function->basic, function->compound);
  fprintf(file, "%s(", function->name);
  translateParameters(function->arguments);
  fprintf(file, ")");
}

void translateParameters(variableList *arguments)
{
  variableList *next = arguments;
  while (next != NULL)
  {
    variableNode *variable = next->variable;
    translateType(variable->basic, variable->compound);
    fprintf(file, "%s", variable->name);
    next = next->next;
    if (next != NULL)
      fprintf(file, ", ");
  }
}

void translateFunctions(functions_node *functions)
{
  functions_node *next = functions;
  while (next != NULL)
  {
    function_node *function = next->function;
    functionNode *fun = getFunction(function->name);
    funCurrent = fun;
    translateFunctionDefinition(fun);
    fprintf(file, " {\n");
    //declareVariables(fun->variables);
    translateSentences(function->sentences);
    fprintf(file, "}\n\n");
    next = next->next;
  }
}

void declareVariables(variableList *variables)
{
  variableList *next = variables;
  while (next != NULL)
  {
    variableNode *variable = next->variable;
    translateType(variable->basic, variable->compound);
    fprintf(file, "%s;\n", variable->name);
    next = next->next;
  }
}

void translateSentences(sentences_node *sentences)
{
  sentences_node *next = sentences;
  while (next != NULL)
  {
    sentence_node *sentence = next->sentence;
    translateSentence(sentence);
    next = next->sentences;
  }
}

void translateSentence(sentence_node *sentence)
{
  switch (sentence->production)
  {
  case SENTENCE_DECLARATION:
    translateDeclaration(sentence);
    break;
  case SENTENCE_IF:
    translateIf(sentence->if_node);
    break;
  case SENTENCE_FOR:
    translateFor(sentence->for_node);
    break;
  case SENTENCE_WHILE:
    translateWhile(sentence->while_node);
    break;
  case SENTENCE_FUNCTION:
    translateFunctionCall(sentence);
    break;
  case SENTENCE_VARIABLE:
    translateVariableOperation(sentence);
    break;
  case SENTENCE_RETURN:
    translateReturn(sentence);
    break;
  default:;
  }
}

void translateDeclaration(sentence_node *sentence)
{
  declaration_node *declaration = sentence->declaration;
  variableNode *variable = getVariable(declaration->name, funCurrent);
  translateType(variable->basic, variable->compound);
  fprintf(file, "%s;\n", variable->name);
}

void translateIf(if_node *ifNode)
{
  fprintf(file, "if(");
  translateCondition(ifNode->condition);
  fprintf(file, ") {\n");
  translateSentences(ifNode->sentences);
  fprintf(file, "}\n");
  translateElse(ifNode->else_branch);
}

void translateElse(if_node *elseNode)
{
  if (elseNode == NULL)
    return;

  fprintf(file, "else {\n");

  if (elseNode->condition != NULL)
  {
    translateIf(elseNode);
  }
  else
  {
    translateSentences(elseNode->sentences);
  }
  fprintf(file, "}\n");
  translateElse(elseNode->else_branch);
}

void translateCondition(condition_node *condition)
{
  switch (condition->production)
  {
  case CONDITION_LOGICAL:
    translateExpression(condition->expression_1);
    fprintf(file, " %s ", condition->logical_operation);
    translateExpression(condition->expression_2);
    break;
  case CONDITION_PARENTHESES:
    fprintf(file, "(");
    translateCondition(condition->condition);
    fprintf(file, ")");
    break;
  case CONDITION_EXPRESSION:
    translateExpression(condition->expression_1);
    break;
  default:;
  }
}

void translateExpression(expression_node *expression)
{
  type_node *type = getExpressionType(expression);
  switch (expression->production)
  {
  case EXPRESSION_BOOLEAN:
  case EXPRESSION_INTEGER:
    fprintf(file, "%d", expression->boolean_number);
    break;
  case EXPRESSION_VARIABLE:
    fprintf(file, "%s", expression->name);
    break;
  case EXPRESSION_FUNCTION:
    translateExpressionFunctionCall(expression->function_execute);
    break;
  case EXPRESSION_OPERATION:
    translateOperation(expression);
    break;
  default:;
  }
}

void translateOperation(expression_node *expression)
{
  if (expression->expression_1->production == EXPRESSION_VARIABLE)
  {
    variableNode *var = getVariable(expression->expression_1->name, funCurrent);
    variableNode *var2 = getVariable(expression->expression_2->name, funCurrent);
    if (var->compound == MATRIX_T && var2->compound == MATRIX_T)
    {
      switch (expression->op)
      {
      case '-':
        fprintf(file, "subMatrix(%s, %s)", expression->expression_1->name, expression->expression_2->name);
        return;
      case '+':
        fprintf(file, "sumMatrix(%s, %s)", expression->expression_1->name, expression->expression_2->name);
        return;
      case '*':
        fprintf(file, "mulMatrix(%s, %s)", expression->expression_1->name, expression->expression_2->name);
        return;
      default:
        error(INCOMPATIBLE);
      }
    }
    else if (var->compound == MATRIX_T && var2->compound == INTEGER_T)
    {
      if (expression->op == '*')
      {
        fprintf(file, "multMatrixEsc(%s, %s)", expression->expression_1->name, expression->expression_2->name);
        return;
      }
    }
    else if (var->compound == INTEGER_T && var2->compound == MATRIX_T)
    {
      if (expression->op == '*')
      {
        fprintf(file, "multMatrixEsc(%s, %s)", expression->expression_2->name, expression->expression_1->name);
        return;
      }
    }
    translateExpression(expression->expression_1);
    fprintf(file, " %c ", expression->op);
    translateExpression(expression->expression_2);
  }
}

void translateExpressionFunctionCall(function_execute_node *function)
{
  fprintf(file, "%s(", function->name);
  functionNode *fun = getFunction(function->name);
  if (fun == NULL)
  {
    error(FUNCTION_NOT_DEFINED);
  }
  translateCallParameters(function->parameters, fun);
  fprintf(file, ")");
}

void translateFor(for_node *forNode)
{
  if (forNode->production == REGULAR_FOR)
  {
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
  error(BAD_FOR_ERROR);
}

void translateForVariableOperation(variable_operation_node *variableOperation)
{
  switch (variableOperation->production)
  {
  case VARIABLE_INCREMENT:
    fprintf(file, "%s++", variableOperation->increment_decrement_name);
    break;
  case VARIABLE_DECREMENT:
    fprintf(file, "%s--", variableOperation->increment_decrement_name);
    break;
  default:;
  }
}

void translateWhile(while_node *whileNode)
{
  fprintf(file, "while(");
  translateCondition(whileNode->condition);
  fprintf(file, ") {\n");
  translateSentences(whileNode->sentences);
  fprintf(file, "}\n");
}

void translateFunctionCall(sentence_node *sentence)
{
  function_execute_node *function = sentence->function_execute;
  if(strcmp(function->name,"printf") == 0) {
    translateCallPrintfParameters(function->parameters);
    return;
  }
  functionNode *fun = getFunction(function->name);
  if (fun == NULL)
  {
    error(FUNCTION_NOT_DEFINED);
  }

  fprintf(file, "%s(", function->name);
  if (translateCallParameters(function->parameters, fun) != getFunctionParameterCount(fun))
  {
    error(ERROR_ARGUMENTS);
  }
  fprintf(file, ");\n");
}

int translateCallParameters(call_parameters_node *parameters, functionNode *function)
{
  int i = 0;
  call_parameters_node *next = parameters;
  type_node *type = new_type_node(INTEGER_T, NONE);
  variableNode *variable;
  while (next != NULL)
  {
    variable = getParameterI(function, i);
    type->basicType = variable->basic;
    type->compoundType = variable->compound;
    call_parameter_node *parameter = next->parameter;
    translateCallParameter(parameter, type);
    next = next->next;
    if (next != NULL)
      fprintf(file, ", ");
    i++;
  }
  return i;
}

int translateCallPrintfParameters(call_parameters_node *parameters)
{
  int i = 0;
  call_parameters_node *next = parameters;
  variableNode *variable;
  char *str = calloc(strlen(next->parameter->string), sizeof(char));
  strcpy(str, next->parameter->string + 1);
  str[strlen(str)-1] = 0;
  next = next->next;
  if(next == NULL) {
    fprintf(file, "printf(\"");
    fprintf(file, "%s", str);
    fprintf(file, "\");\n");
    printf("1");
    return i;
  }
  int pieces = 0;
  for(int j=0; j<strlen(str); j++) {
    if(str[j] == '%') {
      pieces++;
    }
  }
  char **strPieces = calloc((2*pieces+1),sizeof(char*));
  int piece = 0;
  strPieces[0] = calloc(strlen(str),sizeof(char));
  for(int j=0; j<strlen(str); j++) {
    char *concat = malloc(sizeof(char));
    *concat = str[j];
    if(str[j] == '%' && j-1 >= 0 && str[j-1] != '\\') {
      strPieces[++piece] = calloc(2,sizeof(char));
      
      strcat(strPieces[piece], concat);
      if(++j < strlen(str)) {
        *concat = str[j];
        strcat(strPieces[piece], concat);
      }
      strPieces[++piece] = calloc(strlen(str),sizeof(char));
    } else {
      strcat(strPieces[piece], concat);
    }
  }
  while (next != NULL)
  {
    if(strPieces[i][0] != '%') {
      printf("2\n");
      fprintf(file, "printf(\"");
      fprintf(file, "%s", strPieces[i]);
      fprintf(file, "\");\n");
    } else if(strPieces[i][1] == 'm') {
      printf("3\n");
      fprintf(file, "printf(\"\\n\");\n");
      fprintf(file, "printMatrix(");
      if(next->parameter->expression == NULL) {
        fprintf(file, "%s", next->parameter->string);
      } else {
        translateExpression(next->parameter->expression);
      }
      fprintf(file, ");\n");
      next = next->next;
    } else {
      printf("4\n");
      fprintf(file, "printf(\"");
      fprintf(file, "%s", strPieces[i]);
      fprintf(file, "\", ");
      if(next->parameter->expression == NULL) {
        fprintf(file, "%s", next->parameter->string);
      } else {
        translateExpression(next->parameter->expression);
      }
      fprintf(file, ");\n");
      next = next->next;
    }
    i++;
  }
  if(i == piece && strlen(strPieces[i]) > 0) {
    printf("5\n");
    fprintf(file, "printf(\"");
    fprintf(file, "%s", strPieces[i]);
    fprintf(file, "\");\n");
  }
  fprintf(file, "printf(\"\\n\");\n");
  return i;
}

void translateCallParameter(call_parameter_node *parameter, type_node *expected)
{
  if (parameter->production == PARAMETER_STRING)
  {
    if (expected->basicType != STRING_T || expected->compoundType != NONE)
    {
      error(INCOMPATIBLE_TYPE);
    }
    fprintf(file, "%s", parameter->string);
  }
  else
  {
    type_node *expr = getExpressionType(parameter->expression);
    if (expected->basicType != expr->basicType || expected->compoundType != expr->compoundType)
      error(INCOMPATIBLE_TYPE);
    translateExpression(parameter->expression);
  }
}

void translateVariableOperation(sentence_node *sentence)
{
  variable_operation_node *variableOperation = sentence->variable_opration;
  switch (variableOperation->production)
  {
  case VARIABLE_ASSIGNMENT:
    translateAssignment(variableOperation->assignment);
    break;
  case VARIABLE_INCREMENT:
    fprintf(file, "%s++;\n", variableOperation->increment_decrement_name);
    break;
  case VARIABLE_DECREMENT:
    fprintf(file, "%s--;\n", variableOperation->increment_decrement_name);
    break;
  default:;
  }
}

void translateAssignment(assignment_node *assignment)
{
  variableNode *variable = getVariable(assignment->name, funCurrent);
  switch (assignment->production)
  {
  case ASSIGNMENT_STRING:
    if (variable->basic != STRING_T || variable->compound != NONE)
    {
      error(INCOMPATIBLE_TYPE);
    }
    fprintf(file, "%s = malloc(strlen(%s) + 1);\n", assignment->name, assignment->string);
    fprintf(file, "strcpy(%s, %s);\n", assignment->name, assignment->string);
    break;
  case ASSIGNMENT_MATRIX:
    translateMatrix(assignment);
    break;
  case ASSIGNMENT_EXPRESSION:
    fprintf(file, "%s %s ", assignment->name, assignment->assignment_operation);
    translateExpression(assignment->expression);
    fprintf(file, ";\n");
    break;
  default:;
  }
}

void translateMatrix(assignment_node *assignment)
{
  fprintf(file, "%s = createMatrix(%d, %d, INT_TYPE);\n", assignment->name, assignment->matrix->rowsnum, assignment->matrix->cols);
  translateElementList(assignment);
}

void translateElementList(assignment_node *assignment)
{
  rows_node *next = assignment->matrix->rows;
  variableNode *variable;
  variableNode *list = getVariable(assignment->name, funCurrent);
  int c = 0;
  int r = 0;
  while (next != NULL)
  {
    row_node *row = next->row;
    c=0;
    while (row != NULL)
    {
      fprintf(file, "addValue(%d, %d, %d, %s);\n", r, c, row->value, assignment->name);
      row = row->next;
      c++;
    }
    next = next->next;
    r++;
  }
}

void translateReturn(sentence_node *sentence)
{
  fprintf(file, "return ");
  return_node *returnNode = sentence->return_node;
  if (returnNode->production == RETURN_STRING)
  {
    if (funCurrent->basic != STRING_T || funCurrent->compound != NONE)
      error(INCOMPATIBLE_TYPE);
    fprintf(file, "%s", returnNode->string);
  }
  else
  {
    type_node *value = getExpressionType(returnNode->expression);
    if (funCurrent->basic != value->basicType || funCurrent->compound != value->compoundType)
    {
      error(INCOMPATIBLE_TYPE);
    }
    translateExpression(returnNode->expression);
    free(value);
  }
  fprintf(file, ";\n");
}

type_node *getExpressionType(expression_node *expression)
{
  type_node *t1;
  type_node *t2;
  type_node *aux;
  if (expression->production == EXPRESSION_BOOLEAN)
  {
    t1 = new_type_node(BOOLEAN_T, NONE);
    return t1;
  }

  if (expression->production == EXPRESSION_INTEGER)
  {
    t1 = new_type_node(INTEGER_T, NONE);
    return t1;
  }

  if (expression->production == EXPRESSION_VARIABLE)
  {
    variableNode *var = getVariable(expression->name, funCurrent);
    if (var == NULL)
      error(VARIABLE_NOT_DEFINED);
    t1 = new_type_node(var->basic, var->compound);
    return t1;
  }

  if (expression->production == EXPRESSION_FUNCTION)
  {
    functionNode *function = getFunction(expression->function_execute->name);
    if (function == NULL)
      error(FUNCTION_NOT_DEFINED);
    t1 = new_type_node(function->basic, function->compound);
    return t1;
  }

  t1 = getExpressionType(expression->expression_1);
  t2 = getExpressionType(expression->expression_2);

  if (isCompatible(t1, t2, expression->op))
  {
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

int isCompatible(type_node *t1, type_node *t2, char op)
{
  switch (op)
  {
  case '+':
    return isCompatibleAddition(t1, t2);
  case '-':
    return isCompatibleAddition(t1, t2);
  case '/':
    return isCompatibleMultMod(t1, t2);
  case '*':
    return isCompatibleMultMod(t1, t2);
  case '%':
    return isCompatibleMultMod(t1, t2);
  }
  return 1;
}

int isCompatibleAddition(type_node *t1, type_node *t2)
{
  if (t1->compoundType == MATRIX_T || t2->compoundType == MATRIX_T)
  {
    return 1;
  }

  switch (t1->basicType)
  {
  case INTEGER_T:
  case BOOLEAN_T:
    return 1;
  case STRING_T:
    return 0;
  }
}

int isCompatibleMultMod(type_node *t1, type_node *t2)
{
  if (t1->compoundType == MATRIX_T || t2->compoundType == MATRIX_T)
  {
    return (t1->basicType == INTEGER_T && t2->basicType == INTEGER_T);
  }

  switch (t1->basicType)
  {
  case INTEGER_T:
  case BOOLEAN_T:
    return 1;
  case STRING_T:
    return 0;
  }
}

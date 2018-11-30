#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Compiler/nodes.h"
#include "typesCheck.h"

functionList * functions = NULL;
variableList * defines;
functionNode * current = NULL;

functionList * getFunctionList() {
  return functions;
}

int functionExists(char * name) {
  return getFunction(name) != NULL;
}

functionNode * createFunction() {
  functionNode * function = malloc(sizeof(functionNode));
	function->basic = INTEGER_T;
  function->compound = INTEGER_T;
	function->arguments = NULL;
	function->variables = NULL;
  current = function;
  return function;
}

int renameCurrent(char * name) {
  if(functionExists(name)) {
		return 0;
	}
  current->name = malloc(strlen(name) + 1);
  strcpy(current->name, name);

  addToList(current, &functions);
  current = createFunction();
  return 1;
}

void addToList(functionNode * function, functionList ** list) {
  functionList * node = malloc(sizeof(functionList));
  node->function = function;
  node->next = *list;
	*list = node;
}

int addReturn(basicTypes basic, compoundTypes compound) {
  if(current == NULL) {
    current = createFunction();
  }

  current->basic = basic;
  current->compound = compound;
  return 1;
}

int addParameterToFunction(char * name, basicTypes basic, compoundTypes compound) {
  if(current == NULL) {
    current = createFunction();
  }
  if(parameterExists(name))
    return 0;

  variableList * node = malloc(sizeof(variableList));
  node->variable = createVariable(name, basic, compound);
  node->next = current->arguments;
  current->arguments = node;

  return 1;
}

void addToDefines(char * name, basicTypes basic) {
  variableList * node = malloc(sizeof(variableList));
  node->variable = createVariable(name, basic, basic);
  node->next = defines;
  defines = node;
}

int existsDefine(char * name) {
  if(current == NULL) {
    current = createFunction();
  }
  variableNode * ret = getVariableFromList(name, defines);
  if(ret != NULL)
    return 1;
}

variableNode * createVariable(char * name, basicTypes basic, compoundTypes compound) {
  variableNode * variable = malloc(sizeof(variableNode));
  variable->name = malloc(strlen(name) + 1);
	strcpy(variable->name, name);
	variable->basic = basic;
  variable->compound = compound;

  return variable;
}

int addVariable(char * name, basicTypes basic, compoundTypes compound) {
  if(current == NULL) {
    current = createFunction();
  }
  if(existsVariable(name))
    return 0;

  variableList * node = malloc(sizeof(variableList));
  node->variable = createVariable(name, basic, compound);
  node->next = current->variables;
  current->variables = node;

  return 1;
}

int parameterExists(char * name) {
  variableNode * ret = getVariableFromList(name, defines);
  if(ret != NULL)
    return 1;
  ret = getVariableFromList(name, current->arguments);
  return ret != NULL;
}

functionNode * getFunction(char * name) {
  functionList * next = functions;
  while(next != NULL) {
    functionNode * function = next->function;
    if(strcmp(function->name, name) == 0)
      return function;
    next = next->next;
  }
  return NULL;
}

variableNode * getVariable(char * name, functionNode * function) {
  variableNode * ret = getVariableFromList(name, defines);
  if(ret != NULL)
    return ret;
  ret = getVariableFromList(name, function->arguments);
  if(ret != NULL)
    return ret;
  ret = getVariableFromList(name, function->variables);
  return ret;
}

variableNode * getVariableFromList(char * name, variableList * list) {
  variableList * next = list;
  while(next != NULL) {
    variableNode * variable = next->variable;
    if(strcmp(variable->name, name) == 0)
      return variable;
    next = next->next;
  }
  return NULL;
}

int existsVariableTyped(char * name, basicTypes basic, compoundTypes compound) {
  variableNode * ret = getVariableFromList(name, current->arguments);
  if(ret != NULL) {
    if(ret->basic != basic || ret->compound != compound) {
      return -1;
    }
    return 1;
  }
  ret = getVariableFromList(name, current->variables);
  if(ret != NULL) {
    if(ret->basic != basic || ret->compound != compound) {
      return -1;
    }
    return 1;
  }
  return 0;
}

int existsVariable(char * name) {
  if(current == NULL) {
    current = createFunction();
  }
  variableNode * ret = getVariableFromList(name, current->arguments);
  if(ret != NULL)
    return 1;
  ret = getVariableFromList(name, current->variables);
  return ret != NULL;
}

int getFunctionParameterCount(functionNode * function) {
  int i = 0;
  variableList * next = function->arguments;
  while(next != NULL) {
    variableNode * variable = next->variable;
    i++;
    next = next->next;
  }
  return i;
}

variableNode * getParameterI(functionNode * function, int i) {
  int j = 0;
  variableList * next = function->arguments;
  while(next != NULL) {
    variableNode * variable = next->variable;
    if(j == i)
      return variable;
    j++;
    next = next->next;
  }
  return NULL;
}


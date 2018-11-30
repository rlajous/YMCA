#ifndef TYPECHECKS_H
#define TYPECHECKS_H

#define TYPE_DEFINED 2
#define INCOMPATIBLE_DEFINITION 1

typedef struct {
  char * name;
  basicTypes basic;
  compoundTypes compound;
} variableNode;

typedef struct variableList {
  struct variableList * next;
  variableNode * variable;
} variableList;

typedef struct {
  char * name;
  variableList * variables;
  variableList * arguments;
  basicTypes basic;
  compoundTypes compound;
} functionNode;

typedef struct functionList {
  struct functionList * next;
  functionNode * function;
} functionList;

functionList * getFunctionList();

int functionExists(char * name);

functionNode * createFunction();

int renameCurrent(char * name);

void addToList(functionNode * function, functionList ** list);

int addReturn(basicTypes basic, compoundTypes compound);

int addParameterToFunction(char * name, basicTypes basic, compoundTypes compound);

void addToDefines(char * name, basicTypes basic);

int existsDefine(char * name);

variableNode * createVariable(char * name, basicTypes basic, compoundTypes compound);

int addVariable(char * name, basicTypes basic, compoundTypes compound);

int parameterExists(char * name);

functionNode * getFunction(char * name);

variableNode * getVariable(char * name, functionNode * function);

variableNode * getVariableFromList(char * name, variableList * list);

int existsVariableTyped(char * name, basicTypes basic, compoundTypes compound);

int existsVariable(char * name);

int getFunctionParameterCount(functionNode * function);

variableNode * getParameterI(functionNode * function, int i);

#endif

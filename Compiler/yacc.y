%{
#include <stdio.h>
/*extern void yyerror(char *);*/
%}

%start sentence

%token A_TOKEN ANOTHER ETC

%%
 /* Las producciones (o "reglas") de la gramatica
  * que describe nuestro lenguaje
  */
sentence: ANOTHER sentence 
    |     ANOTHER {printf("bien formado\n");}
    ;

%%

int main() {
    return(yyparse());
}

yyerror(s)
char *s;
{
  fprintf(stderr, "%s\n",s);
}

yywrap()
{
  return(1);
}
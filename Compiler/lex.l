%{
//aca va codigo C que queremos que se incluya
//en el output (headers por ejemplo)

#include <stdio.h>
#include "y.tab.h" /* token codes from the parser */
%}

%%
[a-zA-Z]+ {printf("%s", yytext);}
.|\n {ECHO;}
%%
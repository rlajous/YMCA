# YMCA
YET MATRIX COMPILER ANOTHER feat Village People
https://www.youtube.com/watch?v=Vc0gYbTNctU

To compile and run (using packages 'flex' and 'byacc' on Linux) we say:

flex lex.l && yacc -d yacc.y && cc -o parser lex.yy.c y.tab.c && ./parser
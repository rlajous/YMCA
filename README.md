# YMCA
YET MATRIX COMPILER ANOTHER feat Village People
https://www.youtube.com/watch?v=Vc0gYbTNctU

## To compile and run (using packages 'flex' and 'byacc' on Linux) we do:

#### Compile the compiler (Only first time use):
make all

#### Compile the .ymca file:
./compiler.sh your_input_file.ymca

#### Run the compiled .ymca file:
./executable

## In pampero, bash scripts can't be run, so we can do:
make all
cat input.ymca | ./Compiler/parser
gcc -o executable ./Compiler/compiled.c ./Utilities/matrix.c
./executable

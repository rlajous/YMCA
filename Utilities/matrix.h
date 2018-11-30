#ifndef MATRIX_H
#define MATRIX_H

enum types { INT_TYPE, FLOAT_TYPE, DOUBLE_TYPE, CHAR_TYPE, STR_TYPE};

typedef struct matrixT{
	size_t width;
	size_t height;
	enum types type;
	int * mtrx;
} matrixT;

typedef matrixT* matrix;

matrix newMatrix();

void freeMatrix(matrix mat);

matrix createMatrix(size_t w, size_t h, int t);

void addValue(int row, int col, int value, matrix mat);

matrix sumMatrix( matrix a, matrix b);

matrix subMatrix( matrix a, matrix b);

matrix multMatrixEsc( matrix a, double e);

matrix mulMatrix( matrix a, matrix b);

matrix transMatrix(matrix a);


#endif
#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrixT{
	size_t width;
	size_t height;
	void *type;
	void *mtrx;
} matrixT;

typedef matrixT* matrix;

matrix newMatrix();

void freeMatrix(matrix mat);

matrix createMatrix(size_t w, size_t h, void *t);

#endif
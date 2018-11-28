#include <stdlib.h>
#include <string.h>
#include "matrix.h"



matrix newMatrix() {
	return calloc(1, sizeof(matrix));
}

void freeMatrix(matrix mat){
	if(mat == NULL)
		return;

	if(mat->type != NULL){
		free(mat->type);
	}
	if(mat->mtrx != NULL){
		free(mat->mtrx);
	}
	free(mat);
}

matrix createMatrix(size_t w, size_t h, void *t) {
	matrix mat = newMatrix();

	if(t == NULL)
		return NULL;

	mat->type = calloc(1, sizeof(t));
	if(mat->type == NULL)
		return NULL;
	memcpy(mat->type,t,sizeof(t));


	int matSize = w*h*sizeof(t);
	mat->width = w;
	mat->height = h;
	mat->mtrx = calloc(1, matSize);
	if(mat->mtrx == NULL){
		free(mat->type);
		return NULL;
	}

	return mat;
}
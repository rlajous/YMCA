#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "matrix.h"



matrix newMatrix() {
	return calloc(1, sizeof(matrixT));
}

void freeMatrix(matrix mat){
	if(mat == NULL)
		return;

	if(mat->mtrx != NULL){
		free(mat->mtrx);
	}
	free(mat);
}

matrix createMatrix(size_t h, size_t w, int t) {
	matrix mat = newMatrix();

	switch(t) {
		case INT_TYPE: mat->type = INT_TYPE;
		mat->mtrx = calloc(w*h,sizeof(int));
		break;
		case FLOAT_TYPE: mat->type = FLOAT_TYPE;
		mat->mtrx = calloc(w*h,sizeof(float));
		break;
		case DOUBLE_TYPE: mat->type = DOUBLE_TYPE;
		mat->mtrx = calloc(w*h,sizeof(double));
		break;
		case CHAR_TYPE: mat->type = CHAR_TYPE;
		mat->mtrx = calloc(w*h,sizeof(char));
		break;
		case STR_TYPE: mat->type = STR_TYPE;
		mat->mtrx = calloc(w*h,sizeof(char *));
		break;
		default: freeMatrix(mat);return NULL;
	}
	
	if (mat->mtrx == NULL){
		freeMatrix(mat);
		return NULL;
	}

	mat->width = w;
	mat->height = h;


	return mat;
}

void addValue(int row, int col, int value, matrix mat){
	int * m = mat->mtrx;
	*(m + (row*mat->width + col))  = value;
}


  
matrix sumMatrix( matrix a, matrix b) {
	
	if(b->type != INT_TYPE && b->type != DOUBLE_TYPE && b->type != FLOAT_TYPE && a->type != INT_TYPE && a->type != DOUBLE_TYPE && a->type != FLOAT_TYPE) { 
		return NULL;
	}

	if(a->width != b->width || a->height != b->height) {
		return NULL;
	}
 
	int i,k;
	matrix mat;
	
	if(a->type >= b->type){
		mat = createMatrix(a->width, a->height, a->type);
	}else{
		mat = createMatrix(a->width, a->height, b->type);
	}

	int * m = a->mtrx;
	int * n = b->mtrx;


	for(i = 0; i < a->width; i++) {
		for(k = 0; k < a->height; k++) {
			addValue(i, k,  m[k*a->width + i] + n[k*b->width + i], mat);
		}
	}

	return mat;
}

matrix subMatrix( matrix a, matrix b) {
	
	if(b->type != INT_TYPE && b->type != DOUBLE_TYPE && b->type != FLOAT_TYPE && a->type != INT_TYPE && a->type != DOUBLE_TYPE && a->type != FLOAT_TYPE) { 
		return NULL;
	}

	if(a->width != b->width || a->height != b->height) {
		return NULL;
	}
 
	int i,k;
	matrix mat;
	
	if(a->type >= b->type){
		mat = createMatrix(a->width, a->height, a->type);
	}else{
		mat = createMatrix(a->width, a->height, b->type);
	}

	int * m = a->mtrx;
	int * n = b->mtrx;


	for(i = 0; i < a->width; i++) {
		for(k = 0; k < a->height; k++) {
			addValue(i, k,  m[k*a->width + i] - n[k*b->width + i], mat);
		}
	}

	return mat;
}


matrix multMatrixEsc( matrix a, double e) {
	
	if(a->type != INT_TYPE && a->type != DOUBLE_TYPE && a->type != FLOAT_TYPE) { 
		return NULL;
	}


	int i,k;
	matrix mat;
	
	mat = createMatrix(a->width, a->height, a->type);
	

	int * m = a->mtrx;


	for(i = 0; i < a->width; i++) {
		for(k = 0; k < a->height; k++) {
			addValue(i, k,  m[k*a->width + i] * e, mat);
		}
	}


	return mat;
}


matrix mulMatrix( matrix a, matrix b) {
	
	if(b->type != INT_TYPE && b->type != DOUBLE_TYPE && b->type != FLOAT_TYPE && a->type != INT_TYPE && a->type != DOUBLE_TYPE && a->type != FLOAT_TYPE) { 
		return NULL;
	}

	if(a->width != a->height) {
		return NULL;
	}
 
	
	matrix mat;
	
	if(a->type >= b->type){
		mat = createMatrix(a->width, a->height, a->type);
	}else{
		mat = createMatrix(a->width, a->height, b->type);
	}

	int * m = a->mtrx;
	int * n = b->mtrx;
	int c,d,k,sum = 0;

	for (c = 0; c < a->height; c++) {
    	for (d = 0; d < b->width; d++) {
    		for (k = 0; k < a->width; k++) {
          		sum = sum + m[c*a->width + k] * n[k*b->width + d];
        	}
        	addValue(c, d,  sum, mat);
    	    sum = 0;
      	}
    }

	return mat;
}

matrix transMatrix(matrix a){

	matrix mat;
	int i,k;
	mat = createMatrix(a->width, a->height, a->type);

	int * m = a->mtrx;

	for(i = 0; i < a->width; i++) {
		for(k = 0; k < a->height; k++) {
			addValue(i, k,  m[k*a->width + i], mat);
		}
	}
	
	return mat;

}

void printMatrix(matrix m){
	int i, k;

	int * a = m->mtrx;

	
	for(i = 0; i < m->height; i++) {

		for(k = 0; k < m->width; k++) {
			printf("%d",a[i*m->width + k]);
			if(k != m->width - 1){
				printf(", ");
			}
		}

		printf("\n");
	
	}

	



}



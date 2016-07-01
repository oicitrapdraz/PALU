#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "matrix.h"

int** matrix_define(int dim, bool init) {
	int i, j;

	int **m;

	m = calloc(dim, sizeof(int *));

	for (i = 0; i < dim; i++)
		m[i] = calloc(dim, sizeof(int));

	if (init) {
		for (i = 0; i < dim; i++) {
			for (j = 0; j < dim; j++)
				m[i][j] = rand() % 10;
		}
	}

	return m;
}

void matrix_show(int **m, int dim) {
	int i, j;

	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++)
			printf("\t%d", m[i][j]);
		printf("\n\n");
	}
}

int** matrix_delete(int **m, int dim) {
	int i;

	for (i = 0; i < dim; i++)
		free(m[i]);

	free(m);

	return NULL;
}

void matrix_mult(int **a, int **b, int **res, int dim) {
	int i, j, k, acumulator = 0;

	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++, acumulator = 0) {
			for (k = 0; k < dim; k++)
				acumulator += a[i][k] * b[k][j];
			res[i][j] = acumulator;
		}
}

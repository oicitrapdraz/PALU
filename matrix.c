#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "matrix.h"

double** matrix_identity_define(int dim) {
	double **m = calloc(dim, sizeof(double *));
	int i, j;

	for (i = 0; i < dim; i++)
		m[i] = calloc(dim, sizeof(double));

	for (i = 0; i < dim; i++)
		m[i][i] = 1;

	return m;
}

double** matrix_zero_define(int dim) {
	double **m = calloc(dim, sizeof(double *));
	int i, j;

	for (i = 0; i < dim; i++)
		m[i] = calloc(dim, sizeof(double));

	return m;
}

double** matrix_random_define(int dim) {
	double **m = calloc(dim, sizeof(double *));
	int i, j;

	for (i = 0; i < dim; i++)
		m[i] = calloc(dim, sizeof(double));

	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++)
			m[i][j] = 1 + rand() % 9;
	}

	return m;
}

void matrix_show(double **m, int dim) {
	if (!m) {
		printf("\n\nError: Matriz nula\n\n");

		return ;
	}

	int i, j;

	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++)
			printf("\t%.1f", m[i][j]);
		printf("\n\n");
	}
}

double** matrix_delete(double **m, int dim) {
	if (!m) {
		//printf("\n\nError: Matriz nula\n\n");

		return NULL;
	}

	int i;

	for (i = 0; i < dim; i++)
		free(m[i]);

	free(m);

	return NULL;
}

void matrix_dot(double **a, double **b, double **res, int dim) {
	if (!a || !b || !res) {
		//printf("\n\nError: Matriz nula\n\n");

		return ;
	}

	double acumulator = 0;
	int i, j, k;

	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++, acumulator = 0) {
			for (k = 0; k < dim; k++)
				acumulator += a[i][k] * b[k][j];
			res[i][j] = acumulator;
		}
}

double** matrix_p(double **a, int col, int dim) {
	if (!a) {
		//printf("\n\nError: Matriz nula\n\n");

		return NULL;
	}

	if (col > dim - 2) {
		//printf("\n\nError: Evaluando en una columna \"mayor\" o igual a la ultima\n\n");

		return NULL;
	}

	int i, max_index = col;
	double max_pivot = abs(a[col][col]), *tmp, **perm = matrix_identity_define(dim);

	for (i = col + 1; i < dim; i++)
		if (max_pivot < abs(a[i][col])) {
			max_pivot = a[i][col];
			max_index = i;
		}

	tmp = perm[col];
	perm[col] = perm[max_index];
	perm[max_index] = tmp;

	return perm;
}

double** matrix_l(double **a, int col, int dim) {
	if (col > dim - 2) {
		//printf("\n\nError: Evaluando en una columna \"mayor\" o igual a la ultima\n\n");

		return NULL;
	}

	if (a[col][col] == 0) {
		//printf("\n\nError: No se puede dividir por 0\n\n");

		return NULL;
	}

	double *tmp, **l = matrix_identity_define(dim);
	int i;

	for (i = col + 1; i < dim; i++)
		l[i][col] = a[i][col] / a[col][col];

	return l;
}

void matrix_row_operation(double **a, int col, int dim) {
	if (col > dim - 2) {
		//printf("\n\nError: Evaluando en una columna \"mayor\" o igual a la ultima\n\n");

		return ;
	}

	if (a[col][col] == 0) {
		//printf("\n\nError: No se puede dividir por 0\n\n");

		return ;
	}

	double factor;
	int i, j;

	for (i = col + 1; i < dim; i++) {
		factor = a[i][col] / a[col][col];
		for (j = 0; j < dim; j++)
			a[i][j] = a[i][j] - factor * a[col][j];
	}

	return ;
}

bool matrix_p_needed(double **a, int col, int dim) {
	if (col > dim - 2) {
		//printf("\n\nError: Evaluando en una columna \"mayor\" o igual a la ultima\n\n");

		return NULL;
	}

	int i, max_index = col;
	double max_pivot = a[col][col];

	for (i = col + 1; i < dim; i++)
		if (max_pivot < a[i][col]) {
			max_pivot = a[i][col];
			max_index = i;
		}

	if (max_index == col)
		return false;
	else
		return true;
}

void matrix_copy(double **a, double **b, int dim) {
	if (!a || !b) {
		//printf("\n\nError: Matriz nula\n\n");

		return ;
	}

	int i, j;

	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			b[i][j] = a[i][j];
}

void matrix_palu_show(double **p, double **a, double **l, double **u, int dim) {
	if (!p || !a || !l || !u) {
		//printf("\n\nError: Matriz nula\n\n");

		return ;
	}

	int i, j;

	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++)
			printf("\t | %.1f", p[i][j]);

		printf(" | ");

		for (j = 0; j < dim; j++)
			printf("\t | %.1f", a[i][j]);

		printf(" |\t= ");

		for (j = 0; j < dim; j++)
			printf("\t | %.1f", l[i][j]);

		printf(" | ");

		for (j = 0; j < dim; j++)
			printf("\t | %.1f", u[i][j]);

		printf(" | ");

		printf("\n\n");
	}
}

void matrix_permute_l(double **p, double **l, int dim) {
	if (!p || !l) {
		//printf("\n\nError: Matriz nula\n\n");

		return ;
	}

	int i;

	for (i = 0; i < dim; i++)
		l[i][i] = 0;

	double **res = matrix_zero_define(dim);

	matrix_dot(p, l, res, dim);

	matrix_copy(res, l, dim);

	for (i = 0; i < dim; i++)
		l[i][i] = 1;

	matrix_delete(res, dim);
}

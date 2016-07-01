#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

int** matrix_define(int dim, bool init);

void matrix_show(int **m, int dim);

int** matrix_delete(int **m, int dim);

void matrix_mult(int **a, int **b, int **res, int dim);

#endif

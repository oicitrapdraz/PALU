#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

/* Operaciones con matrices de dimension dim x dim */

// Crea una matriz identidad y la retorna
double** matrix_identity_define(int dim);

// Crea una matriz con todas sus entradas iguales a 0 y la retorna
double** matrix_zero_define(int dim);

// Crea una matriz random (con entradas entre 0 y 9) y la retorna
double** matrix_random_define(int dim);

// Muestra la matriz m
void matrix_show(double **m, int dim);

// Libera la memoria de la matriz m
double** matrix_delete(double **m, int dim);

// Calcula la multiplicacion de matrices a x b y guarda el resultado en res
void matrix_dot(double **a, double **b, double **res, int dim);

// Crea la matriz de p (de permutation) considerando la columna col (para dejar el maximo en a[col][col]) y la retorna
double** matrix_p(double **a, int col, int dim);

// Crea la matriz de l (de lower triangular) considerando la columna col y la retorna
double** matrix_l(double **a, int col, int dim);

// Calcula y realiza las operaciones fila para dejar todas las entradas debajo de a[col][col] igual a 0
void matrix_row_operation(double **a, int col, int dim);

// Verifica si es necesario hacer alguna permutacion
bool matrix_p_needed(double **a, int col, int dim);

#endif

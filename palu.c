#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "matrix.h"

int main(int argc, char *argv[]) {
	if ((argc > 2) || (argc < 2))
		return 0;

	srand(time(NULL));

	int i = 0, j = 0, k = 0, acumulator = 0, n = atoi(argv[1]);

	double **a = NULL;
	double **b = NULL;
	double **c = NULL;

	a = matrix_random_define(n);
	b = matrix_random_define(n);
	c = matrix_zero_define(n);

	printf("\nMatriz A:\n\n");
	matrix_show(a, n);

	printf("Matriz B:\n\n");
	matrix_show(b, n);

	matrix_dot(a, b, c, n);

	printf("Resultado:\n\n");
	matrix_show(c, n);

	a = matrix_delete(a, n);
	b = matrix_delete(b, n);
	c = matrix_delete(c, n);

	return 0;
}

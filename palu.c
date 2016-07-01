#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "matrix.h"

int main(int argc, char *argv[]) {
	int i = 0, j = 0, k = 0, acumulator = 0;

	if ((argc > 2) || (argc < 2))
		return 0;

	srand(time(NULL));

	int n = atoi(argv[1]);

	int **a = NULL;
	int **b = NULL;
	int **c = NULL;

	a = matrix_define(n, true);
	b = matrix_define(n, true);
	c = matrix_define(n, false);

	printf("\nMatriz A:\n\n");
	matrix_show(a, n);

	printf("\nMatriz B:\n\n");
	matrix_show(b, n);

	matrix_mult(a, b, c, n);

	printf("Resultado:\n\n");
	matrix_show(c, n);

	a = matrix_delete(a, n);
	b = matrix_delete(b, n);
	c = matrix_delete(c, n);

	return 0;
}

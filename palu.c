#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>

#include "matrix.h"

int n;

void palu(int n) {
	int i = 0, j = 0, k = 0, acumulator = 0;

	double **a = NULL;
	double **u = NULL;
	double **u_res = NULL;
	double **p = NULL;
	double **p_tmp = NULL;
	double **p_res = NULL;
	double **l = NULL;
	double **l_tmp = NULL;
	double **l_res = NULL;

	// Creamos las matrices a (con valores alreatorios), p y l (matrices identidad)
	a = matrix_random_define(n);
	p = matrix_identity_define(n);
	l = matrix_identity_define(n);

	// Creamos la matriz u que sera una copia de la matriz a
	u = matrix_zero_define(n);
	matrix_copy(a, u, n);

	// Recorremos las columnas de A
	for (i = 0; i < n - 1; i++) {
		if (matrix_p_needed(u, i, n)) {
			// Creamos la matriz p en p_tmp
			p_tmp = matrix_p(u, i, n);

			// Para permutar la matriz l (solo las entradas debajo de la diagonal)
			matrix_permute_l(p_tmp, l, n);

			// Actualizamos u
			u_res = matrix_zero_define(n);
			matrix_dot(p_tmp, u, u_res, n);
			matrix_copy(u_res, u, n);
			u_res = matrix_delete(u_res, n);

			// Actualizamos p
			p_res = matrix_zero_define(n);
			matrix_dot(p_tmp, p, p_res, n);
			matrix_copy(p_res, p, n);

			p_tmp = matrix_delete(p_tmp, n);
			p_res = matrix_delete(p_res, n);
		}

		// Creamos la matriz l en l_tmp
		l_tmp = matrix_l(u, i, n);

		// Aplico operaciones columnas a la matriz
		matrix_row_operation(u, i, n);

		// Actualizamos l
		l_res = matrix_zero_define(n);

		matrix_dot(l, l_tmp, l_res, n);

		matrix_copy(l_res, l, n);

		l_tmp = matrix_delete(l_tmp, n);
		l_res = matrix_delete(l_res, n);
	}

	a = matrix_delete(a, n);
	u = matrix_delete(u, n);
	p = matrix_delete(p, n);
	l = matrix_delete(l, n);
}

void* thread(void *ptr) {
	int i;

	for (i = 0; i < *(int *)ptr; i++)
		palu(n);
}

int main(int argc, char *argv[]) {
	if ((argc > 4) || (argc < 4))
		return 0;

	srand(time(NULL));

	int i, times = atoi(argv[2]), threads = atoi(argv[3]), *times_per_thread;

	pthread_t *threads_tab;
	threads_tab = malloc(threads * sizeof(pthread_t));

	n = atoi(argv[1]);

	times_per_thread = malloc(sizeof(int));

	*times_per_thread = times / threads;

	for (i = 0; i < threads; i++)
		pthread_create(&threads_tab[i], NULL, thread, times_per_thread);

	for(i = 0; i < threads; i++)
		pthread_join(threads_tab[i], NULL);

	return 0;
}

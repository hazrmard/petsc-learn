// defines utility functions to be used by ex*.c source files

#include <stdio.h>
#include <stdlib.h>

int read_matrix(char fname[], int rows, int columns, double ***matrix) {
	FILE *f;
	f = fopen(fname, "r");
	int i,j;
	for (j=0; j<rows; j++) {
		for (i=0; i<columns; i++) {
			fscanf(f, "%lf", &(*matrix)[j][i]);
			//printf("%.1f ", (*matrix)[j][i]);
		}
		//printf("\n");
	}
	fclose(f);
	return 0;
}

int read_vector(char fname[], int elements, double **vector) {
	return read_matrix(fname, 1, elements, &vector);
}

int gen_mat(int rows, int columns, unsigned int seed, char *fname) {
	srand(seed);
	FILE *f;
	f = fopen(fname, "w");
	int i,j;
	for (j=0; j<rows; j++) {
		for (i=0; i<columns; i++) {
			fprintf(f, "%lf ", (double) rand());
		}
		fprintf(f, "\n");
	}
	fclose(f);
	return 0;
}

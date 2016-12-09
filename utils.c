// defines utility functions to be used by ex*.c source files

#include <stdio.h>

int read_matrix(char fname[], int rows, int columns, double ***matrix) {
	FILE *f;
	f = fopen(fname, "r");
	int i,j;
	for (j=0; j<rows; j++) {
		for (i=0; i<columns; i++) {
			fscanf(f, "%lf", &(*matrix)[j][i]);
			//printf("%.1f ", (*matrix)[j][i]);
		}
		printf("\n");
	}
	fclose(f);
}

int read_vector(char fname[], int elements, double **vector) {
	return read_matrix(fname, 1, elements, &vector);
}

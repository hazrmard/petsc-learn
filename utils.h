#ifndef UTILS_H
#define UTILS_H

int read_matrix(char fname[], int rows, int columns, double ***matrix);
int read_vector(char fname[], int elements, double **vector);
int gen_mat(int rows, int columns, unsigned int seed, char *fname);

#endif

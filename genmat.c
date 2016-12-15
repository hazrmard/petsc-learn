// generates a random square matrix to file
// Usage:
// genmat.out OUTFILE ROWS COLUMNS
//
// a vector is a single row (not column)

# include <stdlib.h>
# include <utils.h>

int main(int argc, char **argv) {
	
	char *fname = argv[1];
	int rows = atoi(argv[2]);
	int columns = atoi(argv[3]);
	unsigned int seed = (unsigned int) atoi(argv[3]);
	gen_mat(rows, columns, seed, fname);
	return 0;
}

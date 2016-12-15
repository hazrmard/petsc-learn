// This program solves a system of linear equations of the form:
//	A . x = b
// Where A is the coefficient matrix, and x is the solution.
// x and b are vectors of the same shape.
// i.e. if A has shape m x n, then b and x are of shape: n x 1

# include <petsc.h>
# include <utils.h>
# include <stdio.h>
# include <stdlib.h>
//# define DIM 3

int main(int argc, char** argv) {
	
	Vec x, b;
	Mat A;
	KSP ksp;
	double **matrix;
	double *results;
	char *fmat = argv[1];
	char *fvec = argv[2];
	int DIM = atoi(argv[3]);
	int indices[DIM];

	// allocating space for coefficient and result matrix read from file
	results = malloc(sizeof(double) * DIM);
	matrix = malloc(sizeof(double *) * DIM);
	int i;
	for (i=0; i<DIM; i++) {
		indices[i] = i;
		matrix[i] = malloc(sizeof(double) * DIM);
	}
	
	// initialize PETSc
	PetscInitialize(&argc, &argv, NULL, "Solve a linear system of equations.");
	
	// create result vector b
	read_vector(fvec, DIM, &results);
	VecCreate(PETSC_COMM_WORLD, &b);
	VecSetSizes(b, PETSC_DECIDE, DIM);
	VecSetFromOptions(b);
	VecSetValues(b, DIM, indices, results, INSERT_VALUES);
	VecAssemblyBegin(b);
	VecAssemblyEnd(b);
	printf("\n");

	//create coefficient matrix A
	read_matrix(fmat, DIM, DIM, &matrix);
	MatCreate(PETSC_COMM_WORLD, &A);
	MatSetSizes(A, PETSC_DECIDE, PETSC_DECIDE, DIM, DIM);
	MatSetFromOptions(A);
	MatSetUp(A);
	for (i=0; i<DIM; i++) {
		MatSetValues(A, 1, &i, DIM, indices, matrix[i], INSERT_VALUES);
	}
	MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);
	MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);
	
	// create solver and solve
	KSPCreate(PETSC_COMM_WORLD, &ksp);
	KSPSetOperators(ksp, A, A);
	KSPSetFromOptions(ksp);
	VecDuplicate(b, &x);
	KSPSolve(ksp, b, x);
	//VecView(x, PETSC_VIEWER_STDOUT_WORLD);

	// free up memory
	for (i=0; i<DIM; i++) {
		free(matrix[i]);
	}
	free(matrix);
	free(results);
	KSPDestroy(&ksp);
	VecDestroy(&b);
	VecDestroy(&x);
	MatDestroy(&A);
	PetscFinalize();
	return 0;
}

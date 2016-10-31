# include <petsc.h>
# include <stdio.h>

int main(int argc, char** argv) {
	
	int rank;		// the process number
	PetscErrorCode perr;	// error code returned by all PETSc operations
	
	// initializing library (always happens)
	PetscInitialize(&argc, &argv, NULL, "Hello World!");

	// getting process number, and error if any
	perr = MPI_Comm_rank(PETSC_COMM_WORLD, &rank); CHKERRQ(perr);

	// printing Hello World from each process along with the proces number
	printf("Hello world from process: %d\n", rank);

	// closing library (always happens)
	PetscFinalize();
	
	// exiting main() function
	return 0;
}

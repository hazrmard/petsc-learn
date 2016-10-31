// Calculates sin(x) for an argument x.
// Usage:
//	ex2.out NUMBER_IN_DEGREES
//
// Distributes calculation of various terms of expansion of sin(x)
// over multiple processes. Then sums the terms before printing them.

# include <petsc.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define PI acos(-1.0)	// define a value for pi (in case math.h doesn't have it)

long int factorial(int);


int main(int argc, char** argv) {
	
	if (argc !=2) {
		printf("Enter argument of sin when running:\n\tex2.out NUMBER\n");
		exit(1);
	}

	double x = atof(argv[1]);	// convert argument to double
	int rank;			// the process number
	PetscErrorCode perr;		// error code returned by all PETSc operations
	double sinx;			// contains final sin(x) result
	double nth;			// nth term in sin(x) expansion
	
	// initializing library (always happens)
	PetscInitialize(&argc, &argv, NULL, "Hello World!");

	// getting process number, and error if any
	perr = MPI_Comm_rank(PETSC_COMM_WORLD, &rank); CHKERRQ(perr);

	// computing nth term of sin() where n == rank
	x = fmod((x * PI / 180L), 2*PI);
	nth = pow(-1L, (double) rank) * pow(x, (double) 2*rank + 1L) / factorial(2*rank+1);	

	// sum all terms and return to root process (rank==0)
	perr = MPI_Reduce(&nth, &sinx, 1, MPI_DOUBLE, MPI_SUM, 0, PETSC_COMM_WORLD); CHKERRQ(perr);

	// print result if root node
	if (rank==0) {
		printf("Sin(%.3f) = %.6f\n", x, sinx);
	}
	
	// closing library (always happens)
	PetscFinalize();
	
	// exiting main() function
	return 0;
}


long int factorial(int n) {
	
	int fac = 1;
	int i;
	for (i=1; i<=n; i++) {
		fac = fac * i;
	}
	return fac;
}

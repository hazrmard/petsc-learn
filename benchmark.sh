#! /bin/bash
# tests performance of traditional Laplace Expansion (tinverse.c) and LU Factorization 
# (pinverse.c) approaches to solving linear systems of equations.

function benchmark() {
	a=$(echo $( TIMEFORMAT="%4U + %4S"; { time  ./pinverse.out rmat$1.dat rvec$1.dat $1; } 2>&1) "*1000" | bc -l)
	b=$(echo $( TIMEFORMAT="%4U + %4S"; { time  ./tinverse.out rmat$1.dat rvec$1.dat $1; } 2>&1) "*1000" | bc -l)
	echo $1, $a, $b
}

function rparams() {
	./genmat.out rmat$1.dat $1 $1
	./genmat.out rvec$1.dat 1 $1
}

make tinverse
make pinverse
make genmat

clear

rparams 2
rparams 3
rparams 4
rparams 5
rparams 6
rparams 7
rparams 8
rparams 9
rparams 10

benchmark 2 > results.csv
benchmark 3 >> results.csv
benchmark 4 >> results.csv
benchmark 5 >> results.csv
benchmark 6 >> results.csv
benchmark 7 >> results.csv
benchmark 8 >> results.csv
benchmark 9 >> results.csv
benchmark 10 >> results.csv

rm rmat*.dat
rm rvec*.dat



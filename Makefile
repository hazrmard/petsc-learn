# Usage:
#	make ex<NUMBER>

.PHONY:all

include ${PETSC_DIR}/lib/petsc/conf/variables
include ${PETSC_DIR}/lib/petsc/conf/rules

CC = gcc
CFLAGS = -I .
SRC_FILES = ${wildcard ex*.c}
SRC = ${SRC_FILES:.c=}

ex%: ex%.o chkopts utils
	-$(CC) $(CFLAGS) -o $@.out $< utils.o ${PETSC_LIB}
	rm $<

pinverse: pinverse.o chkopts utils
	-$(CC) $(CFLAGS) -o $@.out $< utils.o ${PETSC_LIB}
	rm $<

tinverse: utils
	-$(CC) $(CFLAGS) -o tinverse.out tinverse.c utils.o -lm

utils: 
	-$(CC) $(CFLAGS) -c -o utils.o utils.c

genmat: utils
	-$(CC) $(CFLAGS) -o genmat.out genmat.c utils.o

all: $(SRC) genmat


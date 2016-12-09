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

utils: 
	-$(CC) $(CFLAGS) -c -o utils.o utils.c

all: $(SRC)


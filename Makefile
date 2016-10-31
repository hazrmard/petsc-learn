# Usage:
#	make ex<NUMBER>

.PHONY:all

include ${PETSC_DIR}/lib/petsc/conf/variables
include ${PETSC_DIR}/lib/petsc/conf/rules

CC = gcc
SRC_FILES = ${wildcard ex*.c}
SRC = ${SRC_FILES:.c=}

ex%: ex%.o chkopts
	-$(CC) -o $@.out $< ${PETSC_LIB}
	rm $<

all: $(SRC)


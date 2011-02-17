# Makefile

GCC = gcc
SRC = meanfilter.c
OUT = meanfilter

all:
	${GCC} -O0 -g ${SRC} -o ${OUT}

clean:
	rm ${OUT}

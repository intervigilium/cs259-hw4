# Makefile

GCC= gcc
SRC= meanfilter.c
OUT= meanfilter

LDFLAGS= -lm

all:
	${GCC} -O0 -g ${SRC} -o ${OUT} ${LDFLAGS}

clean:
	rm ${OUT}

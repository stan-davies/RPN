CC = gcc

FILES = main.c ouop.c

OUT = -o prog

all : compile
compile:
	@${CC} ${FILES} ${OUT}

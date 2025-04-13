CC = gcc

FILES = main.c soup/soup-util.c soup/soup-conv.c soup/soup-eval.c stew/stew-conv.c

OUT = -o prog

all : compile
compile:
	@${CC} ${FILES} ${OUT}

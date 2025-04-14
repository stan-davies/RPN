CC = gcc

FILES = main.c soup/soup-util.c soup/soup-conv.c soup/soup-eval.c stew/stew-conv.c util/util.c

INC = -I .

OUT = -o prog

all : compile
compile:
	@${CC} ${FILES} ${INC} ${OUT}

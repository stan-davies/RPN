#ifndef SOUP_UTIL_H
#define SOUP_UTIL_H

#include <stdlib.h>
#include <stdio.h>

#define OP_PERROR        0
#define OP_PFINE         1
#define OP_NULL          (void *)0
#define OP_STACK_SIZE    32

#define OP_PLUS          43 
#define OP_MINUS         45
#define OP_TIMES         42
#define OP_DIVIDE        47
#define OP_LBRACK        40
#define OP_RBRACK        41

#define OP_ZERO          48
#define OP_NINE          57

#define OP_PLUS_P        1
#define OP_MINUS_P       1
#define OP_TIMES_P       2
#define OP_DIVIDE_P      2
#define OP_LBRACK_P      3
#define OP_RBRACK_P      4

/*
 *   precedence
 *
 *   input  : An operator ('+', '-', '*', '/', '(', ')').
 *   output : Precedence of the given operator.
 */
int op_P(char oper);

/*
 *   move stacks 
 *   input  : Pointer to source stack. Pointer to destination stack. Index of
 *            write head in source stack. Index of write head in destination 
 *            stack. Exception character.
 *   output : F/E
 *
 *   notes  : Moves the top element of the source to the top of the destination.
 *            Errors if the source is empty or the destination is full.
 */
int op_moves(char **s1, char **s2, int *s1_at, int *s2_at);

/*
 *   push
 *
 *   input  : Pointer to stack. Pointer to position of write head on stack.
 *            Item to add to stack.
 *   output : F/E
 */
int op_pushc(char **stack, int *at, char item);

/*
 *   pop
 *
 *   input  : Stack. Pointer to position of write head on stack. Pointer to
 *            item that will be popped from stack.
 *   output : F/E
 */
int op_popc(char *stack, int *at, char *item);

int op_pushi(int **stack, int *at, int item);

int op_popi(int *stack, int *at, int *item);

#endif

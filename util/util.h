#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdio.h>

#define NU_PERROR        0
#define NU_PFINE         1
#define NU_NULL          (void *)0
#define NU_STACK_SIZE    64

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
int nu_moves(char **s1, char **s2, int *s1_at, int *s2_at);

/*
 *   push
 *
 *   input  : Pointer to stack. Pointer to position of write head on stack.
 *            Item to add to stack.
 *   output : F/E
 */
int nu_pushc(char **stack, int *at, char item);

/*
 *   pop
 *
 *   input  : Stack. Pointer to position of write head on stack. Pointer to
 *            item that will be popped from stack.
 *   output : F/E
 */
int nu_popc(char *stack, int *at, char *item);

int nu_pushi(int **stack, int *at, int item);

int nu_popi(int *stack, int *at, int *item);

#endif

#ifndef OUOP_H
#define OUOP_H

#include <stdlib.h>
#include <stdio.h>

#define OP_PERROR   0 
#define OP_PFINE    1
#define OP_NULL    (void *)0
#define OP_STACK_SIZE 32

#define OP_PLUS     43 
#define OP_MINUS    45
#define OP_TIMES    42
#define OP_DIVIDE   47
#define OP_LBRACK   40
#define OP_RBRACK   41

#define OP_ZERO     48
#define OP_NINE     57

#define OP_PLUS_P   1
#define OP_MINUS_P  1
#define OP_TIMES_P  2
#define OP_DIVIDE_P 2
#define OP_LBRACK_P 3
#define OP_RBRACK_P 4

/*
 *   process 
 *   
 *   input  : String containing infix formatted expression. Pointer to string
 *            containing same expression but in postfix format (reverse Polish
 *            notation. Length of input string. Pointer to length of output
 *            string.
 *   output : F/E
 */
int op_process(char *in, char **out, int in_at, int *out_at);

/*
 *   precedence
 *
 *   input  : An operator ('+', '-', '*', '/', '(', ')').
 *   output : Precedence of the given operator.
 */
int op_P(char oper);

/*
 *   close brackets
 *
 *   input  : Pointer to output string. Pointer to operator stack. Index of
 *            write head in output string. Index of write head in operator
 *            stack.
 *   output : F/E
 *   
 *   notes  : Moves all elements from operator stack over to the output string
 *            as far back as the first left bracket found.
 */
int op_closeb(char **out, char **ops, int *out_at, int *ops_at);

/*
 *   add operator
 *
 *   input  : Pointer to output string. Pointer to operator stack. Index of
 *            write head in output string. Index of write head in operator
 *            stack. Operator to add to the operator stack.
 *   output : F/E
 *
 *   notes  : Adds new operator to operator stack, first moving any operators
 *            of greater than or equivalent precedence that are immediately
 *            below it onto the output string.
 */
int op_addop(char **out, char **ops, int *out_at, int *ops_at, char add);

/*
 *   clear out
 *   input  : Pointer to output string. Pointer to operator stack. Index of
 *            write head in output string. Index of write head in operator
 *            stack.
 *   output : F/E
 *
 *   notes  : Empties operator stack, moving all items in it to the output
 *            string.
 */
int op_clearout(char **out, char **ops, int *out_at, int *ops_at);

/*
 *   move stacks 
 *   input  : Pointer to source stack. Pointer to destination stack. Index of
 *            write head in source stack. Index of write head in destination 
 *            stack.
 *   output : F/E
 *
 *   notes  : Empties operator stack, moving all items in it to the output
 *            string.
 */

int op_moves(char **s1, char **s2, int *s1_at, int *s2_at);

/*
 *   push
 *
 *   input  : Pointer to stack. Pointer to position of write head on stack.
 *            Operator to add to stack.
 *   output : F/E
 */
int op_push(char **stack, int *at, char oper);

/*
 *   pop
 *
 *   input  : Stack. Pointer to position of write head on stack. Pointer to
 *            operator that will be popped from stack.
 *   output : F/E
 */
int op_pop(char *stack, int *at, char *oper);

#endif

#ifndef OUOP_H
#define OUOP_H

#include "util/util.h"
#include "soup-util.h"

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

#endif

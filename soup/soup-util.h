#ifndef SOUP_UTIL_H
#define SOUP_UTIL_H

#include "util/util.h"

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

#endif

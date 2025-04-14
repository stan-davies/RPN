#ifndef SOUP_EVAL_H
#define SOUP_EVAL_H

#include "util/util.h"
#include "soup-util.h"

int op_evaluate(char *exp, int exp_at, int *result);

int op_condense(int **nums, int *nums_at, char oper);

int op_operate(int a, char oper, int b, int *res);

int op_converti(char numc, int *numi);

#endif

#ifndef STEW_UTIL_H
#define STEW_UTIL_H

#include <stdlib.h>
#include <stdio.h>

#include "util/util.h"

#define ST_CHUNK_SIZE     64
#define ST_EXPR_SIZE      128

#define ST_PLUS           43
#define ST_MINUS          45 
#define ST_TIMES          42
#define ST_DIVIDE         47
#define ST_LBRACK         40
#define ST_RBRACK         41

#define ST_PMINOR         1
#define ST_PMAJOR         2
#define ST_PUNKNOWN       -1

int st_process(char *exp, int exp_s, int exp_e, char **out, int *out_at);

int st_LSOP(char *exp, int exp_s, int exp_e);

int st_P(char oper);

#endif

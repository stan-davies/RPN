#ifndef STEW_UTIL_H
#define STEW_UTIL_H

#include <stdlib.h>
#include <stdio.h>

#define ST_CHUNK_SIZE     32
#define ST_TRUE           1
#define ST_FALSE          0
#define ST_NULL           (void *)0

#define ST_PLUS           43
#define ST_MINUS          45 
#define ST_TIMES          42
#define ST_DIVIDE         47
#define ST_LBRACK         40
#define ST_RBRACK         41

#define ST_PMINOR         1
#define ST_PMAJOR         2
#define ST_PUNKNOWN       -1

struct st_node {
        int             leaf;
        char            chr;
        struct st_node *left;
        struct st_node *rght;
};

void st_process(char *in, char **out, int in_at, int *out_at);

struct st_node *st_maken(char *exp, int exp_len);

int st_LSOP(char *exp_chunk, int len);

int st_P(char oper);

void st_porder(struct st_node n, char **out, int *out_at);

#endif

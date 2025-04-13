#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "soup/soup-conv.h"
#include "soup/soup-eval.h"

#include "stew/stew-conv.h"

#define EXP_LENGTH 64

int main() {
        char *inf_expr = calloc(EXP_LENGTH, sizeof(char));
        int inf_at = 9; // as so *after* the following line
        memcpy(inf_expr, "3+(2*4)-5", inf_at + 1);

        char *pof_expr = calloc(EXP_LENGTH, sizeof(char));
        int pof_at = 0;

        if (OP_PERROR == op_process(inf_expr, &pof_expr, inf_at, &pof_at)) {
                printf("Something has gone awry!\n");
                return 0;
        }

        printf("%s -> %s\n", inf_expr, pof_expr);

        int result;
        if (OP_PERROR == op_evaluate(pof_expr, pof_at, &result)) {
                printf("Could not evaluate =(\n");
                return 0;
        }

        printf(" = %d\n", result);


        char *pof_expr_t = calloc(EXP_LENGTH, sizeof(char));
        int pof_at_t = 0;

        st_process(inf_expr, &pof_expr_t, inf_at, &pof_at_t);

        printf("\n---\ntree gave: %s\n", pof_expr_t);

        return 0;
}

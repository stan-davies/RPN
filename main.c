#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ouop.h"

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

        return 0;
}

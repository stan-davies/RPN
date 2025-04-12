#include "soup-eval.h"

int op_evaluate(char *exp, int exp_at, int *result) {
        char curc;
        int  prec;
        int  curi;
        int *nums = calloc(OP_STACK_SIZE, sizeof(char));
        int  nums_at = 0;
        for (int i = 0; i < exp_at; ++i) {
                curc = exp[i];
                prec = op_P(curc);
                if (OP_PERROR != prec) {
                        if (OP_PERROR == op_condense(&nums, &nums_at, curc)) {
                                goto errf_nums;
                        }
                        continue;
                }

                if (OP_PERROR == op_converti(curc, &curi)) {
                        goto errf_nums;
                }

                if (OP_PERROR == op_pushi(&nums, &nums_at, curi)) {
                        goto errf_nums;
                }
        }

        if (OP_PERROR == op_popi(nums, &nums_at, result)) {
                goto errf_nums;
        }

fine:
        free(nums);
        nums = OP_NULL;
        return OP_PFINE;

errf_nums:
        free(nums);
        nums = OP_NULL;
        return OP_PERROR;
}

int op_condense(int **nums, int *nums_at, char oper) {
        int a;
        int b;
        int r;
        if (OP_PERROR == op_popi(*nums, nums_at, &a)) {
                return OP_PERROR;
        }
        if (OP_PERROR == op_popi(*nums, nums_at, &b)) {
                return OP_PERROR;
        }
        if (OP_PERROR == op_operate(b, oper, a, &r)) {
                return OP_PERROR;
        }
        if (OP_PERROR == op_pushi(nums, nums_at, r)) {
                return OP_PERROR;
        }
        return OP_PFINE;
}

int op_operate(int a, char oper, int b, int *res) {
        switch (oper) {
        case OP_PLUS:
                *res = a + b;
                break;
        case OP_MINUS:
                *res = a - b;
                break;
        case OP_TIMES:
                *res = a * b;
                break;
        case OP_DIVIDE:
                *res = a / b;
                break;
        default:
                return OP_PERROR;
        }

        return OP_PFINE;
}

int op_converti(char numc, int *numi) {
        if (numc < OP_ZERO || numc > OP_NINE) {
                return OP_PERROR;
        }

        *numi = numc - OP_ZERO;
        return OP_PFINE;
}



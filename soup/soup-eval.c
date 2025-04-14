#include "soup-eval.h"

int op_evaluate(char *exp, int exp_at, int *result) {
        char curc;
        int  prec;
        int  curi;
        int *nums = calloc(NU_STACK_SIZE, sizeof(char));
        int  nums_at = 0;
        for (int i = 0; i < exp_at; ++i) {
                curc = exp[i];
                prec = op_P(curc);
                if (NU_PERROR != prec) {
                        if (NU_PERROR == op_condense(&nums, &nums_at, curc)) {
                                goto errf_nums;
                        }
                        continue;
                }

                if (NU_PERROR == op_converti(curc, &curi)) {
                        goto errf_nums;
                }

                if (NU_PERROR == nu_pushi(&nums, &nums_at, curi)) {
                        goto errf_nums;
                }
        }

        if (NU_PERROR == nu_popi(nums, &nums_at, result)) {
                goto errf_nums;
        }

fine:
        free(nums);
        nums = NU_NULL;
        return NU_PFINE;

errf_nums:
        free(nums);
        nums = NU_NULL;
        return NU_PERROR;
}

int op_condense(int **nums, int *nums_at, char oper) {
        int a;
        int b;
        int r;
        if (NU_PERROR == nu_popi(*nums, nums_at, &a)) {
                return NU_PERROR;
        }
        if (NU_PERROR == nu_popi(*nums, nums_at, &b)) {
                return NU_PERROR;
        }
        if (NU_PERROR == op_operate(b, oper, a, &r)) {
                return NU_PERROR;
        }
        if (NU_PERROR == nu_pushi(nums, nums_at, r)) {
                return NU_PERROR;
        }
        return NU_PFINE;
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
                return NU_PERROR;
        }

        return NU_PFINE;
}

int op_converti(char numc, int *numi) {
        if (numc < OP_ZERO || numc > OP_NINE) {
                return NU_PERROR;
        }

        *numi = numc - OP_ZERO;
        return NU_PFINE;
}



#include "soup-util.h"

int op_P(char oper) {
        switch (oper) {
        case OP_PLUS:
                return OP_PLUS_P;
        case OP_MINUS:
                return OP_MINUS_P;
        case OP_TIMES:
                return OP_TIMES_P;
        case OP_DIVIDE:
                return OP_DIVIDE_P;
        case OP_LBRACK:
                return OP_LBRACK_P;
        case OP_RBRACK:
                return OP_RBRACK_P;
        default:
                return OP_PERROR;
        }
}

int op_moves(char **s1, char **s2, int *s1_at, int *s2_at) {
        char move;
        if (OP_PERROR == op_popc(*s1, s1_at, &move)) {
                return OP_PERROR;
        }
        if (OP_PERROR == op_pushc(s2, s2_at, move)) {
                return OP_PERROR;
        }
        return OP_PFINE;
}

int op_pushc(char **stack, int *at, char item) {
        if (*at < 0 || *at >= OP_STACK_SIZE) {
                return OP_PERROR;
        }

        (*stack)[*at] = item;
        (*at)++;
        return OP_PFINE;
}

int op_popc(char *stack, int *at, char *item) {
        if (*at <= 0 || *at > OP_STACK_SIZE) {
                return OP_PERROR;
        }
        
        (*at)--;
        *item = stack[*at];
        return OP_PFINE;
}

int op_pushi(int **stack, int *at, int item) {
        if (*at < 0 || *at >= OP_STACK_SIZE) {
                return OP_PERROR;
        }

        (*stack)[*at] = item;
        (*at)++;
        return OP_PFINE;
}

int op_popi(int *stack, int *at, int *item) {
        if (*at <= 0 || *at > OP_STACK_SIZE) {
                return OP_PERROR;
        }

        (*at)--;
        *item = stack[*at];
        return OP_PFINE;
}

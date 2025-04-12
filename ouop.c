#include "ouop.h"

int op_process(char *in, char **out, int in_at, int *out_at) {
        char c;
        char *ops = calloc(OP_STACK_SIZE, sizeof(char));
        int  ops_at = 0;
        int  p;
        int  suc;
        for (int i = 0; i < in_at; ++i) {
                c = in[i];
                if (c > OP_ZERO && c < OP_NINE) {
                        if (OP_PERROR == op_push(out, out_at, c)) {
                                goto err;
                        }
                        continue;
                }

                p = op_P(c);
                switch (p) {
                case OP_PERROR:
                        goto err;
                case OP_LBRACK_P:
                        if (OP_PERROR == op_push(&ops, &ops_at, c)) {
                                goto err;
                        }
                        break;
                case OP_RBRACK_P:
                        suc = op_closeb(out, &ops, out_at, &ops_at);
                        if (OP_PERROR == suc) {
                                goto err;
                        }
                        break;
                default:
                        suc = op_addop(out, &ops, out_at, &ops_at, c);
                        if (OP_PERROR == suc) {
                                goto err;
                        }
                        break;
                }
        }

        if (OP_PERROR == op_clearout(out, &ops, out_at, &ops_at)) {
                goto err;
        }

        return OP_PFINE;

        err:
        free(ops);
        ops = OP_NULL;
        return OP_PERROR;
}

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

int op_closeb(char **out, char **ops, int *out_at, int *ops_at) {
        char c;

        for (;;) {
                // moves with exception?
                if (OP_PERROR == op_pop(*ops, ops_at, &c)) {
                        break;
                }
                if (OP_LBRACK == c) {
                        break;
                }
                if (OP_PERROR == op_push(out, out_at, c)) {
                        return OP_PERROR;
                }
       }

        return OP_PFINE;
}

int op_addop(char **out, char **ops, int *out_at, int *ops_at, char add) {
        int pa = op_P(add);
        char c;
        while (*ops_at > 0) {
                c = (*ops)[(*ops_at) - 1];
                if (OP_LBRACK == c || op_P(c) >= pa) {
                        break;
                }
                if (OP_PERROR == op_moves(ops, out, ops_at, out_at)) {
                        return OP_PERROR;
                }
        }

        if (OP_PERROR == op_push(ops, ops_at, add)) {
                return OP_PERROR;
        }
        return OP_PFINE;
}

int op_clearout(char **out, char **ops, int *out_at, int *ops_at) {
        char move;
        while (*ops_at > 0) {
                if (OP_PERROR == op_moves(ops, out, ops_at, out_at)) {
                        return OP_PERROR;
                }
        }
        return OP_PFINE;
}

int op_moves(char **s1, char **s2, int *s1_at, int *s2_at) {
        char move;
        if (OP_PERROR == op_pop(*s1, s1_at, &move)) {
                return OP_PERROR;
        }
        if (OP_PERROR == op_push(s2, s2_at, move)) {
                return OP_PERROR;
        }
        return OP_PFINE;
}

int op_push(char **stack, int *at, char oper) {
        if (*at < 0 || *at >= OP_STACK_SIZE) {
                return OP_PERROR;
        }

        (*stack)[*at] = oper;
        (*at)++;
        return OP_PFINE;
}

int op_pop(char *stack, int *at, char *oper) {
        if (*at <= 0) {
                return OP_PERROR;
        }

        (*at)--;
        *oper = stack[*at];
        return OP_PFINE;
}

#include "soup-conv.h"

int op_process(char *in, char **out, int in_at, int *out_at) {
        char c;
        char *ops = calloc(OP_STACK_SIZE, sizeof(char));
        int  ops_at = 0;
        int  p;
        int  suc;
        for (int i = 0; i < in_at; ++i) {
                c = in[i];
                if (c > OP_ZERO && c < OP_NINE) {
                        if (OP_PERROR == op_pushc(out, out_at, c)) {
                                goto errf_ops;
                        }
                        continue;
                }

                p = op_P(c);
                switch (p) {
                case OP_PERROR:
                        goto errf_ops;
                case OP_LBRACK_P:
                        if (OP_PERROR == op_pushc(&ops, &ops_at, c)) {
                                goto errf_ops;
                        }
                        break;
                case OP_RBRACK_P:
                        suc = op_closeb(out, &ops, out_at, &ops_at);
                        if (OP_PERROR == suc) {
                                goto errf_ops;
                        }
                        break;
                default:
                        suc = op_addop(out, &ops, out_at, &ops_at, c);
                        if (OP_PERROR == suc) {
                                goto errf_ops;
                        }
                        break;
                }
        }

        if (OP_PERROR == op_clearout(out, &ops, out_at, &ops_at)) {
                goto errf_ops;
        }

fine:
        free(ops);
        ops = OP_NULL;
        return OP_PFINE;

errf_ops:
        printf("\n");
        free(ops);
        ops = OP_NULL;
        return OP_PERROR;
}

int op_closeb(char **out, char **ops, int *out_at, int *ops_at) {
        char c;

        for (;;) {
                if (OP_PERROR == op_popc(*ops, ops_at, &c)) {
                        return OP_PERROR;
                }
                if (OP_LBRACK == c) {
                        break;
                }
                if (OP_PERROR == op_pushc(out, out_at, c)) {
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
                if (OP_LBRACK == c || op_P(c) > pa) {
                        break;
                }
                if (OP_PERROR == op_moves(ops, out, ops_at, out_at)) {
                        return OP_PERROR;
                }
        }

        if (OP_PERROR == op_pushc(ops, ops_at, add)) {
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

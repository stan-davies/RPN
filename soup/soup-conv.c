#include "soup-conv.h"

int op_process(char *in, char **out, int in_at, int *out_at) {
        char c;
        char *ops = calloc(NU_STACK_SIZE, sizeof(char));
        int  ops_at = 0;
        int  p;
        int  suc;
        for (int i = 0; i < in_at; ++i) {
                c = in[i];
                if (c > OP_ZERO && c < OP_NINE) {
                        if (NU_PERROR == nu_pushc(out, out_at, c)) {
                                goto errf_ops;
                        }
                        continue;
                }

                p = op_P(c);
                switch (p) {
                case NU_PERROR:
                        goto errf_ops;
                case OP_LBRACK_P:
                        if (NU_PERROR == nu_pushc(&ops, &ops_at, c)) {
                                goto errf_ops;
                        }
                        break;
                case OP_RBRACK_P:
                        suc = op_closeb(out, &ops, out_at, &ops_at);
                        if (NU_PERROR == suc) {
                                goto errf_ops;
                        }
                        break;
                default:
                        suc = op_addop(out, &ops, out_at, &ops_at, c);
                        if (NU_PERROR == suc) {
                                goto errf_ops;
                        }
                        break;
                }
        }

        if (NU_PERROR == op_clearout(out, &ops, out_at, &ops_at)) {
                goto errf_ops;
        }

fine:
        free(ops);
        ops = NU_NULL;
        return NU_PFINE;

errf_ops:
        printf("\n");
        free(ops);
        ops = NU_NULL;
        return NU_PERROR;
}

int op_closeb(char **out, char **ops, int *out_at, int *ops_at) {
        char c;

        for (;;) {
                if (NU_PERROR == nu_popc(*ops, ops_at, &c)) {
                        return NU_PERROR;
                }
                if (OP_LBRACK == c) {
                        break;
                }
                if (NU_PERROR == nu_pushc(out, out_at, c)) {
                        return NU_PERROR;
                }
       }

        return NU_PFINE;
}

int op_addop(char **out, char **ops, int *out_at, int *ops_at, char add) {
        int pa = op_P(add);
        char c;
        while (*ops_at > 0) {
                c = (*ops)[(*ops_at) - 1];
                if (OP_LBRACK == c || op_P(c) > pa) {
                        break;
                }
                if (NU_PERROR == nu_moves(ops, out, ops_at, out_at)) {
                        return NU_PERROR;
                }
        }

        if (NU_PERROR == nu_pushc(ops, ops_at, add)) {
                return NU_PERROR;
        }
        return NU_PFINE;
}

int op_clearout(char **out, char **ops, int *out_at, int *ops_at) {
        char move;
        while (*ops_at > 0) {
                if (NU_PERROR == nu_moves(ops, out, ops_at, out_at)) {
                        return NU_PERROR;
                }
        }
        return NU_PFINE;
}

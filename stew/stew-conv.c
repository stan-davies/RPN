#include "stew-conv.h"

void st_process(char *in, char **out, int in_at, int *out_at) {
        struct st_node *root = st_maken(in, in_at);
        st_porder(*root, out, out_at);
}

struct st_node *st_maken(char *exp, int exp_len) {
        char *left = calloc(ST_CHUNK_SIZE, sizeof(char));
        char *rght = calloc(ST_CHUNK_SIZE, sizeof(char));
        struct st_node *this = calloc(1, sizeof(struct st_node));
        this->leaf = ST_FALSE;

        int lsoi = st_LSOP(exp, exp_len);

        if (ST_PUNKNOWN == lsoi) {
                this->leaf = ST_TRUE;
                for (int i = 0; i < exp_len; ++i) {
                        if (ST_LBRACK == exp[i] || ST_RBRACK == exp[i]) {
                                continue;
                        }
                        this->chr = exp[i];
                        break;
                }
                goto finef_lr;
        }

        this->chr = exp[lsoi];

        for (int i = 0; i < exp_len; ++i) {
                if (i < lsoi) {
                        left[i] = exp[i];
                }
                if (i > lsoi) {
                        rght[i - (lsoi + 1)] = exp[i];
                }
        }

        this->left = st_maken(left, lsoi);
        this->rght = st_maken(rght, exp_len - (lsoi + 1));

finef_lr:
        free(left);
        left = ST_NULL;
        free(rght);
        rght = ST_NULL;
        return this;
}

int st_LSOP(char *exp_chunk, int len) {
        int  br_o  = 0;
        int  lsopi = ST_PUNKNOWN;
        int  l_sig = 10;
        int  sig;
        int  p;
        char c;
        for (int i = 0; i < len; ++i) {
                c = exp_chunk[i];
                if (ST_LBRACK == c) {
                        br_o += 2;
                } else if (ST_RBRACK == c) {
                        br_o -= 2;
                }

                sig = br_o + st_P(c);

                if (sig < br_o) {
                        continue;
                } else if (sig <= l_sig) {
                        lsopi = i;
                        l_sig = sig;
                }
        }
        return lsopi;
}

int st_P(char oper) {
        switch (oper) {
        case ST_PLUS:
                return ST_PMINOR;
        case ST_MINUS:
                return ST_PMINOR;
        case ST_TIMES:
                return ST_PMAJOR;
        case ST_DIVIDE:
                return ST_PMAJOR;
        default:
                return ST_PUNKNOWN;
        }
}

void st_porder(struct st_node n, char **out, int *out_at) {
        if (n.leaf) {
                (*out)[*out_at] = n.chr;
                (*out_at)++;
                return;
        }

        st_porder(*(n.left), out, out_at);
        st_porder(*(n.rght), out, out_at);

        (*out)[*out_at] = n.chr;
        (*out_at)++;
}

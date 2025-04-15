#include "stew-conv.h"

int st_process(char *exp, int exp_s, int exp_e, char **out, int *out_at) {
        int lsoi = st_LSOP(exp, exp_s, exp_e);

        if (ST_PUNKNOWN == lsoi) {
                for (int i = exp_s; i <= exp_e; ++i) {
                        if (ST_LBRACK == exp[i] || ST_RBRACK == exp[i]) {
                                continue;
                        }
                        if (NU_PERROR == nu_pushc(out, out_at, exp[i])) {
                                return NU_PERROR;
                        }
                }
                return NU_PFINE;
        }

        st_process(exp, exp_s, lsoi - 1, out, out_at);
        st_process(exp, lsoi + 1, exp_e, out, out_at);

        if (NU_PERROR == nu_pushc(out, out_at, exp[lsoi])) {
                return NU_PERROR;
        }
        return NU_PFINE;
}

int st_LSOP(char *exp, int exp_s, int exp_e) {
        int  br_o  = 0;
        int  lsopi = ST_PUNKNOWN;
        int  l_sig = 10;
        int  sig;
        char c;
        for (int i = exp_e; i >= exp_s; --i) {
                c = exp[i];
                if (ST_LBRACK == c) {
                        br_o -= 2;
                        continue;
                } else if (ST_RBRACK == c) {
                        br_o += 2;
                        continue;
                }

                sig = br_o + st_P(c);

                if (sig < br_o) {
                        continue;
                } else if (1 == sig) {
                        return i;
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

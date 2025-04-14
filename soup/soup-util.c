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
                return NU_PERROR;
        }
}

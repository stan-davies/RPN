#include "util.h"

int nu_moves(char **s1, char **s2, int *s1_at, int *s2_at) {
        char move;
        if (NU_PERROR == nu_popc(*s1, s1_at, &move)) {
                return NU_PERROR;
        }
        if (NU_PERROR == nu_pushc(s2, s2_at, move)) {
                return NU_PERROR;
        }
        return NU_PFINE;
}

int nu_pushc(char **stack, int *at, char item) {
        if (*at < 0 || *at >= NU_STACK_SIZE) {
                return NU_PERROR;
        }

        (*stack)[*at] = item;
        (*at)++;
        return NU_PFINE;
}

int nu_popc(char *stack, int *at, char *item) {
        if (*at <= 0 || *at > NU_STACK_SIZE) {
                return NU_PERROR;
        }
        
        (*at)--;
        *item = stack[*at];
        return NU_PFINE;
}

int nu_pushi(int **stack, int *at, int item) {
        if (*at < 0 || *at >= NU_STACK_SIZE) {
                return NU_PERROR;
        }

        (*stack)[*at] = item;
        (*at)++;
        return NU_PFINE;
}

int nu_popi(int *stack, int *at, int *item) {
        if (*at <= 0 || *at > NU_STACK_SIZE) {
                return NU_PERROR;
        }

        (*at)--;
        *item = stack[*at];
        return NU_PFINE;
}

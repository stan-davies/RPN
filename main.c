#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "soup/soup-conv.h"
#include "soup/soup-eval.h"

#include "stew/stew-conv.h"

#define EXP_LENGTH 64

#define EXP_TESTS 4
#define EXP_TRIAL 1000000

double benchmark2() {
        char *exp1 = calloc(EXP_LENGTH, sizeof(char));
        int   exp1_at = 23;
        memcpy(exp1, "3+(2+4)+(2*4+(3-1)*6)-5", exp1_at);

        char *exp2 = calloc(EXP_LENGTH, sizeof(char));
        int   exp2_at = 3;
        memcpy(exp2, "1+1", exp2_at);

        clock_t tic;
        clock_t toc;
        double  soup_dur;
        double  stew_dur;
        int     suc;


        char *pof = calloc(EXP_LENGTH, sizeof(char));
        int   pof_at;

        tic = clock();
        for (int i = 0; i < EXP_TRIAL; ++i) {
                pof_at = 0;
                suc = op_process(exp1, &pof, exp1_at, &pof_at);
                if (NU_PERROR == suc) {
                        printf("Something has gone awry!\n");
                }
//                printf("soup: %s -> %s\n", exp2, pof);
        }
        toc = clock();
        
        soup_dur = (double)(toc - tic) / CLOCKS_PER_SEC;
        printf("soup: %.10fs\n", soup_dur);
        
        tic = clock();
        for (int i = 0; i < EXP_TRIAL; ++i) {
                pof_at = 0;
                suc = st_process(exp1, 0, exp1_at - 1, &pof, &pof_at);
                if (NU_PERROR == suc) {
                        printf("Something has gone awry!\n");
                }
//                printf("stew: %s -> %s\n", exp2, pof);
        }
        toc = clock();

        stew_dur = (double)(toc - tic) / CLOCKS_PER_SEC;
        printf("stew: %.10fs\n", stew_dur);

        free(pof);
        return soup_dur - stew_dur;
}

double benchmark() {
        char **exps = calloc(EXP_TESTS, sizeof(char *));
        for (int i = 0; i < EXP_TESTS; ++i) {
                exps[i] = calloc(EXP_LENGTH, sizeof(char));
        }
        int *lens = calloc(EXP_TESTS, sizeof(int));

        lens[0] = 9;
        memcpy(exps[0], "3+(2*4)-5", lens[0] + 1);

        lens[1] = 8;
        memcpy(exps[1], "5*(12-4)", lens[1] + 1);

        lens[2] = 11;
        memcpy(exps[2], "7+(3*(2-6))", lens[2] + 1);

        lens[3] = 9;
        memcpy(exps[3], "5+5+5+5+5", lens[2] + 1);

        clock_t tic;
        clock_t toc;
        double  op_dur;
        double  st_dur;
        int suc;

        tic = clock();
        for (int t = 0; t < EXP_TRIAL; ++t) {
                for (int e = 0; e < EXP_TESTS; ++e) {
                        char *pof_expr = calloc(EXP_LENGTH, sizeof(char));
                        int pof_at = 0;
                        suc = op_process(exps[e], &pof_expr, lens[e], &pof_at);
                        if (NU_PERROR == suc) {
                                printf("Something has gone awry!\n");
                        }
//                        printf("soup: %s -> %s\n", exps[e], pof_expr);
                        free(pof_expr);
                }
        }
        toc = clock();
        op_dur = (double)(toc - tic) / CLOCKS_PER_SEC;
        printf("soup time spent: %fs\n", op_dur);

        tic = clock();
        for (int t = 0; t < EXP_TRIAL; ++t) {
                for (int e = 0; e < EXP_TESTS; ++e) {
                        char *pof_expr = calloc(EXP_LENGTH, sizeof(char));
                        int pof_at = 0;
                        suc = st_process(exps[e], 0, lens[e] - 1, &pof_expr, &pof_at);
                        if (NU_PERROR == suc) {
                                printf("Something has gone awry!\n");
                        }
//                        printf("stew: %s -> %s\n", exps[e], pof_expr);
                        free(pof_expr);
                }
        }
        toc = clock();
        st_dur = (double)(toc - tic) / CLOCKS_PER_SEC;
        printf("stew time spent: %fs\n", st_dur);
        return op_dur - st_dur;
}


int main() {
        double diff = 0.0;
        for (int i = 0; i < 4; ++i) {
                diff += benchmark();
        }
        diff /= 4.0;
        if (diff < 0.0) {
                printf("soup");
                diff *= -1.0;
        } else if (diff > 0.0){
                printf("stew");
        } else {
                printf("neither really");
        }

        printf(" ran faster. Difference of ~ %.10fs\n", diff);

        /*
        clock_t begin;
        clock_t end;
        double  duration;

        char *inf_expr = calloc(EXP_LENGTH, sizeof(char));
        int inf_at = 9; // as so *after* the following line
        memcpy(inf_expr, "3+(2*4)-5", inf_at + 1);

        char *pof_expr = calloc(EXP_LENGTH, sizeof(char));
        int pof_at = 0;

        begin = clock();
        if (OP_PERROR == op_process(inf_expr, &pof_expr, inf_at, &pof_at)) {
                printf("Something has gone awry!\n");
                return 0;
        }
        end = clock();
        duration = (end - begin) / CLOCKS_PER_SEC;

        printf("soup: %s -> %s in %.10fs\n", inf_expr, pof_expr, duration);

        int result;
        if (OP_PERROR == op_evaluate(pof_expr, pof_at, &result)) {
                printf("Could not evaluate =(\n");
                return 0;
        }

        printf(" = %d\n", result);


        char *pof_expr_t = calloc(EXP_LENGTH, sizeof(char));
        int pof_at_t = 0;

        begin = clock();
        st_process(inf_expr, &pof_expr_t, inf_at, &pof_at_t);
        end = clock();

        printf("stew: %s -> %s in %.10fs\n", inf_expr, pof_expr, duration);

        return 0;
*/
}

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "emmintrin.h"
#include "pmmintrin.h"

#include "papi_helper.h"
#include "time_helper.h"

#define IL(i, j) ((((i) * (i + 1)) / 2) + (j))

double* cholesky(double *A, int n) {
    //int i, j, k, k1, k2, k3;
    //double a, m1, m2, m3, m4;
    int i, j, k;
    double a;
    __m128d pd1, pd2, pd3;
    //double a1[100] __attribute__((aligned(16)));
    double a1[100];
    for (i = 0; i < n; ++i) {
        for (j = 0; j <= i; ++j) {
            a = A[IL(i, j)];
            for (k = 0; k + 2 < j; k += 2) {
                pd1 = _mm_load_pd(&A[IL(i, k)]);
                /*
                pd2 = _mm_load_pd(&A[IL(j, k)]);
                pd3 = _mm_mul_pd(pd1, pd2);
                pd3 = _mm_hadd_pd(pd3, pd3);
                */
                //_mm_store_pd1(a1, pd3);
                //a -= a1[0];
            }

            for (; k < j; ++k) {
                a -= A[IL(i, k)] * A[IL(j, k)];
            }

            A[IL(i, j)] = j < i ? a / A[IL(j, j)] : sqrt(a);
        }
    }

    return A;
} 

int main(int argc, char* argv[]) {
    int i, j;
    int n = atoi(argv[1]);
    void *A = NULL;
    posix_memalign(&A, 16, n * n * sizeof(double));
    double *L = NULL;
    FILE *fp = NULL;
    char filename[150];

    sprintf(filename, "matrices/%d", n);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        return 1;
    }

    double tmp;
    for (i = 0; i < n; ++i) {
        for (j = 0; j <= i; ++j) {
            fscanf(fp, "%lf", &((double*)A)[IL(i, j)]);
        }

        for (; j < n; ++j) {
            fscanf(fp, "%lf", &tmp);
        }
    }

    start_clock();
    start_papi();
    L = cholesky(A, n);
    stop_papi();
    stop_clock();

    double checksum = 0.0;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (j <= i) {
                checksum += i + j + L[IL(i, j)];
            } else {
                checksum += i + j;
            }
        }
    }

    printf("Size: %d\n", n);
    printf("Checksum: %lf\n", checksum);
    return 0;
}

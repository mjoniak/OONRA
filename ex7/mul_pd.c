#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include "emmintrin.h"
#include "pmmintrin.h"

#include "papi_helper.h"
#include "time_helper.h"

#define IL(i, j) ((((i + 1) * (i + 1)) / 2) + (j))

double* cholesky(double *A, int n) {
    int i, j, k, k2;
    double a __attribute((aligned(16)));
    __m128d a1, m1, m2, m3, m4;
    for (i = 0; i < n; ++i) {
        for (j = 0; j <= i; ++j) {
            a1 = _mm_load_sd(&A[IL(i, j)]);
            for (k = 0; k + 3 < j; k += 4) {
                k2 = k + 2;
                m1 = _mm_load_pd(&A[IL(i, k)]);
                m2 = _mm_load_pd(&A[IL(j, k)]);
                m3 = _mm_load_pd(&A[IL(i, k2)]);
                m4 = _mm_load_pd(&A[IL(j, k2)]);

                m1 = _mm_mul_pd(m1, m2);
                m2 = _mm_mul_pd(m3, m4);

                a1 = _mm_sub_pd(a1, m1);
                a1 = _mm_sub_pd(a1, m2);
            }

            a1 = _mm_hadd_pd(a1, a1);
            _mm_store_pd1(&a, a1);

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
    double *A = NULL;
    posix_memalign((void**)&A, 16, IL(n - 1, n) * sizeof(double));
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
            fscanf(fp, "%lf", &A[IL(i, j)]);
        }

        for (; j < n; ++j) {
            fscanf(fp, "%lf", &tmp);
        }
    }

    start_clock();
    start_papi();
    cholesky(A, n);
    stop_papi();
    stop_clock();

    double checksum = 0.0;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (j <= i) {
                checksum += i + j + A[IL(i, j)];
            } else {
                checksum += i + j;
            }
        }
    }

    printf("Size: %d\n", n);
    printf("Checksum: %lf\n", checksum);
    free(A);
    return 0;
}

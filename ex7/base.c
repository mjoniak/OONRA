#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "emmintrin.h"

#include "papi_helper.h"
#include "time_helper.h"

#define IL(i, j) ((((i) * (i + 1)) / 2) + (j))

double* cholesky(double *A, int n) {
    int i, j, k, k1, k2, k3;
    double a, m1, m2, m3, m4;
    for (i = 0; i < n; ++i) {
        for (j = 0; j <= i; ++j) {
            a = A[IL(i, j)];
            for (k = 0; k + 4 < j; k += 4) {
                k1 = k + 1;
                k2 = k + 2;
                k3 = k + 3;
                m1 = A[IL(i, k)] * A[IL(j, k)];
                m2 = A[IL(i, k1)] * A[IL(j, k1)]; 
                m3 = A[IL(i, k2)] * A[IL(j, k2)];
                m4 = A[IL(i, k3)] * A[IL(j, k3)];
                a += -m1 - m2 - m3 - m4;
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
    double* A = calloc(n * n, sizeof(double));
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
            fscanf(fp, "%lf", &A[IL(i, j)]);  
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

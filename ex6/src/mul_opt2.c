#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "emmintrin.h"

#include "papi_helper.h"
#include "time_helper.h"

#define IL(i, j) ((((i) * (i + 1)) / 2) + (j))
#define IA(i, j) ((i) * n + (j))
#define PATH "/home/mateusz/oonra/ex6"

double* cholesky(double *A, int n) {
    int i, j, k, k1, k2, k3;
    double a, m1, m2, m3, m4;
    double *L = (double*)calloc(n * n, sizeof(double));
    for (i = 0; i < n; ++i) {
        for (j = 0; j < i; ++j) {
            a = A[IA(i, j)];
            for (k = 0; k < j; k += 4) {
                k1 = k + 1;
                k2 = k + 2;
                k3 = k + 3;
                m1 = L[IL(i, k)] * L[IL(j, k)];
                m2 = L[IL(i, k1)] * L[IL(j, k1)]; 
                m3 = L[IL(i, k2)] * L[IL(j, k2)];
                m4 = L[IL(i, k3)] * L[IL(j, k3)];
                a -= (m1 + m2 + m3 + m4);
            }

            L[IL(i, j)] = a / L[IL(j, j)];
        }

        a = A[IA(i, i)];
        for (k = 0; k < i; k += 4) {
            k1 = k + 1;
            k2 = k + 2;
            k3 = k + 3;
            m1 = L[IL(i, k)] * L[IL(i, k)];
            m2 = L[IL(i, k1)] * L[IL(i, k1)];
            m3 = L[IL(i, k2)] * L[IL(i, k2)];
            m4 = L[IL(i, k3)] * L[IL(i, k3)];
            a -= (m1 + m2 + m3 + m4);
        }

        L[IL(i, i)] = sqrt(a);
    }

    return L;
} 

int main(int argc, char* argv[]) {
    int i, j;
    int n = (SIZE);
    double A[(SIZE) * (SIZE)] = {0};
    double *L = NULL;
    FILE *fp = NULL;
    char filename[150];

    sprintf(filename, "%s/matrices/%d", PATH, SIZE);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        return 1;
    }

    for (i = 0; i < n * n; ++i) {
        fscanf(fp, "%lf", A + i);  
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

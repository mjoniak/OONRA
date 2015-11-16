#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "papi_helper.h"
#include "time_helper.h"

#define INDEX(i, j) ((i * n) + j)
#define PATH "/home/mateusz/oonra/ex6"

double* cholesky(double *A, int n) {
    register int i, j, k;
    double *L = (double*)calloc(n * n, sizeof(double));
    for (i = 0; i < n; ++i) {
        for (j = 0; j < i; ++j) {
            L[INDEX(i, j)] = A[INDEX(i, j)];
            for (k = 0; k < j; ++k) {
                L[INDEX(i, j)] -= L[INDEX(i, k)] * L[INDEX(j, k)];
            }

            L[INDEX(i, j)] /= L[INDEX(j, j)];
        }

        L[INDEX(j, j)] = A[INDEX(j, j)];
        for (k = 0; k < i; ++k) {
            L[INDEX(i, i)] -= L[INDEX(i, k)] * L[INDEX(i, k)];
        }
       
        L[INDEX(i, i)] = sqrt(L[INDEX(i, i)]);
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
            checksum += i + j + L[INDEX(i, j)];
        }
    }

    printf("Size: %d\n", n);
    printf("Checksum: %lf\n", checksum);
    return 0;
}

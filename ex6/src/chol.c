#include <stdio.h>

#include "papi_helper.h"

int cholesky(double *A, int n) {
    return 0;
} 

int main(int argc, char* argv[]) {
    int n = (SIZE);
    double A[(SIZE)]; 

    start_papi();
    cholesky(A, n);
    stop_papi();

    printf("Size: %d\n", n);
    return 0;
}

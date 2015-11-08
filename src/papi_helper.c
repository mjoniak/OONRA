#include <stdio.h>
#include <papi.h>

int events[2] = { PAPI_L1_DCM, PAPI_FP_OPS };
long long values[2] = {0,};
int eventSet = PAPI_NULL;
int papi_err;
int papi_supported = 1;

void start_papi() {
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
        fprintf(stderr, "PAPI is unsupported.\n");
        papi_supported = 0;
    }

    if (PAPI_num_counters() < 2) {
        fprintf(stderr, "PAPI is unsupported.\n");
        papi_supported = 0;
    }
    
    if ((papi_err = PAPI_create_eventset(&eventSet)) != PAPI_OK) {
        fprintf(stderr, "Could not create event set: %s\n", PAPI_strerror(papi_err));
    }

    for (int i=0; i<2; ++i) {
        if ((papi_err = PAPI_add_event(eventSet, events[i])) != PAPI_OK ) {
            fprintf(stderr, "Could not add event: %d %s\n", i, PAPI_strerror(papi_err));
        }
    }

    /* start counters */

    if (papi_supported) {
        if ((papi_err = PAPI_start(eventSet)) != PAPI_OK) {
            fprintf(stderr, "Could not start counters: %s\n", PAPI_strerror(papi_err));
        }
    }
}

void stop_papi() {
    if (papi_supported) {
        if ((papi_err = PAPI_stop(eventSet, values)) != PAPI_OK) {
            fprintf(stderr, "Could not get values: %s\n", PAPI_strerror(papi_err));
        }
        printf("L1_DCM: %ld\n", values[0]);
        printf("FP_OPS: %ld\n", values[1]);
    }
}

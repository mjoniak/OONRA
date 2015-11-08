#include <stdio.h>
#include <stdlib.h>
#include <papi.h>

int en = 2;
const char* event_names[] = { "PAPI_L2_DCM", "PAPI_L2_DCH" };
int events[] = { PAPI_L2_DCM, PAPI_L2_DCH };
//const char* event_names[] = { "PAPI_FP_OPS", "PAPI_L1_DCM" };
//int events[] = { PAPI_FP_OPS, PAPI_L1_DCM };
long long* values;
int eventSet = PAPI_NULL;
int papi_err;
int papi_supported = 1;

void start_papi() {
    values = calloc(en, sizeof(long long));

    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
        fprintf(stderr, "PAPI is unsupported.\n");
        papi_supported = 0;
    }

    if (PAPI_num_counters() < en) {
        fprintf(stderr, "PAPI is unsupported.\n");
        papi_supported = 0;
    }
    
    if ((papi_err = PAPI_create_eventset(&eventSet)) != PAPI_OK) {
        fprintf(stderr, "Could not create event set: %s\n", PAPI_strerror(papi_err));
    }

    for (int i=0; i<en; ++i) {
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
        
        int i;
        for (i = 0; i < en; ++i) {
            printf("%s: %ld\n", event_names[i], values[i]);
        }
    }
}

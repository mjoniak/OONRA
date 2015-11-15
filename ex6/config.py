PROGRAMS = ['chol']
SIZES = range(500, 1100, 100)
METRICS = ['L1_DCM', 'L1_ICM', 'L1_TCM', 'FP_OPS']
EXEC_SUBDIR = "L1"

COMPILE_CMD_EXT = {\
        'default': ['src/papi_helper.c', '-O0', '-lpapi']\
}

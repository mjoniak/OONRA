PROGRAMS = ['cache_opt_O3']
PLOT_PROGRAMS = ['naive', 'compressed_mat', 'compressed_mat_register', 'naive_register', 'cache_opt', 'cache_opt2', 'cache_opt_O3']

SIZES = range(100, 1100, 100)
METRICS = ['L1_DCM', 'FP_OPS', 'Time']
EXEC_SUBDIR = "all"

COMPILE_CMD_EXT = {\
        'default': ['src/papi_helper.c', 'src/time_helper.c', '-O0', '-lpapi', '-lm'],\
        'cache_opt_O3': ['-O3']\
}

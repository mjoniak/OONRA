PROGRAMS = ['cache_opt2_compressed_mat', 'mul_opt', 'mul_opt2', 'naive']
PLOT_PROGRAMS = ['cache_opt2_compressed_mat', 'mul_opt', 'mul_opt2', 'naive']

SIZES = range(100, 1100, 100)
METRICS = ['L1_DCM', 'FP_OPS', 'Time']
EXEC_SUBDIR = "3"

COMPILE_CMD_EXT = {\
        'default': ['src/papi_helper.c', 'src/time_helper.c', '-O3', '-lpapi', '-lm'],\
}

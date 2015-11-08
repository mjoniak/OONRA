import subprocess

from config import *

if __name__ == '__main__':
    subprocess.call(['mkdir', 'exec/' + EXEC_SUBDIR])

    for prog in PROGRAMS:
        for n in SIZES:
            progname = 'mm' + prog
            source = progname + '.c'
            str_n = str(n)
            progname_full = progname + '_' + str_n
            print('compiling', source, 'for N =', n)
            cmd = ['gcc', '-O0', '-o' + progname_full, '-DSIZE=' + str_n, 'src/' + source, 'src/papi_helper.c', '-O0', '-lpapi']
            if prog == '10':
                cmd.extend(['-L/opt/intel/mkl/lib/intel64', '-lmkl_intel_ilp64', '-lmkl_sequential', '-lmkl_core', '-lm', '-lpthread', '-I/opt/intel/composer_xe_2015.3.187/mkl/include'])

            subprocess.call(cmd)
            subprocess.call(['mv', progname_full, 'exec/' + EXEC_SUBDIR])

    print('done.')

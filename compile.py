import subprocess

from config import *

if __name__ == '__main__':
    for prog in PROGRAMS:
        for n in SIZES:
            progname = 'mm' + prog
            source = progname + '.c'
            str_n = str(n)
            progname_size = progname + '_' + str_n
            print('compiling', source, 'for N =', n)
            subprocess.call(['gcc', '-O0', '-o' + progname_size, '-DSIZE=' + str_n, 'src/' + source, 'src/papi_helper.c', '-lpapi'])
            subprocess.call(['mv', progname_size, 'exec'])

    print('done.')

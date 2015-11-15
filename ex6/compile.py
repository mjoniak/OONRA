import subprocess

from config import *

if __name__ == '__main__':
    subprocess.call(['mkdir', 'exec/' + EXEC_SUBDIR])

    for prog in PROGRAMS:
        for n in SIZES:
            source = prog + '.c'
            str_n = str(n)
            progname_full = prog + '_' + str_n
            print('compiling', source, 'for N =', n)
            cmd = ['gcc', '-o' + progname_full, '-DSIZE=' + str_n, 'src/' + source]
            cmd.extend(COMPILE_CMD_EXT.get('default', []))
            cmd.extend(COMPILE_CMD_EXT.get(prog, []))
            subprocess.call(cmd)
            subprocess.call(['mv', progname_full, 'exec/' + EXEC_SUBDIR])

    print('done.')

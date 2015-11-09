import subprocess
import re

from config import *

if __name__ == '__main__':
    for m in METRICS:
        subprocess.call(['rm', '-r', 'results/' + m])
        subprocess.call(['mkdir', 'results/' + m])

    for i, prog in enumerate(PROGRAMS):
        for n in SIZES:
            progname = 'mm' + prog
            str_n = str(n)
            progname_size = progname + '_' + str_n
            res = str(subprocess.getoutput(['./exec/' + EXEC_SUBDIR + '/' + progname_size]))
            for m in METRICS:
                with open('results/' + m + '/' + prog, 'a') as f:
                    match = re.search(m + ': ([0-9]*)', res)
                    val = match.group(1)
                    print(prog, 'n:', n, m, val)
                    f.write(str(n) + ' ' + val + '\n')

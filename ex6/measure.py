import subprocess
import re

from config import *

if __name__ == '__main__':
    for m in METRICS:
        subprocess.call(['rm', '-r', 'results/' + m])
        subprocess.call(['mkdir', 'results/' + m])

    for i, prog in enumerate(PLOT_PROGRAMS):
        for n in SIZES:
            str_n = str(n)
            progname_size = prog + '_' + str_n
            res = str(subprocess.getoutput(['./exec/' + EXEC_SUBDIR + '/' + progname_size]))
            for m in METRICS:
                print(prog, 'n:', n)
                with open('results/' + m + '/' + prog, 'a') as f:
                    match = re.search(m + ': ([0-9]*.[0-9]*)', res)
                    val = match.group(1)
                    print(m, val)
                    f.write(str(n) + ' ' + val + '\n')

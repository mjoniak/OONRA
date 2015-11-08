import matplotlib.pyplot as plt
from random import random as rand

from config import *

if __name__ == '__main__':
    for m in METRICS:
        print(m)
        cm = plt.get_cmap('gist_rainbow')
        fig = plt.figure()
        ax = fig.add_subplot(111)
        num_colours = len(PROGRAMS)
        ax.set_color_cycle([cm(1.*i/num_colours) for i in range(num_colours)])
        for i, prog in enumerate(PROGRAMS):
            X = []
            Y = []
            filename = prog + '_' + m
            with open('results/' + filename, 'r') as f:
                for line in f:
                    vals = line.split(' ')
                    size = int(vals[0])
                    val = float(vals[1])
                    X.append(size)
                    Y.append(val)
            color = (rand(), rand(), rand())
            ax.plot(X, Y, label=prog)
        ax.legend()
        ax.set_xlabel('SIZE')
        ax.set_ylabel(m)
        #fig.show()
        fig.savefig('figures/' + m + '.png') 

    print('done.')


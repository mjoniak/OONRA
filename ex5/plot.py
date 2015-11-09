import matplotlib.pyplot as plt

from config import *

if __name__ == '__main__':
    for m in METRICS:
        print(m)
        cm = plt.get_cmap('gist_rainbow')
        fig = plt.figure()
        fig.clear()
        ax = fig.add_subplot(111)
        ax.grid(True)
        num_colours = len(PROGRAMS)
        ax.set_color_cycle([cm(1.*i/num_colours) for i in range(num_colours)])
        for i, prog in enumerate(PROGRAMS):
            X = []
            Y = []
            with open('results/' + m + '/' + prog, 'r') as f:
                for line in f:
                    vals = line.split(' ')
                    size = int(vals[0])
                    val = int(vals[1])
                    X.append(size)
                    Y.append(val)
            ax.plot(X, Y, label=prog)
        ax.legend(loc='upper left', fancybox=True)
        ax.set_xlabel('SIZE')
        ax.set_ylabel(m)
        #fig.show()
        fig.savefig('figures/' + m + '.png') 

    print('done.')


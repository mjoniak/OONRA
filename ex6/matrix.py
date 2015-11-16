from random import randint
import numpy as np
from config import *

if __name__ == '__main__':
    for n in SIZES:
        data = [] 
        for i in range(n):
            row = []
            for j in range(n):
                if j > i:
                    row.append(0)
                elif j == i:
                    row.append(randint(1, 10))
                else:
                    row.append(randint(-10, 10))
            data.append(row)

        L = np.matrix(data)
        A = L * np.transpose(L)
        L2 = np.linalg.cholesky(A)
        np.savetxt('matrices/{:d}'.format(n), A, delimiter=' ', fmt='%d')

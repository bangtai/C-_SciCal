"""
Example of calling Cholesky decomposition
"""

from __future__ import print_function
from scipy import array, linalg

# construct the matrix in hint 1
A = array([[2.0,-1.0,0.0],
           [-1.0,2.0,1.0,],
           [0.0,-1.0,2.0]])

print('The SPD system is')
print(A)
print()

# call cholesky
R = linalg.cholesky(A, lower=False)

# print
print('The upper triangular system is')
print(R)

import numpy as np

L = np.array([
    [ 3, -1,  0,  0,  0,  0, -1, -1,  0,  0],
    [-1,  2, -1,  0,  0,  0,  0,  0,  0,  0],
    [ 0, -1,  2, -1,  0,  0,  0,  0,  0,  0],
    [ 0,  0, -1,  2, -1,  0,  0,  0,  0,  0],
    [ 0,  0,  0, -1,  2, -1,  0,  0,  0,  0],
    [ 0,  0,  0,  0, -1,  2, -1,  0,  0,  0],
    [-1,  0,  0,  0,  0, -1,  2,  0,  0,  0],
    [-1,  0,  0,  0,  0,  0,  0,  3, -1, -1],
    [ 0,  0,  0,  0,  0,  0,  0, -1,  2, -1],
    [ 0,  0,  0,  0,  0,  0,  0, -1, -1,  2]
])

# if we had use .eig instead eigh we wouldve had to use argsort
# eigh can be used for symmetric matrices and is much faster than the general purpose eig
eigenvalues, eigenvectors = np.linalg.eigh(L)

fiedler_value = eigenvalues[1]
# we use : here to tell numpy we want all the values in that row of that column vs us doing it manually with loops
fiedler_vector = eigenvectors[:, 1]

print(f"fiedler value is {fiedler_value}, fiedlervector is {fiedler_vector}")

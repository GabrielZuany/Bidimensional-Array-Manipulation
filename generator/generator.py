from scipy.sparse import random
from scipy import stats
from numpy.random import default_rng
import numpy as np

def convolve2d(image, kernel):
    kernel = np.flipud(np.fliplr(kernel)) # flip the kernel
    output = np.zeros_like(image) # convolution output
    # Add zero padding to the input image
    image_padded = np.zeros((image.shape[0] + 2, image.shape[1] + 2))   
    image_padded[1:-1, 1:-1] = image
    for x in range(image.shape[1]):     # Loop over every pixel of the image
        for y in range(image.shape[0]):
            # element-wise multiplication of the kernel and the image
            output[y,x]=(kernel*image_padded[y:y+3,x:x+3]).sum()        
    return output

def matrix_binary_save(filename, matrix):
    try:
        f = open(filename, 'wb')
    except:
        f = open(filename, 'x')
        f.close()
    with open(filename, 'wb') as f:
        f.write(np.int32(len(matrix)))
        f.write(np.int32(len(matrix[0])))
        for i in range(len(matrix)):
            for j in range(len(matrix[0])):
                f.write(np.float64(matrix[i][j]))

rng = default_rng()
rvs = stats.poisson(25, loc=10).rvs

rows = cols = rng.integers(1, 10)
matrix1 = random(rows, cols, density=0.25, random_state=rng, data_rvs=rvs)
matrix1 = matrix1.toarray()

matrix2 = random(rows, cols, density=0.25, random_state=rng, data_rvs=rvs)
matrix2 = matrix2.toarray()

kernel = np.array([[1.0,2.0,1.0], [2.0,4.0,2.0], [1.0,2.0,1.0]]) # gauss blur kernel matrix
kernel = kernel / np.sum(kernel)

matrix_binary_save('generator/matrix_1.bin', matrix1)
matrix_binary_save('generator/matrix_2.bin', matrix2)
matrix_binary_save('generator/kernel.bin', kernel)

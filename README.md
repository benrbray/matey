# Matey:  Numerical Linear Algebra from Scratch

Curious about how libraries like `numpy` work internally, I decided to make my own.  Matey will be a Python package that supports basic matrix operations, least squares, matrix factorization, eigenvalue computations, and more.  The core logic will be written in C for speed and efficiency.  There are several popular methods for writing Python wrappers around C code, and it is currently unclear to me which is better.  Until I decide, I will be writing all algorithms in each of [Python C extensions](https://docs.python.org/3.5/extending/extending.html), [ctypes](https://docs.python.org/3/library/ctypes.html), [Cython](http://cython.org/), and pure Python.

## Current Features

| Feature                 | Python+C | Cython | ctypes |
|-------------------------|:--------:|:------:|:------:|
| Basic Matrix Operations | ✓        | ✓      | ✓      |
| QR Factorization        | 🔧       |        |        |
| Least Squares           | 🔧       |        |        |

## Wishlist

* LU Decomposition
* Cholesky Decomposition
* Compute Eigenvalues / Eigenvectors
* Singular Value Decomposition
* Support for matrices with special structure
    - Sparse matrices
    - Toeplitz matrices
    - Block matrices
* Transforms
    - Fast Fourier Transform
    - Nonuniform Fast Fourier Transform
    - Ewald Summation

# python
import timeit;
# scientific
import numpy as np;
# matey
import sys; sys.path.append("/home/ben/Documents/projects/matey");
import matey;

def setup_dot():
    global a;
    global b;
    n = 1000;
    a = list(np.random.randn(n));
    b = list(np.random.randn(n));

def test_dot(dot_func, a, b):
    dot_func(a,b);

def py_dot(a,b):
    result = 0;
    for k in range(len(a)):
        result += a[k] * b[k];
    return result;
    
def np_dot(a,b):
    return np.dot(np.array(a), np.array(b));

n = 10000;
print("Python:\t", timeit.timeit("test_dot(py_dot, a, b)", setup="setup_dot()", number=n, globals=globals()));
print("Numpy:\t", timeit.timeit("test_dot(np_dot, a, b)", setup="setup_dot()",  number=n, globals=globals()));
print("Matey:\t", timeit.timeit("test_dot(matey.dot, a, b)", setup="setup_dot()",  number=n, globals=globals()));

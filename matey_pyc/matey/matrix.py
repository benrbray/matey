import os;
print(os.getcwd());

from matey_pyc._matey import Matrix;

def as_str(self):
    print("This is a matrix!");

Matrix.__str__ = as_str;

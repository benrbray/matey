# built-in
import ctypes;
import os;

# import matey shared library
current_dir = os.path.dirname(__file__);
matey_path = os.path.join(current_dir, "matey.so");
libmatey = ctypes.CDLL(matey_path);

#### SUM #######################################################################

libmatey.sum.restype = ctypes.c_int;
libmatey.sum.argtypes = (
	ctypes.c_int,
	ctypes.POINTER(ctypes.c_int)
);

def sum(numbers):
	# prepare arguments
	size = len(numbers);
	array_type = ctypes.c_int * size;
	
	# compute sum
	result = libmatey.sum(
		ctypes.c_int(size),
		array_type(*numbers)
	);
	
	return int(result);

#### DOT PRODUCT ###############################################################

libmatey.dot.restype = ctypes.c_double;
libmatey.dot.argtypes = (
	ctypes.c_int,						# size
	ctypes.POINTER(ctypes.c_double),	# a
	ctypes.POINTER(ctypes.c_double)		# b
);

def dot(a,b):
	# validate input
	assert len(a) == len(b);
	
	# prepare arguments
	size = len(a);
	a_type = ctypes.c_double * size;
	b_type = ctypes.c_double * size;
	
	# compute dot product
	result = libmatey.dot(
		ctypes.c_int(size),
		a_type(*a),
		b_type(*b)
	);
	
	return float(result);

#### SAXPY #####################################################################

libmatey.saxpy.restype = None;
libmatey.saxpy.argtypes = (
	ctypes.c_int,						# size
	ctypes.c_double,					# a
	ctypes.POINTER(ctypes.c_double),	# x
	ctypes.POINTER(ctypes.c_double),	# y
)

def saxpy(a,x,y):
	# validate input
	assert len(x) == len(y);
	
	# prepare arguments
	size = len(x);
	vector_type = ctypes.c_double * size;
	
	# perform saxpy
	libmatey.saxpy(
		ctypes.c_int(size),
		ctypes.c_double(a),
		ctypes.byref(vector_type(*x)),
		ctypes.byref(vector_type(*x))
	);

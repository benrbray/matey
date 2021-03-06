#include "debug.h"
#include "matrix.h"

//// LIFECYCLE /////////////////////////////////////////////////////////////////

// Destructor ------------------------------------------------------------------

void Matrix_dealloc(Matrix* self) {
	debug("Matrix_dealloc()\n");
	// free matrix data
	//debug("\tFree Matrix Data\n");
	debug("\t%p\n", self->data);
	debug("\t%f\n", *self->data);
	//if(self->data != NULL && self->data != 0) free(self->data);
	// deallocate type (need to cast to handle subtypes)
	debug("\tDeallocate Type\n");
	Py_TYPE(self)->tp_free((PyObject*)self);
	debug("\tDone!\n");
}

// New (__new__) ---------------------------------------------------------------

/* MATRIX.__NEW__(self, shape)
 * @param `shape` is an int or two-tuple of ints.
 */
PyObject* Matrix_new(PyTypeObject *type, PyObject *args, PyObject *kwargs){
	// allocate
	// tp_alloc returns a pointer to a block of memory of adequate
	// length for the instance, suitably aligned, and initialized to zeros,
	// but with ob_refcnt set to 1 and ob_type set to the type argument.
	debug("Matrix_new()\n");
	Matrix *self = (Matrix*)type->tp_alloc(type, 0);
	return (PyObject*) self;
}

// Initialize (__init__) -------------------------------------------------------

int Matrix_init(Matrix *self, PyObject *args, PyObject *kwargs) {
	// check for instance
	if(self == NULL) return 0;

	// parse arguments
	int nrows=1, ncols=1;
	if(!PyArg_ParseTuple(args, "|ii", &nrows, &ncols)) return 0;

	debug("Matrix_init():  nrows=%d, ncols=%d\n", nrows, ncols);

	// initialize attributes
	if(self != NULL){
		// dimensions
		self->nrows = nrows;
		self->ncols = ncols;

		// allocate matrix data, initialize with zeros
		self->data = (double*)calloc(nrows * ncols, sizeof(double));
	}

	return 0;
}

//// ATTRIBUTES ////////////////////////////////////////////////////////////////

//// METHODS ///////////////////////////////////////////////////////////////////

// void Matrix.fill(double value)
PyObject* Matrix_fill(Matrix *self, PyObject *args){
	// check matrix exists
	if(self == NULL) return NULL;

	// parse arguments
	double value = 0;
	if(!PyArg_ParseTuple(args, "d", &value)) return NULL;

	// fill matrix
	int size = self->nrows * self->ncols;
	for(int k = 0; k < size; k++) self->data[k] = value;

	// return
	Py_RETURN_NONE;
}

// double Matrix_get(int row, int col)
PyObject* Matrix_get(Matrix *self, PyObject *args){
	// check matrix exists
	if(self == NULL) return NULL;

	// parse arguments
	int row = 0;
	int col = 0;
	if(!PyArg_ParseTuple(args, "ii", &row, &col)) return NULL;

	// check bounds
	if(row > self->nrows-1 || row < 0){
		PyErr_SetString(PyExc_IndexError, "Invalid row index.");
		return NULL;
	} else if(col > self->ncols-1 || col < 0){
		PyErr_SetString(PyExc_IndexError, "Invalid column index.");
		return NULL;
	}

	// access matrix entry
	int index = (row * self->ncols) + col;
	return PyFloat_FromDouble(self->data[index]);
}

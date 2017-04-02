#include "debug.h"
#include "matrix.h"

//// LIFECYCLE /////////////////////////////////////////////////////////////////

// Destructor ------------------------------------------------------------------

void Matrix_dealloc(Matrix* self) {
	// deallocate type (need to cast to handle subtypes)
	Py_TYPE(self)->tp_free((PyObject*)self);
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
	Matrix *self = (Matrix*)type->tp_alloc(type, 0);

	// parse arguments
	int nrows=1, ncols=1;
	if(!PyArg_ParseTuple(args, "|ii", &nrows, &ncols)) return NULL;

	debug("nrows=%d, ncols=%d\n", nrows, ncols);

	// initialize attributes
	if(self != NULL){
		// dimensions
		self->nrows = nrows;
		self->ncols = ncols;

		// allocate matrix data, initialize with zeros
		self->data = (double*)calloc(nrows * ncols, sizeof(double));
	}

	return (PyObject*) self;
}

// Initialize (__init__) -------------------------------------------------------

int Matrix_init(Matrix *self, PyObject *args, PyObject *kwargs) {
	if(self != NULL){
		// initialization
	}

	return 0;
}

//// ATTRIBUTES ////////////////////////////////////////////////////////////////

//// METHODS ///////////////////////////////////////////////////////////////////

// void Matrix.fill(double value)
PyObject* Matrix_fill(Matrix* self, PyObject* args){
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

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
        // default number
        self->number = 0;
    }

    return (PyObject*) self;
}

// Initialize (__init__) -------------------------------------------------------

int Matrix_init(Matrix *self, PyObject *args, PyObject *kwargs) {
    if(self != NULL){
        self->number = 10;
    }

    return 0;
}

//// ATTRIBUTES ////////////////////////////////////////////////////////////////

//// METHODS ///////////////////////////////////////////////////////////////////

PyObject* Matrix_nothing(Matrix* self){
    Py_RETURN_NONE;
}

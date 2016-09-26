#include "matrix.h"

//// LIFECYCLE /////////////////////////////////////////////////////////////////

// Destructor ------------------------------------------------------------------

void Matrix_dealloc(Matrix* self) {
    // deallocate type (need to cast to handle subtypes)
    Py_TYPE(self)->tp_free((PyObject*)self);
}

// New (__new__) ---------------------------------------------------------------

PyObject* Matrix_new(PyTypeObject *type, PyObject *args, PyObject *kwargs){
    // allocate
    // tp_alloc returns a pointer to a block of memory of adequate
    // length for the instance, suitably aligned, and initialized to zeros,
    // but with ob_refcnt set to 1 and ob_type set to the type argument.
    Matrix *self = (Matrix*)type->tp_alloc(type, 0);
    
    if(self != NULL){
        // default number
        self->number = 0;
    }
    
    return (PyObject*) self;
}

// Initialize (__init__) -------------------------------------------------------

int Matrix_init(Matrix *self, PyObject *args, PyObject *kwargs) {
    return 0;
}

//// ATTRIBUTES ////////////////////////////////////////////////////////////////

//// METHODS ///////////////////////////////////////////////////////////////////

PyObject* Matrix_nothing(Matrix* self){
    Py_RETURN_NONE;
}

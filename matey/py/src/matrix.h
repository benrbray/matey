#ifndef MATEY_MATRIX
#define MATEY_MATRIX

/*
MATEY.MATRIX
Matrix base type, supporting basic matrix operations and arithmetic.
@see: https://docs.python.org/3.5/extending/newtypes.html
*/

// includes
#include <Python.h>
#include "structmember.h"

// type-specific fields
typedef struct {
    PyObject_HEAD
    int number;
    int nrows;
    int ncols;
    double *data;
} Matrix;

//// LIFECYCLE /////////////////////////////////////////////////////////////////

// deconstructor
void Matrix_dealloc(Matrix* self);

// __new__ (guaranteed to be called)
PyObject* Matrix_new(PyTypeObject *type,
                     PyObject *args,
                     PyObject *kwargs);

// __init__ (not guaranteed to be called, or could be called more than once)
int Matrix_init(Matrix *self,
                PyObject *args,
                PyObject *kwargs);

//// METHODS & ATTRIBUTES //////////////////////////////////////////////////////

// Attributes ------------------------------------------------------------------

// simple members
static PyMemberDef Matrix_members[] = {
    {"number", T_INT, offsetof(Matrix, number), 0, "Number"},
    {"nrows", T_INT, offsetof(Matrix, nrows), READONLY, "Row dimension"},
    {"ncols", T_INT, offsetof(Matrix, ncols), READONLY, "Column dimension"},
    {NULL}
};

// Methods ---------------------------------------------------------------------

// Matrix.fill(value)
PyObject* Matrix_fill(Matrix* self, PyObject* args);

// Methods
static PyMethodDef Matrix_methods[] = {
    {"fill", (PyCFunction)Matrix_fill, METH_VARARGS, "Fill matrix with single value."},
    {NULL}
};

//// TYPE DEFINITION ///////////////////////////////////////////////////////////

static PyTypeObject MatrixType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name */           "matey.Matrix",
    /* tp_basicsize */      sizeof(Matrix),
    /* tp_itemsize */       0,
    /* tp_dealloc */        (destructor)Matrix_dealloc,
    /* tp_print */          0,
    /* tp_getattr */        0,
    /* tp_setattr */        0,
    /* tp_reserved */       0,
    /* tp_repr */           0,
    /* tp_as_number */      0,
    /* tp_as_sequence */    0,
    /* tp_as_mapping */     0,
    /* tp_hash  */          0,
    /* tp_call */           0,
    /* tp_str */            0,
    /* tp_getattro */       0,
    /* tp_setattro */       0,
    /* tp_as_buffer */      0,
    /* tp_flags */          Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    /* tp_doc */            "Matrix base object.",
    /* tp_traverse */       0,
    /* tp_clear */          0,
    /* tp_richcompare */    0,
    /* tp_weaklistoffset */ 0,
    /* tp_iter */           0,
    /* tp_iternext */       0,
    /* tp_methods */        Matrix_methods,
    /* tp_members */        Matrix_members,
    /* tp_getset */         0,
    /* tp_base */           0,
    /* tp_dict */           0,
    /* tp_descr_get */      0,
    /* tp_descr_set */      0,
    /* tp_dictoffset */     0,
    /* tp_init */           (initproc)Matrix_init,
    /* tp_alloc */          0,
    /* tp_new */            Matrix_new,
};

#endif

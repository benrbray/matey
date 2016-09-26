#ifndef MATEY_FULLNAME
#define MATEY_FULLNAME

/*
FullName
A simple Python type representing a first and last name.
@see: https://docs.python.org/3.5/extending/newtypes.html
*/

// includes
#include <Python.h>
#include "structmember.h"

// type-specific fields
typedef struct {
    PyObject_HEAD
    PyObject *first;            /* first name (string) */
    PyObject *last;             /* last name (string) */
    int number;
} FullName;

//// LIFECYCLE ///////////////////////////////////////////////////////////////

// deconstructor
void FullName_dealloc(FullName* self);

// __new__ (guaranteed to be called)
PyObject* FullName_new(PyTypeObject *type,
                              PyObject *args,
                              PyObject *kwargs);

// __init__ (not guaranteed to be called, or could be called more than once)
int FullName_init(FullName *self,
                         PyObject *args,
                         PyObject *kwargs);

//// METHODS & ATTRIBUTES ////////////////////////////////////////////////////

// Attributes ------------------------------------------------------------------

// simple members
static PyMemberDef FullName_members[] = {
    {"number", T_INT, offsetof(FullName, number), 0, "Number"},
    {NULL}
};

// first:  first name
PyObject* FullName_getfirst(FullName *self, void *closure);
int FullName_setfirst(FullName *self, PyObject *value, void *closure);

// last:  last name
PyObject* FullName_getlast(FullName *self, void *closure);
int FullName_setlast(FullName *self, PyObject *value, void *closure);

// define getters and setters
static PyGetSetDef FullName_getsetters[] = {
    {"first", (getter)FullName_getfirst, (setter)FullName_setfirst,
        "first name", NULL},
    {"last", (getter)FullName_getlast, (setter)FullName_setlast,
        "last name", NULL},
    {NULL}
};

// Methods ---------------------------------------------------------------------

// FullName.name()
PyObject* FullName_name(FullName* self);

// Methods
static PyMethodDef FullName_methods[] = {
    {"name", (PyCFunction)FullName_name, METH_NOARGS,
        "Return the full name."},
    {NULL}
};

//// TYPE DEFINITION ///////////////////////////////////////////////////////////

static PyTypeObject FullNameType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name */           "matey.FullName",
    /* tp_basicsize */      sizeof(FullName),
    /* tp_itemsize */       0,
    /* tp_dealloc */        (destructor)FullName_dealloc,
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
    /* tp_doc */            "Python type example.",
    /* tp_traverse */       0,
    /* tp_clear */          0,
    /* tp_richcompare */    0,
    /* tp_weaklistoffset */ 0,
    /* tp_iter */           0,
    /* tp_iternext */       0,
    /* tp_methods */        FullName_methods,
    /* tp_members */        FullName_members,
    /* tp_getset */         FullName_getsetters,
    /* tp_base */           0,
    /* tp_dict */           0,
    /* tp_descr_get */      0,
    /* tp_descr_set */      0,
    /* tp_dictoffset */     0,
    /* tp_init */           (initproc)FullName_init,
    /* tp_alloc */          0,
    /* tp_new */            FullName_new,
};

#endif

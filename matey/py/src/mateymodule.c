#include <Python.h>
#include "matrix.h"
#include "example.h"

//// MODULE METHODS ///////////////////////////////////////////////////////////

static PyObject* matey_nothing(PyObject *self, PyObject *args){
    Py_RETURN_NONE;
}

//// MODULE DEFINITION ////////////////////////////////////////////////////////

static PyMethodDef MateyMethods[] = {
    {"nothing", matey_nothing, METH_VARARGS, "Do nothing."},
    // sentinel
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mateymodule = {
    PyModuleDef_HEAD_INIT,
    "matey",                // module name
    NULL,                   // module documentation
    -1,                     // module keeps state in global variables
    MateyMethods            // method table
};

PyMODINIT_FUNC PyInit_matey(void){
    PyObject* m;
    
    // create module
    m = PyModule_Create(&mateymodule);
    if(m == NULL) return NULL;
    
    // prepare matrix type
    MatrixType.tp_new = PyType_GenericNew;
    if(PyType_Ready(&MatrixType) < 0) return NULL;
    
    Py_INCREF(&MatrixType);
    PyModule_AddObject(m, "Matrix", (PyObject*)&MatrixType);
    
    // prepare fullname type
    if(PyType_Ready(&FullNameType) < 0) return NULL;
    Py_INCREF(&FullNameType);
    PyModule_AddObject(m, "FullName", (PyObject*)&FullNameType);
    
    // done
    return m;
}

#include <Python.h>
#include "matrix.h"

//// MODULE METHODS ///////////////////////////////////////////////////////////

static PyObject* matey_nothing(PyObject *self, PyObject *args){
	Py_RETURN_NONE;
}

/* MATEY.MATRIX()
 * Dynamically create a matey.Matrix type from a Python list object.
 */
static PyObject* matey_matrix(PyObject *self, PyObject *args){
	Matrix* matrix = PyObject_New(Matrix, &MatrixType);
	PyObject_Init((PyObject*)matrix, &MatrixType);
	return (PyObject*)matrix;
}

// String Conversion -----------------------------------------------------------

static PyObject *Matrix_StrFunction = NULL;
static PyObject *Matrix_ReprFunction = NULL;

/*static PyObject* matey_set_string_function(PyObject *self, PyObject *args){

}*/

//// MODULE DEFINITION ////////////////////////////////////////////////////////

static PyMethodDef MateyMethods[] = {
	{"nothing", matey_nothing, METH_VARARGS, "Do nothing."},
	{"matrix", matey_matrix, METH_VARARGS, "Construct a matrix."},
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

PyMODINIT_FUNC PyInit__matey(void){
	PyObject* m;

	// create module
	m = PyModule_Create(&mateymodule);
	if(m == NULL) return NULL;

	// prepare matrix type
	if(PyType_Ready(&MatrixType) < 0) return NULL;
	Py_INCREF(&MatrixType);
	PyModule_AddObject(m, "Matrix", (PyObject*)&MatrixType);

	// done
	return m;
}

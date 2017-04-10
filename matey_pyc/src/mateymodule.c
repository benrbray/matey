#include <Python.h>
#include <stdbool.h>
#include "matrix.h"
#include "debug.h"

//// MODULE METHODS ///////////////////////////////////////////////////////////

static PyObject* matey_nothing(PyObject *self, PyObject *args){
	Py_RETURN_NONE;
}

static PyObject* matrixFromDouble(double value){
	// create object
	Matrix* matrix = PyObject_New(Matrix, &MatrixType);
	PyObject_Init((PyObject*)matrix, &MatrixType);

	// call constructor
	PyObject *newArgs = Py_BuildValue("ii", 1,1);
	Matrix_init(matrix, newArgs, NULL);
	Py_DECREF(newArgs);

	// set value
	matrix->data[0] = value;

	return (PyObject*)matrix;
}

static PyObject* matrixFromSequence(PyObject *array){
	debug("matrixFromSequence()\n");
	// Validation --------------------------------------------------------------

	// check for sequence type
	if(!PySequence_Check(array)){
		PyErr_SetString(PyExc_TypeError, "Expected sequence.");
		return NULL;
	}

	// ensure sequence has at least one element
	int nrows = PySequence_Length(array);

	if(nrows < 0){
		PyErr_SetString(PyExc_ValueError, "Failed to access sequence length.");
		return NULL;
	}
	if(nrows == 0){
		PyErr_SetString(PyExc_ValueError, "Cannot create matrix from empty sequence.");
		return NULL;
	}

	// matrix create object
	Matrix* matrix = NULL;

	// get first array element
	PyObject *firstElement = PySequence_GetItem(array, 0);

	// Column Vector -----------------------------------------------------------

	if(PyFloat_Check(firstElement) || PyLong_Check(firstElement)){
		debug("\tColumn Vector\n");
		// call constructor
		PyObject *newArgs = Py_BuildValue("ii", nrows, 1);
		matrix = (Matrix*)PyObject_CallObject((PyObject *)&MatrixType, newArgs);
		Py_DECREF(newArgs);

		// set matrix entries
		for(int r = 0; r < nrows; r++){
			PyObject *element = PySequence_GetItem(array, r);

			// get element value
			double value = 0;

			if(PyFloat_Check(element)){
				value = PyFloat_AS_DOUBLE(element);
			} else if(PyLong_Check(element)){
				value = PyLong_AsDouble(element);
			} else {
				PyErr_SetString(PyExc_TypeError, "Vector entries must be numbers.");
				goto FAILURE;
			}

			// set matrix data
			matrix->data[r] = value;
			Py_DECREF(element);
		}
	}

	// Matrix ------------------------------------------------------------------

	else if(PySequence_Check(firstElement)){
		debug("\t2-Dimensional Matrix\n");
		// validate column length
		int ncols = PySequence_Length(firstElement);

		if(ncols < 0){
			PyErr_SetString(PyExc_ValueError, "Failed to access sequence length.");
			goto FAILURE;
		}
		if(ncols == 0){
			PyErr_SetString(PyExc_ValueError, "Cannot create matrix from empty sequence.");
			goto FAILURE;
		}

		// call constructor
		PyObject *newArgs = Py_BuildValue("ii", nrows, ncols);
		matrix = (Matrix*)PyObject_CallObject((PyObject *)&MatrixType, newArgs);
		Py_DECREF(newArgs);

		// visit rows
		for(int r = 0; r < nrows; r++){
			// validate row
			PyObject *row = PySequence_GetItem(array, r);
			if(!PySequence_Check(row)){
				PyErr_SetString(PyExc_ValueError, "Expected two-dimensional sequence.");
				goto FAILURE;
			}

			// validate row length
			if(PySequence_Length(row) != ncols){
				PyErr_SetString(PyExc_ValueError, "Cannot create matrix from jagged array.");
				goto FAILURE;
			}

			// visit column entries
			for(int c = 0; c < ncols; c++){
				PyObject *element = PySequence_GetItem(row, c);

				// get element value
				double value = 0;

				if(PyFloat_Check(element)){
					value = PyFloat_AS_DOUBLE(element);
				} else if(PyLong_Check(element)){
					value = PyLong_AsDouble(element);
				} else {
					PyErr_SetString(PyExc_TypeError, "Matrix entries must be numbers.");
					goto FAILURE;
				}

				// set matrix data
				matrix->data[r*ncols + c] = value;
				Py_DECREF(element);
			}
		}

	}

	// Unexpected Data Format --------------------------------------------------

	else {
		debug("\tUnexpected Format\n");
		// unexpected data format
		PyErr_SetString(PyExc_TypeError, "Unexpected data format.");
		goto FAILURE;
	}

	// pass object reference
	Py_XDECREF(firstElement);
	return (PyObject*)matrix;

FAILURE:
	Py_XDECREF(matrix);
	return NULL;
}

/* MATEY.MATRIX()
 * Dynamically create a matey.Matrix type from a Python list object.
 */
static PyObject* matey_matrix(PyObject *self, PyObject *args){
	// Argument Parsing & Validation -------------------------------------------
	// parse arguments
	PyObject *array = NULL;
	if(!PyArg_ParseTuple(args, "O", &array)) return NULL;

	// check for sequence or number
	bool isSequence = PySequence_Check(array);
	bool isLong = PyLong_Check(array);
	bool isFloat = PyFloat_Check(array);
	if(!isSequence && !isLong && !isFloat){
		PyErr_SetString(PyExc_TypeError, "Expected sequence or number.");
		return NULL;
	}

	// return 1x1 matrix if given number
	if(isFloat){ return matrixFromDouble(PyFloat_AS_DOUBLE(array)); }
	if(isLong) { return matrixFromDouble(PyLong_AsDouble(array)); }
	else       { return matrixFromSequence(array); }
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

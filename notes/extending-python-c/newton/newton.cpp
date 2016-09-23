#include <Python.h>

////////////////////////////////////////////////////////////////////////////////

/* NEWTON.FIND_ZERO()
 * Find zeros of the provided function.
 */
static PyObject* newton_find_zero(PyObject *self, PyObject *args){
	
}

////////////////////////////////////////////////////////////////////////////////

// method table
static PyMethodDef newton_module_methods[] = {
	{"find_zero", newton_find_zero, METH_VARARGS, "Run Newton's method."},
	{NULL, NULL, 0, NULL}
}

// module definition
static struct PyModuleDef newton_module = {
	PyModuleDef_HEAD_INIT,
	"newton",								// module name
	"Find zeros using Newton's method.",	// module description
	-1,										// -1 for global state
	newton_module_methods					// method table
}

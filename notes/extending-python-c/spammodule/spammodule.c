#include <Python.h>

static PyObject* spam_system(PyObject *self, PyObject *args){
	const char *command;
	int status;
	
	if(!PyArg_ParseTuple(args, "s", &command)){
		return NULL;
	}
	
	status = system(command);
	return PyLong_FromLong(status);
}

static PyObject* spam_nothing(PyObject *self, PyObject *args){
	/* 
	 * The following is a macro for returning the special Py_None singleton.
	 * First increments the reference to Py_None then returns it.
	 */
	Py_RETURN_NONE;
}

static PyMethodDef SpamMethods[] = {
	{"system", spam_system, METH_VARARGS, "Execute a shell command."},
	{"nothing", spam_nothing, METH_VARARGS, "Do nothing."},
	// sentinel
	{NULL, NULL, 0, NULL} 
};

static struct PyModuleDef spammodule = {
	PyModuleDef_HEAD_INIT,
	"spam",						// name of module
	"documentation",			// module documentation
	-1,							// size of per-interpreter state, or -1 if global
	SpamMethods					// method table
};

PyMODINIT_FUNC PyInit_spammodule(void) {
    return PyModule_Create(&spammodule);
}


#include "example.h"

//// LIFECYCLE /////////////////////////////////////////////////////////////////

// Destructor ------------------------------------------------------------------

void FullName_dealloc(FullName* self) {
    // unreference first/last name strings
    Py_XDECREF(self->first);
    Py_XDECREF(self->last);
    // deallocate type (need to cast to handle subtypes)
    Py_TYPE(self)->tp_free((PyObject*)self);
}

// New (__new__) ---------------------------------------------------------------

PyObject* FullName_new(PyTypeObject *type, PyObject *args, PyObject *kwargs){
    // allocate
    // tp_alloc returns a pointer to a block of memory of adequate
    // length for the instance, suitably aligned, and initialized to zeros,
    // but with ob_refcnt set to 1 and ob_type set to the type argument.
    FullName *self = (FullName*)type->tp_alloc(type, 0);
    
    if(self != NULL){
        // initialize first name to empty string
        self->first = PyUnicode_FromString("");
        if(self->first == NULL){
            Py_DECREF(self);
            return NULL;
        }
        
        // initialize last name to empty string
        self->last = PyUnicode_FromString("");
        if(self->last == NULL){
            Py_DECREF(self);
            return NULL;
        }
        
        // default number
        self->number = 0;
    }
    
    return (PyObject*) self;
}

// Initialize (__init__) -------------------------------------------------------

int FullName_init(FullName *self, PyObject *args, PyObject *kwargs) {
    PyObject *first=NULL, *last=NULL, *tmp;

    static char *kwlist[] = {"first", "last", "number", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwargs, "|UUi", kwlist,
                                      &first, &last,
                                      &self->number))
        return -1;
    
    /* WHY DO WE INITIALIZE MEMBERS IN THIS FUNKY WAY BELOW?
     * We might be temped to assign the `first` member like this:
     *      if(first){
     *          Py_XDECREF(self->first);
     *          Py_INCREF(first);
     *          self->first = first;
     *      }
     * But this would be risky.  Our type doesn't restrict the type of the
     * `first` member, so it could be any type of object.  To be paranoid and
     * protect ourselves against his possibility, we almost always reassign
     * members before decrementing their reference counts.
     */

    // set first name
    if (first) {
        tmp = self->first;
        Py_INCREF(first);
        self->first = first;
        Py_XDECREF(tmp);
    }
    
    // set last name
    if (last) {
        tmp = self->last;
        Py_INCREF(last);
        self->last = last;
        Py_XDECREF(tmp);
    }

    return 0;
}

//// ATTRIBUTES ////////////////////////////////////////////////////////////////

// First ---------------------------------------------------------------------

PyObject* FullName_getfirst(FullName *self, void *closure){
    Py_INCREF(self->first);
    return self->first;
}

int FullName_setfirst(FullName *self, PyObject *value, void *closure){
    if(value == NULL){
        PyErr_SetString(PyExc_TypeError, "Cannot delete attribute 'first'.");
        return -1;
    }
    
    if(!PyUnicode_Check(value)){
        PyErr_SetString(PyExc_TypeError, "Attribute 'first' must be a string.");
        return -1;
    }
    
    Py_DECREF(self->first);
    Py_INCREF(value);
    self->first = value;
    
    return 0;
}

// Last ------------------------------------------------------------------------

PyObject* FullName_getlast(FullName *self, void *closure){
    Py_INCREF(self->last);
    return self->last;
}

int FullName_setlast(FullName *self, PyObject *value, void *closure){
    if(value == NULL){
        PyErr_SetString(PyExc_TypeError, "Cannot delete attribute 'last'.");
        return -1;
    }
    
    if(!PyUnicode_Check(value)){
        PyErr_SetString(PyExc_TypeError, "Attribute 'last' must be a string.");
        return -1;
    }
    
    Py_DECREF(self->last);
    Py_INCREF(value);
    self->last = value;
    
    return 0;
}

//// METHODS ///////////////////////////////////////////////////////////////////

PyObject* FullName_name(FullName* self){
    return PyUnicode_FromFormat("%S %S", self->first, self->last);
}

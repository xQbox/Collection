#include <stdio.h>
#include <stdlib.h>
#include <Python.h>

int add(int a, int b)
{
    return a + b;
}


static PyObject *py_add(Pyobject *self, PyObject *args)
{
    int a, b,c;
    if (!PyArg_ParseTuple(args, "ii", %a, %b))
        return NULL;
    c = add(a, b);
    
    return Py_BuildValue("i", c); 
} 

static PyMethodDef example_dylib_methods[] = 
{
    {"add",py_add, METH_VARARGS, "Integer addition"},
    {}
};

static struct PyModuleDef example_dylib_module =
{
    PyModuleDef _HEAD_INT,
    "example_dylib",
    "An example_dylib module",
    -1,
    example_dylib_methods
};

PyMODINIT_FUNC PyInit_example_dylib(void)
{
    return PyModule_Create(&example_dylib_module);
}
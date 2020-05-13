#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <msikeyboard/msikeyboard.h>

#if PY_MAJOR_VERSION >= 3
#define OUTPUT_FORMAT "y#"
#else
#define OUTPUT_FORMAT "s#"
#endif

static PyObject *msikeyboard_set_color_by_names(PyObject *self, PyObject *args) {
    int code = init_msi_keyboard();
    if ( code != 0 )
        return NULL;

    const char *region;
    const char *color;
    const char *intensity;

    if ( !PyArg_ParseTuple(args, "sss", &region, &color, &intensity))
        return NULL;

    int result = set_color_by_names(region, color, intensity);

    code = free_msi_keyboard();
    if ( code != 0 )
        return NULL;

    return Py_BuildValue( "i", result );
}

static PyObject *msikeyboard_set_rgb_color_by_name(PyObject *self, PyObject *args) {
    int code = init_msi_keyboard();
    if ( code != 0 )
        return NULL;

    const char *region;
    const char *intensity;
    unsigned char r;
    unsigned char g;
    unsigned char b;

    if ( !PyArg_ParseTuple(args, "siiis", &region, &r, &g, &b, &intensity))
        return NULL;
    struct RGB rgb = {};
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    int result = set_rgb_color_by_name(region, rgb, intensity);

    code = free_msi_keyboard();
    if ( code != 0 )
        return NULL;

    return Py_BuildValue("i", result);
}

static PyObject *msikeyboard_set_mode_by_name(PyObject *self, PyObject *args) {
    int code = init_msi_keyboard();
    if ( code != 0 )
        return NULL;

    const char *mode;

    if ( !PyArg_ParseTuple(args, "s", &mode))
        return NULL;
    int result = set_mode_by_name(mode);
    code = free_msi_keyboard();
    if ( code != 0 )
        return NULL;

    return Py_BuildValue("i", result);
}

static PyObject *get_string_list(char **result, size_t size) {
    PyObject *list = PyList_New(0);
    if ( list == NULL )
        return NULL;

    size_t i;
    for(i = 0; i < size; i++) {
        PyObject *value = Py_BuildValue("s", result[i]);
        if (PyList_Append(list, value) == -1) {
            return NULL;
        }
    }

    return list;
}

static PyObject *msikeyboard_get_regions(PyObject *self, PyObject *args) {
    if ( !PyArg_ParseTuple(args, ""))
        return NULL;
    size_t size;
    char **result = get_regions(&size);

    return get_string_list(result, size);
}

static PyObject *msikeyboard_get_colors(PyObject *self, PyObject *args) {
    if ( !PyArg_ParseTuple(args, ""))
        return NULL;
    size_t size;
    char **result = get_colors(&size);

    return get_string_list(result, size);
}

static PyObject *msikeyboard_get_modes(PyObject *self, PyObject *args) {
    if ( !PyArg_ParseTuple(args, ""))
        return NULL;
    size_t size;
    char **result = get_modes(&size);

    return get_string_list(result, size);
}

static PyObject *msikeyboard_get_intensities(PyObject *self, PyObject *args) {
    if ( !PyArg_ParseTuple(args, ""))
        return NULL;
    size_t size;
    char **result = get_intensities(&size);

    return get_string_list(result, size);
}

static PyMethodDef msikeyboard_funcs[] = {
        { "set_color", (PyCFunction)msikeyboard_set_color_by_names,  METH_VARARGS, "set MSI keyboard color on given region with standard color and intensity" },
        { "set_rgb_color", (PyCFunction)msikeyboard_set_rgb_color_by_name,  METH_VARARGS, "set MSI keyboard color on given region with RGB colors and intensity" },
        { "set_mode", (PyCFunction)msikeyboard_set_mode_by_name,  METH_VARARGS, "set MSI keyboard color mode" },
        { "get_regions", (PyCFunction)msikeyboard_get_regions,  METH_VARARGS, "get MSI keyboard region names" },
        { "get_colors", (PyCFunction)msikeyboard_get_colors,  METH_VARARGS, "get MSI keyboard color names" },
        { "get_modes", (PyCFunction)msikeyboard_get_modes,  METH_VARARGS, "get MSI keyboard mode names" },
        { "get_intensities", (PyCFunction)msikeyboard_get_intensities,  METH_VARARGS, "get MSI keyboard intensity names" },
        { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static char msikeyboard_docs[] = "Python module for msikeyboard";
/* \
     set_keyboard_color( region, color, intensity ): set MSI keyboard color \n \
     decrypt_buffer( buffer, key ): decrypt some encrypted string buffer with key\n"; */

static struct PyModuleDef msikeyboard_def = {
   PyModuleDef_HEAD_INIT,
   "msikeyboard",   /* name of module */
   msikeyboard_docs, /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   msikeyboard_funcs
};
#endif

PyMODINIT_FUNC

#if PY_MAJOR_VERSION >= 3
PyInit_msikeyboard(void) {
    PyObject *m;
    m = PyModule_Create(&msikeyboard_def);
    if ( m == NULL )
        return NULL;
    return m;
}
#endif

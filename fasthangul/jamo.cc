#include "fasthangul/jamo.hh"
#include "PythonExtension.hh"
#include <string>

static fasthangul::jamo::JamoConverter converter;

static PyObject *JAMO_compose_jamo(PyObject *self, PyObject *args) {
  PyObject *string = NULL;
  if (!PyArg_UnpackTuple(args, "args", 1, 1, &string))
    return NULL;

  if (!PyUnicode_Check(string)) {
    PyErr_SetString(PyExc_TypeError, "arg must be str type");
    return NULL;
  }

  wchar_t *hangulString = PyUnicode_AsWideCharString(string, NULL);
  if (hangulString == NULL) {
    return NULL;
  }
  std::wstring composed = converter.compose(std::wstring{hangulString});
  PyObject *result = PyUnicode_FromWideChar(composed.c_str(), composed.length());
  PyMem_Free(hangulString);
  return result;
}

static PyObject *JAMO_decompose_jamo(PyObject *self, PyObject *args) {
  PyObject *string = NULL;
  if (!PyArg_UnpackTuple(args, "args", 1, 1, &string))
    return NULL;

  if (!PyUnicode_Check(string)) {
    PyErr_SetString(PyExc_TypeError, "arg must be str type");
    return NULL;
  }

  wchar_t *hangulString = PyUnicode_AsWideCharString(string, NULL);
  if (hangulString == NULL) {
    return NULL;
  }
  std::wstring decomposed = converter.decompose(std::wstring{hangulString});
  PyObject *result = PyUnicode_FromWideChar(decomposed.c_str(), decomposed.length());
  PyMem_Free(hangulString);
  return result;
}

/* ------------------- */
/* delcare Jamo Module */
static PyMethodDef jamoMethods[] = {
    {"compose_jamo", (PyCFunction)JAMO_compose_jamo, METH_VARARGS, "자모를 조합하는 함수입니다."},
    {"decompose_jamo", (PyCFunction)JAMO_decompose_jamo, METH_VARARGS, "자모를 분리하는 함수입니다."},
    {NULL}};

static PyModuleDef fasthangulJamoModule = {PyModuleDef_HEAD_INIT, "fasthangul.jamo", "", -1, jamoMethods};

PyMODINIT_FUNC PyInit_jamo(void) {
  PyObject *fasthangulJamo = PyModule_Create(&fasthangulJamoModule);

  if (fasthangulJamo == NULL)
    return NULL;

  converter.initializeJamos();

  return fasthangulJamo;
}

#include "jellyfishmodule.h"
/*
 * struct jellyfish_ObjectReturn 
{
    //* ANSI C/C++ Variable requirement 
    double          DoubleResultReturn ;
    int             IntResultReturn ;
    char*           StringReturn ;
    // Python Variable requirement 
    PyObject        *ObjectErrorReturn ; 
    // Ruby Variable requirement 
    unsigned long   RubyValue ;
    unsigned long   RubyID ;
    char            *StringValuePtr ;
    char            *ConstStringValue ;
    struct RBasic   RubyBasicType  ;
    struct RObject  RubyObjectType ;
    struct RClass   RubyClassType  ;
    struct RFloat   RubyFloatType  ;
    struct RString  RubyStringType ;
    struct RArray   RubyArrayType  ;
    struct RRegexp  RubyRegexpType ;
    struct RHash    RubyHashType   ;
};
*/

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct jellyfish_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct jellyfish_state _state;
#endif

#if PY_MAJOR_VERSION >= 3
#define UTF8_BYTES(s) (PyBytes_AS_STRING(s))
#else
#define UTF8_BYTES(s) (PyString_AS_STRING(s))
#endif

/* Returns a new reference to a PyString (python < 3) or
 * PyBytes (python >= 3.0).
 *
 * If passed a PyUnicode, the returned object will be NFKD UTF-8.
 * If passed a PyString or PyBytes no conversion is done.
 */
static inline PyObject* normalize(PyObject *mod, PyObject *pystr) 
{
    PyObject *unicodedata_normalize;
    PyObject *normalized;
    PyObject *utf8;

#if PY_MAJOR_VERSION < 3
    if (PyString_Check(pystr)) 
    {
      Py_INCREF(pystr);
      return pystr;
    }
#else
    if (PyBytes_Check(pystr)) 
    {
      Py_INCREF(pystr);
      return pystr;
    }
#endif

    if (PyUnicode_Check(pystr)) 
    {
      unicodedata_normalize = GETSTATE(mod)->unicodedata_normalize;
      normalized = PyObject_CallFunction(unicodedata_normalize, PyAnsiStringType, "NFKD", pystr);
      if (!normalized) 
      {
        return PyDefaultReturn;
      }
      utf8 = PyUnicode_AsUTF8String(normalized);
      Py_DECREF(normalized);
      return utf8;
    }

    PyErr_SetString(PyExc_TypeError, "expected str or unicode");
    return PyDefaultReturn;
}

static bool BooleanPythonTest( int IntTest )
{
  PyObject* ValueEval = Py_False ;
  if (IntTest) 
  {
    ValueEval=Py_True;
  } 
  return ValueEval ;
}

PyObject* IsErrorOnMemoryResult( )

static PyObject* jellyfish_jaro_winkler(PyObject *self, PyObject *args, PyObject *keywds)
{
    const char *s1, *s2;
    double result;

    if (!PyArg_ParseTuple(args, PyStreamStringType, &s1, &s2)) 
    {
      return PyDefaultReturn;
    }

    result = jaro_winkler(s1, s2, false);
    if (isnan(result)) /* test is double */
    {
      PyErr_NoMemory();
      return PyDefaultReturn;
    }

    return Py_BuildValue(PyDecimalType, result);
}

static PyObject * jellyfish_jaro_distance(PyObject *self, PyObject *args, PyObject *keywds)
{
    const char *s1, *s2;
    double result;

    if (!PyArg_ParseTuple(args, PyStreamStringType, &s1, &s2)) 
    {
      return PyDefaultReturn;
    }

    result = jaro_distance(s1, s2);
    if (isnan(result)) /* test is double */
    {
      PyErr_NoMemory();
      return PyDefaultReturn;
    }

    return Py_BuildValue(PyDecimalType, result);
}

static PyObject * jellyfish_hamming_distance(PyObject *self, PyObject *args, PyObject *keywds)
{
    const char *s1, *s2;
    unsigned result;

    if (!PyArg_ParseTuple(args, PyStreamStringType, &s1, &s2)) 
    {
      return PyDefaultReturn;
    }

    result = hamming_distance(s1, s2);

    return Py_BuildValue(PyIntegerType, result);
}

static PyObject* jellyfish_levenshtein_distance(PyObject *self, PyObject *args)
{
    const char *s1, *s2;
    /* int result; --> Will attempt to change it into double to uniformized the Error Management */ 
    double result ; 
    
    if (!PyArg_ParseTuple(args, PyStreamStringType, &s1, &s2)) 
    {
      return PyDefaultReturn;
    }

    result = levenshtein_distance(s1, s2);
    if (result == -1D) 
    {
      // levenshtein_distance only returns failure code (-1) on
      // failed malloc
      PyErr_NoMemory();
      return PyDefaultReturn;
    }

    return Py_BuildValue(PyShortIntegerType, result);
}

static PyObject* jellyfish_damerau_levenshtein_distance(PyObject *self, PyObject *args)
{
    const char *s1, *s2;
    /* int result; --> Will attempt to change it into double to uniformized the Error Management */ 
    double result ; 

    if (!PyArg_ParseTuple(args, PyStreamStringType, &s1, &s2)) 
    {
      return PyDefaultReturn;
    }

    result = damerau_levenshtein_distance(s1, s2);
    if (result == -1D) 
    {
      PyErr_NoMemory();
      return PyDefaultReturn;
    }

    return Py_BuildValue(PyShortIntegerType, result);
}

static PyObject* jellyfish_soundex(PyObject *self, PyObject *args)
{
    PyObject *pystr;
    PyObject *normalized;
    PyObject* ret;
    char *result;

    if (!PyArg_ParseTuple(args, PyObjectType, &pystr)) 
    {
      return PyDefaultReturn;
    }

    normalized = normalize(self, pystr);
    if (!normalized) 
    {
      return PyDefaultReturn;
    }

    result = soundex(UTF8_BYTES(normalized));
    Py_DECREF(normalized);

    if (!result) 
    {
      // soundex only fails on bad malloc
      PyErr_NoMemory();
      return PyDefaultReturn;
    }

    ret = Py_BuildValue(PyStringType, result);
    free(result);

    return ret;
}

static PyObject* jellyfish_metaphone(PyObject *self, PyObject *args)
{
    PyObject *pystr;
    PyObject *normalized;
    PyObject *ret;
    char *result;

    if (!PyArg_ParseTuple(args, PyObjectType, &pystr)) 
    {
        return PyDefaultReturn;
    }

    normalized = normalize(self, pystr);
    if (!normalized) 
    {
        return PyDefaultReturn;
    }

    result = metaphone((const char*)UTF8_BYTES(normalized));
    Py_DECREF(normalized);

    if (!result) 
    {
        // metaphone only fails on bad malloc
        PyErr_NoMemory();
        return PyDefaultReturn;
    }

    ret = Py_BuildValue(PyStringType, result);
    free(result);

    return ret;
}

static PyObject* jellyfish_match_rating_codex(PyObject *self, PyObject *args)
{
    const char *str;
    char *result;
    PyObject *ret;

    if (!PyArg_ParseTuple(args, PyStringType, &str)) 
    {
        return PyDefaultReturn;
    }

    result = match_rating_codex(str);
    if (!result) 
    {
        PyErr_NoMemory();
        return PyDefaultReturn;
    }

    ret = Py_BuildValue(PyStringType, result);
    free(result);

    return ret;
}
/* TODO : Implementing multiple value insertion, 
 * Using PyObject **kws, int kwcount, PyObject **defs, int defcount, PyObject *closure)
 * 
 */


static PyObject* jellyfish_match_rating_comparison(PyObject *self, PyObject *args)
{
    const char *str1, *str2;
    int result;

    if (!PyArg_ParseTuple(args, PyStreamStringType, &str1, &str2)) 
    {
        return PyDefaultReturn;
    }

    result = match_rating_comparison(str1, str2);
    
    if (result == -1) 
    {
        PyErr_NoMemory();
        return PyDefaultReturn;
    }

    return BooleanPythonTest( result );
    //~ if (result) 
    //~ {
      //~ return Py_True;
    //~ } 
    //~ else 
    //~ {
      //~ return Py_False;
    //~ }
}

static PyObject* jellyfish_nysiis(PyObject *self, PyObject *args)
{
    const char *str;
    char *result;
    PyObject *ret;

    if (!PyArg_ParseTuple(args, PyStringType, &str)) 
    {
      return PyDefaultReturn;
    }

    result = nysiis(str);
    if (!result) 
    {
      PyErr_NoMemory();
      return PyDefaultReturn;
    }

    ret = Py_BuildValue(PyStringType, result);
    free(result);

    return ret;
}

static PyObject* jellyfish_porter_stem(PyObject *self, PyObject *args)
{
    const char *str;
    char *result;
    PyObject *ret;
    struct stemmer *z;
    int end;
    

    if (!PyArg_ParseTuple(args, PyStringType, &str)) 
    {
      return PyDefaultReturn;
    }

    z = create_stemmer();
    if (!z) 
    {
      PyErr_NoMemory();
      return PyDefaultReturn;
    }

    result = strdup(str);
    if (!result) 
    {
      free_stemmer(z);
      PyErr_NoMemory();
      return PyDefaultReturn;
    }

    end = stem(z, result, strlen(result) - 1);
    result[end + 1] = PyStringEndChar;

    ret = Py_BuildValue(PyStringType, result);

    free(result);
    free_stemmer(z);

    return ret;
}


#if PY_MAJOR_VERSION >= 3
#define INITERROR return PyDefaultReturn

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "strfry",
    PyDefaultReturn,
    sizeof(struct jellyfish_state),
    jellyfish_methods,
    PyDefaultReturn,
    PyDefaultReturn,
    PyDefaultReturn,
    PyDefaultReturn
};

PyObject* PyInit_jellyfish(void)
#else

#define INITERROR return

PyMODINIT_FUNC initjellyfish(void)
#endif
{
    PyObject *unicodedata;
    int IntModuleCacheCommand ;
    const char *ModuleCache[3] = [ "import GenericCache", 
                                   "from GenericCache.decorators import cached", 
                                   "from GenericCache.GenericCache import GenericCache" ] ;
    

#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule(MODULENAME, jellyfish_methods);
    for( intCountCommand=0 ; intCountCommand <= 3)
    IntModuleCacheCommand = PyRun_SimpleString(ModuleCache[intCountCommand])
#endif

    if (module == PyDefaultReturn) 
    {
        INITERROR;
    }

    unicodedata = PyImport_ImportModule(CHARSETMODULE);
    if (!unicodedata) 
    {
        INITERROR;
    }

    GETSTATE(module)->unicodedata_normalize =
        PyObject_GetAttrString(unicodedata, "normalize");
    Py_DECREF(unicodedata);

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}

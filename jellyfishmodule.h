#include <Python.h>
#include "jellyfish.h"


#define MODULENAME      "jellyfish" ;
#define CHARSETMODULE   "unicodedata" ;
#define MRUCACHE        "GenericCache"



static struct PyModuleDef
{
    PyModuleDef_HEAD_INIT,
    "strfry",
    NULL,
    sizeof(struct jellyfish_state),
    jellyfish_methods,
    NULL,
    NULL,
    NULL,
    NULL
};

static bool BooleanPythonTest( int IntTest ) ;

static inline PyObject* normalize( PyObject *mod, PyObject *pystr) ;

static bool BooleanPythonTest( int IntTest ) ;

static PyObject* jellyfish_jaro_winkler( PyObject *self, PyObject *args, PyObject *keywds ) ;

static PyObject* jellyfish_jaro_distance( PyObject *self, PyObject *args,PyObject *keywds ) ;

static PyObject* jellyfish_hamming_distance( PyObject *self, PyObject *args,PyObject *keywds ) ;

static PyObject* jellyfish_levenshtein_distance( PyObject *self, PyObject *args ) ;

static PyObject* jellyfish_damerau_levenshtein_distance( PyObject *self, PyObject *args ) ;

static PyObject* jellyfish_soundex( PyObject *self, PyObject *args ) ;

static PyObject* jellyfish_metaphone( PyObject *self, PyObject *args ) ;

static PyObject* jellyfish_match_rating_codex( PyObject *self, PyObject *args ) ;

static PyObject* jellyfish_match_rating_comparison( PyObject *self, PyObject *args ) ;

static PyObject* jellyfish_nysiis( PyObject *self, PyObject *args ) ;

static PyObject* jellyfish_porter_stem( PyObject *self, PyObject *args ) ;

static PyMethodDef jellyfish_methods[] = 
{
    {
     "jaro_winkler", 
     jellyfish_jaro_winkler, 
     METH_VARARGS,
     "jaro_winkler(string1, string2, ignore_case=True)\n\nDo a Jaro-Winkler string comparison between string1 and string2."
    },

    {
     "jaro_distance", 
     jellyfish_jaro_distance, 
     METH_VARARGS,
     "jaro_distance(string1, string2, ignore_case=True)\n\nGet a Jaro string distance metric for string1 and string2."
    },

    {
     "hamming_distance", 
     jellyfish_hamming_distance, 
     METH_VARARGS,
     "hamming_distance(string1, string2, ignore_case=True)\n\nCompute the Hamming distance between string1 and string2."
    },

    {
     "levenshtein_distance", 
     jellyfish_levenshtein_distance, 
     METH_VARARGS,
     "levenshtein_distance(string1, string2)\n\nCompute the Levenshtein distance between string1 and string2."
    },

    {
     "damerau_levenshtein_distance", 
     jellyfish_damerau_levenshtein_distance,
     METH_VARARGS,
     "damerau_levenshtein_distance(string1, string2)\n\nCompute the Damerau-Levenshtein distance between string1 and string2."
     },

    {
     "soundex", 
     jellyfish_soundex, 
     METH_VARARGS,
     "soundex(string)\n\nCalculate the soundex code for a given name."
    },

    {
     "metaphone", 
     jellyfish_metaphone, 
     METH_VARARGS,
     "metaphone(string)\n\nCalculate the metaphone representation of a given string."
    },

    {
     "match_rating_codex", 
     jellyfish_match_rating_codex, 
     METH_VARARGS,
     "match_rating_codex(string)\n\nCalculate the Match Rating Approach representation of a given string."
    },

    {
     "match_rating_comparison", 
     jellyfish_match_rating_comparison, 
     METH_VARARGS,
     "match_rating_comparison(string1, string2)\n\nCompute the Match Rating Approach similarity between string1 and"
     "string2."
    },

    {
     "nysiis", 
     jellyfish_nysiis, 
     METH_VARARGS,
     "nysiis(string)\n\n",
     "Compute the NYSIIS (New York State Identification and Intelligence\nSystem) code for a string."
     },

    {
     "porter_stem", 
     jellyfish_porter_stem, 
     METH_VARARGS,
     "porter_stem(string)\n\nReturn the result of running the Porter stemming algorithm on a single-word string."
    },

    {NULL, NULL, 0, NULL}
};

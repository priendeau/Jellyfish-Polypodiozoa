/* jellyfishmodule.i */
%module _jellyfishmodule
%{
/* Put header files here or function declarations like below */

extern static struct PyModuleDef ; 
extern static bool BooleanPythonTest( int IntTest ) ;
extern static inline PyObject* normalize( PyObject *mod, PyObject *pystr) 
extern static bool BooleanPythonTest( int IntTest )
extern static PyObject* jellyfish_jaro_winkler( PyObject *self, PyObject *args, PyObject *keywds ) ;
extern static PyObject* jellyfish_jaro_distance( PyObject *self, PyObject *args,PyObject *keywds ) ;
extern static PyObject* jellyfish_hamming_distance( PyObject *self, PyObject *args,PyObject *keywds ) ;
extern static PyObject* jellyfish_levenshtein_distance( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_damerau_levenshtein_distance( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_soundex( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_metaphone( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_match_rating_codex( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_match_rating_comparison( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_nysiis( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_porter_stem( PyObject *self, PyObject *args ) ;
%}


extern static struct PyModuleDef ; 
extern static bool BooleanPythonTest( int IntTest ) ;
extern static inline PyObject* normalize( PyObject *mod, PyObject *pystr) 
extern static bool BooleanPythonTest( int IntTest )
extern static PyObject* jellyfish_jaro_winkler( PyObject *self, PyObject *args, PyObject *keywds ) ;
extern static PyObject* jellyfish_jaro_distance( PyObject *self, PyObject *args,PyObject *keywds ) ;
extern static PyObject* jellyfish_hamming_distance( PyObject *self, PyObject *args,PyObject *keywds ) ;
extern static PyObject* jellyfish_levenshtein_distance( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_damerau_levenshtein_distance( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_soundex( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_metaphone( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_match_rating_codex( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_match_rating_comparison( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_nysiis( PyObject *self, PyObject *args ) ;
extern static PyObject* jellyfish_porter_stem( PyObject *self, PyObject *args ) ;


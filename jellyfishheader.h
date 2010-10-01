#include <Python.h>
#include <ruby.h>

#define PyStreamStringType    "ss"
#define PyAnsiStringType      "s0"
#define PyStringType          "s"
#define PyDecimalType         "d"
#define PyIntegerType         "I"
#define PyShortIntegerType    "i"
#define PyObjectType          "O"


#define PyStringEndChar       '\0'

PyObject* PyDefaultReturn = NULL ;

struct jellyfish_state 
{
    PyObject *unicodedata_normalize;
};

/*
 * This is the Transfert structure between different module 
 * and Python Core-Tentaticle between different 
 * modele... 
 * 
 * */
struct jellyfish_ObjectReturn 
{
    /* ANSI C/C++ Variable requirement */
    double          DoubleResultReturn ;
    int             IntResultReturn ;
    char*           StringReturn ;
    /* Python Variable requirement */
    PyObject        *ObjectErrorReturn ; 
    /* Ruby Variable requirement */
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

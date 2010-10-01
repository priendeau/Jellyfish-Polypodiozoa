#include "jellyfish.h"

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

//size_t hamming_distance(const char *s1, const char *s2) 
PyObjPolypodiozoa* hamming_distance(const char *s1, const char *s2) 
{
    unsigned distance = 0;

    for (; *s1 && *s2; s1++, s2++) {
        if (*s1 != *s2) {
            distance++;
        }
    }

    for ( ; *s1; s1++) {
        distance++;
    }

    for ( ; *s2; s2++) {
        distance++;
    }

    return distance;
}


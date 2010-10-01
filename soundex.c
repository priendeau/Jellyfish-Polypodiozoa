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

char* soundex(const char *str)
{
    const char *s;
    char c, prev;
    int i;
    char *result = calloc(5, sizeof(char));

    if (!result) {
        return NULL;
    }

    if (!*str) {
        return result;
    }

    prev = '\0';
    for(s = str, i = 1; *s && i < 4; s++) {
        switch(tolower(*s)) {
        case 'b':
        case 'f':
        case 'p':
        case 'v':
            c = '1';
            break;
        case 'c':
        case 'g':
        case 'j':
        case 'k':
        case 'q':
        case 's':
        case 'x':
        case 'z':
            c = '2';
            break;
        case 'd':
        case 't':
            c = '3';
            break;
        case 'l':
            c = '4';
            break;
        case 'm':
        case 'n':
            c = '5';
            break;
        case 'r':
            c = '6';
            break;
        default:
            c = '\0';
        }

        if (c && c != prev && s != str) {
            result[i++] = c;
        }
        prev = c;
    }

    for ( ; i < 4; i++) {
        result[i] = '0';
    }

    result[0] = toupper(*str);

    return result;
}

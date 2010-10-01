#include <ruby.h>
#include "jellyfish.h"

VALUE jellyfish = Qnil;
VALUE c_jellyfish = Qnil;
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


VALUE method_soundex(int args, VALUE *argv, VALUE self) 
{
    const char *str;
    char *result;
    struct jellyfish_ObjectReturn ReturnResult ;
    VALUE *rb_res;
    
    if (TYPE(*argv) == T_STRING) 
    {
      str = RSTRING(*argv)->ptr;
      result = soundex(str);
      rb_res = rb_str_new2(result);
      
      free(result);
    } 
    else 
    {
      ReturnResult.
      rb_raise(rb_eTypeError, "expects a string");
    }
    ReturnResult.StringReturn=rb_res ;
    return rb_res;
}

void Init_jellyfish()
{
  jellyfish = rb_define_module("Jellyfish");
  //  c_jellyfish = rb_define_class_under(jellyfish, "J", rb_cObject);
  rb_define_module_function(jellyfish, "soundex", method_soundex, -1);
}


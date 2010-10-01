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

#define ISVOWEL(a) ((a) == 'a' || (a) == 'e' || (a) == 'i' || \
                    (a) == 'o' || (a) == 'u')

//struct jellyfish_ObjectReturn metaphone(const char *str)
PyObjPolypodiozoa* 
{
    const char *s;
    char c, next, temp = '\0';
    struct jellyfish_ObjectReturn ResultObj ;

    // Worst case (a string of all x's) will result in a
    // metaphone twice as large as the original string
    char *result = calloc(strlen(str) * 2 + 1, sizeof(char));
    char *r;

    if (!result) 
    {
      //return NULL;
      ResultObj.ObjectErrorReturn = PyDefaultReturn ;
    }

    c = tolower(*str);
    if (c) 
    {
      next = tolower(*(str + 1));

      if ((c == 'k' && next == 'n') || (c == 'g' && next == 'n') || (c == 'p' && next == 'n') || 
      (c == 'a' && next == 'c') || (c == 'w' && next == 'r') || (c == 'a' && next == 'e')) 
        { str++; }
    }


    next = tolower(*str);
    for (s = str, r = result; next; s++) 
    {
        c = next;
        next = tolower(*(s + 1));

        if (c == next && c != 'c') 
          { continue; }

        switch(c) 
        {
          case 'a':
          case 'e':
          case 'i':
          case 'o':
          case 'u':
              if (s == str || *(s - 1) == ' ') 
                { *r++ = toupper(c); }
              break;
          case 'b':
              if (!(s > str && *(s - 1) == 'm') || next) 
                { *r++ = 'B'; }
              break;
          case 'c':
              if ((next == 'i' && *(s + 2) == 'a') || next == 'h') 
                { *r++ = 'X'; next = tolower(*(++s + 1)); } 
              else 
                if (next == 'i' || next == 'e' || next == 'y') 
                  { *r++ = 'S'; next = tolower(*(++s + 1)); } 
                else 
                  { *r++ = 'K'; }
              break;
          case 'd':
              if (next == 'g' && ((temp = *(s + 2)) == 'e' || temp == 'y' || temp == 'i')) 
                { *r++ = 'J'; s += 2; next = tolower(*(s + 1)); } 
              else 
                { *r++ = 'T'; }
              break;
          case 'f':
              *r++ = 'F';
              break;
          case 'g':
              if (next == 'i' || next == 'e' || next == 'y' ) 
                { *r++ = 'J'; } 
              else 
                if(next != 'h' && next != 'n') 
                  { *r++ = 'K'; } 
              else 
                if(next == 'h' && (temp = tolower(*(s + 2))) && !(ISVOWEL(temp))) 
                  { s++; next = tolower(*(s + 1)); } 
                else 
                  if(next != 'n') 
                    { *r++ = 'K'; }
              break;
          case 'h':
              if (s == str || ISVOWEL(next) || (temp = tolower(*(s - 1)) && ISVOWEL(temp))) 
                { *r++ = 'H'; }
              break;
          case 'j':
              *r++ = 'J';
              break;
          case 'k':
              if (s == str || *(s - 1) != 'c') 
                { *r++ = 'K'; }
              break;
          case 'l':
              *r++ = 'L';
              break;
          case 'm':
              *r++ = 'M';
              break;
          case 'n':
              *r++ = 'N';
              break;
          case 'p':
              if (next == 'h') 
                { *r++ = 'F'; next = tolower(*(++s + 1)); } 
              else 
                { *r++ = 'P'; }
              break;
          case 'q':
              *r++ = 'K';
              break;
          case 'r':
              *r++ = 'R';
              break;
          case 's':
              if (next == 'h') 
                { *r++ = 'X'; next = tolower(*(++s + 1)); }
              else 
                if (next == 'i' && (temp = tolower(*(s + 2))) && (temp == 'o' || temp == 'a')) 
                  { *r++ = 'X'; s += 2; next = tolower(*(s + 1)); } 
                else 
                  { *r++ = 'S'; }
              break;
          case 't':
              if (next == 'i' && ((temp = tolower(*(s + 2))) == 'a' || temp == 'o')) 
                { *r++ = 'X'; } 
              else 
                if(next == 'h') 
                  { *r++ = '0'; next = tolower(*(++s + 1)); }
                else 
                  if(next != 'c' || (temp = tolower(*(s + 2))) != 'h') 
                    { *r++ = 'T'; }
              break;
          case 'v':
              *r++ = 'F';
              break;
          case 'w':
              if (s == str && next == 'h') 
                { next = tolower(*(++s + 1)); }
              if (ISVOWEL(next)) 
                { *r++ = 'W'; }
              break;
          case 'x':
              if (s == str) 
              {
                if (next == 'h' || (next == 'i' && (temp = tolower(*(s + 2))) && (temp == 'o' || temp == 'a'))) 
                  { *r++ = 'X'; } 
                else 
                  { *r++ = 'S'; }
              } 
              else 
                { *r++ = 'K';  *r++ = 'S'; }
              break;
          case 'y':
              if (ISVOWEL(next)) 
                { *r++ = 'Y'; }
              break;
          case 'z':
              *r++ = 'S';
              break;
          case ' ':
              if (*r != ' ') 
                { *r++ = ' '; }
              break;
        }
    }
    ResultObj.DoubleResultReturn = result ;
    ResultObj.IntResultReturn = result ;
    ResultObj.ObjectErrorReturn = PyDefaultReturn ;
    ResultObj.StringReturn = result ;
    return result;
}

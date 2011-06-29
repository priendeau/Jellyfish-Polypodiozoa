#!/usr/bin/env python

import os, sys, re
from setuptools import setup, Extension
import distutils.ccompiler 

CompilerOS=distutils.ccompiler.get_default_compiler()

CompilerOption=list()


  

long_description = open('README.rst').read()

DictRegularExpr={
  'MVS':{
    'path':re.compile(r'(?ui).(Microsoft Visual Studio [0-9]+.[0-9]+)(\\[A-Z]+)'),
    'iscpp':re.compile(r'(?ui).\\VC')
    }
  }

MSVCPath = os.environ.get('VCInstallDir')
MSVCPathSource=str()
MSVCPathIncludePath=str()

if MSVCPath != None :
  print "Microsoft Visual Dev Installation Path: %s\n" % ( MSVCPath ) 
  MSVCPathSource = DictRegularExpr['MVS']['path'].sub( '\\\\\\1', MSVCPath )
  if CompilerOS == "msvc":
    CompilerOption.append( "/W4" )
    CompilerOption.append( "/EHsc" )
    CompilerOption.append( "/GR" )
    CompilerOption.append( "/Zc:forScope,wchar_t" )

  if DictRegularExpr['MVS']['iscpp'].search( MSVCPath ):
    MSVCPathIncludePath="%s\\include" % ( MSVCPath )

PlateformeName = sys.platform
_win32              ='win32'
_cygwin             ='cygwin'
_any                ='any'
_name               ='name'
_version            ='version'
_platforms          ='platforms'
_description        ='description'
_url                ='url'
_long_description   ='long_description'
_classifiers        ='classifiers'
_ext_modules        ='ext_modules'

ClassifierList=["Development Status :: 4 - Beta"         ,
                "Intended Audience :: Developers"        ,
                "License :: OSI Approved :: BSD License" ,
                "Natural Language :: English"            ,
                "Operating System :: OS Independent"     ,
                "Programming Language :: Python"         ,
                "Topic :: Text Processing :: Linguistic" ]

VersionID="0.1.2a"

UrlID="https://github.com/priendeau/Jellyfish-Polypodiozoa"

DescriptionTuple=("a library for doing approximate and phonetic matching of strings.")

NameModuleSetup="Jellyfish-Polypodiozoa"

PlatformListConf=[ _win32, _cygwin, _any ]



__DICTOSCONF__={
  _win32:{
    _name:NameModuleSetup,
    _version:VersionID,
    _platforms:PlatformListConf,
    _description:DescriptionTuple,
    _url:UrlID,
    _long_description:long_description,
    _classifiers:ClassifierList,
    _ext_modules:[ Extension('jellyfish', 
                    ['jellyfishmodule.c'],
                    extra_compile_args = CompilerOption ,
                    include_dirs=[ MSVCPathIncludePath,
                                   'c:\\vm\\os\\microsoft\\include\\boost\\boost_1_44\\boost'],
                    libraries=['']),
        Extension('_jellyfishheader', 
                  ['jellyfishheader.i'] , 
                  extra_compile_args = CompilerOption,
                  swig_opts=['-modern'], 
                  include_dirs=[ MSVCPathIncludePath,
                                 'c:\\vm\\os\\microsoft\\include\\boost\\boost_1_44\\boost'],
                  libraries=[''] ),
        Extension('_jellyfishmodule', 
                  ['jellyfishmodule.i'] , 
                  extra_compile_args = CompilerOption,
                  swig_opts=['-modern'], 
                  include_dirs=[ MSVCPathIncludePath,
                                 'c:\\vm\\os\\microsoft\\include\\boost\\boost_1_44\\boost' ],
                  libraries=[''] ) ],
    },
  _cygwin:{
    _name:NameModuleSetup,
    _version:VersionID,
    _platforms:PlatformListConf,
    _description:DescriptionTuple,
    _url:UrlID,
    _long_description:long_description,
    _classifiers:ClassifierList,
    _ext_modules:[ Extension('jellyfish', 
                    ['jellyfishmodule.c'], 
                    extra_compile_args = CompilerOption ,
                    include_dirs=[ '/usr/include',
                                   '/cygdrive/c/vm/os/microsoft/include/boost/boost_1_44/boost'],
                    libraries=['']),
        Extension('_jellyfishheader', 
                  ['jellyfishheader.i'] , 
                  extra_compile_args = CompilerOption ,
                  swig_opts=['-modern'], 
                  include_dirs=[ '/usr/include',
                                 '/cygdrive/c/vm/os/microsoft/include/boost/boost_1_44/boost'],
                    libraries=[''] ),
        Extension('_jellyfishmodule', 
                  ['jellyfishmodule.i'] , 
                  extra_compile_args = CompilerOption ,
                  swig_opts=['-modern'], 
                  include_dirs=[ '/usr/include',
                                 '/cygdrive/c/vm/os/microsoft/include/boost/boost_1_44/boost'],
                    libraries=[''] ) ]
    },
  _any:{ }
}


setup(name          =__DICTOSCONF__[PlateformeName]['name']               ,
      version       =__DICTOSCONF__[PlateformeName]['version']            ,
      platforms     =__DICTOSCONF__[PlateformeName]['platforms']          ,
      description   =__DICTOSCONF__[PlateformeName]['description']        ,
      url           =__DICTOSCONF__[PlateformeName]['url']                ,
      long_description=__DICTOSCONF__[PlateformeName]['long_description'] ,
      classifiers   =__DICTOSCONF__[PlateformeName]['classifiers']        ,
      ext_modules   =__DICTOSCONF__[PlateformeName]['ext_modules']        )

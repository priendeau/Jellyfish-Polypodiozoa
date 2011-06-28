#!/usr/bin/env python
from setuptools import setup, Extension

long_description = open('README.rst').read()

setup(name="jellyfish",
      version="0.1.2a",
      platforms=["any"],
      description=("a library for doing approximate and "
                   "phonetic matching of strings."),
      url="http://github.com/sunlightlabs/jellyfish",
      long_description=long_description,
      classifiers=["Development Status :: 4 - Beta",
                   "Intended Audience :: Developers",
                   "License :: OSI Approved :: BSD License",
                   "Natural Language :: English",
                   "Operating System :: OS Independent",
                   "Programming Language :: Python",
                   "Topic :: Text Processing :: Linguistic"],
      ext_modules=[
        Extension("jellyfish", ['jellyfishmodule.c']),
        Extension('_jellyfishheader', ['jellyfishheader.i'] , swig_opts=['-modern', '-I /usr/include']),
        Extension('_jellyfishmodule', ['jellyfishmodule.i'] , swig_opts=['-modern', '-I /usr/include'])
        ]
)

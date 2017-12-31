# setup.py
# Author: Thomas MINIER - MIT License 2017-2018
from distutils.core import setup, Extension
from os import listdir
from shutil import rmtree
from subprocess import call
import pybind11

__pyhdt_version__ = "1.0.0"


def list_files(path, extension=".cpp", exclude="-1"):
    """List paths to all files that ends with a given extension"""
    return ["%s/%s" % (path, f) for f in listdir(path) if f.endswith(extension) and (not f.endswith(exclude))]

# pyHDT source files
sources = [
    "src/hdt.cpp"
]

# HDT source files
sources += list_files("hdt-cpp/hdt-lib/src/bitsequence")
sources += list_files("hdt-cpp/hdt-lib/src/dictionary")
sources += list_files("hdt-cpp/hdt-lib/src/hdt")
sources += list_files("hdt-cpp/hdt-lib/src/header")
sources += list_files("hdt-cpp/hdt-lib/src/huffman")
sources += list_files("hdt-cpp/hdt-lib/src/libdcs")
sources += list_files("hdt-cpp/hdt-lib/src/libdcs/fmindex")
sources += list_files("hdt-cpp/hdt-lib/src/rdf")
sources += list_files("hdt-cpp/hdt-lib/src/sequence")
sources += list_files("hdt-cpp/hdt-lib/src/triples")
sources += list_files("hdt-cpp/hdt-lib/src/util")

# pybind11 + pyHDT headers
include_dirs = [
    pybind11.get_include(),
    pybind11.get_include(True),
    "include/"
]

# HDT-lib + libcds headers
include_dirs += [
    "hdt-cpp/hdt-lib/include/",
    "hdt-cpp/hdt-lib/src/dictionary/",
    "hdt-cpp/libcds-v1.0.12/src/static/bitsequence",
    "hdt-cpp/libcds-v1.0.12/src/static/coders",
    "hdt-cpp/libcds-v1.0.12/src/static/mapper",
    "hdt-cpp/libcds-v1.0.12/src/static/permutation",
    "hdt-cpp/libcds-v1.0.12/src/static/sequence",
    "hdt-cpp/libcds-v1.0.12/src/utils"
]

libraries = ['cds']
library_dirs = ['hdt-cpp/libcds-v1.0.12/lib']

# Need to build in c++11 minimum
# TODO add a check to use c++14 or c++17 if available
extra_compile_args = ["-std=c++11"]

# build libcds first
call(["make", "-C", "hdt-cpp/libcds-v1.0.12"])

# build HDT extension
hdt_extension = Extension("hdt", sources=sources, include_dirs=include_dirs,
                          libraries=libraries, library_dirs=library_dirs,
                          extra_compile_args=extra_compile_args, language='c++')

setup(
    name="hdt",
    version=__pyhdt_version__,
    author="Thomas Minier",
    author_email="thomas.minier@univ-nantes.fr",
    url="https://github.com/Callidon/pyHDT",
    description="Read and query HDT document with ease in Python",
    license="MIT",
    ext_modules=[hdt_extension]
)

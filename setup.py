# setup.py
# Author: Thomas MINIER - MIT License 2017-2018
from setuptools import setup, Extension
from os import listdir
import pybind11

__pyhdt_version__ = "1.1.0"

with open('README.rst') as file:
    long_description = file.read()


def list_files(path, extension=".cpp", exclude="S.cpp"):
    """List paths to all files that ends with a given extension"""
    return ["%s/%s" % (path, f) for f in listdir(path) if f.endswith(extension) and (not f.endswith(exclude))]


# pyHDT source files
sources = [
    "src/hdt.cpp",
    "src/hdt_document.cpp",
    "src/hdt_triple_iterator.cpp",
    "src/triple_iterator.cpp",
    "src/tripleid_iterator.cpp"
]

# HDT source files
sources += list_files("hdt-cpp-1.3.2/libcds/src/static/bitsequence")
sources += list_files("hdt-cpp-1.3.2/libcds/src/static/coders")
sources += list_files("hdt-cpp-1.3.2/libcds/src/static/mapper")
sources += list_files("hdt-cpp-1.3.2/libcds/src/static/sequence")
sources += list_files("hdt-cpp-1.3.2/libcds/src/static/permutation")
sources += list_files("hdt-cpp-1.3.2/libcds/src/utils")
sources += list_files("hdt-cpp-1.3.2/libhdt/src/bitsequence")
sources += list_files("hdt-cpp-1.3.2/libhdt/src/dictionary")
sources += list_files("hdt-cpp-1.3.2/libhdt/src/hdt")
sources += list_files("hdt-cpp-1.3.2/libhdt/src/header")
sources += list_files("hdt-cpp-1.3.2/libhdt/src/huffman")
sources += list_files("hdt-cpp-1.3.2/libhdt/src/libdcs")
sources += list_files("hdt-cpp-1.3.2/libhdt/src/libdcs/fmindex")
sources += list_files("hdt-cpp-1.3.2/libhdt/src/rdf")
sources += list_files("hdt-cpp-1.3.2/libhdt/src/sequence")
sources += list_files("hdt-cpp-1.3.2/libhdt/src/triples")
sources += list_files("hdt-cpp-1.3.2/libhdt/src/util")

# pybind11 + pyHDT + libcds +  HDT-lib headers
include_dirs = [
    pybind11.get_include(),
    pybind11.get_include(True),
    "include/",
    "hdt-cpp-1.3.2/libhdt/include/",
    "hdt-cpp-1.3.2/libhdt/src/dictionary/",
    "hdt-cpp-1.3.2/libcds/include/",
    "hdt-cpp-1.3.2/libcds/src/static/bitsequence",
    "hdt-cpp-1.3.2/libcds/src/static/coders",
    "hdt-cpp-1.3.2/libcds/src/static/mapper",
    "hdt-cpp-1.3.2/libcds/src/static/permutation",
    "hdt-cpp-1.3.2/libcds/src/static/sequence",
    "hdt-cpp-1.3.2/libcds/src/utils"
]

# Need to build in c++11 minimum
# TODO add a check to use c++14 or c++17 if available
extra_compile_args = ["-std=c++11"]

# build HDT extension
hdt_extension = Extension("hdt", sources=sources, include_dirs=include_dirs,
                          extra_compile_args=extra_compile_args, language='c++')

setup(
    name="hdt",
    version=__pyhdt_version__,
    author="Thomas Minier",
    author_email="thomas.minier@univ-nantes.fr",
    url="https://github.com/Callidon/pyHDT",
    description="Read and query HDT document with ease in Python",
    long_description=long_description,
    keywords=["hdt", "rdf", "semantic web", "search"],
    license="MIT",
    install_requires=['pybind11==2.2.1'],
    ext_modules=[hdt_extension]
)

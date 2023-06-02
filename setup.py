# setup.py
# Author: Thomas MINIER - MIT License 2017-2019
from setuptools import find_packages, setup, Extension
from os import listdir, remove
from shutil import unpack_archive, move, rmtree
import urllib.request
import pybind11

__rdflib_hdt_version__ = "3.1"

def download_hdt_and_unzip():
    print("Downloading HDT...")
    urllib.request.urlretrieve("https://github.com/rdfhdt/hdt-cpp/archive/v1.3.3.zip", "v1.3.3.zip")
    unpack_archive("v1.3.3.zip", "tmp")
    move("tmp/hdt-cpp-1.3.3", "hdt-cpp-1.3.3")
    rmtree("tmp")

download_hdt_and_unzip()

def list_files(path: str, extension=".cpp", exclude="S.cpp"):
    """List paths to all files that ends with a given extension"""
    return ["%s/%s" % (path, f) for f in listdir(path) if f.endswith(extension) and (not f.endswith(exclude))]


# pyHDT source files
sources = [
    "src/hdt.cpp",
    "src/hdt_document.cpp",
    "src/triple_iterator.cpp",
    "src/triple_iterator_bytes.cpp",
    "src/tripleid_iterator.cpp",
    "src/join_iterator.cpp",
    "src/join_iterator_bytes.cpp"
]

# HDT source files
sources += list_files("hdt-cpp-1.3.3/libcds/src/static/bitsequence")
sources += list_files("hdt-cpp-1.3.3/libcds/src/static/coders")
sources += list_files("hdt-cpp-1.3.3/libcds/src/static/mapper")
sources += list_files("hdt-cpp-1.3.3/libcds/src/static/sequence")
sources += list_files("hdt-cpp-1.3.3/libcds/src/static/permutation")
sources += list_files("hdt-cpp-1.3.3/libcds/src/utils")
sources += list_files("hdt-cpp-1.3.3/libhdt/src/bitsequence")
sources += list_files("hdt-cpp-1.3.3/libhdt/src/dictionary")
sources += list_files("hdt-cpp-1.3.3/libhdt/src/hdt")
sources += list_files("hdt-cpp-1.3.3/libhdt/src/header")
sources += list_files("hdt-cpp-1.3.3/libhdt/src/huffman")
sources += list_files("hdt-cpp-1.3.3/libhdt/src/libdcs")
sources += list_files("hdt-cpp-1.3.3/libhdt/src/libdcs/fmindex")
sources += list_files("hdt-cpp-1.3.3/libhdt/src/rdf")
sources += list_files("hdt-cpp-1.3.3/libhdt/src/sequence")
sources += list_files("hdt-cpp-1.3.3/libhdt/src/triples")
sources += list_files("hdt-cpp-1.3.3/libhdt/src/util")
sources += list_files("hdt-cpp-1.3.3/libhdt/src/sparql")

# pybind11 + pyHDT + libcds + HDT-lib headers
include_dirs = [
    pybind11.get_include(),
    pybind11.get_include(True),
    "include/",
    "hdt-cpp-1.3.3/libhdt/include/",
    "hdt-cpp-1.3.3/libhdt/src/dictionary/",
    "hdt-cpp-1.3.3/libhdt/src/sparql/",
    "hdt-cpp-1.3.3/libcds/include/",
    "hdt-cpp-1.3.3/libcds/src/static/bitsequence",
    "hdt-cpp-1.3.3/libcds/src/static/coders",
    "hdt-cpp-1.3.3/libcds/src/static/mapper",
    "hdt-cpp-1.3.3/libcds/src/static/permutation",
    "hdt-cpp-1.3.3/libcds/src/static/sequence",
    "hdt-cpp-1.3.3/libcds/src/utils"
]

# Need to build in c++11 minimum
# TODO add a check to use c++14 or c++17 if available
extra_compile_args = ["-std=c++11"]

# build HDT extension
hdt_extension = Extension("hdt",
                          sources=sources,
                          include_dirs=include_dirs,
                          extra_compile_args=extra_compile_args,
                          language='c++')

setup(
    version=__rdflib_hdt_version__,
    packages=find_packages(exclude=["tests"]),
    ext_modules=[hdt_extension]
)

print("Cleaning up...")
rmtree("hdt-cpp-1.3.3")
remove("v1.3.3.zip")

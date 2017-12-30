from distutils.core import setup, Extension
from os import listdir
from shutil import rmtree


def listFiles(path, extension=".cpp"):
    return ["%s/%s" % (path, f) for f in listdir(path) if f.endswith(extension)]

sources = [
    "src/hdt.cpp"
]

sources += listFiles("hdt-cpp/hdt-lib/src/bitsequence")
sources += listFiles("hdt-cpp/hdt-lib/src/hdt")
sources += listFiles("hdt-cpp/hdt-lib/src/header")
sources += listFiles("hdt-cpp/hdt-lib/src/huffman")
sources += listFiles("hdt-cpp/hdt-lib/src/libdcs")
sources += listFiles("hdt-cpp/hdt-lib/src/libdcs/fmindex")
sources += listFiles("hdt-cpp/hdt-lib/src/rdf")
sources += listFiles("hdt-cpp/hdt-lib/src/sequence")
sources += listFiles("hdt-cpp/hdt-lib/src/triples")
sources += listFiles("hdt-cpp/hdt-lib/src/util")
sources += listFiles("hdt-cpp/libcds-v1.0.12/src/static/bitsequence")
sources += listFiles("hdt-cpp/libcds-v1.0.12/src/static/coders")
sources += listFiles("hdt-cpp/libcds-v1.0.12/src/static/mapper")
sources += listFiles("hdt-cpp/libcds-v1.0.12/src/static/sequence")

include_dirs = [
    "hdt-cpp/hdt-lib/include/",
    "hdt-cpp/hdt-lib/src/dictionary/",
    "hdt-cpp/libcds-v1.0.12/src/static/bitsequence",
    "hdt-cpp/libcds-v1.0.12/src/static/coders",
    "hdt-cpp/libcds-v1.0.12/src/static/mapper",
    "hdt-cpp/libcds-v1.0.12/src/static/permutation",
    "hdt-cpp/libcds-v1.0.12/src/static/sequence",
    "hdt-cpp/libcds-v1.0.12/src/utils"
]

# clean build folder
# rmtree("build")

# Need to build in c++11 minimum
# TODO add a check to use c++14 or c++17 if available
extra_compile_args = ["-std=c++11"]

extension_mod = Extension("hdt", sources=sources, include_dirs=include_dirs, extra_compile_args=extra_compile_args, language='c++')

setup(name="hdt", ext_modules=[extension_mod])

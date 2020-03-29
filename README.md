# rdflib-hdt

![Build status](https://github.com/RDFLib/rdflib-hdt/workflows/Python%20integration%20tests/badge.svg?branch=master) [![Documentation Status](https://readthedocs.org/projects/pyhdt/badge/?version=latest)](https://callidon.github.io/pyHDT) [![PyPI version](https://badge.fury.io/py/hdt.svg)](https://badge.fury.io/py/hdt)

A Store back-end for [rdflib](https://github.com/RDFLib) to allow for reading and querying HDT documents.

[Online Documentation](https://callidon.github.io/pyHDT)

# Requirements

* Python *version 3.6.4 or higher*
* [pip](https://pip.pypa.io/en/stable/)
* **gcc/clang** with **c++11 support**
* **Python Development headers**
> You should have the `Python.h` header available on your system.   
> For example, for Python 3.6, install the `python3.6-dev` package on Debian/Ubuntu systems.

Then, install the [pybind11 library](http://pybind11.readthedocs.io/en/stable/)
```
pip install pybind11
```

# Installation

Installation in a [virtualenv](https://virtualenv.pypa.io/en/stable/) is **strongly advised!**

## PyPi installation (recommended)

```
pip install hdt
```

## Manual installation

```
git clone https://github.com/Callidon/pyHDT
cd pyHDT/
./install.sh
```

# Getting started

You can use the `rdflib-hdt` library in two modes: as an rdflib Graph or as a raw HDT document

## Graph usage

```python
from rdflib_hdt import HDTGraph
from rdflib.namespace import FOAF

# Load an HDT file.
# Missing indexes are generated automatically, add False as the second argument to disable them
graph = HDTGraph("test.hdt")

# Display some metadata about the HDT document itself
print(f"number of triples: {len(graph)}")
print(f"number of subjects: ${graph.nb_subjects}")
print(f"number of predicates: {graph.nb_predicates}")
print(f"number of objects: {graph.nb_objects}")
print(f"number of shared subject-object: {graph.nb_shared}")

# Fetch all triples that matches { ?s foaf:name ?o }
# Use None to indicates variables
triples = graph.triples((None, FOAF("name"), None))

print(f"cardinality of (?s foaf:name ?o): {len(triples)}")
for s, p, o in triples:
  print(triple)
```

## HDT Document usage

```python
from rdflib_hdt import Document

 # Load an HDT file.
 # Missing indexes are generated automatically, add False as the second argument to disable them
document = Document("test.hdt")

# Display some metadata about the HDT document itself
print(f"number of triples: {document.total_triples}")
print(f"number of subjects: ${document.nb_subjects}")
print(f"number of predicates: {document.nb_predicates}")
print(f"number of objects: {document.nb_objects}")
print(f"number of shared subject-object: {document.nb_shared}")

# Fetch all triples that matches { ?s foaf:name ?o }
# Use None to indicates variables
triples, cardinality = document.search_triples((None, FOAF("name"), None))

print(f"cardinality of (?s foaf:name ?o): {cardinality}")
for s, p, o in triples:
  print(triple)

# Search also support limit and offset
triples, cardinality = document.search_triples((None, FOAF("name"), None), limit=10, offset=100)
# etc ...
```

# Handling non UTF-8 strings in python

If the HDT document has been encoded with a non UTF-8 encoding the previous code won't work correctly and will result in a `UnicodeDecodeError`.
More details on how to convert string to str from C++ to Python [here](https://pybind11.readthedocs.io/en/stable/advanced/cast/strings.html)

To handle this, we doubled the API of the HDT document by adding:
- `search_triples_bytes(...)` return an iterator of triples as `(py::bytes, py::bytes, py::bytes)`
- `search_join_bytes(...)` return an iterator of sets of solutions mapping as `py::set(py::bytes, py::bytes)`
- `convert_tripleid_bytes(...)` return a triple as: `(py::bytes, py::bytes, py::bytes)`
- `convert_id_bytes(...)` return a `py::bytes`

**Parameters and documentation are the same as the standard version**

```python
from hdt import HDTDocument

 # Load an HDT file.
 # Missing indexes are generated automatically, add False as the second argument to disable them
document = HDTDocument("test.hdt")
it = document.search_triple_bytes("", "", "")

for s, p, o in it:
  print(s, p, o) # print b'...', b'...', b'...'
  # now decode it, or handle any error
  try:
    s, p, o = s.decode('UTF-8'), p.decode('UTF-8'), o.decode('UTF-8')
  except UnicodeDecodeError as err:
    # try another other codecs
    pass
```

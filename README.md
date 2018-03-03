# pyHDT

[![Build Status](https://travis-ci.org/Callidon/pyHDT.svg?branch=master)](https://travis-ci.org/Callidon/pyHDT) [![Documentation Status](https://readthedocs.org/projects/pyhdt/badge/?version=latest)](http://pyhdt.readthedocs.io/en/latest/?badge=latest) [![PyPI version](https://badge.fury.io/py/hdt.svg)](https://badge.fury.io/py/hdt)

Read and query HDT document with ease in Python

[Online Documentation](http://pyhdt.readthedocs.io/en/latest)

# Requirements

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

## Pip install (recommended)

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

```python
from hdt import HDTDocument

 # Load an HDT file. Missing indexes are generated automatically
document = HDTDocument("test.hdt")

# Display some metadata about the HDT document itself
print("nb triples: %i" % document.get_total_triples())
print("nb subjects: %i" % document.get_nb_subjects())
print("nb predicates: %i" % document.get_nb_predicates())
print("nb objects: %i" % document.get_nb_objets())
print("nb shared subject-object: %i" % document.get_nb_shared())

# Fetch all triples that matches { ?s ?p ?o }
# Use empty strings ("") to indicates variables
(triples, cardinality) = document.search_triples("", "", "")

print("cardinality of { ?s ?p ?o }: %i" % cardinality)
for triple in triples:
  print(triple)

# Search also support limit and offset
(triples, cardinality) = document.search_triples("", "", "", limit=10, offset=100)
# etc ...
```

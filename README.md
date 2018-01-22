# pyHDT [![Build Status](https://travis-ci.org/Callidon/pyHDT.svg?branch=master)](https://travis-ci.org/Callidon/pyHDT)

Read and query HDT document with ease in Python

# Requirements

* [git](https://git-scm.com/)
* [pip](https://pip.pypa.io/en/stable/)
* **gcc/clang** with **c++11 support**
* **Python Development headers**
> You sould have the `Python.h` header available on your system.   
> For example, for Python 3.4, install the `python3.4-dev` package on Debian/Ubuntu systems.

# Installation

Installation in a [virtualenv](https://virtualenv.pypa.io/en/stable/) is strongly advised!

```
git clone --recursive https://github.com/Callidon/pyHDT
cd pyHDT/
pip install -r requirements.txt
python setup.py install
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

# pyHDT
Read and query HDT document with ease in Python

# Installation

```
git clone --recursive https://github.com/Callidon/pyHDT
cd pyHDT/
pip install -r requirements.txt
python setup.py install
```

# Getting started

```python
from hdt import HDTDocument

 # Load HDT file. Missing indexes are generated automatically
document = HDTDocument("test.hdt")

# fetch all triples that matches { ?s ?p ?o }
(triples, cardinality) = document.search_triples("", "", "")

print("cardinality: %i" % cardinality)

for triple in triples:
  print(triple)
```

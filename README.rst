|rdflib-htd logo|

|Build Status| |PyPI version|

A Store back-end for `rdflib <https://github.com/RDFLib>`_ to allow for reading and querying HDT documents.

`Online Documentation <https://rdflib.dev/rdflib-hdt/>`_

Requirements
============


* Python *version 3.6.4 or higher*
* `pip <https://pip.pypa.io/en/stable/>`_
* **gcc/clang** with **c++11 support**
* **Python Development headers**
  ..

     You should have the ``Python.h`` header available on your system.\
     For example, for Python 3.6, install the ``python3.6-dev`` package on Debian/Ubuntu systems.


Installation
============

Installation using `pipenv <https://github.com/pypa/pipenv>`_ or a `virtualenv <https://virtualenv.pypa.io/en/stable/>`_ is **strongly advised!**

PyPi installation (recommended)
-------------------------------

.. code-block:: bash

   # you can install using pip
   pip install rdflib-hdt

   # or you can use pipenv
   pipenv install rdflib-hdt

Manual installation
-------------------

**Requirement:** `pipenv <https://github.com/pypa/pipenv>`_ 

.. code-block:: bash

   git clone https://github.com/Callidon/pyHDT
   cd pyHDT/
   ./install.sh

Getting started
===============

You can use the ``rdflib-hdt`` library in two modes: as an rdflib Graph or as a raw HDT document.

Graph usage (recommended)
-------------------------

.. code-block:: python

   from rdflib import Graph
   from rdflib_hdt import HDTStore
   from rdflib.namespace import FOAF

   # Load an HDT file. Missing indexes are generated automatically
   # You can provide the index file by putting them in the same directory than the HDT file.
   store = HDTGraph("test.hdt")

   # Display some metadata about the HDT document itself
   print(f"Number of RDF triples: {len(store)}")
   print(f"Number of subjects: {store.nb_subjects}")
   print(f"Number of predicates: {store.nb_predicates}")
   print(f"Number of objects: {store.nb_objects}")
   print(f"Number of shared subject-object: {store.nb_shared}")


Using the RDFlib API, you can also `execute SPARQL queries <https://rdflib.readthedocs.io/en/stable/intro_to_sparql.html>`_ over an HDT document.
If you do so, we recommend that you first call the ``optimize_sparql`` function, which optimize
the RDFlib SPARQL query engine in the context of HDT documents.

.. code-block:: python

   from rdflib import Graph
   from rdflib_hdt import HDTStore, optimize_sparql

   # Calling this function optimizes the RDFlib SPARQL engine for HDT documents
   optimize_sparql()

   graph = Graph(store=HDTStore("test.hdt"))

   # You can execute SPARQL queries using the regular RDFlib API
   qres = graph.query("""
   PREFIX foaf: <http://xmlns.com/foaf/0.1/>
   SELECT ?name ?friend WHERE {
      ?a foaf:knows ?b.
      ?a foaf:name ?name.
      ?b foaf:name ?friend.
   }""")

   for row in qres:
     print(f"{row.name} knows {row.friend}")

HDT Document usage
------------------

.. code-block:: python

   from rdflib_hdt import HDTDocument

   # Load an HDT file. Missing indexes are generated automatically.
   # You can provide the index file by putting them in the same directory than the HDT file.
   document = HDTDocument("test.hdt")

   # Display some metadata about the HDT document itself
   print(f"Number of RDF triples: {document.total_triples}")
   print(f"Number of subjects: {document.nb_subjects}")
   print(f"Number of predicates: {document.nb_predicates}")
   print(f"Number of objects: {document.nb_objects}")
   print(f"Number of shared subject-object: {document.nb_shared}")

   # Fetch all triples that matches { ?s foaf:name ?o }
   # Use None to indicates variables
   triples, cardinality = document.search_triples((None, FOAF("name"), None))

   print(f"Cardinality of (?s foaf:name ?o): {cardinality}")
   for s, p, o in triples:
     print(triple)

   # The search also support limit and offset
   triples, cardinality = document.search_triples((None, FOAF("name"), None), limit=10, offset=100)
   # etc ...

An HDT document also provides support for evaluating joins over a set of triples patterns.

.. code-block:: python

  from rdflib_hdt import HDTDocument
  from rdflib import Variable
  from rdflib.namespace import FOAF, RDF
  
  document = HDTDocument("test.hdt")
  
  # find the names of two entities that know each other
  tp_a = (Variable("a"), FOAF("knows"), Variable("b"))
  tp_b = (Variable("a"), FOAF("name"), Variable("name"))
  tp_c = (Variable("b"), FOAF("name"), Variable("friend"))
  query = set([tp_a, tp_b, tp_c])
  
  iterator = document.search_join(query)
  print(f"Estimated join cardinality: {len(iterator)}")
  
  # Join results are produced as ResultRow, like in the RDFlib SPARQL API
  for row in iterator:
     print(f"{row.name} knows {row.friend}")

Handling non UTF-8 strings in python
====================================

If the HDT document has been encoded with a non UTF-8 encoding the previous code won't work correctly and will result in a ``UnicodeDecodeError``.
More details on how to convert string to str from C++ to Python `here <https://pybind11.readthedocs.io/en/stable/advanced/cast/strings.html>`_

To handle this, we doubled the API of the HDT document by adding:


* ``search_triples_bytes(...)`` return an iterator of triples as ``(py::bytes, py::bytes, py::bytes)``
* ``search_join_bytes(...)`` return an iterator of sets of solutions mapping as ``py::set(py::bytes, py::bytes)``
* ``convert_tripleid_bytes(...)`` return a triple as: ``(py::bytes, py::bytes, py::bytes)``
* ``convert_id_bytes(...)`` return a ``py::bytes``

**Parameters and documentation are the same as the standard version**

.. code-block:: python

   from rdflib_hdt import HDTDocument

   document = HDTDocument("test.hdt")
   it = document.search_triple_bytes("", "", "")

   for s, p, o in it:
   print(s, p, o) # print b'...', b'...', b'...'
   # now decode it, or handle any error
   try:
      s, p, o = s.decode('UTF-8'), p.decode('UTF-8'), o.decode('UTF-8')
   except UnicodeDecodeError as err:
      # try another other codecs, ignore error, etc
      pass

.. |Build Status| image:: https://github.com/RDFLib/rdflib-hdt/workflows/Python%20tests/badge.svg
   :target: https://github.com/RDFLib/rdflib-hdt/actions?query=workflow%3A%22Python+tests%22
.. |PyPI version| image:: https://badge.fury.io/py/rdflib-hdt.svg
   :target: https://badge.fury.io/py/rdflib-hdt
.. |rdflib-htd logo| image:: https://raw.githubusercontent.com/RDFLib/rdflib-hdt/master/docs/source/_static/rdflib-hdt-250.png
   :target: https://rdflib.dev/rdflib-hdt/

|Build Status| |Documentation Status| |PyPI version|

Read and query HDT document with ease in Python

`Online Documentation <https://callidon.github.io/pyHDT>`__

Requirements
============

-  Python *version 3.6.4 or higher*
-  `pip <https://pip.pypa.io/en/stable/>`__
-  **gcc/clang** with **c++11 support**
-  **Python Development headers** > You should have the ``Python.h``
   header available on your system.
   > For example, for Python 3.6, install the ``python3.6-dev`` package
   on Debian/Ubuntu systems.

Then, install the `pybind11
library <http://pybind11.readthedocs.io/en/stable/>`__

::

    pip install pybind11

Installation
============

Installation in a `virtualenv <https://virtualenv.pypa.io/en/stable/>`__
is **strongly advised!**

Pip install (recommended)
-------------------------

::

    pip install hdt

Manual installation
-------------------

::

    git clone https://github.com/Callidon/pyHDT
    cd pyHDT/
    ./install.sh

Getting started
===============

.. code:: python

    from hdt import HDTDocument

    # Load an HDT file.
    # Missing indexes are generated automatically, add False as the second argument to disable them
    document = HDTDocument("test.hdt")

    # Display some metadata about the HDT document itself
    print("nb triples: %i" % document.total_triples)
    print("nb subjects: %i" % document.nb_subjects)
    print("nb predicates: %i" % document.nb_predicates)
    print("nb objects: %i" % document.nb_objects)
    print("nb shared subject-object: %i" % document.nb_shared)

    # Fetch all triples that matches { ?s ?p ?o }
    # Use empty strings ("") to indicates variables
    triples, cardinality = document.search_triples("", "", "")

    print("cardinality of { ?s ?p ?o }: %i" % cardinality)
    for triple in triples:
      print(triple)

    # Search also support limit and offset
    triples, cardinality = document.search_triples("", "", "", limit=10, offset=100)
    # etc ...

.. |Build Status| image:: https://travis-ci.org/Callidon/pyHDT.svg?branch=master
   :target: https://travis-ci.org/Callidon/pyHDT
.. |Documentation Status| image:: https://readthedocs.org/projects/pyhdt/badge/?version=latest
   :target: https://callidon.github.io/pyHDT
.. |PyPI version| image:: https://badge.fury.io/py/hdt.svg
   :target: https://badge.fury.io/py/hdt

Handling non UTF-8 strings in python
====================================

If the HDT document has been encoded with a non UTF-8 encoding the
previous code won’t work correctly and will result in a
``UnicodeDecodeError``. More details on how to convert string to str
from c++ to python `here`_

To handle this we doubled the API of the HDT document by adding:

- ``search_triples_bytes(...)`` return an iterator of triples as ``(py::bytes, py::bytes, py::bytes)``
- ``search_join_bytes(...)`` return an iterator of sets of solutions mapping as ``py::set(py::bytes, py::bytes)``
- ``convert_tripleid_bytes(...)`` return a triple as: ``(py::bytes, py::bytes, py::bytes)``
- ``convert_id_bytes(...)`` return a ``py::bytes``

**Parameters and documentation are the same as the standard version**

.. code:: python

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

.. _here: https://pybind11.readthedocs.io/en/stable/advanced/cast/strings.html

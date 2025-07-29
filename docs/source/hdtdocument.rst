Low-level Usage
===============

Loading HDT files
^^^^^^^^^^^^^^^^^

The main class for directly manipulating an HDT document using rdflib_hdt is :py:class:`rdflib_hdt.HDTDocument`.
Upon creation, it searches for an index file in the same directory than the HDT file you wish to load.
For example, if you load a file */home/awesome-user/test.hdt*, :py:class:`rdflib_hdt.HDTDocument` will look for the index file
*/home/awesome-user/test.hdt.index.v1-1*.

.. warning:: By default, an HDTDocument discards RDF Terms with invalid UTF-8 encoding. You can change this behavior with the `safe_mode` parameter of the constructor.

.. note:: Missing indexes are generated automatically, but be careful, as it requires loading all HDT triples in memory!


.. code-block:: python

  from rdflib_hdt import HDTDocument

  # Load an HDT file.
  # Missing indexes are generated automatically, add False as the second argument to disable them
  document = HDTDocument("test.hdt")

  # Display some metadata about the HDT document itself
  print(f"Number of RDF triples: {document.total_triples}")
  print(f"Number of subjects: {document.nb_subjects}")
  print(f"Number of predicates: {document.nb_predicates}")
  print(f"Number of objects: {document.nb_objects}")
  print(f"Number of shared subject-object: {document.nb_shared}")


Searching for triples
^^^^^^^^^^^^^^^^^^^^^^

You can search for all RDF triples in the HDT file matching a triple pattern using :py:meth:`rdflib_hdt.HDTDocument.search`.
It returns a 2-element tuple: an :py:class:`rdflib_hdt.HDTIterator` over the matching RDF triples and the estimated triple pattern *cardinality*.

.. note:: The :py:meth:`rdflib_hdt.HDTDocument.search` method also accepts ``limit`` and ``offset`` parameters, to perform range queries over the matching RDF triples.

.. code-block:: python

  from rdflib.namespace import FOAF
  from rdflib_hdt import HDTDocument
  document = HDTDocument("test.hdt")

  # Fetch all triples that matches { ?s foaf:name ?o }
  # Use None to indicates variables
  triples, cardinality = document.search((None, FOAF("name"), None))

  print(f"Cardinality of (?s foaf:name ?o): {cardinality}")
  for s, p, o in triples:
    print(triple)

  # The search also support limit and offset
  triples, cardinality = document.search((None, FOAF("name"), None), limit=10, offset=100)
  # etc ...

Searching for triple IDs
^^^^^^^^^^^^^^^^^^^^^^^^^

A typical HDT document encodes a triple's subject, predicate, and object as unique integers, named **TripleID**.
For example, the triple ``("ex:Toto", "ex:type", "ex:Person")`` can be encoded as ``(1, 2, 3)``.
An :py:class:`rdflib_hdt.HDTDocument` allows for searching RDF triples and retrieving them in this format, using the :py:meth:`rdflib_hdt.HDTDocument.search_ids` method, which takes the same parameters as the :py:meth:`rdflib_hdt.HDTDocument.search` method.

.. note:: You can transform RDF terms or RDF triples to/from TripleIDs using the :meth:`rdflib_hdt.HDTDocument.from_tripleid`, :py:meth:`rdflib_hdt.HDTDocument.to_tripleid`, :meth:`rdflib_hdt.HDTDocument.term_to_id`, and :meth:`rdflib_hdt.HDTDocument.id_to_term` methods.

.. code-block:: python

  from rdflib_hdt import HDTDocument
  document = HDTDocument("test.hdt")

  (triples, cardinality) = document.search_ids((None, None, None))

  for s, p, o in triples:
    print(s, p, o) # will print 3-element tuples of integers

    # convert a triple ID to a string format
    print(f"TripleID {(s, p, o)} = RDF Triple {document.from_tripleid(s, p, o)}")

    # print only the subject
    print(f"ID {s} = Term {document.id_to_term(s, 0)}")

Join evaluation
^^^^^^^^^^^^^^^

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

Ordering
^^^^^^^^^^^

When searching for triples (either in a string or TripleID format), results are ordered by (subject, predicate, object).
However, this order is **not** an order on string values, but an order on **triple ids**.
For example, ``("ex:2", "ex:type", "ex:Person") < ("ex:1", "ex:type", "ex:Person")``,
because their triple ids counterparts are ``(1, 2, 3)`` and ``(2, 2, 3)``.

For more details about this topic, please refer to the `HDT journal article <http://www.imap.websemanticsjournal.org/preprints/index.php/ps/article/viewFile/328/333>`_.

Handling non UTF-8 strings in Python
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If the HDT document is encoded without valid UTF-8 encoding and it does not run in *safe mode*, querying the document may raise an
``UnicodeDecodeError``. More details on how to convert string
from C++ to Python `here`_

To allow fine control over string conversion in this case, we doubled the API of the HDT document by adding the following methods (Parameters and documentation are the same as their standard counterparts).

- :py:meth:`rdflib_hdt.HDTDocument.search_triples_bytes` returns an iterator of triples as ``(py::bytes, py::bytes, py::bytes)``
- :py:meth:`rdflib_hdt.HDTDocument.search_join_bytes` returns an iterator of sets of solutions mapping as ``py::set(py::bytes, py::bytes)``
- :py:meth:`rdflib_hdt.HDTDocument.convert_tripleid_bytes` returns a triple as: ``(py::bytes, py::bytes, py::bytes)``
- :py:meth:`rdflib_hdt.HDTDocument.convert_id_bytes` returns a ``py::bytes``

.. code:: python

  from rdflib_hdt import HDTDocument

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

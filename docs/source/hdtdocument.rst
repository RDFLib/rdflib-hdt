HDTDocument
===========

Loading HDT files
^^^^^^^^^^^^^^^^^

The main class for manipulating HDT Dicument using pyHDT is ``HDTDocument``.
Upon creation, it search for an index file in the same dicrectory than the HDT file you wish to load.

For example, if you load a file */home/awesome-user/test.hdt*, HDTDocument will look for the index file
*/home/awesome-user/test.hdt.index.v1-1*.

Missing indexes are generated automatically, but be careful, as it requires to load all HDT triples in memory!

.. code-block:: python

  from hdt import HDTDocument

  # Load HDT file. Missing indexes are generated automatically
  document = HDTDocument("test.hdt")

  # Display some metadata about the HDT document itself
  print("nb triples: %i" % document.get_total_triples())
  print("nb subjects: %i" % document.get_nb_subjects())
  print("nb predicates: %i" % document.get_nb_predicates())
  print("nb objects: %i" % document.get_nb_objets())
  print("nb shared subject-object: %i" % document.get_nb_shared())


Searching for triples
^^^^^^^^^^^^^^^^^^^^^^

You can search for all RDF triples in the HDT file matching a triple pattern using `search_triples`.
It returns a 2-element tuple, with an *iterator* over the matching RDF triples and the estimated triple pattern *cardinality*.

.. code-block:: python

  from hdt import HDTDocument
  document = HDTDocument("test.hdt")

  # Fetch all triples that matches { ?s ?p ?o }
  # Use empty strings ("") to indicates variables
  (triples, cardinality) = document.search_triples("", "", "")

  print("cardinality of { ?s ?p ?o }: %i" % cardinality)
  for triple in triples:
    print(triple)

  # Search also support limit and offset
  (triples, cardinality) = document.search_triples("", "", "", limit=10, offset=100)
  # etc ...

Searching for triple IDs
^^^^^^^^^^^^^^^^^^^^^^^^^

A typical HDT document encodes a triple's subject, predicate and object as unique integers, named **TripleID**.
For example, the triple ``("ex:Toto", "ex:type", "ex:Person")`` can be encoded as ``(1, 2, 3)``.
An ``HDTDocument`` allows for searching RDF triples in this format, using the ``search_triple_ids`` method, which works exactly like the classic ``search_triple``.

.. code-block:: python

  from hdt import HDTDocument
  document = HDTDocument("test.hdt")

  (triples, cardinality) = document.search_triples_ids("", "", "")

  for triple in triples:
    print(triple) # will print 3-element tuples of integers

Ordering
^^^^^^^^^^^

When searching for triples (either in string or triple id format), results are returned ordred by (subject, predicate, object).
However, this order is **not** an order on string values, but an order on **triple ids**.
For example, ``("ex:2", "ex:type", "ex:Person") < ("ex:1", "ex:type", "ex:Person")``,
because their triple ids counterparts are ``(1, 2, 3)`` and ``(2, 2, 3)``.

For more details about this topic, please refer to the `HDT journal article <http://www.imap.websemanticsjournal.org/preprints/index.php/ps/article/viewFile/328/333>`_.

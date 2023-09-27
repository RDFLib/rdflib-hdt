Querying HDT documents
======================

Getting started
---------------

The primary way of using ``rdflib-hdt`` is the :py:class:`rdflib_hdt.HDTStore` class.
Upon creation, it searches for an index file in the same directory than the HDT file you wish to load.
For example, if you load a file */home/awesome-user/test.hdt*, :py:class:`rdflib_hdt.HDTDocument` will look for the index file
*/home/awesome-user/test.hdt.index.v1-1*.

.. warning:: By default, an HDTStore discards RDF Terms with invalid UTF-8 encoding. You can change this behavior with the `safe_mode` parameter of the constructor.

.. note:: Missing indexes are generated automatically, but be careful, as it requires to load all HDT triples in memory!

.. code-block:: python

   from rdflib import Graph
   from rdflib_hdt import HDTStore
   from rdflib.namespace import FOAF

   # Load an HDT file. Missing indexes are generated automatically
   # You can provide the index file by putting them in the same directory than the HDT file.
   store = HDTStore("test.hdt")

   # Display some metadata about the HDT document itself
   print(f"Number of RDF triples: {len(store)}")
   print(f"Number of subjects: {store.nb_subjects}")
   print(f"Number of predicates: {store.nb_predicates}")
   print(f"Number of objects: {store.nb_objects}")
   print(f"Number of shared subject-object: {store.nb_shared}")

Executing SPARQL queries
------------------------

Using the RDFlib API, you can also `execute SPARQL queries <https://rdflib.readthedocs.io/en/stable/intro_to_sparql.html>`_ over an HDT document.
If you do so, we recommend that you first call the :py:func:`rdflib_hdt.optimize_sparql` function, which optimize
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

.. note::
      Calling the :py:func:`rdflib_hdt.optimize_sparql` function triggers a global modification of the RDFlib SPARQL engine.
      However, executing SPARQL queries using other RDFlib stores will continue to work as before,
      so you can safely call this function at the beginning of your code.

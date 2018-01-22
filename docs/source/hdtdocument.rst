HDTDocument
===========

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

  # Fetch all triples that matches { ?s ?p ?o }
  # Use empty strings ("") to indicates variables
  (triples, cardinality) = document.search_triples("", "", "")

  print("cardinality of { ?s ?p ?o }: %i" % cardinality)
  for triple in triples:
    print(triple)

  # Search also support limit and offset
  (triples, cardinality) = document.search_triples("", "", "", limit=10, offset=100)
  # etc ...

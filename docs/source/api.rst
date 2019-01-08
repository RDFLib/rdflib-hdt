API documentation
=================

.. currentmodule:: hdt

HDTDocument
-----------

.. autoclass:: HDTDocument
  :members:

  .. method:: __init__(self, filePath) -> hdt.HDTDocument

    Build a new :class:`hdt.HDTDocument` by the loading the HDT file located in ``filePath``.

    Args:
      - filePath ``str``: the path to the HDT file to load.

    .. code-block:: python

      from hdt import HDTDocument

      # Load HDT file. Missing indexes are generated automatically
      document = HDTDocument("test.hdt")

      # Display some metadata about the HDT document itself
      print("nb triples: %i" % document.total_triples)
      print("nb subjects: %i" % document.nb_subjects)
      print("nb predicates: %i" % document.nb_predicates)
      print("nb objects: %i" % document.nb_objets)
      print("nb shared subject-object: %i" % document.nb_shared)


TripleIterator
--------------

.. autoclass:: TripleIterator
  :inherited-members:
  :members:

TripleIDIterator
----------------

.. autoclass:: TripleIDIterator
  :inherited-members:
  :members:

JoinIterator
--------------

.. autoclass:: JoinIterator
  :inherited-members:
  :members:


Enumerations
-------------

IdentifierPosition
^^^^^^^^^^^^^^^^^^^

.. autoclass:: IdentifierPosition

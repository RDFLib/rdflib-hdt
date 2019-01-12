/**
 * docstrings.hpp
 * Author: Thomas MINIER - MIT License 2017-2019
 */

#ifndef PYHDT_DOCSTRINGS_HPP
#define PYHDT_DOCSTRINGS_HPP

#include <string>

const char *MODULE_DOC = R"(
  The hdt module enables to load and query HDT files with ease.
)";

/**
 * Enums docstrings
 */

const char *IDENTIFIER_POSITION_DOC = R"(
 An enum used to indicate the position (subject, predicate or object) of an Object identifier.

 Possibles values:
  - ``IdentifierPosition.Subject``: the subject position
  - ``IdentifierPosition.Predicate``: the subject position
  - ``IdentifierPosition.Object``: the object position

 .. code-block:: python

   from hdt import IdentifierPosition
   print(IdentifierPosition.Subject)
   print(IdentifierPosition.Predicate)
   print(IdentifierPosition.Object)

)";

/**
 * HDT Document docstrings
 */

const char *HDT_DOCUMENT_CLASS_DOC = R"(
  An HDTDocument enables to load and query a HDT file.
  Indexes are automatically generated if missing.
)";

const char *HDT_DOCUMENT_GETFILEPATH_DOC = R"(
  Return the path to the HDT file currently loaded
)";

const char *HDT_DOCUMENT_GETNBTRIPLES_DOC = R"(
  Return the total number of triples in the HDT document
)";

const char *HDT_DOCUMENT_GETNBSUBJECTS_DOC = R"(
  Return the number of subjects in the HDT document
)";

const char *HDT_DOCUMENT_GETNBPREDICATES_DOC = R"(
  Return the number of predicates in the HDT document
)";

const char *HDT_DOCUMENT_GETNBOBJECTS_DOC = R"(
  Return the number of objects in the HDT document
)";

const char *HDT_DOCUMENT_GETNBSHARED_DOC = R"(
  Return the number of shared subject-object in the HDT document
)";

const char *HDT_DOCUMENT_SEARCH_TRIPLES_DOC = R"(
  Search for RDF triples matching the triple pattern { ``subject`` ``predicate`` ``object`` },
  with an optional ``limit`` and ``offset``.
  Use empty strings (``""``) to indicate wildcards.

  Args:
    - subject ``str``: The subject of the triple pattern to seach for.
    - predicate ``str``: The predicate of the triple pattern to seach for.
    - obj ``str``: The object of the triple pattern ot seach for.
    - limit ``int`` ``optional``: Maximum number of triples to search for.
    - offset ``int`` ``optional``: Number of matching triples to skip before returning results.

  Return:
    A 2-elements ``tuple`` (:class:`hdt.TripleIterator`, estimated pattern cardinality), where
    the TripleIterator iterates over matching RDF triples.

    A RDF triple itself is a 3-elements ``tuple`` (subject, predicate, object).

    .. code-block:: python

      from hdt import HDTDocument
      document = HDTDocument("test.hdt")

      # Fetch all triples that matches { ?s ?p ?o }
      (triples, cardinality) = document.search_triples("", "", "")

      print("cardinality of { ?s ?p ?o }: %i" % cardinality)
      for triple in triples:
        print(triple)

)";

const char *HDT_DOCUMENT_SEARCH_TRIPLES_IDS_DOC = R"(
  Same as :meth:`hdt.HDTDocument.search_triples`, but RDF triples are represented as unique ids (from the HDT Dictionnary).
  Use the integer `0` to indicate wildcards.

  Mapping between ids and RDF terms is done using :meth:`hdt.HDTDocument.convert_id`, :meth:`hdt.HDTDocument.convert_term` and :meth:`hdt.HDTDocument.convert_tripleid`.

  Args:
    - subject ``int``: The Object identifier of the triple pattern's subject.
    - predicate ``int``: The Object identifier of the triple pattern's predicate.
    - obj ``int``: The Object identifier of the triple pattern's object.
    - limit ``int`` ``optional``: Maximum number of triples to search for.
    - offset ``int`` ``optional``: Number of matching triples to skip before returning results.

  Return:
    A 2-elements ``tuple`` (:class:`hdt.TripleIDIterator`, estimated pattern cardinality), where
    the TripleIDIterator iterates over matching RDF triples IDs.

    A RDF triple ID itself is a 3-elements ``tuple`` (subjectID, predicateID, objectID).

    .. code-block:: python

      from hdt import HDTDocument
      document = HDTDocument("test.hdt")

      pred = document.convert_term("http://xmlns.com/foaf/0.1/")
      # Fetch all RDF triples that matches { ?s foaf:name ?o }
      (triples, cardinality) = document.search_triples_ids(0, pred, 0)

      print("cardinality of { ?s foaf:name ?o }: %i" % cardinality)
      for triple in triples:
        print(triple)

)";

const char *HDT_DOCUMENT_SEARCH_JOIN_DOC = R"(
  Evaluate a join between a set of triple patterns using an iterator.
  A triple pattern itself is a 3-elements ``tuple`` (subject, predicate, object), where SPARQL variables, i.e., join predicates, are prefixed by a ``?``.

  Args:
    - patterns ``set``: set of triple patterns.

  Return:
    A :class:`hdt.JoinIterator`, which can be consumed as a Python iterator to evaluates the join.

    .. code-block:: python

      from hdt import HDTDocument
      document = HDTDocument("test.hdt")

      # find all actors with their names in the HDT document
      tp_a = ("?s", "http://www.w3.org/1999/02/22-rdf-syntax-ns#type", "http://example.org#Actor")
      tp_b = ("?s", "http://xmlns.com/foaf/0.1/name", "?name")
      iterator = document.search_join(set([tp_a, tp_b]))

      print("estimated join cardinality : %i" % len(iterator))
      for mappings in iterator:
        print(mappings)

)";

const char *HDT_DOCUMENT_TRIPLES_IDS_TO_STRING_DOC = R"(
  Transform a RDF triple from a TripleID representation to a string representation.

  Args:
    - subject ``int``: unique ID of the subject.
    - predicate ``int``: unique ID of the predicate.
    - obj ``int``: unique ID of the object.

  Return:
    A triple in string representation, i.e., a 3-elements ``tuple`` (subject, predicate, object)

    .. code-block:: python

      from hdt import HDTDocument
      document = HDTDocument("test.hdt")

      # Fetch all triples that matches { ?s foaf:name ?o }
      pred = document.convert_term("http://xmlns.com/foaf/0.1/")
      (triples, cardinality) = document.search_triples_ids(0, pred, 0)

      for s, p, o in triples:
        print(s, p, o) # will print Object identifiers, i.e., integers
        # convert a triple ID to a string format
        print(document.convert_tripleid(s, p, o))

)";

const char *HDT_DOCUMENT_CONVERT_ID_DOC = R"(
  Transform an Object Identifier to a RDF term.
  Such identifier are used in TripleID.

  Args:
    - id ``int``: Object identifier.
    - position :class:`hdt.IdentifierPosition`: Identifier position.

  Return:
    The RDF term associated with of the Object Identifier, i.e., either an URI or a RDF literal.

    .. code-block:: python

      from hdt import HDTDocument, IdentifierPosition
      document = HDTDocument("test.hdt")
      print(document.convert_id(10, IdentifierPosition.Subject))

)";

const char *HDT_DOCUMENT_CONVERT_TERM_DOC = R"(
  Transform an RDF Term to the associated Object Identifier.
  Such identifier are used in TripleID.

  Args:
    - term ``str``: RDF Term.
    - position :class:`hdt.IdentifierPosition`: Identifier position.

  Return:
    The the Object Identifier associated with the RDF Term

    .. code-block:: python

      from hdt import HDTDocument, IdentifierPosition
      document = HDTDocument("test.hdt")
      print(document.convert_term("http://example.org#Alice", IdentifierPosition.Subject))

)";

/**
 * TripleIterator & TripleIDIterator docstrings
 */

const char *TRIPLE_ITERATOR_CLASS_DOC = R"(
  A TripleIterator iterates over triples in a HDT file matching a triple pattern, with an optional limit & offset.

  Such iterator is returned by :meth:`hdt.HDTDocument.search_triples`.
)";

const char *TRIPLE_ID_ITERATOR_CLASS_DOC = R"(
  A TripleIDIterator iterates over triples' IDs in a HDT file matching a triple pattern, with an optional limit & offset.

  Such iterator is returned by :meth:`hdt.HDTDocument.search_triples_ids`

  Conversion from a tuple of triple ids into a RDF triple is done using :meth:`hdt.HDTDocument.convert_tripleid`.
)";

const char *TRIPLE_ITERATOR_NEXT_DOC = R"(
  Return the next matching triple read by the iterator, or raise ``StopIterator`` if there is no more items to yield.
)";

const char *TRIPLE_ITERATOR_PEEK_DOC = R"(
  Return the next matching triple read by the iterator without advancing it, or raise ``StopIterator`` if there is no more items to yield.
)";

const char *TRIPLE_ITERATOR_HASNEXT_DOC = R"(
  Return true if the iterator still has items to yield, false otherwise.
)";

const char *TRIPLE_ITERATOR_GETSUBJECT_DOC = R"(
  Return the subject of the triple pattern currently evaluated.
)";

const char *TRIPLE_ITERATOR_GETPREDICATE_DOC = R"(
  Return the predicate of the triple pattern currently evaluated.
)";

const char *TRIPLE_ITERATOR_GETOBJECT_DOC = R"(
  Return the object of the triple pattern currently evaluated.
)";

const char *TRIPLE_ITERATOR_GETLIMIT_DOC = R"(
  Return the limit of the iterator, i.e., the maximum number of items the iterator will yield.
  A limit of 0 indicates that the iterator limit is the cardinality of the triple pattern currently evaluated.
)";

const char *TRIPLE_ITERATOR_GETOFFSET_DOC = R"(
  Return the offset of the iterator, i.e., the number of items the iterator will first skip before yielding.
  An offset of 0 indicates that the iterator will not skip any items.
)";

const char *TRIPLE_ITERATOR_NBREADS_DOC = R"(
  Return the number of items read by the iterator until now.
  Do not include any offset, thus the real position of the iterator in the collection of triples can be computed as offset + nb_reads
)";

const char *TRIPLE_ITERATOR_SIZE_DOC = R"(
  Get a hint on the cardinality of the triple pattern currently evaluated.
  The iterator's limit and offset are not taken into account.

  Return:
    A 2-element ``tuple`` (integer, boolean), where the left member is the estimated cardinality,
    and the right member is True is the estimation is accurate, False otherwise
)";

const char *TRIPLE_ITERATOR_ACC_ESTIMATION_DOC = R"(
  Return True if the iterator can accuratly estimate the cardinality of the triple pattern, False otherwise.
)";

const char *JOIN_ITERATOR_CLASS_DOC = R"(
  A JoinIterator iterates over the set of solution mappings for a join between several triple patterns. It implements the Python iterator protocol and yields sets of solutions mappings.

  Such iterator is returned by :meth:`hdt.HDTDocument.search_join`
)";

const char *JOIN_ITERATOR_NEXT_DOC = R"(
  Return the next set of solution mappings read by the iterator, or raise ``StopIterator`` if there is no more items to yield.
)";

const char *JOIN_ITERATOR_HAS_NEXT_DOC = R"(
  Return true if the iterator still has items to yield, false otherwise.
)";

const char *JOIN_ITERATOR_SIZE_DOC = R"(
  Return the estimated join cardinality.
)";

const char *JOIN_ITERATOR_RESET_DOC = R"(
  Reset the join, i.e., move the iterator back to its initial state.
)";

#endif /* PYHDT_DOCSTRINGS_HPP */

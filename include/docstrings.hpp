/**
 * s.hpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#ifndef PYHDT_DOCSTRINGS_HPP
#define PYHDT_DOCSTRINGS_HPP

#include <string>

const char *MODULE_DOC = R"(
  The hdt module enables to load and query HDT files with ease.
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
  Use empty strings (``""``) to indicate SPARQL variables.

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
  Use empty strings ("") to indicate variables.

  Transformation from triple ids to triple strings is done using :meth:`hdt.HDTDocument.tripleid_to_string`.

  Args:
    - subject ``str``: The subject of the triple pattern to seach for.
    - predicate ``str``: The predicate of the triple pattern to seach for.
    - obj ``str``: The object of the triple pattern ot seach for.
    - limit ``int`` ``optional``: Maximum number of triples to search for.
    - offset ``int`` ``optional``: Number of matching triples to skip before returning results.

  Return:
    A 2-elements ``tuple`` (:class:`hdt.TripleIDIterator`, estimated pattern cardinality), where
    the TripleIDIterator iterates over matching RDF triples IDs.

    A RDF triple ID itself is a 3-elements ``tuple`` (subjectID, predicateID, objectID).

    .. code-block:: python

      from hdt import HDTDocument
      document = HDTDocument("test.hdt")

      # Fetch all triples that matches { ?s ?p ?o }
      (triples, cardinality) = document.search_triples_ids("", "", "")

      print("cardinality of { ?s ?p ?o }: %i" % cardinality)
      for triple in triples:
        print(triple)

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
      (triples, cardinality) = document.search_triples_ids("", "", "")

      for s, p, o in triples:
        print(s, p, o) # will print IDS, i.e., integers
        # convert a triple ID to a string format
        print(document.tripleid_to_string(s, p, o))

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

  Conversion from a tuple of triple ids into a RDF triple is done using :meth:`hdt.HDTDocument.tripleid_to_string`.
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
#endif /* PYHDT_DOCSTRINGS_HPP */

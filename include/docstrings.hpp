/**
 * s.hpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#ifndef PYHDT_DOCSTRINGS_HPP
#define PYHDT_DOCSTRINGS_HPP

#include <string>

const char * MODULE_DOC = R"(
  The hdt module enables to load and query HDT files with ease.

  Example:

  from hdt import HDTDocument

  # Load an HDT file. Missing indexes are generated automatically
  document = HDTDocument("test.hdt")

  # Fetch all triples that matches { ?s ?p ?o }
  (triples, cardinality) = document.search_triples("", "", "")

  print("cardinality of { ?s ?p ?o }: %i" % cardinality)
  for s, p, o in triples:
    print(s, p, o)
)";

/**
 * HDT Document docstrings
 */

const char * HDT_DOCUMENT_CLASS_DOC = R"(
  An HDTDocument enables to load and query a HDT file.
  Indexes are automatically generated if missing.

  Example:

  from hdt import HDTDocument

  # Load an HDT file. Missing indexes are generated automatically
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
  for s, p, o in triples:
    print(s, p, o)

  # Search also support limit and offset
  (triples, cardinality) = document.search_triples("", "", "", limit=10, offset=100)
  # etc ...
)";

const char * HDT_DOCUMENT_GETFILEPATH_DOC = R"(
  Return the path to the HDT file currently loaded
)";

const char * HDT_DOCUMENT_GETNBTRIPLES_DOC = R"(
  Return the total number of triples in the HDT document
)";

const char * HDT_DOCUMENT_GETNBSUBJECTS_DOC = R"(
  Return the number of subjects in the HDT document
)";

const char * HDT_DOCUMENT_GETNBPREDICATES_DOC = R"(
  Return the number of predicates in the HDT document
)";

const char * HDT_DOCUMENT_GETNBOBJECTS_DOC = R"(
  Return the number of objects in the HDT document
)";

const char * HDT_DOCUMENT_GETNBSHARED_DOC = R"(
  Return the number of shared subject-object in the HDT document
)";

const char * HDT_DOCUMENT_SEARCH_TRIPLES_DOC = R"(
  Search for RDF triples matching the triple pattern { subject predicate object }, with an optional limit and offset.
  Use empty strings ("") to indicate variables.

  Args:
    subject (str): The subject of the triple pattern to seach for.
    predicate (str): The predicate of the triple pattern to seach for.
    obj (str): The object of the triple pattern ot seach for.
    limit (int, optional): Maximum number of triples to search for.
    offset (int, optional): Number of matching to skip before returning results.

  Return:
    A tuple (list of matching triples, triple pattern cardinality).
    A triple itself is a tuple (subject, predicate, object).

  Example:
  (triples, cardinality) = document.search_triples("", "", "")
  print("cardinality of { ?s ?p ?o }: %i" % cardinality)
  for s, p, o in triples:
    print(s, p, o)
)";

/**
 * TripleIterator & TripleIDIterator docstrings
 */

const char * TRIPLE_ITERATOR_CLASS_DOC = R"(
  A TripleIterator iterates over triples in a HDT file matching a triple pattern, with an optional limit & offset.
  Such iterator can be obtained by a call to HDTDocument#search_triples
)";

const char * TRIPLE_ID_ITERATOR_CLASS_DOC = R"(
  A TripleIDIterator iterates over triples' IDs in a HDT file matching a triple pattern, with an optional limit & offset.
  Such iterator can be obtained by a call to HDTDocument#search_triples_ids.
  Conversion from a tuple of triple ids into a RDF triple is done using HDTDocument#ids_to_string()
)";

const char * TRIPLE_ITERATOR_NEXT_DOC = R"(
  Return the next matching triple read by the iterator, or raise StopIterator if there is no more items to yield.
)";

const char * TRIPLE_ITERATOR_HASNEXT_DOC = R"(
  Return true if the iterator still has items to yield, false otherwise.
)";

const char * TRIPLE_ITERATOR_GETSUBJECT_DOC = R"(
  Return the subject of the triple pattern currently evaluated.
)";

const char * TRIPLE_ITERATOR_GETPREDICATE_DOC = R"(
  Return the predicate of the triple pattern currently evaluated.
)";

const char * TRIPLE_ITERATOR_GETOBJECT_DOC = R"(
  Return the object of the triple pattern currently evaluated.
)";

const char * TRIPLE_ITERATOR_GETLIMIT_DOC = R"(
  Return the limit of the iterator, i.e., the maximum number of items the iterator will yield.
  A limit of 0 indicates that the iterator limit is the cardinality of the triple pattern currently evaluated.
)";

const char * TRIPLE_ITERATOR_GETOFFSET_DOC = R"(
  Return the offset of the iterator, i.e., the number of items the iterator will first skip before yielding.
  An offset of 0 indicates that the iterator will not skip any items.
)";

const char * TRIPLE_ITERATOR_SIZE_DOC = R"(
  Return the estimated cardinality of the triple pattern currently evaluated.
  The iterator's limit and offset are not taken into account.
)";

const char * TRIPLE_ITERATOR_ACC_ESTIMATION_DOC = R"(
  Return true if the iterator can accuratly estimate the cardinality of the triple pattern, false otherwise.
)";
#endif /* PYHDT_DOCSTRINGS_HPP */

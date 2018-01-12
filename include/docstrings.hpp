/**
 * docstrings.hpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#ifndef DOCSTRINGS_HPP
#define DOCSTRINGS_HPP

#include <string>

namespace pyhdtdoc {
  const std::string MODULE = R"docstring(
    The hdt module enables to load and query HDT files with ease.

    Example:
    
    from hdt import HDTDocument

    # Load HDT file. Missing indexes are generated automatically
    document = HDTDocument("test.hdt")

    # Fetch all triples that matches { ?s ?p ?o }
    (triples, cardinality) = document.search_triples("", "", "")

    print("cardinality of { ?s ?p ?o }: %i" % cardinality)
    for triple in triples:
      print(triple)
  )docstring"

  const std::string HDT_DOCUMENT_CLASS = R"docstring(
    An HDTDocument enables to load and query a HDT file.
    Indexes are automatically generated if missing.

    Example:

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
  )docstring"

  const std::string HDT_DOCUMENT_GETFILEPATH = R"docstring(
    Return the path to the HDT file currently loaded
  )docstring"

  const std::string HDT_DOCUMENT_GETNBTRIPLES = R"docstring(
    Return the total number of triples in the HDT document
  )docstring"

  const std::string HDT_DOCUMENT_GETNBSUBJECTS = R"docstring(
    Return the number of subjects in the HDT document
  )docstring"

  const std::string HDT_DOCUMENT_GETNBPREDICATES = R"docstring(
    Return the number of predicates in the HDT document
  )docstring"

  const std::string HDT_DOCUMENT_GETNBOBJECTS = R"docstring(
    Return the number of objects in the HDT document
  )docstring"

  const std::string HDT_DOCUMENT_GETNBSHARED = R"docstring(
    Return the number of shared subject-object in the HDT document
  )docstring"

  const std::string HDT_DOCUMENT_SEARCH_TRIPLES = R"docstring(
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

    from hdt import HDTDocument
    document = HDTDocument("test.hdt")

    (triples, cardinality) = document.search_triples("", "", "")

    print("cardinality of { ?s ?p ?o }: %i" % cardinality)
    for triple in triples:
      print(triple)
  )docstring"
}

#endif /* DOCSTRINGS_HPP */

/**
 * hdt_document.cpp
 * Author: Thomas MINIER - MIT License 2017-2019
 */

#include "hdt_document.hpp"
#include "triple_iterator.hpp"
#include <HDTEnums.hpp>
#include <HDTManager.hpp>
#include <SingleTriple.hpp>
#include <fstream>
#include <pybind11/stl.h>

using namespace hdt;

/*!
 * Skip `offset` items from an iterator, optimized for HDT iterators.
 * @param it          - Iterator which should skip items
 * @param offset      - How many items to skip
 * @param cardinality - (Estimated) number of results
 */
template <typename T>
inline void applyOffset(T *it, unsigned int offset, unsigned int cardinality) {
  if (offset > 0 && offset >= cardinality) {
    // hdt does not allow to skip past beyond the estimated nb of results,
    // so we may have a few results to skip manually
    unsigned int remainingSteps = offset - cardinality + 1;
    it->skip(cardinality - 1);
    while (it->hasNext() && remainingSteps > 0) {
      it->next();
      remainingSteps--;
    }
  } else if (offset > 0) {
    it->skip(offset);
  }
}

/*!
 * Returns true if a file is readable, false otherwise
 * @param  name - Path to the file to test
 * @return true if the file is readable, false otherwise
 */
inline bool file_exists(const std::string &name) {
  std::ifstream f(name.c_str());
  bool result = f.good();
  f.close();
  return result;
}

/*!
 * Constructor
 * @param file - Path to HDT file to load
 */
HDTDocument::HDTDocument(std::string file) {
  hdt_file = file;
  if (!file_exists(file)) {
    throw std::runtime_error("Cannot open HDT file '" + file + "': Not Found!");
  }
  hdt = HDTManager::mapIndexedHDT(file.c_str());
  processor = new QueryProcessor(hdt);
}

/*!
 * Destructor
 */
HDTDocument::~HDTDocument() {}

/*!
 * Get the path to the HDT file currently loaded
 * @return The path to the HDT file currently loaded
 */
std::string HDTDocument::getFilePath() { return hdt_file; }

/*!
 * Implementation for Python function "__repr__"
 * @return A string representation of the object
 */
std::string HDTDocument::python_repr() {
  return "<HDTDocument " + hdt_file + " (~" + std::to_string(getNbTriples()) +
         " RDF triples)>";
}

/*!
 * Search all matching triples for a triple pattern, whith an optional limit and offset.
 * Returns a tuple<TripleIterator*, cardinality>
 * @param subject   - Triple pattern's subject
 * @param predicate - Triple pattern's predicate
 * @param object    - Triple pattern's object
 * @param limit     - (Optional) Maximum number of matching triples to read
 * @param offset    - (Optional) Number of matching triples to skip
 * @return A tuple (TripleIterator*, cardinality)
 */
search_results HDTDocument::search(std::string subject,
                                   std::string predicate,
                                   std::string object,
                                   unsigned int limit,
                                   unsigned int offset) {
  unsigned int idSubject = hdt->getDictionary()->stringToId(subject, hdt::SUBJECT);
  unsigned int idPredicate = hdt->getDictionary()->stringToId(predicate, hdt::PREDICATE);
  unsigned int idObject = hdt->getDictionary()->stringToId(object, hdt::OBJECT);
  search_results_ids tRes = searchIDs(idSubject, idPredicate, idObject, limit, offset);
  TripleIterator *resultIterator = new TripleIterator(std::get<0>(tRes), hdt->getDictionary());
  return std::make_tuple(resultIterator, std::get<1>(tRes));
}

/*!
 * Same as HDTDocument#search, but search for a TripleIDs instead.
 * Returns a tuple<TripleIDIterator*, cardinality>
 * @param subject   - Triple pattern's subject identifier
 * @param predicate - Triple pattern's predicate identifier
 * @param object    - Triple pattern's object identifier
 * @param limit     - (Optional) Maximum number of matching triples to read
 * @param offset    - (Optional) Number of matching triples to skip
 * @return A tuple (TripleIDIterator*, cardinality)
 */
search_results_ids HDTDocument::searchIDs(unsigned int subject,
                                          unsigned int predicate,
                                          unsigned int object,
                                          unsigned int limit,
                                          unsigned int offset) {
  TripleID tp(subject, predicate, object);
  // get RDF terms associated with each ID for metadata
  std::string strSubject = hdt->getDictionary()->idToString(subject, hdt::SUBJECT);
  std::string strPredicate = hdt->getDictionary()->idToString(predicate, hdt::PREDICATE);
  std::string strObject = hdt->getDictionary()->idToString(object, hdt::OBJECT);

  // build iterator
  IteratorTripleID *it = hdt->getTriples()->search(tp);
  size_t cardinality = it->estimatedNumResults();
  // apply offset
  applyOffset<IteratorTripleID>(it, offset, cardinality);
  TripleIDIterator *resultIterator =
      new TripleIDIterator(it, strSubject, strPredicate, strObject, limit, offset);
  return std::make_tuple(resultIterator, cardinality);
}

/*!
 * Get the total number of triples in the HDT document
 * @return The total number of triples in the HDT document
 */
unsigned int HDTDocument::getNbTriples() {
  return hdt->getTriples()->getNumberOfElements();
}

/*!
 * Get the number of distinct subjects in the HDT document
 * @return The number of distinct subjects in the HDT document
 */
unsigned int HDTDocument::getNbSubjects() {
  return hdt->getDictionary()->getNsubjects();
}

/*!
 * Get the number of distinct predicates in the HDT document
 * @return The number of distinct predicates in the HDT document
 */
unsigned int HDTDocument::getNbPredicates() {
  return hdt->getDictionary()->getNpredicates();
}

/*!
 * Get the number of distinct objects in the HDT document
 * @return The number of distinct objects in the HDT document
 */
unsigned int HDTDocument::getNbObjects() {
  return hdt->getDictionary()->getNobjects();
}

/*!
 * Get the number of shared subjects-objects in the HDT document
 * @return The number of shared subjects-objects in the HDT document
 */
unsigned int HDTDocument::getNbShared() {
  return hdt->getDictionary()->getNshared();
}

/*!
 * Convert a TripleID to a string RDF triple
 * @param  subject   - Triple's subject
 * @param  predicate - Triple's predicate
 * @param  object    - Triple's object
 * @return The associated RDF triple
 */
triple HDTDocument::convertTripleID(unsigned int subject, unsigned int predicate,
                                unsigned int object) {
  return std::make_tuple(
      hdt->getDictionary()->idToString(subject, hdt::SUBJECT),
      hdt->getDictionary()->idToString(predicate, hdt::PREDICATE),
      hdt->getDictionary()->idToString(object, hdt::OBJECT));
}

/**
 * Convert an Object Identifier into the equivalent URI/Literal value
 * @param  id  - Object Identifier
 * @param  pos - Identifier position (subject, predicate or object)
 * @return The URI/Literal equivalent to the Object Identifier
 */
string HDTDocument::convertID(unsigned int id, IdentifierPosition pos) {
  switch (pos) {
    case IdentifierPosition::Subject:
      return hdt->getDictionary()->idToString(id, hdt::SUBJECT);
    case IdentifierPosition::Predicate:
      return hdt->getDictionary()->idToString(id, hdt::PREDICATE);
    case IdentifierPosition::Object:
      return hdt->getDictionary()->idToString(id, hdt::OBJECT);
    default:
      throw std::runtime_error("Invalid Object Identifier exception");
  }
}

/**
 * Convert an RDF term into the associated an Object Identifier.
 * @param  term  - RDF Term in string format
 * @param  pos - Identifier position (subject, predicate or object)
 * @return The Object Identifier associated with the RDF term
 */
unsigned int HDTDocument::convertTerm(std::string term, IdentifierPosition pos) {
  switch (pos) {
    case IdentifierPosition::Subject:
      return hdt->getDictionary()->stringToId(term, hdt::SUBJECT);
    case IdentifierPosition::Predicate:
      return hdt->getDictionary()->stringToId(term, hdt::PREDICATE);
    case IdentifierPosition::Object:
      return hdt->getDictionary()->stringToId(term, hdt::OBJECT);
    default:
      throw std::runtime_error("Invalid Object Identifier exception");
  }
}

/**
 * Evaluate a join between a set of triple patterns using a JoinIterator.
 * @param  patterns - Set of triple patterns
 * @return A JoinIterator* used to evaluated the join.
 */
JoinIterator * HDTDocument::searchJoin(std::vector<triple> patterns) {
  set<string> vars {};
  vector<TripleString> joinPatterns {};
  std::string subj, pred, obj;

  for (auto it = patterns.begin(); it != patterns.end(); it++) {
    // unpack pattern
    std::tie(subj, pred, obj) = *it;
    // add variables
    if (subj.at(0) == '?') {
      vars.insert(subj);
    }
    if (pred.at(0) == '?') {
      vars.insert(pred);
    }
    if (obj.at(0) == '?') {
      vars.insert(obj);
    }
    // build join pattern
    TripleString pattern(subj, pred, obj);
    joinPatterns.push_back(pattern);
  }

  VarBindingString *iterator = processor->searchJoin(joinPatterns, vars);
  return new JoinIterator(iterator);
}

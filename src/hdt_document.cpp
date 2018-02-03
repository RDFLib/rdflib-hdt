/**
 * hdt_document.hpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#include <HDTManager.hpp>
#include <SingleTriple.hpp>
#include <HDTEnums.hpp>
#include "hdt_document.hpp"
#include "triple_iterator.hpp"

using namespace hdt;

/*!
 * Constructor
 * @param file [description]
 */
HDTDocument::HDTDocument(std::string file) {
  hdt_file = file;
  hdt = HDTManager::mapIndexedHDT(file.c_str());
}

/*!
 * Destructor
 */
HDTDocument::~HDTDocument() {}

/*!
 * Get the path to the HDT file currently loaded
 * @return [description]
 */
std::string HDTDocument::getFilePath() {
  return hdt_file;
}

/*!
 * Implementation for Python function "__repr__"
 * @return [description]
 */
std::string HDTDocument::python_repr() {
  return "<HDTDocument " + hdt_file + " (~" + std::to_string(getNbTriples()) + " RDF triples)>";
}

/*!
 * Search all matching triples for a triple pattern, whith an optional limit and offset.
 * Returns a tuple<vector<triples>, cardinality>
 * @param subject   [description]
 * @param predicate [description]
 * @param object    [description]
 * @param limit     [description]
 * @param offset    [description]
 */
search_results HDTDocument::search(std::string subject, std::string predicate, std::string object, unsigned int limit, unsigned int offset) {
  IteratorTripleString *it = hdt->search(subject.c_str(), predicate.c_str(), object.c_str());
  size_t cardinality = it->estimatedNumResults();

  // apply offset, limited to the triple cardinality at max
  if (offset > 0 && offset >= cardinality) {
    // hdt does not allow to skip past beyond nb of results,
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
  TripleIterator* resultIterator = new TripleIterator(it, subject, predicate, object, limit, offset);
  return std::make_tuple(resultIterator, cardinality);
}

/*!
 * Same as search, but for an iterator over TripleIDs.
 * Returns a tuple<TripleIDIterator*, cardinality>
 * @param subject   [description]
 * @param predicate [description]
 * @param object    [description]
 * @param limit     [description]
 * @param offset    [description]
 */
search_results_ids HDTDocument::searchIDs(std::string subject, std::string predicate, std::string object, unsigned int limit, unsigned int offset) {
  TripleID tp(
    hdt->getDictionary()->stringToId(subject, hdt::SUBJECT),
    hdt->getDictionary()->stringToId(predicate, hdt::PREDICATE),
    hdt->getDictionary()->stringToId(object, hdt::OBJECT)
  );
  IteratorTripleID *it = hdt->getTriples()->search(tp);
  size_t cardinality = it->estimatedNumResults();

  // apply offset
  if (offset > 0 && offset >= cardinality) {
    // hdt does not allow to skip past beyond nb of results,
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
  TripleIDIterator* resultIterator = new TripleIDIterator(it, subject, predicate, object, limit, offset);
  return std::make_tuple(resultIterator, cardinality);
}

/*!
 * Get the total number of triples in the HDT document
 * @return [description]
 */
unsigned int HDTDocument::getNbTriples() {
  return hdt->getTriples()->getNumberOfElements();
}

/*!
 * Get the number of subjects in the HDT document
 * @return [description]
 */
unsigned int HDTDocument::getNbSubjects() {
  return hdt->getDictionary()->getNsubjects();
}

/*!
 * Get the number of predicates in the HDT document
 * @return [description]
 */
unsigned int HDTDocument::getNbPredicates() {
  return hdt->getDictionary()->getNpredicates();
}

/*!
 * Get the number of objects in the HDT document
 * @return [description]
 */
unsigned int HDTDocument::getNbObjects() {
  return hdt->getDictionary()->getNobjects();
}

/*!
 * Get the number of shared subjects-objects in the HDT document
 * @return [description]
 */
unsigned int HDTDocument::getNbShared() {
  return hdt->getDictionary()->getNshared();
}

/*!
 * Convert a TripleID to a string triple pattern
 * @param  subject   [description]
 * @param  predicate [description]
 * @param  object    [description]
 * @return           [description]
 */
triple HDTDocument::idsToString (unsigned int subject, unsigned int predicate, unsigned int object) {
  return std::make_tuple(
    hdt->getDictionary()->idToString(subject, hdt::SUBJECT),
    hdt->getDictionary()->idToString(predicate, hdt::PREDICATE),
    hdt->getDictionary()->idToString(object, hdt::OBJECT)
  );
}

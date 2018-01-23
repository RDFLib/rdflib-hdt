/**
 * tripleid_iterator.cpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#include "tripleid_iterator.hpp"
#include <HDTEnums.hpp>
#include <SingleTriple.hpp>
#include <pybind11/pybind11.h>

/*!
 * Constructor
 * @param iterator [description]
 */
TripleIDIterator::TripleIDIterator(hdt::IteratorTripleID *_it, std::string _subj, std::string _pred, std::string _obj, unsigned int _limit, unsigned int _offset) :
  iterator(_it),
  subject((_subj.compare("") == 0) ? "?s" : _subj),
  predicate((_pred.compare("") == 0) ? "?p" : _pred),
  object((_obj.compare("") == 0) ? "?o" : _obj),
  limit(_limit),
  offset(_offset) {};

  /*!
   * Destructor
   */
TripleIDIterator::~TripleIDIterator() {
  delete iterator;
};

/*!
 * Implementation for Python function "__repr__"
 * @return [description]
 */
std::string TripleIDIterator::python_repr() {
  if (limit != 0 && offset > 0) {
    return "<TripleIDIterator {" + subject + " " + predicate + " " + object + "} LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + " >";
  } else if (limit != 0) {
    return "<TripleIDIterator {" + subject + " " + predicate + " " + object + "} LIMIT " + std::to_string(limit) + " >";
  } else if (offset > 0) {
    return "<TripleIDIterator {" + subject + " " + predicate + " " + object + "} OFFSET " + std::to_string(offset) + ">";
  }
  return "<TripleIDIterator {" + subject + " " + predicate + " " + object + "}>";
}

/*!
 * Implementation for Python function "__iter__"
 * @return [description]
 */
TripleIDIterator* TripleIDIterator::python_iter() {
  return this;
}

/*!
 * Get the subject of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIDIterator::getSubject() {
  return subject;
}

/*!
 * Get the predicate of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIDIterator::getPredicate() {
  return predicate;
}

/*!
 * Get the object of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIDIterator::getObject() {
  return object;
}

/*!
 * Get the limit of the current iterator
 * @return [description]
 */
unsigned int TripleIDIterator::getLimit() {
  return limit;
}

/*!
 * Get the offset of the current iterator
 * @return [description]
 */
unsigned int TripleIDIterator::getOffset() {
  return offset;
}

/*!
 * Get the estimated cardinality of the pattern currently evaluated.
 * Offset & limit are not taken into account.
 * @return [description]
 */
size_t TripleIDIterator::estimateCardinality() {
  return iterator->estimatedNumResults();
}

/*!
 * Return true if the estimated number of results is accurate, false otherwise
 * @return [description]
 */
bool TripleIDIterator::accurateEstimation() {
  return iterator->numResultEstimation() == hdt::EXACT;
}

/*!
 * Return true if the iterator still has items available, False otherwise.
 * @return [description]
 */
bool TripleIDIterator::hasNext() {
  bool noLimit = limit == 0;
  return iterator->hasNext() && (noLimit || limit > resultsRead);
}

/**
 * Get the next item in the iterator, or raise py::StopIteration if the iterator has ended.
 * Used to implement Python Itertor protocol.
 * @return [description]
 */
triple_id TripleIDIterator::next() {
  bool noLimit = limit == 0;
  if(iterator->hasNext() && (noLimit || limit > resultsRead)) {
    resultsRead++;
    hdt::TripleID *ts = iterator->next();
    return std::make_tuple(ts->getSubject(), ts->getPredicate(), ts->getObject());
  }
  throw pybind11::stop_iteration();
}

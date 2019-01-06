/**
 * tripleid_iterator.cpp
 * Author: Thomas MINIER - MIT License 2017-2019
 */

#include "tripleid_iterator.hpp"
#include <HDTEnums.hpp>
#include <SingleTriple.hpp>
#include <pybind11/pybind11.h>

/*!
 * Constructor
 * @param iterator [description]
 */
TripleIDIterator::TripleIDIterator(hdt::IteratorTripleID *_it,
                                   std::string _subj, std::string _pred,
                                   std::string _obj, unsigned int _limit,
                                   unsigned int _offset)
    : subject((_subj.compare("") == 0) ? "?s" : _subj),
      predicate((_pred.compare("") == 0) ? "?p" : _pred),
      object((_obj.compare("") == 0) ? "?o" : _obj), limit(_limit),
      offset(_offset), iterator(_it){};

/*!
 * Destructor
 */
TripleIDIterator::~TripleIDIterator() { delete iterator; };

/*!
 * Implementation for Python function "__repr__"
 * @return [description]
 */
std::string TripleIDIterator::python_repr() {
  if (limit != 0 && offset > 0) {
    return "<Iterator {" + subject + " " + predicate + " " + object +
           "} LIMIT " + std::to_string(limit) + " OFFSET " +
           std::to_string(offset) + " >";
  } else if (limit != 0) {
    return "<Iterator {" + subject + " " + predicate + " " + object +
           "} LIMIT " + std::to_string(limit) + " >";
  } else if (offset > 0) {
    return "<Iterator {" + subject + " " + predicate + " " + object +
           "} OFFSET " + std::to_string(offset) + ">";
  }
  return "<Iterator {" + subject + " " + predicate + " " + object + "}>";
}

/*!
 * Get the subject of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIDIterator::getSubject() { return subject; }

/*!
 * Get the predicate of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIDIterator::getPredicate() { return predicate; }

/*!
 * Get the object of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIDIterator::getObject() { return object; }

/*!
 * Get the limit of the current iterator
 * @return [description]
 */
unsigned int TripleIDIterator::getLimit() { return limit; }

/*!
 * Get the offset of the current iterator
 * @return [description]
 */
unsigned int TripleIDIterator::getOffset() { return offset; }

/*!
 * Get the number of results read by the iterator
 * @return [description]
 */
unsigned int TripleIDIterator::getNbResultsRead() { return resultsRead; }

/*!
 * Implementation for Python function "__iter__"
 * @return [description]
 */
TripleIDIterator *TripleIDIterator::python_iter() { return this; }

/*!
 * Get a hint over the cardinality of the triple pattern evaluated.
 * Offset & limit are not taken into account.
 * @return [description]
 */
size_hint TripleIDIterator::sizeHint() {
  return std::make_tuple(iterator->estimatedNumResults(), iterator->numResultEstimation() == hdt::EXACT);
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
 * Get the next item in the iterator, or raise py::StopIteration if the iterator
 * has ended. Used to implement Python Itertor protocol.
 * @return [description]
 */
triple_id TripleIDIterator::next() {
  // return any previously peeked value
  if (hasBufferedTriple) {
    hasBufferedTriple = false;
    resultsRead++;
    return _bufferedTriple;
  }
  bool noLimit = limit == 0;
  if (iterator->hasNext() && (noLimit || limit > resultsRead)) {
    resultsRead++;
    hdt::TripleID *ts = iterator->next();
    return std::make_tuple(ts->getSubject(), ts->getPredicate(),
                           ts->getObject());
  }
  throw pybind11::stop_iteration();
}

/**
 * Get the next item in the iterator, or raise py::StopIteration if the iterator
 * has ended, but without advancing the iterator.
 * @return [description]
 */
triple_id TripleIDIterator::peek() {
  if (hasBufferedTriple) {
    return _bufferedTriple;
  }
  _bufferedTriple = next();
  hasBufferedTriple = true;
  resultsRead--;
  return _bufferedTriple;
}

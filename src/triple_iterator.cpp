/**
 * triple_iterator.cpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#include "triple_iterator.hpp"
#include <HDTEnums.hpp>
#include <SingleTriple.hpp>
#include <pybind11/pybind11.h>

/*!
 * Constructor
 * @param iterator [description]
 */
TripleIterator::TripleIterator(hdt::IteratorTripleString *_it,
                               std::string _subj, std::string _pred,
                               std::string _obj, unsigned int _limit,
                               unsigned int _offset)
    : HDTTripleIterator(_subj, _pred, _obj, _limit, _offset), iterator(_it){};

/*!
 * Destructor
 */
TripleIterator::~TripleIterator() { delete iterator; };

/*!
 * Implementation for Python function "__iter__"
 * @return [description]
 */
TripleIterator *TripleIterator::python_iter() { return this; }

/*!
 * Get the estimated cardinality of the pattern currently evaluated.
 * Offset & limit are not taken into account.
 * @return [description]
 */
size_t TripleIterator::estimateCardinality() {
  return iterator->estimatedNumResults();
}

/*!
 * Return true if the estimated number of results is accurate, false otherwise
 * @return [description]
 */
bool TripleIterator::accurateEstimation() {
  return iterator->numResultEstimation() == hdt::EXACT;
}

/*!
 * Return true if the iterator still has items available, False otherwise.
 * @return [description]
 */
bool TripleIterator::hasNext() {
  bool noLimit = limit == 0;
  return iterator->hasNext() && (noLimit || limit > resultsRead);
}

/**
 * Get the next item in the iterator, or raise py::StopIteration if the iterator
 * has ended. Used to implement Python Itertor protocol.
 * @return [description]
 */
triple TripleIterator::next() {
  // return any previously peeked value
  if (hasBufferedTriple) {
    hasBufferedTriple = false;
    resultsRead++;
    return _bufferedTriple;
  }
  bool noLimit = limit == 0;
  if (iterator->hasNext() && (noLimit || limit > resultsRead)) {
    resultsRead++;
    hdt::TripleString *ts = iterator->next();
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
triple TripleIterator::peek() {
  if (hasBufferedTriple) {
    return _bufferedTriple;
  }
  _bufferedTriple = next();
  hasBufferedTriple = true;
  resultsRead--;
  return _bufferedTriple;
}

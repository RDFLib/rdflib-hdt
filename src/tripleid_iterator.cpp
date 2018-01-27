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
  HDTTripleIterator(_subj,  _pred, _obj, _limit, _offset),
  iterator(_it)
  {};

  /*!
   * Destructor
   */
TripleIDIterator::~TripleIDIterator() {
  delete iterator;
};

/*!
 * Implementation for Python function "__iter__"
 * @return [description]
 */
TripleIDIterator* TripleIDIterator::python_iter() {
  return this;
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

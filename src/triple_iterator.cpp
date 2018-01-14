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
TripleIterator::TripleIterator(hdt::IteratorTripleString *_it, std::string _subj, std::string _pred, std::string _obj, unsigned int _limit, unsigned int _offset) :
  iterator(_it),
  subject(_subj),
  predicate(_pred),
  object(_obj),
  limit(_limit),
  offset(_offset) {};

  /*!
   * Destructor
   */
TripleIterator::~TripleIterator() {
  delete iterator;
};

/*!
 * Implementation for Python function "__repr__"
 * @return [description]
 */
std::string TripleIterator::python_repr() {
  return "<TripleIterator (" + subject + " " + predicate + " " + object + ")>";
}

/*!
 * Implementation for Python function "__iter__"
 * @return [description]
 */
TripleIterator* TripleIterator::python_iter() {
  return this;
}

/*!
 * Get the subject of the triple pattern currenlty evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIterator::getSubject() {
  return subject;
}

/*!
 * Get the predicate of the triple pattern currenlty evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIterator::getPredicate() {
  return predicate;
}

/*!
 * Get the object of the triple pattern currenlty evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIterator::getObject() {
  return object;
}

/*!
 * Get the limit of the current iterator
 * @return [description]
 */
unsigned int TripleIterator::getLimit() {
  return limit;
}

/*!
 * Get the offset of the current iterator
 * @return [description]
 */
unsigned int TripleIterator::getOffset() {
  return offset;
}

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
 * Get the next item in the iterator, or raise py::StopIteration if the iterator has ended.
 * Used to implement Python Itertor protocol.
 * @return [description]
 */
triple TripleIterator::next() {
  bool noLimit = limit == 0;
  if(iterator->hasNext() && (noLimit || limit > resultsRead)) {
    resultsRead++;
    hdt::TripleString *ts = iterator->next();
    return std::make_tuple(ts->getSubject(), ts->getPredicate(), ts->getObject());
  }
  throw pybind11::stop_iteration();
}

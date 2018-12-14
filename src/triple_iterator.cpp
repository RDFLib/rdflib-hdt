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
TripleIterator::TripleIterator(TripleIDIterator *_it, hdt::Dictionary *_dict)
    : iterator(_it), dictionary(_dict) {};

/*!
 * Destructor
 */
TripleIterator::~TripleIterator() { delete iterator; };

/*!
 * Implementation for Python function "__repr__"
 * @return [description]
 */
std::string TripleIterator::python_repr() {
  if (getLimit() != 0 && getOffset() > 0) {
    return "<Iterator {" + getSubject() + " " + getPredicate() + " " + getObject() +
           "} LIMIT " + std::to_string(getLimit()) + " OFFSET " +
           std::to_string(getOffset()) + " >";
  } else if (getLimit() != 0) {
    return "<Iterator {" + getSubject() + " " + getPredicate() + " " + getObject() +
           "} LIMIT " + std::to_string(getLimit()) + " >";
  } else if (getOffset() > 0) {
    return "<Iterator {" + getSubject() + " " + getPredicate() + " " + getObject() +
           "} OFFSET " + std::to_string(getOffset()) + ">";
  }
  return "<Iterator {" + getSubject() + " " + getPredicate() + " " + getObject() + "}>";
}

/*!
 * Get the subject of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIterator::getSubject() { return iterator->getSubject(); }

/*!
 * Get the predicate of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIterator::getPredicate() { return iterator->getPredicate(); }

/*!
 * Get the object of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIterator::getObject() { return iterator->getObject(); }

/*!
 * Get the limit of the current iterator
 * @return [description]
 */
unsigned int TripleIterator::getLimit() { return iterator->getLimit(); }

/*!
 * Get the offset of the current iterator
 * @return [description]
 */
unsigned int TripleIterator::getOffset() { return iterator->getOffset(); }

/*!
 * Get the number of results read by the iterator
 * @return [description]
 */
unsigned int TripleIterator::getNbResultsRead() { return iterator->getNbResultsRead(); }

/*!
 * Implementation for Python function "__iter__"
 * @return [description]
 */
TripleIterator *TripleIterator::python_iter() { return this; }

/*!
 * Get a hint over the cardinality of the triple pattern evaluated.
 * Offset & limit are not taken into account.
 * @return [description]
 */
size_hint TripleIterator::sizeHint() {
  return iterator->sizeHint();
}

/*!
 * Return true if the iterator still has items available, False otherwise.
 * @return [description]
 */
bool TripleIterator::hasNext() {
  return iterator->hasNext();
}

/**
 * Get the next item in the iterator, or raise py::StopIteration if the iterator
 * has ended. Used to implement Python Itertor protocol.
 * @return [description]
 */
triple TripleIterator::next() {
  triple_id t = iterator->next();
  return std::make_tuple(
    dictionary->idToString(std::get<0>(t), hdt::SUBJECT),
    dictionary->idToString(std::get<1>(t), hdt::PREDICATE),
    dictionary->idToString(std::get<2>(t), hdt::OBJECT));
}

/**
 * Get the next item in the iterator, or raise py::StopIteration if the iterator
 * has ended, but without advancing the iterator.
 * @return [description]
 */
triple TripleIterator::peek() {
  triple_id t = iterator->peek();
  return std::make_tuple(
    dictionary->idToString(std::get<0>(t), hdt::SUBJECT),
    dictionary->idToString(std::get<1>(t), hdt::PREDICATE),
    dictionary->idToString(std::get<2>(t), hdt::OBJECT));
}

/**
 * triple_iterator_bytes.cpp
 * Author: Arnaud GRALL - MIT License 2017-2019
 */

#include "triple_iterator_bytes.hpp"
#include <HDTEnums.hpp>
#include <SingleTriple.hpp>
#include <pybind11/pybind11.h>
namespace py = pybind11;

/*!
 * Constructor
 * @param iterator [description]
 */
TripleIteratorBytes::TripleIteratorBytes(TripleIDIterator *_it, hdt::Dictionary *_dict)
    : iterator(_it), dictionary(_dict) {};

/*!
 * Destructor
 */
TripleIteratorBytes::~TripleIteratorBytes() { delete iterator; };

/*!
 * Implementation for Python function "__repr__"
 * @return [description]
 */
std::string TripleIteratorBytes::python_repr() {
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
std::string TripleIteratorBytes::getSubject() { return iterator->getSubject(); }

/*!
 * Get the predicate of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIteratorBytes::getPredicate() { return iterator->getPredicate(); }

/*!
 * Get the object of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string TripleIteratorBytes::getObject() { return iterator->getObject(); }

/*!
 * Get the limit of the current iterator
 * @return [description]
 */
unsigned int TripleIteratorBytes::getLimit() { return iterator->getLimit(); }

/*!
 * Get the offset of the current iterator
 * @return [description]
 */
unsigned int TripleIteratorBytes::getOffset() { return iterator->getOffset(); }

/*!
 * Get the number of results read by the iterator
 * @return [description]
 */
unsigned int TripleIteratorBytes::getNbResultsRead() { return iterator->getNbResultsRead(); }

/*!
 * Implementation for Python function "__iter__"
 * @return [description]
 */
TripleIteratorBytes *TripleIteratorBytes::python_iter() { return this; }

/*!
 * Get a hint over the cardinality of the triple pattern evaluated.
 * Offset & limit are not taken into account.
 * @return [description]
 */
size_hint TripleIteratorBytes::sizeHint() {
  return iterator->sizeHint();
}

/*!
 * Return true if the iterator still has items available, False otherwise.
 * @return [description]
 */
bool TripleIteratorBytes::hasNext() {
  return iterator->hasNext();
}

/**
 * Get the next item in the iterator, or raise py::StopIteration if the iterator
 * has ended. Used to implement Python Itertor protocol.
 * @return [description]
 */
triple_bytes TripleIteratorBytes::next() {
  triple_id t = iterator->next();
  return std::make_tuple(
    py::bytes(dictionary->idToString(std::get<0>(t), hdt::SUBJECT)),
    py::bytes(dictionary->idToString(std::get<1>(t), hdt::PREDICATE)),
    py::bytes(dictionary->idToString(std::get<2>(t), hdt::OBJECT)));
}

/**
 * Get the next item in the iterator, or raise py::StopIteration if the iterator
 * has ended, but without advancing the iterator.
 * @return [description]
 */
triple_bytes TripleIteratorBytes::peek() {
  triple_id t = iterator->peek();
  return std::make_tuple(
    py::bytes(dictionary->idToString(std::get<0>(t), hdt::SUBJECT)),
    py::bytes(dictionary->idToString(std::get<1>(t), hdt::PREDICATE)),
    py::bytes(dictionary->idToString(std::get<2>(t), hdt::OBJECT)));
}

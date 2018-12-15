/**
 * join_iterator.cpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#include "join_iterator.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

/*!
 * Constructor
 * @param _it [description]
 */
JoinIterator::JoinIterator(hdt::VarBindingString *_it) : iterator(_it) {}

/*!
 * Destructor
 */
JoinIterator::~JoinIterator() {
  delete iterator;
}

/*!
 * Implementation for Python function "__repr__"
 * @return [description]
 */
std::string JoinIterator::python_repr() { return ""; }


/*!
 * Implementation for Python function "__iter__"
 * @return [description]
 */
JoinIterator *JoinIterator::python_iter() { return this; }

/**
 * Get the estimated join cardinality
 * @return [description]
 */
size_t JoinIterator::estimatedCardinality() {
  return iterator->estimatedNumResults();
}

/**
 * Reset the iterator into its initial state and restart join processing.
 */
void JoinIterator::reset() {
  iterator->goToStart();
}

/*!
 * Return true if the iterator still has items available, False otherwise.
 * @return [description]
 */
bool JoinIterator::hasNext() {
  return hasNextSolution;
}

/**
 * Return the next set of solutions bindings, or raise py::StopIteration if the iterator
 * has ended. Used to implement Python Itertor protocol.
 * @return [description]
 */
solution_bindings JoinIterator::next() {
  hasNextSolution = iterator->findNext();
  // stop iteration if the iterator has ended
  if (!hasNextSolution) {
    throw pybind11::stop_iteration();
  }
  solution_bindings solutions = new std::set<single_binding>();
  // build solution bindings
  for(unsigned int i = 0; i < iterator->getNumVars(); i++) {
    solutions->insert(std::make_tuple(iterator->getVarName(i), iterator->getVar(i)));
  }
  return solutions;
}

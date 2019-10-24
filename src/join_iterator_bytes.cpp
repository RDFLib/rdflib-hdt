/**
 * join_iterator_bytes.cpp
 * Author: Thomas MINIER - MIT License 2017-2019
 */

#include "join_iterator_bytes.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

/*!
 * Constructor
 * @param _it [description]
 */
JoinIteratorBytes::JoinIteratorBytes(hdt::VarBindingString *_it) : iterator(_it) {}

/*!
 * Destructor
 */
JoinIteratorBytes::~JoinIteratorBytes() {
  delete iterator;
}

/*!
 * Implementation for Python function "__repr__"
 * @return [description]
 */
std::string JoinIteratorBytes::python_repr() {
  return "JoinIteratorBytes";
}


/*!
 * Implementation for Python function "__iter__"
 * @return [description]
 */
JoinIteratorBytes *JoinIteratorBytes::python_iter() { return this; }

/**
 * Get the estimated join cardinality
 * @return [description]
 */
size_t JoinIteratorBytes::estimatedCardinality() {
  return iterator->estimatedNumResults();
}

/**
 * Reset the iterator into its initial state and restart join processing.
 */
void JoinIteratorBytes::reset() {
  iterator->goToStart();
}

/*!
 * Return true if the iterator still has items available, False otherwise.
 * @return [description]
 */
bool JoinIteratorBytes::hasNext() {
  return hasNextSolution;
}

/**
 * Return the next set of solutions bindings, or raise py::StopIteration if the iterator
 * has ended. Used to implement Python Itertor protocol.
 * @return [description]
 */
py::set JoinIteratorBytes::next() {
  hasNextSolution = iterator->findNext();
  // stop iteration if the iterator has ended
  if (!hasNextSolution) {
    throw pybind11::stop_iteration();
  }
  solution_bindings_bytes solutions_bytes;
  // build solution bindings
  for(unsigned int i = 0; i < iterator->getNumVars(); i++) {
    std::string varname = iterator->getVarName(i);
    std::string value = iterator->getVar(i);
    solutions_bytes.add(std::make_tuple(py::bytes(varname), py::bytes(value)));
  }
  return solutions_bytes;
}

/**
 * join_iterator.hpp
 * Author: Arnaud Grall - MIT License 2017-2019
 */

#ifndef JOIN_ITERATOR_BYTES_HPP
#define JOIN_ITERATOR_BYTES_HPP

#include "pyhdt_types.hpp"
#include "QueryProcessor.hpp"
#include <string>

/*!
 * JoinIterator iterates over solution bindings of a join
 * @author Arnaud Grall
 */
class JoinIteratorBytes {
private:
  hdt::VarBindingString *iterator;
  bool hasNextSolution = true;

public:
  /*!
   * Constructor
   * @param iterator [description]
   */
  JoinIteratorBytes(hdt::VarBindingString *_it);

  /*!
   * Destructor
   */
  ~JoinIteratorBytes();

  /*!
   * Implementation for Python function "__repr__"
   * @return [description]
   */
  std::string python_repr();

  /*!
   * Implementation for Python function "__iter__"
   * @return [description]
   */
  JoinIteratorBytes *python_iter();

  /**
   * Get the estimated join cardinality
   * @return [description]
   */
  size_t estimatedCardinality();

  /**
   * Reset the iterator into its initial state and restart join processing.
   */
  void reset();

  /*!
   * Return true if the iterator still has items available, False otherwise.
   * @return [description]
   */
  bool hasNext();

  /**
   * Return the next set of solutions bindings, or raise py::StopIteration if the iterator
   * has ended. Used to implement Python Itertor protocol.
   * @return [description]
   */
  py::set next();

};

#endif /* JOIN_ITERATOR_BYTES_HPP */

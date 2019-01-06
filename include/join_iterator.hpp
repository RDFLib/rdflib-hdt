/**
 * join_iterator.hpp
 * Author: Thomas MINIER - MIT License 2017-2019
 */

#ifndef JOIN_ITERATOR_HPP
#define JOIN_ITERATOR_HPP

#include "pyhdt_types.hpp"
#include "QueryProcessor.hpp"
#include <string>

/*!
 * JoinIterator iterates over solution bindings of a join
 * @author Thomas Minier
 */
class JoinIterator {
private:
  hdt::VarBindingString *iterator;
  bool hasNextSolution = true;

public:
  /*!
   * Constructor
   * @param iterator [description]
   */
  JoinIterator(hdt::VarBindingString *_it);

  /*!
   * Destructor
   */
  ~JoinIterator();

  /*!
   * Implementation for Python function "__repr__"
   * @return [description]
   */
  std::string python_repr();

  /*!
   * Implementation for Python function "__iter__"
   * @return [description]
   */
  JoinIterator *python_iter();

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
  solution_bindings next();

};

#endif /* JOIN_ITERATOR_HPP */

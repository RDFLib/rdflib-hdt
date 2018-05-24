/**
 * triple_iterator.hpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#ifndef TRIPLE_ITERATOR_HPP
#define TRIPLE_ITERATOR_HPP

#include "hdt_triple_iterator.hpp"
#include "pyhdt_types.hpp"
#include <Iterator.hpp>
#include <string>

/*!
 * TripleIterator iterates over RDF triples of an HDT document which match a
 * triple pattern + limit + offset \author Thomas Minier
 */
class TripleIterator : HDTTripleIterator {
private:
  hdt::IteratorTripleString *iterator;
  triple _bufferedTriple;
  bool hasBufferedTriple = false;

public:
  /*!
   * Constructor
   * @param iterator [description]
   */
  TripleIterator(hdt::IteratorTripleString *_it, std::string _subj,
                 std::string _pred, std::string _obj, unsigned int _limit,
                 unsigned int _offset);

  /*!
   * Destructor
   */
  ~TripleIterator();

  /*!
   * Implementation for Python function "__iter__"
   * @return [description]
   */
  TripleIterator *python_iter();

  /*!
   * Get the estimated cardinality of the pattern currently evaluated.
   * Offset & limit are not taken into account.
   * @return [description]
   */
  size_hint sizeHint();

  /*!
   * Return true if the iterator still has items available, False otherwise.
   * @return [description]
   */
  bool hasNext();

  /**
   * Get the next item in the iterator, or raise py::StopIteration if the
   * iterator has ended
   * @return [description]
   */
  triple next();

  /**
   * Get the next item in the iterator, or raise py::StopIteration if the
   * iterator has ended, but without advancing the iterator.
   * @return [description]
   */
  triple peek();
};

#endif /* TRIPLE_ITERATOR_HPP */

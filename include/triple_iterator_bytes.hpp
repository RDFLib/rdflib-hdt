/**
 * triple_iterator_bytes.hpp
 * Author: Arnaud GRALL - MIT License 2017-2019
 */

#ifndef TRIPLE_ITERATOR_BYTES_HPP
#define TRIPLE_ITERATOR_BYTES_HPP

#include "tripleid_iterator.hpp"
#include "pyhdt_types.hpp"
#include "Dictionary.hpp"
#include <string>

/*!
 * TripleIterator iterates over RDF triples of an HDT document which match a
 * triple pattern + limit + offset \author Thomas Minier
 */
class TripleIteratorBytes {
private:
  TripleIDIterator *iterator;
  hdt::Dictionary *dictionary;

public:
  /*!
   * Constructor
   * @param iterator [description]
   */
  TripleIteratorBytes(TripleIDIterator *_it, hdt::Dictionary *_dict);

  /*!
   * Destructor
   */
  ~TripleIteratorBytes();

  /*!
   * Implementation for Python function "__repr__"
   * @return [description]
   */
  std::string python_repr();

  /*!
   * Get the subject of the triple pattern currently evaluated.
   * An empty string represents a variable
   * @return [description]
   */
  std::string getSubject();

  /*!
   * Get the predicate of the triple pattern currently evaluated.
   * An empty string represents a variable
   * @return [description]
   */
  std::string getPredicate();

  /*!
   * Get the object of the triple pattern currently evaluated.
   * An empty string represents a variable
   * @return [description]
   */
  std::string getObject();

  /*!
   * Get the limit of the current iterator
   * @return [description]
   */
  unsigned int getLimit();

  /*!
   * Get the offset of the current iterator
   * @return [description]
   */
  unsigned int getOffset();

  /*!
   * Get the number of results read by the iterator
   * @return [description]
   */
  unsigned int getNbResultsRead();

  /*!
   * Implementation for Python function "__iter__"
   * @return [description]
   */
  TripleIteratorBytes *python_iter();

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
  triple_bytes next();

  /**
   * Get the next item in the iterator, or raise py::StopIteration if the
   * iterator has ended, but without advancing the iterator.
   * @return [description]
   */
  triple_bytes peek();
};

#endif /* TRIPLE_ITERATOR_BYTES_HPP */

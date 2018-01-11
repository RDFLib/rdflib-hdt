/**
 * triple_iterator.hpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#ifndef TRIPLE_ITERATOR_HPP
#define TRIPLE_ITERATOR_HPP

#include <string>
#include "Iterator.hpp"
#include "pyhdt_types.hpp"

/*!
 * TripleIterator iterates over RDF triples of an HDT document which match a triple pattern + limit + offset
 * \author Thomas Minier
 */
class TripleIterator {
private:
  hdt::IteratorTripleString *iterator;
  std::string subject;
  std::string predicate;
  std::string object;
  unsigned int limit;
  unsigned int offset;
public:
  /*!
   * Constructor
   * @param iterator [description]
   */
  TripleIterator(hdt::IteratorTripleString *iterator, std::string subject, std::string predicate, std::string object, unsigned int limit, unsigned int offset);

  /*!
   * Destructor
   */
  ~TripleIterator();

  /*!
   * Implementation for Python function "__repr__"
   * @return [description]
   */
  std::string python_repr();

  /*!
   * Get the subject of the triple pattern currenlty evaluated.
   * An empty string represents a variable
   * @return [description]
   */
  std::string getSubject();

  /*!
   * Get the predicate of the triple pattern currenlty evaluated.
   * An empty string represents a variable
   * @return [description]
   */
  std::string getObject();

  /*!
   * Get the object of the triple pattern currenlty evaluated.
   * An empty string represents a variable
   * @return [description]
   */
  std::string getPredicate();

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
   * Get the estimated cardinality of the pattern currenlty evaluated.
   * Offset & limit are not taken into account.
   * @return [description]
   */
  size_t estimateCardinality();

  /*!
   * Return true if the estimated number of results is accurate, false otherwise
   * @return [description]
   */
  bool accurateEstimation();

  /**
   * Get the next item in the iterator, or raise py::StopIteration if the iterator has ended
   * @return [description]
   */
  triple next();
};

#endif /* TRIPLE_ITERATOR_HPP */

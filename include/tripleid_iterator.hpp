/**
 * tripleid_iterator.hpp
 * Author: Thomas MINIER - MIT License 2017-2019
 */

#ifndef TRIPLEID_ITERATOR_HPP
#define TRIPLEID_ITERATOR_HPP

#include "pyhdt_types.hpp"
#include <Iterator.hpp>
#include <string>

/*!
 * TripleIDIterator iterates over IDs of RDF triples of an HDT document which
 * match a triple pattern + limit + offset \author Thomas Minier
 */
class TripleIDIterator {
private:
  std::string subject;
  std::string predicate;
  std::string object;
  unsigned int limit;
  unsigned int offset;
  hdt::IteratorTripleID *iterator;
  triple_id _bufferedTriple;
  bool hasBufferedTriple = false;
  unsigned int resultsRead = 0;

public:
  /*!
   * Constructor
   * @param iterator [description]
   */
  TripleIDIterator(hdt::IteratorTripleID *_it, std::string _subj,
                   std::string _pred, std::string _obj, unsigned int _limit,
                   unsigned int _offset);

  /*!
   * Destructor
   */
  ~TripleIDIterator();

  /*!
   * Implementation for Python function "__repr__"
   * @return [description]
   */
  std::string python_repr();

  /*!
   * Get the subject of the triple pattern currently evaluated.
   * @return [description]
   */
  std::string getSubject();

  /*!
   * Get the predicate of the triple pattern currently evaluated.
   * @return [description]
   */
  std::string getPredicate();

  /*!
   * Get the object of the triple pattern currently evaluated.
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
  TripleIDIterator *python_iter();

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
  triple_id next();

  /**
   * Get the next item in the iterator, or raise py::StopIteration if the
   * iterator has ended, but without advancing the iterator.
   * @return [description]
   */
  triple_id peek();
};

#endif /* TRIPLEID_ITERATOR_HPP */

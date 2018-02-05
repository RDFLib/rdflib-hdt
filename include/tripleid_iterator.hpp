/**
 * tripleid_iterator.hpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#ifndef TRIPLEID_ITERATOR_HPP
#define TRIPLEID_ITERATOR_HPP

#include <string>
#include <Iterator.hpp>
#include "pyhdt_types.hpp"
#include "hdt_triple_iterator.hpp"

/*!
 * TripleIDIterator iterates over IDs of RDF triples of an HDT document which match a triple pattern + limit + offset
 * \author Thomas Minier
 */
class TripleIDIterator: HDTTripleIterator {
private:
  hdt::IteratorTripleID *iterator;
  triple_id _bufferedTriple;
  bool hasBufferedTriple = false;
public:
  /*!
   * Constructor
   * @param iterator [description]
   */
  TripleIDIterator(hdt::IteratorTripleID *_it, std::string _subj, std::string _pred, std::string _obj, unsigned int _limit, unsigned int _offset);

  /*!
   * Destructor
   */
  ~TripleIDIterator();

  /*!
   * Implementation for Python function "__iter__"
   * @return [description]
   */
  TripleIDIterator* python_iter();

  /*!
   * Get the estimated cardinality of the pattern currently evaluated.
   * Offset & limit are not taken into account.
   * @return [description]
   */
  size_t estimateCardinality();

  /*!
   * Return true if the estimated number of results is accurate, false otherwise
   * @return [description]
   */
  bool accurateEstimation();

  /*!
   * Return true if the iterator still has items available, False otherwise.
   * @return [description]
   */
  bool hasNext();

  /**
   * Get the next item in the iterator, or raise py::StopIteration if the iterator has ended
   * @return [description]
   */
  triple_id next();

  /**
   * Get the next item in the iterator, or raise py::StopIteration if the iterator has ended,
   * but without advancing the iterator.
   * @return [description]
   */
  triple_id peek();
};

#endif /* TRIPLEID_ITERATOR_HPP */

/**
 * hdt_triple_iterator.hpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#ifndef HDT_TRIPLE_ITERATOR_HPP
#define HDT_TRIPLE_ITERATOR_HPP

#include <string>

/*!
 * HDTTripleIterator represents an abstract iterator over an HDTDocument
 * \author Thomas Minier
 */
class HDTTripleIterator {
protected:
  std::string subject;
  std::string predicate;
  std::string object;
  unsigned int limit;
  unsigned int offset;
  unsigned int resultsRead = 0;

public:
  /*!
   * Constructor
   * @param iterator [description]
   */
  HDTTripleIterator(std::string _subj, std::string _pred, std::string _obj,
                    unsigned int _limit, unsigned int _offset);

  /*!
   * Destructor
   */
  ~HDTTripleIterator();

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
   * Set the number of results read by the iterator
   * @return [description]
   */
  void setNbResultsRead(unsigned int value);
};

#endif /* HDT_TRIPLE_ITERATOR_HPP */

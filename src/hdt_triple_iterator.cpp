/**
 * hdt_triple_iterator.cpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#include "hdt_triple_iterator.hpp"

/*!
 * Constructor
 * @param iterator [description]
 */
HDTTripleIterator::HDTTripleIterator(std::string _subj, std::string _pred, std::string _obj, unsigned int _limit, unsigned int _offset) :
  subject((_subj.compare("") == 0) ? "?s" : _subj),
  predicate((_pred.compare("") == 0) ? "?p" : _pred),
  object((_obj.compare("") == 0) ? "?o" : _obj),
  limit(_limit),
  offset(_offset) {};

/*!
 * Destructor
 */
HDTTripleIterator::~HDTTripleIterator() {};

/*!
 * Implementation for Python function "__repr__"
 * @return [description]
 */
std::string HDTTripleIterator::python_repr() {
  if (limit != 0 && offset > 0) {
    return "<Iterator {" + subject + " " + predicate + " " + object + "} LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + " >";
  } else if (limit != 0) {
    return "<Iterator {" + subject + " " + predicate + " " + object + "} LIMIT " + std::to_string(limit) + " >";
  } else if (offset > 0) {
    return "<Iterator {" + subject + " " + predicate + " " + object + "} OFFSET " + std::to_string(offset) + ">";
  }
  return "<Iterator {" + subject + " " + predicate + " " + object + "}>";
}

/*!
 * Get the subject of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string HDTTripleIterator::getSubject() {
  return subject;
}

/*!
 * Get the predicate of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string HDTTripleIterator::getPredicate() {
  return predicate;
}

/*!
 * Get the object of the triple pattern currently evaluated.
 * An empty string represents a variable
 * @return [description]
 */
std::string HDTTripleIterator::getObject() {
  return object;
}

/*!
 * Get the limit of the current iterator
 * @return [description]
 */
unsigned int HDTTripleIterator::getLimit() {
  return limit;
}

/*!
 * Get the offset of the current iterator
 * @return [description]
 */
unsigned int HDTTripleIterator::getOffset() {
  return offset;
}

/*!
 * Get the number of results read by the iterator
 * @return [description]
 */
unsigned int HDTTripleIterator::getNbResultsRead() {
  return resultsRead;
}

/*!
 * Set the number of results read by the iterator
 * @return [description]
 */
void HDTTripleIterator::setNbResultsRead(unsigned int value) {
  resultsRead = value;
}

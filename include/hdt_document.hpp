/**
 * hdt_document.hpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#ifndef PYHDT_DOCUMENT_HPP
#define PYHDT_DOCUMENT_HPP

#include <string>
#include <list>
#include "HDT.hpp"
#include "pyhdt_types.hpp"

/*!
 * HDTDocument is the main entry to manage an hdt document
 * \author Thomas Minier
 */
class HDTDocument {
private:
  std::string hdt_file;
  hdt::HDT *hdt;
  HDTDocument(std::string file);
public:
  /*!
   * Destructor
   */
  ~HDTDocument();

  /*!
   * Get the path to the HDT file currently loaded
   * @return [description]
   */
  std::string getFilePath();

  /*!
   * Implementation for Python function "__repr__"
   * @return [description]
   */
  std::string python_repr();

  /*!
   * Get the total number of triples in the HDT document
   * @return [description]
   */
  unsigned int getNbTriples();

  /*!
   * Get the number of subjects in the HDT document
   * @return [description]
   */
  unsigned int getNbSubjects();

  /*!
   * Get the number of predicates in the HDT document
   * @return [description]
   */
  unsigned int getNbPredicates();

  /*!
   * Get the number of objects in the HDT document
   * @return [description]
   */
  unsigned int getNbObjects();

  /*!
   * Get the number of shared subjects-objects in the HDT document
   * @return [description]
   */
  unsigned int getNbShared();

  /*!
   * Static factory method used to create a new HDT Document
   * @param  file
   */
  static HDTDocument create(std::string file) {
    return HDTDocument(file);
  }

  /*!
   * Search all matching triples for a triple pattern, whith an optional limit and offset.
   * Returns a tuple<vector<triples>, cardinality>
   * @param subject   [description]
   * @param predicate [description]
   * @param object    [description]
   * @param limit     [description]
   * @param offset    [description]
   */
  search_results search(std::string subject, std::string predicate, std::string object, unsigned int limit = 0, unsigned int offset = 0);
};

#endif /* PYHDT_DOCUMENT_HPP */

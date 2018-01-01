/**
 * hdt_document.hpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#ifndef PYHDT_DOCUMENT_HPP
#define PYHDT_DOCUMENT_HPP

#include <string>
#include "HDT.hpp"
#include <list>
#include <tuple>

typedef std::tuple<std::string, std::string, std::string> triple;
typedef std::list<triple> triple_list;
typedef std::tuple<triple_list, size_t> search_results;

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

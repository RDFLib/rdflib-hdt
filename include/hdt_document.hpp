/**
 * hdt_document.hpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#include <string>

/*!
 * HDTDocument is the main entry to manage an hdt document
 * \author Thomas Minier
 */
class HDTDocument {
private:
 HDTDocument(std::string file);
public:
   static HDTDocument create(std::string file) {
     return HDTDocument(file);
   }
};

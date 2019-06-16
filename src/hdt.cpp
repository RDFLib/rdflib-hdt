/**
 * hdt.cpp
 * Author: Thomas MINIER - MIT License 2017-2019
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "docstrings.hpp"
#include "hdt_document.hpp"
#include "triple_iterator.hpp"
#include "tripleid_iterator.hpp"
#include "join_iterator.hpp"

namespace py = pybind11;

PYBIND11_MODULE(hdt, m) {
  m.doc() = MODULE_DOC;

  py::enum_<IdentifierPosition>(m, "IdentifierPosition", IDENTIFIER_POSITION_DOC)
    .value("Subject", IdentifierPosition::Subject)
    .value("Predicate", IdentifierPosition::Predicate)
    .value("Object", IdentifierPosition::Object)
    .export_values();

  py::class_<TripleIterator>(m, "TripleIterator", TRIPLE_ITERATOR_CLASS_DOC)
      .def("next", &TripleIterator::next, TRIPLE_ITERATOR_NEXT_DOC)
      .def("__next__", &TripleIterator::next, TRIPLE_ITERATOR_NEXT_DOC)
      .def("peek", &TripleIterator::peek, TRIPLE_ITERATOR_PEEK_DOC)
      .def("has_next", &TripleIterator::hasNext, TRIPLE_ITERATOR_HASNEXT_DOC)
      .def("size_hint", &TripleIterator::sizeHint, TRIPLE_ITERATOR_SIZE_DOC)
      .def("__len__", &TripleIterator::sizeHint,
           TRIPLE_ITERATOR_SIZE_DOC)
      .def("__iter__", &TripleIterator::python_iter)
      .def_property_readonly("subject", &TripleIterator::getSubject,
                             TRIPLE_ITERATOR_GETSUBJECT_DOC)
      .def_property_readonly("predicate", &TripleIterator::getPredicate,
                             TRIPLE_ITERATOR_GETPREDICATE_DOC)
      .def_property_readonly("object", &TripleIterator::getObject,
                             TRIPLE_ITERATOR_GETOBJECT_DOC)
      .def_property_readonly("limit", &TripleIterator::getLimit,
                             TRIPLE_ITERATOR_GETLIMIT_DOC)
      .def_property_readonly("offset", &TripleIterator::getOffset,
                             TRIPLE_ITERATOR_GETOFFSET_DOC)
      .def_property_readonly("nb_reads", &TripleIterator::getNbResultsRead,
                    TRIPLE_ITERATOR_NBREADS_DOC)
      .def("__repr__", &TripleIterator::python_repr);

  py::class_<TripleIDIterator>(m, "TripleIDIterator", TRIPLE_ID_ITERATOR_CLASS_DOC)
      .def("next", &TripleIDIterator::next, TRIPLE_ITERATOR_NEXT_DOC)
      .def("__next__", &TripleIDIterator::next, TRIPLE_ITERATOR_NEXT_DOC)
      .def("peek", &TripleIDIterator::peek, TRIPLE_ITERATOR_PEEK_DOC)
      .def("has_next", &TripleIDIterator::hasNext, TRIPLE_ITERATOR_HASNEXT_DOC)
      .def("size_hint", &TripleIDIterator::sizeHint, TRIPLE_ITERATOR_SIZE_DOC)
      .def("__len__", &TripleIDIterator::sizeHint, TRIPLE_ITERATOR_SIZE_DOC)
      .def("__iter__", &TripleIDIterator::python_iter)
      .def_property_readonly("subject", &TripleIDIterator::getSubject,
                             TRIPLE_ITERATOR_GETSUBJECT_DOC)
      .def_property_readonly("predicate", &TripleIDIterator::getPredicate,
                             TRIPLE_ITERATOR_GETPREDICATE_DOC)
      .def_property_readonly("object", &TripleIDIterator::getObject,
                             TRIPLE_ITERATOR_GETOBJECT_DOC)
      .def_property_readonly("limit", &TripleIDIterator::getLimit,
                             TRIPLE_ITERATOR_GETLIMIT_DOC)
      .def_property_readonly("offset", &TripleIDIterator::getOffset,
                             TRIPLE_ITERATOR_GETOFFSET_DOC)
      .def_property_readonly("nb_reads", &TripleIDIterator::getNbResultsRead,
                    TRIPLE_ITERATOR_NBREADS_DOC)
      .def("__repr__", &TripleIDIterator::python_repr);

  py::class_<JoinIterator>(m, "JoinIterator", JOIN_ITERATOR_CLASS_DOC)
    .def("next", &JoinIterator::next, JOIN_ITERATOR_NEXT_DOC)
    .def("has_next", &JoinIterator::hasNext, JOIN_ITERATOR_HAS_NEXT_DOC)
    .def("cardinality", &JoinIterator::estimatedCardinality, JOIN_ITERATOR_SIZE_DOC)
    .def("reset", &JoinIterator::reset, JOIN_ITERATOR_RESET_DOC)
    .def("__len__", &JoinIterator::estimatedCardinality, JOIN_ITERATOR_SIZE_DOC)
    .def("__next__", &JoinIterator::next, JOIN_ITERATOR_NEXT_DOC)
    .def("__iter__", &JoinIterator::python_iter)
    .def("__repr__", &JoinIterator::python_repr);

  py::class_<HDTDocument>(m, "HDTDocument", HDT_DOCUMENT_CLASS_DOC)
      .def(py::init(&HDTDocument::create), py::arg("file"),
                                           py::arg("map") = true,
                                           py::arg("indexed") = true)
      .def_property_readonly("file_path", &HDTDocument::getFilePath,
                             HDT_DOCUMENT_GETFILEPATH_DOC)
      .def_property_readonly("total_triples", &HDTDocument::getNbTriples,
                             HDT_DOCUMENT_GETNBTRIPLES_DOC)
      .def_property_readonly("nb_subjects", &HDTDocument::getNbSubjects,
                             HDT_DOCUMENT_GETNBSUBJECTS_DOC)
      .def_property_readonly("nb_predicates", &HDTDocument::getNbPredicates,
                             HDT_DOCUMENT_GETNBPREDICATES_DOC)
      .def_property_readonly("nb_objects", &HDTDocument::getNbObjects,
                             HDT_DOCUMENT_GETNBOBJECTS_DOC)
      .def_property_readonly("nb_shared", &HDTDocument::getNbShared,
                             HDT_DOCUMENT_GETNBSHARED_DOC)
      .def("search_triples", &HDTDocument::search,
           HDT_DOCUMENT_SEARCH_TRIPLES_DOC, py::arg("subject"),
           py::arg("predicate"), py::arg("object"), py::arg("limit") = 0,
           py::arg("offset") = 0)
      .def("search_join", &HDTDocument::searchJoin, HDT_DOCUMENT_SEARCH_JOIN_DOC, py::arg("patterns"))
     .def("search_triples_ids", &HDTDocument::searchIDs,
          HDT_DOCUMENT_SEARCH_TRIPLES_IDS_DOC, py::arg("subject"),
          py::arg("predicate"), py::arg("object"), py::arg("limit") = 0,
          py::arg("offset") = 0)
      .def("convert_tripleid", &HDTDocument::convertTripleID,
           HDT_DOCUMENT_TRIPLES_IDS_TO_STRING_DOC,
           py::arg("subject"), py::arg("predicate"), py::arg("object"))
      .def("convert_id", &HDTDocument::convertID, HDT_DOCUMENT_CONVERT_ID_DOC,
           py::arg("id"), py::arg("position"))
     .def("convert_term", &HDTDocument::convertTerm, HDT_DOCUMENT_CONVERT_TERM_DOC,
          py::arg("term"), py::arg("position"))
      .def("__len__", &HDTDocument::getNbTriples, HDT_DOCUMENT_GETNBTRIPLES_DOC)
      .def("__repr__", &HDTDocument::python_repr);

}

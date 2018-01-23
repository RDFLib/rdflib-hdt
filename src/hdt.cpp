#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "docstrings.hpp"
#include "hdt_document.hpp"
#include "triple_iterator.hpp"
#include "tripleid_iterator.hpp"

namespace py = pybind11;

PYBIND11_MODULE(hdt, m) {
    m.doc() = MODULE_DOC;

    py::class_<TripleIterator>(m, "TripleIterator", TRIPLE_ITERATOR_CLASS_DOC)
    .def("next", &TripleIterator::next, TRIPLE_ITERATOR_NEXT_DOC)
    .def("__next__", &TripleIterator::next, TRIPLE_ITERATOR_NEXT_DOC)
    .def("has_next", &TripleIterator::hasNext, TRIPLE_ITERATOR_HASNEXT_DOC)
    .def("get_subject", &TripleIterator::getSubject, TRIPLE_ITERATOR_GETSUBJECT_DOC)
    .def("get_predicate", &TripleIterator::getPredicate, TRIPLE_ITERATOR_GETPREDICATE_DOC)
    .def("get_object", &TripleIterator::getObject, TRIPLE_ITERATOR_GETOBJECT_DOC)
    .def("get_limit", &TripleIterator::getLimit, TRIPLE_ITERATOR_GETLIMIT_DOC)
    .def("get_offset", &TripleIterator::getOffset, TRIPLE_ITERATOR_GETOFFSET_DOC)
    .def("get_nb_results", &TripleIterator::estimateCardinality, TRIPLE_ITERATOR_SIZE_DOC)
    .def("accurate_estimation", &TripleIterator::accurateEstimation, TRIPLE_ITERATOR_ACC_ESTIMATION_DOC)
    .def("__len__", &TripleIterator::estimateCardinality, TRIPLE_ITERATOR_SIZE_DOC)
    .def("__iter__", &TripleIterator::python_iter)
    .def("__repr__", &TripleIterator::python_repr);

    py::class_<TripleIDIterator>(m, "TripleIDIterator", TRIPLE_ID_ITERATOR_CLASS_DOC)
    .def("next", &TripleIDIterator::next, TRIPLE_ITERATOR_NEXT_DOC)
    .def("__next__", &TripleIDIterator::next, TRIPLE_ITERATOR_NEXT_DOC)
    .def("has_next", &TripleIDIterator::hasNext, TRIPLE_ITERATOR_HASNEXT_DOC)
    .def("get_subject", &TripleIDIterator::getSubject, TRIPLE_ITERATOR_GETSUBJECT_DOC)
    .def("get_predicate", &TripleIDIterator::getPredicate, TRIPLE_ITERATOR_GETPREDICATE_DOC)
    .def("get_object", &TripleIDIterator::getObject, TRIPLE_ITERATOR_GETOBJECT_DOC)
    .def("get_limit", &TripleIDIterator::getLimit, TRIPLE_ITERATOR_GETLIMIT_DOC)
    .def("get_offset", &TripleIDIterator::getOffset, TRIPLE_ITERATOR_GETOFFSET_DOC)
    .def("get_nb_results", &TripleIDIterator::estimateCardinality, TRIPLE_ITERATOR_SIZE_DOC)
    .def("accurate_estimation", &TripleIDIterator::accurateEstimation, TRIPLE_ITERATOR_ACC_ESTIMATION_DOC)
    .def("__len__", &TripleIDIterator::estimateCardinality, TRIPLE_ITERATOR_SIZE_DOC)
    .def("__iter__", &TripleIDIterator::python_iter)
    .def("__repr__", &TripleIDIterator::python_repr);

    py::class_<HDTDocument>(m, "HDTDocument", HDT_DOCUMENT_CLASS_DOC)
      .def(py::init(&HDTDocument::create))
      .def("get_file_path", &HDTDocument::getFilePath, HDT_DOCUMENT_GETFILEPATH_DOC)
      .def("get_total_triples", &HDTDocument::getNbTriples, HDT_DOCUMENT_GETNBTRIPLES_DOC)
      .def("get_nb_subjects", &HDTDocument::getNbSubjects, HDT_DOCUMENT_GETNBSUBJECTS_DOC)
      .def("get_nb_predicates", &HDTDocument::getNbPredicates, HDT_DOCUMENT_GETNBPREDICATES_DOC)
      .def("get_nb_objects", &HDTDocument::getNbObjects, HDT_DOCUMENT_GETNBOBJECTS_DOC)
      .def("get_nb_shared", &HDTDocument::getNbShared, HDT_DOCUMENT_GETNBSHARED_DOC)
      .def("search_triples", &HDTDocument::search, HDT_DOCUMENT_SEARCH_TRIPLES_DOC,
          py::arg("subject"), py::arg("predicate"), py::arg("object"), py::arg("limit") = 0, py::arg("offset") = 0)
      .def("search_triples_ids", &HDTDocument::searchIDs, HDT_DOCUMENT_SEARCH_TRIPLES_DOC,
          py::arg("subject"), py::arg("predicate"), py::arg("object"), py::arg("limit") = 0, py::arg("offset") = 0)
      .def("tripleid_to_string", &HDTDocument::idsToString)
      .def("__repr__", &HDTDocument::python_repr);
}

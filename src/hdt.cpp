#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "docstrings.hpp"
#include "hdt_document.hpp"
#include "triple_iterator.hpp"

namespace py = pybind11;

PYBIND11_MODULE(hdt, m) {
    m.doc() = MODULE_DOC;

    py::class_<TripleIterator>(m, "TripleIterator", "A TripleIterator iterates over triples in a HDT file matching a triple pattern")
    .def("next", &TripleIterator::next)
    .def("has_next", &TripleIterator::hasNext)
    .def("get_subject", &TripleIterator::getSubject)
    .def("get_predicate", &TripleIterator::getPredicate)
    .def("get_object", &TripleIterator::getObject)
    .def("get_limit", &TripleIterator::getLimit)
    .def("get_offset", &TripleIterator::getOffset)
    .def("get_nb_results", &TripleIterator::estimateCardinality)
    .def("accurate_estimation", &TripleIterator::accurateEstimation)
    .def("__repr__", &TripleIterator::python_repr);

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
      .def("search_triples_iter", &HDTDocument::searchIter, "",
          py::arg("subject"), py::arg("predicate"), py::arg("object"), py::arg("limit") = 0, py::arg("offset") = 0)
      .def("__repr__", &HDTDocument::python_repr);
}

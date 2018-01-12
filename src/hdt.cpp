#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "docstrings.hpp"
#include "hdt_document.hpp"

namespace py = pybind11;

PYBIND11_MODULE(hdt, m) {
    m.doc() = MODULE;

    py::class_<HDTDocument>(m, "HDTDocument", HDT_DOCUMENT_CLASS)
      .def(py::init(&HDTDocument::create))
      .def("get_file_path", &HDTDocument::getFilePath, HDT_DOCUMENT_GETFILEPATH)
      .def("get_total_triples", &HDTDocument::getNbTriples, HDT_DOCUMENT_GETNBTRIPLES)
      .def("get_nb_subjects", &HDTDocument::getNbSubjects, HDT_DOCUMENT_GETNBSUBJECTS)
      .def("get_nb_predicates", &HDTDocument::getNbPredicates, HDT_DOCUMENT_GETNBPREDICATES)
      .def("get_nb_objects", &HDTDocument::getNbObjects, HDT_DOCUMENT_GETNBOBJECTS)
      .def("get_nb_shared", &HDTDocument::getNbShared, HDT_DOCUMENT_GETNBSHARED)
      .def("search_triples", &HDTDocument::search, HDT_DOCUMENT_SEARCH_TRIPLES,
          py::arg("subject"), py::arg("predicate"), py::arg("object"), py::arg("limit") = 0, py::arg("offset") = 0)
      .def("__repr__", &HDTDocument::python_repr);

}

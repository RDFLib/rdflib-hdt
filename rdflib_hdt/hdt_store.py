"""
rdflib_hdt.hdt_store
=======================
"""
from typing import Iterable, Optional, Tuple, Union

from rdflib import Literal, URIRef
from rdflib.store import Store
from rdflib_hdt.hdt_document import HDTDocument

Term = Union[URIRef, Literal]
SearchQuery = Tuple[Optional[Term], Optional[Term], Optional[Term]]


class HDTStore(Store):
    """An implementation of a Store over a HDT document.

    It is heavily inspired by the work from @FlorianLudwig (https://github.com/RDFLib/rdflib/issues/894)

    .. warning:: By default, the HDTStore discards RDF Terms with invalid UTF-8 encoding. You can change this behaviour with the `safe-mode` parameter of the constructor.

    Args:
      - path: Absolute path to the HDT file to load.
      - mapped: True if the document must be mapped on disk, False to load it in-memory.
      - indexed: True if the document must be indexed. Indexed must be located in the same directory as the HDT file. Missing indexes will be generated at startup.
      - safe_mode: True if Unicode errors should be ignored, False otherwise.
    """
    def __init__(self, path: str, mapped: bool = True, indexed: bool = True, safe_mode=True, configuration=None, identifier=None):
        super(HDTStore, self).__init__(configuration=configuration, identifier=identifier)
        self._hdt_document = HDTDocument(path, mapped=mapped, indexed=indexed, safe_mode=safe_mode)

    def is_safe(self) -> bool:
        """Returnd True if the HDT store ignores Unicode errors, False otherwise"""
        return self._hdt_document.is_safe()

    def __len__(self) -> int:
        """The number of RDF triples in the HDT store"""
        return self._hdt_document.total_triples

    def nb_subjects(self) -> int:
        """The number of subjects in the HDT store"""
        return self._hdt_document.nb_subjects

    def nb_predicates(self) -> int:
        """The number of predicates in the HDT store"""
        return self._hdt_document.nb_predicates

    def nb_objects(self) -> int:
        """The number of objects in the HDT store"""
        return self._hdt_document.nb_objects

    def nb_shared(self) -> int:
        """The number of shared subject-object in the HDT store"""
        return self._hdt_document.nb_shared

    def triples(self, pattern, context) -> Iterable[Tuple[Term, Term, Term]]:
        """Search for a triple pattern in a HDT store.

        Args:
          - pattern: The triple pattern (s, p, o) to search for
         - context: The query execution context

        Returns:
          A generator that produces RDF triples matching the input triple pattern
        """
        iterator, cardinality = self._hdt_document.search(pattern)
        for triple in iterator:
            yield triple, None

    def create(self, configuration):
        raise TypeError('The HDT store is read only')

    def destroy(self, configuration):
        raise TypeError('The HDT store is read only')

    def commit(self):
        raise TypeError('The HDT store is read only')

    def rollback(self):
        raise TypeError('The HDT store is read only')

    def add(self, _, context=None, quoted=False):
        raise TypeError('The HDT store is read only')

    def addN(self, quads):
        raise TypeError('The HDT store is read only')

    def remove(self, _, context):
        raise TypeError('The HDT store is read only')

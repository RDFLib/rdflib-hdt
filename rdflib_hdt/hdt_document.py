"""
rdflib_hdt.hdt_document
=======================
"""
from typing import Optional, Tuple, Union

import hdt
from rdflib_hdt.iterators import HDTIterator, HDTJoinIterator
from rdflib_hdt.mapping import rdflib_to_hdt, term_to_rdflib
from rdflib_hdt.types import BGP, SearchQuery, Term


class HDTDocument(hdt.HDTDocument):
    """An HDT document, in read-only mode.

    This class is a wrapper over the original hdt.HDTDocument class,
    which aligns it with the RDFlib data model.

    .. warning:: By default, an HDTDocument discards RDF Terms with invalid UTF-8 encoding. You can change this behavior with the `safe_mode` parameter of the constructor.

    Args:
      - path: Absolute path to the HDT file to load.
      - mapped: True if the document must be mapped on disk, False to load it in memory.
      - indexed: True if the document must be indexed. Indexed must be located in the same directory as the HDT file. Missing indexes are automatically generated at startup.
      - safe_mode: True if Unicode errors should be ignored, False otherwise.
    """
    def __init__(self, path: str, mapped: bool = True, indexed: bool = True, safe_mode=True):
        super(HDTDocument, self).__init__(path, mapped, indexed)
        self._safe_mode = safe_mode

    def is_safe(self) -> bool:
        """Return True if the HDT document ignores Unicode errors, False otherwise."""
        return self._safe_mode

    def from_tripleid(self, triple_id: Union[int, int, int]) -> Term:
        """Transform an RDF triple from a TripleID representation to an RDFlib representation.

        Argument:
          - triple_id: 3-tuple of IDs (s, p, o)

        Return:
            A triple in RDFlib representation, i.e., a 3-tuple of RDFlib terms.
        """
        s, p, o = super().convert_tripleid(triple_id[0], triple_id[1], triple_id[2])
        return (term_to_rdflib(s), term_to_rdflib(p), term_to_rdflib(o))

    def to_tripleid(self, triple: SearchQuery) -> Tuple[int, int, int]:
        """Transform a triple (pattern) from an RDFlib representation to a TripleID.

        It can be used to transform an RDFlib query before feeding it
        into the :py:meth:`rdflib_hdt.HDTDocument.search_ids` method.

        Argument:
          - triple: 3-tuple of RDF Terms. Use `None` to indicate wildcards.

        Return:
            A triple in TripleID representation, i.e., a 3-tuple of integers
        """
        subj = super().convert_term(rdflib_to_hdt(triple[0]), hdt.Subject) if triple[0] is not None else 0
        pred = super().convert_term(rdflib_to_hdt(triple[1]), hdt.Predicate) if triple[1] is not None else 0
        obj = super().convert_term(rdflib_to_hdt(triple[2]), hdt.Object) if triple[2] is not None else 0
        return (subj, pred, obj)

    def search(self, query: SearchQuery, limit=0, offset=0) -> Tuple[HDTIterator, int]:
        """Search for RDF triples matching the query triple pattern, with an optional limit and offset. Use `None` for wildcards/variables.

        Args:
          - query: The triple pattern (s, p, o) to search. Use `None` to indicate wildcards/variables.
          - limit: (optional) Maximum number of triples to search.
          - offset: (optional) Number of matching triples to skip before returning results.

        Return:
            A 2-elements tuple (iterator, estimated pattern cardinality), where
            the iterator is a generator of matching RDF triples. An RDF triple itself is a 3-elements tuple (subject, predicate, object) of RDF terms (in rdflib format).
        """
        subj = rdflib_to_hdt(query[0]) if query[0] is not None else ""
        pred = rdflib_to_hdt(query[1]) if query[1] is not None else ""
        obj = rdflib_to_hdt(query[2]) if query[2] is not None else ""
        triples, cardinality = super().search_triples(subj, pred, obj, limit=limit, offset=offset)
        iterator = HDTIterator(triples, safe_mode=self._safe_mode)
        return iterator, cardinality

    def search_ids(self, query: Union[Optional[int], Optional[int], Optional[int]], limit=0, offset=0) -> Tuple[hdt.TripleIDIterator, int]:
        """Same as :meth:`rdflib_hdt.HDTDocument.search_triples`, but RDF triples are represented as unique ids (from the HDT Dictionnary). Use `None` or `0` to indicate wildcards/variables.

        Mapping between ids and RDF terms is done using the :meth:`rdflib_hdt.HDTDocument.from_tripleid`, :py:meth:`rdflib_hdt.HDTDocument.to_tripleid`, and :meth:`rdflib_hdt.HDTDocument.term_to_id` methods.

        Args:
          - query: A tuple of triple patterns IDs (s, p, o) to search. Use `None` or `0` to indicate wildcards/variables.
          - limit: (optional) Maximum number of triples to search.
          - offset: (optional) Number of matching triples to skip before returning results.

        Return:
            A 2-elements tuple (iterator, estimated pattern cardinality), where
            the iterator is a generator of matching RDF triples. An RDF triple itself is a 3-elements tuple (subject, predicate, object) of IDs (positive integers from the HDT Dictionnary).
        """
        subj = query[0] if query[0] is not None else 0
        pred = query[1] if query[1] is not None else 0
        obj = query[2] if query[2] is not None else 0
        return super().search_triples_ids(subj, pred, obj, limit=limit, offset=offset)

    def search_join(self, patterns: BGP) -> hdt.JoinIterator:
        """Evaluate a join between a set of triple patterns using an iterator.
        A triple pattern itself is a 3-elements ``tuple`` (subject, predicate, object) of RDFlib terms with at least one SPARQL variable.

        Argument: A set of triple patterns.

        Return:
            A :py:class:`rdflib_hdt.HDTJoinIterator` which produces :py:class:`rdflib.query.Results`, per the Python iteration protocol.
        """
        bgp = [(rdflib_to_hdt(s), rdflib_to_hdt(p), rdflib_to_hdt(o)) for s, p, o in patterns]
        join_iterator = super().search_join(bgp)
        return HDTJoinIterator(join_iterator, safe_mode=self._safe_mode)

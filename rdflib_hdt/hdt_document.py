"""
rdflib_hdt.hdt_document
=======================
"""
import hdt
from rdflib import URIRef, Literal
from rdflib.util import from_n3
from typing import Iterable, Optional, Tuple, Union


Term = Union[URIRef, Literal]
SearchQuery = Tuple[Optional[Term], Optional[Term], Optional[Term]]


def term_to_rdflib(term: str) -> Term:
    """Convert an HDT term into its RDFlib representation"""
    if term.startswith("\""):
        return from_n3(term)
    else:
        return URIRef(term)


def triple_to_rdflib(triple: Tuple[str, str, str]) -> Tuple[Term, Term, Term]:
    """Convert an HDT Triple into its RDFlib representation"""
    s, p, o = triple
    return (term_to_rdflib(s), term_to_rdflib(p), term_to_rdflib(o))


def rdflib_to_hdt(term: Term) -> str:
    """Convert an RDFlib term into an HDT representation"""
    value = term.n3()
    if value.startswith('<') and value.endswith('>'):
        return value[1: len(value) - 1]
    return value


class HDTDocument(hdt.HDTDocument):
    """An HDT document, in read-only mode.

    This is a wrapper over the original hdt.HDTDocument class,
    which align it with the RDFlib data model.

    Args:
        - path: Absolute path to the HDT file to load.
        - mapped: True if the document must be mapped on disk, False to load it in-memory.
        - indexed: True if the document must be indexed. Indexed must be located in the same directory as the HDT file. Missing indexes will be generated at startup.
    """
    def __init__(self, path: str, mapped: bool = True, indexed: bool = True):
        super(HDTDocument, self).__init__(path, mapped, indexed)

    def search(self, query: SearchQuery, limit=0, offset=0) -> Tuple[Iterable[Tuple[Term, Term, Term]], int]:
        """Search for RDF triples matching the query triple pattern, with an optional limit and offset. Use `Node` for SPARQL variables.

        Args:
          - subject: The subject of the triple pattern to seach for.
          - predicate: The predicate of the triple pattern to seach for.
          - obj: The object of the triple pattern ot seach for.
          - limit: (optional) Maximum number of triples to search for.
          - offset: (optional) Number of matching triples to skip before returning results.

        Return:
            A 2-elements tuple (iterator, estimated pattern cardinality), where
            the iterator is a generator of matching RDF triples. A RDF triple itself is a 3-elements tuple (subject, predicate, object) of RDF terms (in rdflib format).
        """
        subj = rdflib_to_hdt(query[0]) if query[0] is not None else ""
        pred = rdflib_to_hdt(query[1]) if query[1] is not None else ""
        obj = rdflib_to_hdt(query[2]) if query[2] is not None else ""
        triples, cardinality = super().search_triples(subj, pred, obj, limit=limit, offset=offset)
        return map(triple_to_rdflib, triples), cardinality

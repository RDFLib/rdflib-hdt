"""
rdflib_hdt.hdt_document
=======================
"""
from typing import Iterable, Optional, Tuple, Union

import hdt
from rdflib import Literal, URIRef
from rdflib.util import from_n3

Term = Union[URIRef, Literal]
SearchQuery = Tuple[Optional[Term], Optional[Term], Optional[Term]]


def term_to_rdflib(term: str) -> Term:
    """Convert an HDT term into its RDFlib representation"""
    if term.startswith("\""):
        return from_n3(term)
    else:
        return URIRef(term)


def rdflib_to_hdt(term: Term) -> str:
    """Convert an RDFlib term into an HDT representation"""
    value = term.n3()
    if value.startswith('<') and value.endswith('>'):
        return value[1: len(value) - 1]
    return value


class HDTIterator:
    """An iterator to converts HDT matching triples to RDFlib data model.

    Args:
      - input: Input iterator that produces RDF triples with RDF terms in string format.
      - cardinality: Estimate cardinality of the input iterator.
      - safe_mode: True if Unicode errors should be ignored, False otherwise.
    """
    def __init__(self, input: Iterable[Tuple[str, str, str]], cardinality: int, safe_mode=True):
        super(HDTIterator, self).__init__()
        self._input = input
        self._cardinality = cardinality
        self._safe_mode = safe_mode

    def __len__(self):
        """The estimated number of matchinf RDF triples"""
        return self._cardinality

    def __iter__(self):
        return self

    def __next__(self):
        """Support for the Python 2.x iterator protocol"""
        return self.next()

    def next(self) -> Tuple[Term, Term, Term]:
        """Produce a new RDF triple following the Python iterator protocol"""
        try:
            triple = next(self._input)
            if triple is None:
                raise StopIteration()
            s, p, o = triple
            return (term_to_rdflib(s), term_to_rdflib(p), term_to_rdflib(o))
        except UnicodeDecodeError as e:
            # crash if not in safe mode
            if not self._safe_mode:
                raise e
            # otherwise, try to read a valid RDF triple from the input
            return self.next()
        except StopIteration as e:
            raise e


class HDTDocument(hdt.HDTDocument):
    """An HDT document, in read-only mode.

    This is a wrapper over the original hdt.HDTDocument class,
    which align it with the RDFlib data model.

    Args:
      - path: Absolute path to the HDT file to load.
      - mapped: True if the document must be mapped on disk, False to load it in-memory.
      - indexed: True if the document must be indexed. Indexed must be located in the same directory as the HDT file. Missing indexes will be generated at startup.
      - safe_mode: True if Unicode errors should be ignored, False otherwise.
    """
    def __init__(self, path: str, mapped: bool = True, indexed: bool = True, safe_mode=True):
        super(HDTDocument, self).__init__(path, mapped, indexed)
        self._safe_mode = safe_mode

    def is_safe(self) -> bool:
        """Returnd True if the HDT document ignores Unicode errors, False otherwise"""
        return self._safe_mode

    def search(self, query: SearchQuery, limit=0, offset=0) -> Tuple[HDTIterator, int]:
        """Search for RDF triples matching the query triple pattern, with an optional limit and offset. Use `Node` for SPARQL variables.

        Args:
          - query: The triple pattern (s, p, o) to search for. Use `None` to indicate wildecards.
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
        iterator = HDTIterator(triples, cardinality, safe_mode=self._safe_mode)
        return iterator, cardinality

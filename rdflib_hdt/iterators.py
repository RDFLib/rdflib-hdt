"""
rdflib_hdt.iterators
=======================

This module contains iterators that wraps native HDT iterator to the RDFlib data model.
"""
from typing import Iterable, Tuple

from rdflib_hdt.mapping import term_to_rdflib
from rdflib_hdt.types import Term


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

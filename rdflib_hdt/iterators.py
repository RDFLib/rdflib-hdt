"""
rdflib_hdt.iterators
=======================

This module contains iterators that wraps native HDT iterators to the RDFlib data model.
"""

from rdflib.query import ResultRow

from hdt import JoinIterator, TripleIterator
from rdflib_hdt.mapping import term_to_rdflib
from rdflib_hdt.types import Triple


class HDTIterator:
    """An iterator that converts HDT matching triples to the RDFlib data model.

    Args:
      - input: Input iterator that produces RDF triples with RDF terms in string format.
      - safe_mode: True if Unicode errors should be ignored, False otherwise.
    """
    def __init__(self, input: TripleIterator, safe_mode=True):
        super(HDTIterator, self).__init__()
        self._input = input
        self._safe_mode = safe_mode

    def __len__(self):
        """The estimated number of matching RDF triples."""
        return len(self._input)

    def __iter__(self):
        return self

    def __next__(self) -> Triple:
        """Fallback implementation for the Python 2.x iterator protocol."""
        return self.next()

    def next(self) -> Triple:
        """Produce a new RDF triple, per the Python iterator protocol."""
        try:
            triple = next(self._input)
            if triple is None:
                raise StopIteration()
            s, p, o = triple
            return (term_to_rdflib(s), term_to_rdflib(p), term_to_rdflib(o))
        except UnicodeDecodeError as e:
            # crash if safe mode is off
            if not self._safe_mode:
                raise e
            # otherwise, try to read a valid RDF triple from the input
            return self.next()
        except StopIteration as e:
            raise e


class HDTJoinIterator:
    """An iterator that converts HDT join results to the RDFlib data model.

    Args:
      - input: Input iterator that yields join results
      - safe_mode: True if Unicode errors should be ignored, False otherwise.
    """
    def __init__(self, input: JoinIterator, safe_mode=True):
        super(HDTJoinIterator, self).__init__()
        self._input = input
        self._safe_mode = safe_mode

    def __len__(self):
        """The estimated number of join results."""
        return len(self._input)

    def __iter__(self):
        return self

    def __next__(self) -> ResultRow:
        """Fallback implementation for the Python 2.x iterator protocol."""
        return self.next()

    def next(self) -> ResultRow:
        """Produce a new row of results, per the Python iterator protocol."""
        try:
            row = dict()
            variables = list()
            # convert all solution mappings to the RDFlib data model
            for key, value in next(self._input):
                rdf_key = term_to_rdflib(key)
                rdf_value = term_to_rdflib(value)
                variables.append(rdf_key)
                row[rdf_key] = rdf_value
            return ResultRow(row, variables)
        except UnicodeDecodeError as e:
            # crash if safe mode is off
            if not self._safe_mode:
                raise e
            # otherwise, try to read a valid RDF triple from the input
            return self.next()
        except StopIteration as e:
            raise e

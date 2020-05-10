"""
rdflib_hdt.mapping
=======================
Mapping functions between string RDF terms and the RDFlib data model.
"""
from rdflib import URIRef, Variable
from rdflib.util import from_n3

from rdflib_hdt.types import Term


def term_to_rdflib(term: str) -> Term:
    """Convert an HDT term into its RDFlib representation."""
    if term.startswith('?'):
        return Variable(term[1:])
    elif term.startswith("\""):
        return from_n3(term)
    else:
        return URIRef(term)


def rdflib_to_hdt(term: Term) -> str:
    """Convert an RDFlib term into an HDT term."""
    value = term.n3()
    if value.startswith('<') and value.endswith('>'):
        return value[1: len(value) - 1]
    return value

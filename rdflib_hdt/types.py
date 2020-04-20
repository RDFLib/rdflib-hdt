"""
rdflib_hdt.types
=======================
All commons types found in the rdflib_hdt package
"""
from typing import Optional, Set, Tuple, Union
from rdflib import Literal, URIRef, Variable

Term = Union[URIRef, Literal]
Triple = Tuple[Term, Term, Term]
TriplePattern = Union[URIRef, Literal, Variable]
SearchQuery = Tuple[Optional[Term], Optional[Term], Optional[Term]]
BGP = Set[TriplePattern]

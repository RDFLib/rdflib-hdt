# hdt_store_test.py
# Author: Thomas MINIER - MIT License 2017-2020
import pytest
from rdflib_hdt import HDTStore
from rdflib import Graph, URIRef, Literal

path = "tests/test.hdt"
store = HDTStore(path)
expected_length = 128


def test_rdflib_graph_basic():
    graph = Graph(store=store)
    nb_triples = 0
    for s, p, o in graph.triples((None, None, None)):
        nb_triples += 1
        assert(isinstance(s, URIRef))
        assert(isinstance(p, URIRef))
        assert(isinstance(o, URIRef) or isinstance(o, Literal))
    assert(nb_triples == expected_length)

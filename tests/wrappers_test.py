# wrappers_test.py
# Author: Thomas MINIER - MIT License 2017-2020
from rdflib_hdt import HDTDocument
from rdflib import URIRef, Variable

path = "tests/test.hdt"
document = HDTDocument(path)


def test_search_join_rdflib():
    expected_nb = 2
    join_iter = document.search_join([
        (Variable("s"), URIRef("http://example.org/p1"), URIRef("http://example.org/o001")),
        (Variable("s"), URIRef("http://example.org/p1"), URIRef("http://example.org/o001"))
    ])
    assert len(join_iter) == expected_nb
    cpt = 0
    for row in join_iter:
        cpt += 1
        assert row.s == URIRef('http://example.org/s1') or row.s == URIRef('http://example.org/s2')
    assert cpt == expected_nb

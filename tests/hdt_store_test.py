# hdt_store_test.py
# Author: Thomas MINIER - MIT License 2017-2020
import pytest
from rdflib_hdt import HDTStore
from rdflib import Graph, URIRef, Literal

path = "tests/test.hdt"
store = HDTStore(path)

fixtures = [
    # pattern ?s ?p ?o
    ((None, None, None), 128),
    # pattern s p o
    ((URIRef('http://example.org/s1'), URIRef('http://example.org/p1'), URIRef('http://example.org/o002')), 1),
    ((URIRef('http://example.org/s5'), URIRef('http://example.org/p1'), URIRef('http://example.org/o002')), 0),
    # pattern s ?p ?o
    ((URIRef('http://example.org/s1'), None, None), 100),
    ((URIRef('http://example.org/s2'), None, None), 10),
    ((URIRef('http://example.org/s3'), None, None), 10),
    ((URIRef('http://example.org/s4'), None, None), 8),
    ((URIRef('http://example.org/s5'), None, None), 0),
    # pattern ?s p ?o
    ((None, URIRef('http://example.org/p1'), None), 110),
    ((None, URIRef('http://example.org/p2'), None), 10),
    ((None, URIRef('http://example.org/p3'), None), 8),
    ((None, URIRef('http://example.org/p99'), None), 0),
    # pattern ?s ?p o
    ((None, None, URIRef('http://example.org/o002')), 3),
    ((None, None, URIRef('http://example.org/o004')), 3),
    ((None, None, Literal('a')), 1),
    ((None, None, Literal('a', lang='en')), 1),
    ((None, None, Literal('', lang='en')), 1),
    ((None, None, Literal('', datatype=URIRef('http://example.org/literal'))), 1),
    ((None, None, URIRef('http://example.org/o999')), 0),
    # pattern s ?p o
    ((URIRef('http://example.org/s1'), None, URIRef('http://example.org/o002')), 1),
    ((URIRef('http://example.org/s2'), None, URIRef('http://example.org/o004')), 1),
    ((URIRef('http://example.org/s3'), None, URIRef('http://example.org/o004')), 1),
    ((URIRef('http://example.org/s99'), None, URIRef('http://example.org/o004')), 0),
    # pattern s p ?o
    ((URIRef('http://example.org/s1'), URIRef('http://example.org/p1'), None), 100),
    ((URIRef('http://example.org/s2'), URIRef('http://example.org/p1'), None), 10),
    ((URIRef('http://example.org/s3'), URIRef('http://example.org/p2'), None), 10),
    ((URIRef('http://example.org/s3'), URIRef('http://example.org/p999'), None), 0),
    # pattern ?s p o
    ((None, URIRef('http://example.org/p1'), URIRef('http://example.org/o002')), 2),
    ((None, URIRef('http://example.org/p2'), URIRef('http://example.org/o004')), 1),
    ((None, URIRef('http://example.org/p2'), URIRef('http://example.org/o999')), 0)
]


@pytest.mark.parametrize("query,expected_length", fixtures)
def test_rdflib_graph_search(query, expected_length):
    query_s, query_p, query_o = query
    graph = Graph(store=store)
    nb_triples = 0
    for s, p, o in graph.triples(query):
        nb_triples += 1
        assert isinstance(s, URIRef), f"The subject of an RDF triple must be an URI"
        assert isinstance(p, URIRef), f"The predicate of an RDF triple must be an URI"
        assert isinstance(o, URIRef) or isinstance(o, Literal), f"The object of an RDF triple must be an URI or a Literal"
        if query_s is not None:
            assert s == query_s, f"The expected RDF triple subject's is {query_s}"
        if query_p is not None:
            assert p == query_p, f"The expected RDF triple predicate's is {query_p}"
        if query_o is not None:
            assert o == query_o, f"The expected RDF triple subject's is {query_o}"
    assert nb_triples == expected_length, f"The expected number of matches for {query} is {expected_length}"


def test_rdflib_sparql_query():
    graph = Graph(store=store)
    sparql_query = """
    PREFIX ex: <http://example.org/>
    SELECT * WHERE {
        ?s ex:p1 ?o
    }
    """
    qres = graph.query(sparql_query)

    nb_bindings = 0
    for row in qres:
        nb_bindings += 1

    assert nb_bindings == 110, f"The query should yield 110 set of solution mappings"

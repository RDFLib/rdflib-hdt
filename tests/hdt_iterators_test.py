# hdt_iterators_test.py
# Author: Thomas MINIER - MIT License 2017-2018
from hdt import HDTDocument

path = "tests/test.hdt"
document = HDTDocument(path)
nbTotalTriples = 132


def test_read_document_base():
    (triples, cardinality) = document.search_triples("", "", "")
    assert triples.subject == "?s"
    assert triples.predicate == "?p"
    assert triples.object == "?o"
    assert cardinality == nbTotalTriples
    for subj, pred, obj in triples:
        assert subj is not None
        assert pred is not None
        assert obj is not None
    assert triples.nb_reads == cardinality


def test_read_document_limit():
    nbItems = 0
    (triples, cardinality) = document.search_triples("", "", "", limit=10)
    assert triples.limit == 10
    assert cardinality == nbTotalTriples
    for subj, pred, obj in triples:
        nbItems += 1
        assert subj is not None
        assert pred is not None
        assert obj is not None
    assert nbItems == 10
    assert triples.nb_reads == 10


def test_read_document_offset():
    nbItems = 0
    (triples, cardinality) = document.search_triples("", "", "", offset=10)
    assert triples.offset == 10
    assert cardinality == nbTotalTriples
    for subj, pred, obj in triples:
        nbItems += 1
        assert subj is not None
        assert pred is not None
        assert obj is not None
    assert nbItems == cardinality - 10
    assert triples.nb_reads == cardinality - 10


def test_read_document_ids():
    (triples, cardinality) = document.search_triples_ids("", "", "")
    assert triples.subject == "?s"
    assert triples.predicate == "?p"
    assert triples.object, "?o"
    assert cardinality, nbTotalTriples
    for subj, pred, obj in triples:
        assert subj is not None
        assert pred is not None
        assert obj is not None
    assert triples.nb_reads == cardinality


def test_string_iterator_peek():
    expected = ('http://example.org/s1', 'http://example.org/p1', 'http://example.org/o001')
    (triples, cardinality) = document.search_triples("", "", "")
    v = triples.peek()
    assert v == expected
    assert triples.nb_reads == 0
    v = next(triples)
    assert v == expected
    assert triples.nb_reads == 1


def test_ids_iterator_peek():
    expected = (1, 1, 13)
    (triples, cardinality) = document.search_triples_ids("", "", "")
    v = triples.peek()
    assert v == expected
    assert triples.nb_reads == 0
    v = next(triples)
    assert v == expected
    assert triples.nb_reads == 1


def test_string_iterator_big_offset():
    nbItems = 0
    (triples, cardinality) = document.search_triples("", "", "", offset=nbTotalTriples + 1)
    for s, p, o in triples:
        nbItems += 1
    assert nbItems == 0


def test_ids_iterator_big_offset():
    nbItems = 0
    (triples, cardinality) = document.search_triples_ids("", "", "", offset=nbTotalTriples + 1)
    for s, p, o in triples:
        nbItems += 1
    assert nbItems == 0

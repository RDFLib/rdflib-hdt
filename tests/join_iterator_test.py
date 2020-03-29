# hdt_iterators_test.py
# Author: Thomas MINIER - MIT License 2017-2019
from hdt import HDTDocument

path = "tests/test.hdt"
document = HDTDocument(path)


def test_basic_join():
    join_iter = document.search_join([
        ("?s", "http://example.org/p1", "http://example.org/o001"),
        ("?s", "http://example.org/p1", "http://example.org/o001")
    ])
    cpt = 0
    for b in join_iter:
        cpt += 1
        assert len(b) == 1
        assert ('?s', 'http://example.org/s1') in b or ('?s', 'http://example.org/s2') in b
    assert cpt == 2


def test_basic_join_bytes():
    join_iter = document.search_join_bytes([
        ("?s", "http://example.org/p1", "http://example.org/o001"),
        ("?s", "http://example.org/p1", "http://example.org/o001")
    ])
    cpt = 0
    for b in join_iter:
        cpt += 1
        assert len(b) == 1
        assert (b'?s', b'http://example.org/s1') in b or (b'?s', b'http://example.org/s2') in b
    assert cpt == 2

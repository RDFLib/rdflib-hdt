# hdt_document_test.py
# Author: Thomas MINIER - MIT License 2017-2019
import pytest
from hdt import HDTDocument, IdentifierPosition

path = "tests/test.hdt"
document = HDTDocument(path, False)
nbTotalTriples = 132


def test_missing_file():
    with pytest.raises(RuntimeError):
        HDTDocument("/home/dtrump/wall.hdt")


def test_file_path():
    assert document.file_path == path


def test_total_triples():
    assert document.total_triples == nbTotalTriples
    assert len(document) == nbTotalTriples


def test_nb_subjects():
    assert document.nb_subjects == 4


def tests_nb_predicates():
    assert document.nb_predicates == 3


def tests_nb_objects():
    assert document.nb_objects == 112


def tests_nb_shared():
    assert document.nb_shared == 0


def test_ids_to_string():
    (triples, triplesCard) = document.search_triples("", "", "")
    (ids, idsCard) = document.search_triples_ids(0, 0, 0)
    assert triplesCard == idsCard
    assert triplesCard == nbTotalTriples
    for subj, pred, obj in triples:
        sid, pid, oid = next(ids)
        s, p, o = document.convert_tripleid(sid, pid, oid)
        assert subj == s
        assert pred == p
        assert obj == o


def test_convert_id():
    (triples, triplesCard) = document.search_triples("", "", "")
    (ids, idsCard) = document.search_triples_ids(0, 0, 0)
    assert triplesCard == idsCard
    assert triplesCard == nbTotalTriples
    for subj, pred, obj in triples:
        sid, pid, oid = next(ids)
        s, p, o = (
            document.convert_id(sid, IdentifierPosition.Subject),
            document.convert_id(pid, IdentifierPosition.Predicate),
            document.convert_id(oid, IdentifierPosition.Object)
            )
        assert subj == s
        assert pred == p
        assert obj == o

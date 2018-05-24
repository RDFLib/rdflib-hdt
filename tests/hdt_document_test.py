# hdt_document_test.py
# Author: Thomas MINIER - MIT License 2017-2018
from hdt import HDTDocument
import unittest

path = "tests/test.hdt"
document = HDTDocument(path)
nbTotalTriples = 132


class TestHDTDocument(unittest.TestCase):

    @unittest.expectedFailure
    def test_missing_file(self):
        wrongDoc = HDTDocument("/home/dtrump/wall.hdt")

    def test_file_path(self):
        self.assertEqual(document.file_path, path)

    def test_total_triples(self):
        self.assertEqual(document.total_triples, nbTotalTriples)
        self.assertEqual(len(document), nbTotalTriples)

    def test_nb_subjects(self):
        self.assertEqual(document.nb_subjects, 4)

    def tests_nb_predicates(self):
        self.assertEqual(document.nb_predicates, 3)

    def tests_nb_objects(self):
        self.assertEqual(document.nb_objects, 112)

    def tests_nb_shared(self):
        self.assertEqual(document.nb_shared, 0)

    def test_ids_to_string(self):
        (triples, triplesCard) = document.search_triples("", "", "")
        (ids, idsCard) = document.search_triples_ids("", "", "")
        self.assertEqual(triplesCard, idsCard)
        self.assertEqual(triplesCard, nbTotalTriples)
        self.assertEqual(len(triples)[0], triplesCard)
        for subj, pred, obj in triples:
            sid, pid, oid = next(ids)
            s, p, o = document.tripleid_to_string(sid, pid, oid)
            self.assertEqual(subj, s)
            self.assertEqual(pred, p)
            self.assertEqual(obj, o)

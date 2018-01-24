# hdt_document_test.py
# Author: Thomas MINIER - MIT License 2017-2018
from hdt import HDTDocument
import unittest

path = "tests/test.hdt"
document = HDTDocument(path)
nbTotalTriples = 132

class TestHDTDocument(unittest.TestCase):

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

    def test_read_document(self):
        (triples, cardinality) = document.search_triples("", "", "")
        self.assertEqual(triples.subject, "?s")
        self.assertEqual(triples.predicate, "?p")
        self.assertEqual(triples.object, "?o")
        self.assertEqual(cardinality, nbTotalTriples)
        self.assertEqual(len(triples), cardinality)
        for subj, pred, obj in triples:
            self.assertNotEqual(subj, None)
            self.assertNotEqual(pred, None)
            self.assertNotEqual(obj, None)
        self.assertEqual(triples.nb_reads, cardinality)

    def test_read_document_limit(self):
        nbItems = 0
        (triples, cardinality) = document.search_triples("", "", "", limit=10)
        self.assertEqual(triples.limit, 10)
        self.assertEqual(cardinality, nbTotalTriples)
        self.assertEqual(len(triples), nbTotalTriples)
        for subj, pred, obj in triples:
            nbItems += 1
            self.assertNotEqual(subj, None)
            self.assertNotEqual(pred, None)
            self.assertNotEqual(obj, None)
        self.assertEqual(nbItems, 10)
        self.assertEqual(triples.nb_reads, 10)

    def test_read_document_offset(self):
        nbItems = 0
        (triples, cardinality) = document.search_triples("", "", "", offset=10)
        self.assertEqual(triples.offset, 10)
        self.assertEqual(cardinality, nbTotalTriples)
        self.assertEqual(len(triples), nbTotalTriples)
        for subj, pred, obj in triples:
            nbItems += 1
            self.assertNotEqual(subj, None)
            self.assertNotEqual(pred, None)
            self.assertNotEqual(obj, None)
        self.assertEqual(nbItems, cardinality - 10)
        self.assertEqual(triples.nb_reads, cardinality - 10)

    def test_read_document_ids(self):
        (triples, cardinality) = document.search_triples_ids("", "", "")
        self.assertEqual(triples.subject, "?s")
        self.assertEqual(triples.predicate, "?p")
        self.assertEqual(triples.object, "?o")
        self.assertEqual(cardinality, nbTotalTriples)
        self.assertEqual(len(triples), cardinality)
        for subj, pred, obj in triples:
            self.assertTrue(subj > 0)
            self.assertTrue(pred > 0)
            self.assertTrue(obj > 0)
        self.assertEqual(triples.nb_reads, cardinality)

    def test_ids_to_string(self):
        (triples, triplesCard) = document.search_triples("", "", "")
        (ids, idsCard) = document.search_triples_ids("", "", "")
        self.assertEqual(triplesCard, idsCard)
        self.assertEqual(triplesCard, nbTotalTriples)
        self.assertEqual(len(triples), triplesCard)
        for subj, pred, obj in triples:
            sid, pid, oid = next(ids)
            s, p, o = document.tripleid_to_string(sid, pid, oid)
            self.assertEqual(subj, s)
            self.assertEqual(pred, p)
            self.assertEqual(obj, o)

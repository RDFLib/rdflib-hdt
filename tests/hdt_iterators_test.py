# hdt_iterators_test.py
# Author: Thomas MINIER - MIT License 2017-2018
from hdt import HDTDocument
import unittest

path = "tests/test.hdt"
document = HDTDocument(path)
nbTotalTriples = 132


class TestHDTIterators(unittest.TestCase):

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

    def test_string_iterator_big_offset(self):
        nbItems = 0
        (triples, cardinality) = document.search_triples("", "", "", offset=nbTotalTriples + 1)
        for s, p, o in triples:
            nbItems += 1
        self.assertEqual(nbItems, 0)

    def test_id_iterator_big_offset(self):
        nbItems = 0
        (triples, cardinality) = document.search_triples_ids("", "", "", offset=nbTotalTriples + 1)
        for s, p, o in triples:
            nbItems += 1
        self.assertEqual(nbItems, 0)

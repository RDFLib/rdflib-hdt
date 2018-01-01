# hdt_document_test.py
# Author: Thomas MINIER - MIT License 2017-2018
from hdt import HDTDocument
import unittest


class TestHDTDocument(unittest.TestCase):

    def test_read_document(self):
        document = HDTDocument("tests/test.hdt")
        (triples, cardinality) = document.search_triples("", "", "")
        self.assertEqual(cardinality, 132)
        self.assertEqual(len(triples), cardinality)
        for subj, pred, obj in triples:
            self.assertNotEqual(subj, None)
            self.assertNotEqual(pred, None)
            self.assertNotEqual(obj, None)

    def test_read_document_limit(self):
        document = HDTDocument("tests/test.hdt")
        (triples, cardinality) = document.search_triples("", "", "", limit=10)
        self.assertEqual(cardinality, 132)
        self.assertEqual(len(triples), 10)
        for subj, pred, obj in triples:
            self.assertNotEqual(subj, None)
            self.assertNotEqual(pred, None)
            self.assertNotEqual(obj, None)

    def test_read_document_offset(self):
        document = HDTDocument("tests/test.hdt")
        (triples, cardinality) = document.search_triples("", "", "", offset=10)
        self.assertEqual(cardinality, 132)
        self.assertEqual(len(triples), cardinality - 10)
        for subj, pred, obj in triples:
            self.assertNotEqual(subj, None)
            self.assertNotEqual(pred, None)
            self.assertNotEqual(obj, None)

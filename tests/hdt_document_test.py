# hdt_document_test.py
# Author: Thomas MINIER - MIT License 2017-2018
from hdt import HDTDocument
import unittest


class TestHDTDocument(unittest.TestCase):

    def test_read_document(self):
        document = HDTDocument("tests/test.hdt")
        (triples, cardinality) = document.search_triples("", "", "")
        self.assertEqual(cardinality, 132)
        nbResults = 0
        for subj, pred, obj in triples:
            self.assertNotEqual(subj, None)
            self.assertNotEqual(pred, None)
            self.assertNotEqual(obj, None)
            nbResults += 1
        self.assertEqual(nbResults, cardinality)

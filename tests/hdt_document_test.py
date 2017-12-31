# hdt_document_test.py
# Author: Thomas MINIER - MIT License 2017-2018
from hdt import HDTDocument
import unittest


class TestHDTDocument(unittest.TestCase):

    def test_read_document(self):
        document = HDTDocument("tests/test.hdt")
        for triple, cardinality, exactCount in document.search_triples(None, None, None, limit=-1, offset=0):
            print("triple: %s" % str(triple))
            print("cardinality: %b (exact count: %b)" % (cardinality, triple))

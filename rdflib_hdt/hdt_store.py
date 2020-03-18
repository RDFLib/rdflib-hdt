from rdflib_hdt.hdt_document import HDTDocument
from rdflib import store


def empty():
    return
    yield


class HDTStore(store):
    def __init__(self, configuration=None, identifier=None):
        self._hdt_document = None

    def __len__(self) -> int:
        if self._hdt_document is None:
            return 0
        return self.doc.total_triples

    def open(self, path: str):
        self.doc = HDTDocument(path)

    def triples(self, query, context):
        query = [part if part else "" for part in query]
        triples, cardinality = self.doc.search_triples(*query)
        for triple in triples:
            yield triple, empty()

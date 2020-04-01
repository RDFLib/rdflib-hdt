"""
rdflib_hdt.hdt_store
=======================
"""
from rdflib_hdt.hdt_document import HDTDocument
from rdflib.store import Store


class HDTStore(Store):
    """An implementation of a Store over a HDT document.

    It is heavily inspired by the work from @FlorianLudwig (https://github.com/RDFLib/rdflib/issues/894)

    Args:
        - path: Absolute path to the HDT file to load.
        - mapped: True if the document must be mapped on disk, False to load it in-memory.
        - indexed: True if the document must be indexed. Indexed must be located in the same directory as the HDT file. Missing indexes will be generated at startup.
        - safe_mode: True if Unicode errors should be ignored, False otherwise.
    """
    def __init__(self, path: str, mapped: bool = True, indexed: bool = True, safe_mode=True, configuration=None, identifier=None):
        super(HDTStore, self).__init__(configuration=configuration, identifier=identifier)
        self._safe_mode = safe_mode
        self._hdt_document = HDTDocument(path, mapped=mapped, indexed=indexed)

    def is_safe(self) -> bool:
        """Returnd True if the HDT store ignores Unicode errors, False otherwise"""
        return self._safe_mode

    def __len__(self) -> int:
        """The number of RDF triples in the store"""
        return self._hdt_document.total_triples

    def triples(self, pattern, context):
        """Search for a triple pattern in a HDT document.

        Args:
            - pattern: The triple pattern (s, p, o) to search for
            - context: The query execution context

        Returns:
            A generator of RDF triples matching the input triple pattern
        """
        triples, cardinality = self._hdt_document.search(pattern)
        should_stop = False
        while not should_stop:
            try:
                yield next(triples), None
            except UnicodeDecodeError as e:
                if not self._safe_mode:
                    raise e
            except StopIteration:
                should_stop = True

    def create(self, configuration):
        raise TypeError('The HDT store is read only')

    def destroy(self, configuration):
        raise TypeError('The HDT store is read only')

    def commit(self):
        raise TypeError('The HDT store is read only')

    def rollback(self):
        raise TypeError('The HDT store is read only')

    def add(self, _, context=None, quoted=False):
        raise TypeError('The HDT store is read only')

    def addN(self, quads):
        raise TypeError('The HDT store is read only')

    def remove(self, _, context):
        raise TypeError('The HDT store is read only')

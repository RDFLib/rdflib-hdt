"""
rdflib_hdt.sparql_opt
=======================
Provides functions to overrides the RDFlib SPARQL evaluator for HDT documents.
"""
import rdflib.plugins.sparql.evaluate as sparql_evaluate
from rdflib import Variable
from rdflib.plugins.sparql.sparql import FrozenBindings, QueryContext

from rdflib_hdt.hdt_store import HDTStore
from rdflib_hdt.types import BGP


def optimize_sparql():
    """Overrides the RDFlib SPARQL engine to optimize SPARQL query execution over HDT documents.

    .. note::
      Calling this function triggers a global modification of the RDFlib SPARQL engine.
      However, executing SPARQL queries using other RDFlib stores will continue to work as before,
      so you can safely call this function at the beginning of your code.
    """
    # copy the default RDFlib function for evaluating Basic Graph Patterns
    rdflib_evalBGP = sparql_evaluate.evalBGP

    def __evalBGP__(ctx: QueryContext, bgp: BGP):
        # A SPARQL query executed over a non HDTStore is evaluated as usual
        if not isinstance(ctx.graph.store, HDTStore):
            return rdflib_evalBGP(ctx, bgp)
        if not bgp:
            yield ctx.solution()
            return

        # delegate the join evaluation to HDT
        store: HDTStore = ctx.graph.store
        for row in store.hdt_document.search_join(set(bgp)):
            # convert the ResultRow into a FrozenBindings object
            bindings = dict()
            for key in row.labels:
                bindings[Variable(key)] = row[key]
            yield FrozenBindings(ctx, bindings)
        return
    # overrides RDFlib evalBGP function
    sparql_evaluate.evalBGP = __evalBGP__

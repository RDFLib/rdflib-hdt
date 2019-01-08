/**
 * hdt_types.hpp
 * Author: Thomas MINIER - MIT License 2017-2019
 */

#ifndef PYHDT_TYPES_HPP
#define PYHDT_TYPES_HPP

#include <list>
#include <string>
#include <tuple>
#include <set>

/**
 * Indictates the position of an Object Identifier
 */
enum IdentifierPosition {
  Subject = 1,
  Predicate = 2,
  Object = 3
};

// A RDF Triple. RDF terms are represented as simple strings by HDT.
typedef std::tuple<std::string, std::string, std::string> triple;

// A RDF triple composed of IDs from HDT dictionnary
typedef std::tuple<unsigned int, unsigned int, unsigned int> triple_id;

// A list of RDF triples
typedef std::list<triple> triple_list;

// A list of RDF triples IDs
typedef std::list<triple_id> triple_ids_list;

// A hint over the cardinality of a triple pattern
// The right element of the tuple is True if the hint is accurate, False otherwise
typedef std::tuple<size_t, bool> size_hint;

typedef std::tuple<std::string, std::string> single_binding;

typedef std::set<single_binding> *solution_bindings;

#endif /* PYHDT_TYPES_HPP */

/**
 * hdt_types.hpp
 * Author: Thomas MINIER - MIT License 2017-2018
 */

#ifndef PYHDT_TYPES_HPP
#define PYHDT_TYPES_HPP

#include <string>
#include <tuple>

typedef std::tuple<std::string, std::string, std::string> triple;
typedef std::list<triple> triple_list;
typedef std::tuple<triple_list, size_t> search_results;

#endif /* PYHDT_TYPES_HPP */

#ifndef ROFL_GRAPH_FIND_PREVIOUS_HPP_INCLUDED
#define ROFL_GRAPH_FIND_PREVIOUS_HPP_INCLUDED

#include <rofl/indexed_point.hpp>
#include <rofl/indexed_polygon.hpp>

namespace rofl
{
namespace graph
{
rofl::indexed_point const find_previous(
	rofl::indexed_polygon const &,
	rofl::indexed_point const &,
	rofl::indexed_point const &);
}
}

#endif
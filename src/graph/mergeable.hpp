#ifndef ROFL_GRAPH_MERGEABLE_HPP_INCLUDED
#define ROFL_GRAPH_MERGEABLE_HPP_INCLUDED

#include <rofl/indexed_polygon.hpp>
#include <rofl/indexed_line_segment.hpp>

namespace rofl
{
namespace graph
{
bool mergeable(
	rofl::indexed_polygon const &,
	rofl::indexed_polygon const &,
	rofl::indexed_line_segment const &);
}
}

#endif
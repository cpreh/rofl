#include <rofl/indexed_line_segment.hpp>
#include <rofl/unit.hpp>
#include <rofl/graph/edge_properties.hpp>


rofl::graph::edge_properties::edge_properties(
	rofl::unit const _length,
	rofl::indexed_line_segment const &_adjacent_edge
)
:
	length_(
		_length
	),
	adjacent_edge_(
		_adjacent_edge
	)
{
}

rofl::unit
rofl::graph::edge_properties::length() const
{
	return
		length_;
}

rofl::indexed_line_segment const &
rofl::graph::edge_properties::adjacent_edge() const
{
	return
		adjacent_edge_;
}

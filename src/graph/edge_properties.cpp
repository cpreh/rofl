#include <rofl/graph/edge_properties.hpp>

rofl::graph::edge_properties::edge_properties(
	unit const _length,
	math::line_segment<point> const &_adjacent_edge)
:
	length_(
		_length),
	adjacent_edge_(
		_adjacent_edge)
{
}

rofl::unit 
rofl::graph::edge_properties::length() const
{
	return 
		length_;
}

rofl::math::line_segment<rofl::point> const &
rofl::graph::edge_properties::adjacent_edge() const
{
	return 
		adjacent_edge_;
}
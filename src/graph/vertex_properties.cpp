#include <rofl/graph/vertex_properties.hpp>

rofl::graph::vertex_properties::vertex_properties()
:
	polygon_()
{
}

rofl::graph::vertex_properties::vertex_properties(
	rofl::math::polygon<point> const &_polygon)
:
	polygon_(
		_polygon)
{
}

rofl::math::polygon<rofl::point> const &
rofl::graph::vertex_properties::polygon() const
{
	return polygon_;
}

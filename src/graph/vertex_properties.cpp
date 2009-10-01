#include <rofl/graph/vertex_properties.hpp>
#include <rofl/math/barycenter.hpp>
#include <sge/math/vector/arithmetic.hpp>

rofl::graph::vertex_properties::vertex_properties()
:
	polygon_(),
	barycenter_()
{
}

rofl::graph::vertex_properties::vertex_properties(
	rofl::polygon const &_polygon)
:
	polygon_(
		_polygon),
	barycenter_(
		math::barycenter(
			_polygon))
{
}

rofl::polygon const &
rofl::graph::vertex_properties::polygon() const
{
	return 
		polygon_;
}

rofl::point const &
rofl::graph::vertex_properties::barycenter() const
{
	return 
		barycenter_;
}

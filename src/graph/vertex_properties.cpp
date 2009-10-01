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
	indexed_polygon const &_polygon)
:
	polygon_(
		_polygon),
	barycenter_()
{
}

rofl::graph::vertex_properties::vertex_properties(
	indexed_polygon const &_polygon,
	point const &_barycenter)
:
	polygon_(
		_polygon),
	barycenter_(
		_barycenter)
{
}

rofl::indexed_polygon const &
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

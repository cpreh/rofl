#include <rofl/graph/properties.hpp>
#include <fcppt/math/vector/object_impl.hpp>

rofl::graph::properties::properties()
:
	points_()
{
}

rofl::graph::properties::properties(
	point_vector const &_points)
:
	points_(
		_points)
{

}

rofl::graph::properties::point_vector &
rofl::graph::properties::points()
{
	return points_;
}

rofl::graph::properties::point_vector const &
rofl::graph::properties::points() const
{
	return points_;
}

#include <rofl/graph/properties.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


rofl::graph::properties::properties()
:
	points_()
{
}

rofl::graph::properties::properties(
	point_vector &&_points
)
:
	points_(
		std::move(
			_points
		)
	)
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

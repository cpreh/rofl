#include <rofl/indexed_polygon.hpp>
#include <rofl/polygon.hpp>
#include <rofl/graph/properties.hpp>
#include <rofl/graph/vertex_properties.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


rofl::graph::vertex_properties::vertex_properties()
:
	polygon_(),
	barycenter_(
		fcppt::no_init()
	)
{
}

rofl::graph::vertex_properties::vertex_properties(
	rofl::indexed_polygon &&_polygon
)
:
	polygon_(
		std::move(
			_polygon
		)
	),
	barycenter_(
		fcppt::no_init()
	)
{
}

rofl::graph::vertex_properties::vertex_properties(
	rofl::indexed_polygon &&_polygon,
	rofl::point const &_barycenter
)
:
	polygon_(
		std::move(
			_polygon
		)
	),
	barycenter_(
		_barycenter
	)
{
}

rofl::indexed_polygon const &
rofl::graph::vertex_properties::polygon() const
{
	return
		polygon_;
}

void
rofl::graph::vertex_properties::polygon(
	rofl::indexed_polygon &&_polygon
)
{
	polygon_ =
		std::move(
			_polygon
		);
}


rofl::point const &
rofl::graph::vertex_properties::barycenter() const
{
	return
		barycenter_;
}

void
rofl::graph::vertex_properties::barycenter(
	rofl::point const &_barycenter
)
{
	barycenter_ =
		_barycenter;
}

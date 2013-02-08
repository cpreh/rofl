#ifndef ROFL_AUX_ASTAR_HEURISTIC_IMPL_HPP_INCLUDED
#define ROFL_AUX_ASTAR_HEURISTIC_IMPL_HPP_INCLUDED

#include <rofl/unit.hpp>
#include <rofl/graph/object.hpp>
#include <rofl/graph/vertex_descriptor.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>


rofl::aux::astar::heuristic::heuristic(
	graph::object const &_graph,
	graph::vertex_descriptor const &_destination
)
:
	graph_(
		_graph
	),
	destination_(
		_destination
	)
{
}

rofl::unit
rofl::aux::astar::heuristic::operator()(
	rofl::graph::vertex_descriptor const &_vertex
) const
{
	return
		fcppt::math::vector::length(
			graph_[
				_vertex
			].barycenter()
			-
			graph_[
				destination_
			].barycenter()
		);
}

#endif

#ifndef ROFL_ASTAR_HEURISTIC_IMPL_HPP_INCLUDED
#define ROFL_ASTAR_HEURISTIC_IMPL_HPP_INCLUDED

#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/arithmetic.hpp>

rofl::astar::heuristic::heuristic(
	graph::object const &_graph,
	graph::vertex_descriptor const &_destination)
:
	graph_(
		_graph),
	destination_(
		_destination)
{
}

rofl::unit
rofl::astar::heuristic::operator()(
	graph::vertex_descriptor const &v) const
{
	return
		fcppt::math::vector::length(
			graph_[v].barycenter()-
			graph_[destination_].barycenter());
}

#endif

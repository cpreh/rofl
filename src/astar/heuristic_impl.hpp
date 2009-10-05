#include <sge/math/vector/length.hpp>
#include <sge/math/vector/arithmetic.hpp>

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
		sge::math::vector::length(
			graph_[v].barycenter()-
			graph_[destination_].barycenter());
}
#ifndef ROFL_AUX_ASTAR_HEURISTIC_HPP_INCLUDED
#define ROFL_AUX_ASTAR_HEURISTIC_HPP_INCLUDED

#include <rofl/unit.hpp>
#include <rofl/graph/object.hpp>
#include <rofl/graph/vertex_descriptor.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>


namespace rofl::aux::astar
{

class heuristic
{
public:
	inline
	heuristic(
		rofl::graph::object const &,
		rofl::graph::vertex_descriptor const &
	);

	inline
	rofl::unit
	operator()(
		rofl::graph::vertex_descriptor const &
	) const;
private:
	fcppt::reference<
		rofl::graph::object const
	> graph_;

	rofl::graph::vertex_descriptor destination_;
};

}

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
			graph_.get()[
				_vertex
			].barycenter()
			-
			graph_.get()[
				destination_
			].barycenter()
		);
}

#endif

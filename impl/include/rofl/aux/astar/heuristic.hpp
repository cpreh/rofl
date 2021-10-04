#ifndef ROFL_AUX_ASTAR_HEURISTIC_HPP_INCLUDED
#define ROFL_AUX_ASTAR_HEURISTIC_HPP_INCLUDED

#include <rofl/unit.hpp>
#include <rofl/graph/object_fwd.hpp>
#include <rofl/graph/vertex_descriptor.hpp>
#include <fcppt/reference_impl.hpp>


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

#include <rofl/aux/astar/impl/heuristic.hpp>

#endif

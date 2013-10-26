#ifndef ROFL_AUX_ASTAR_HEURISTIC_HPP_INCLUDED
#define ROFL_AUX_ASTAR_HEURISTIC_HPP_INCLUDED

#include <rofl/unit.hpp>
#include <rofl/graph/object_fwd.hpp>
#include <rofl/graph/vertex_descriptor.hpp>
#include <fcppt/nonassignable.hpp>


namespace rofl
{
namespace aux
{
namespace astar
{

class heuristic
{
	FCPPT_NONASSIGNABLE(
		heuristic
	);
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
	rofl::graph::object const &graph_;

	rofl::graph::vertex_descriptor destination_;
};

}
}
}

#include <rofl/aux/astar/impl/heuristic.hpp>

#endif

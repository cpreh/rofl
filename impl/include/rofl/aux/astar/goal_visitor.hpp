#ifndef ROFL_AUX_ASTAR_GOAL_VISITOR_HPP_INCLUDED
#define ROFL_AUX_ASTAR_GOAL_VISITOR_HPP_INCLUDED

#include <rofl/graph/object_fwd.hpp>
#include <rofl/graph/vertex_descriptor.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/graph/astar_search.hpp>
#include <fcppt/config/external_end.hpp>


namespace rofl::aux::astar
{

class goal_visitor
:
	public boost::default_astar_visitor
{
public:
	inline
	explicit
	goal_visitor(
		rofl::graph::vertex_descriptor const &
	);

	inline
	void
	examine_vertex(
		rofl::graph::vertex_descriptor const &,
		rofl::graph::object const &
	) const;
private:
	rofl::graph::vertex_descriptor goal_;
};

}

#include <rofl/aux/astar/impl/goal_visitor.hpp>

#endif

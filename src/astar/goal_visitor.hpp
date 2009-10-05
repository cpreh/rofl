#ifndef ROFL_ASTAR_GOAL_VISITOR_HPP_INCLUDED
#define ROFL_ASTAR_GOAL_VISITOR_HPP_INCLUDED

#include <rofl/graph/object.hpp>
#include <rofl/graph/vertex_descriptor.hpp>
#include <boost/graph/astar_search.hpp>

namespace rofl
{
namespace astar
{
class goal_visitor
:
	public boost::default_astar_visitor
{
public:
	inline goal_visitor(
		graph::vertex_descriptor const &);
	inline void examine_vertex(
		graph::vertex_descriptor const &,
		graph::object const &);
private:
	graph::vertex_descriptor goal_;
};
}
}

#include "goal_visitor_impl.hpp"

#endif
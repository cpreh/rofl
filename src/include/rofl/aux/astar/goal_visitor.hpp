#ifndef ROFL_AUX_ASTAR_GOAL_VISITOR_HPP_INCLUDED
#define ROFL_AUX_ASTAR_GOAL_VISITOR_HPP_INCLUDED

#include <rofl/graph/object_fwd.hpp>
#include <rofl/graph/vertex_descriptor.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/graph/astar_search.hpp>
#include <fcppt/config/external_end.hpp>


namespace rofl
{
namespace aux
{
namespace astar
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

class goal_visitor
:
	public boost::default_astar_visitor
{
public:
	inline
	goal_visitor(
		rofl::graph::vertex_descriptor const &
	);

	inline
	void
	examine_vertex(
		graph::vertex_descriptor const &,
		graph::object const &
	);
private:
	rofl::graph::vertex_descriptor goal_;
};

FCPPT_PP_POP_WARNING

}
}
}

#include <rofl/aux/astar/impl/goal_visitor.hpp>

#endif

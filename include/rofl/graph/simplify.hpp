#ifndef ROFL_GRAPH_SIMPLIFY_HPP_INCLUDED
#define ROFL_GRAPH_SIMPLIFY_HPP_INCLUDED

#include <rofl/symbol.hpp>
#include <rofl/graph/object_fwd.hpp>
#include <fcppt/reference_fwd.hpp>


namespace rofl::graph
{

ROFL_SYMBOL
void
simplify(
	fcppt::reference<
		rofl::graph::object
	>
);

}

#endif

#ifndef ROFL_GRAPH_VERTICES_END_HPP_INCLUDED
#define ROFL_GRAPH_VERTICES_END_HPP_INCLUDED

#include <rofl/symbol.hpp>
#include <rofl/graph/const_vertex_iterator.hpp>
#include <rofl/graph/object_fwd.hpp>
#include <rofl/graph/vertex_iterator.hpp>


namespace rofl::graph
{

ROFL_SYMBOL
rofl::graph::vertex_iterator
vertices_end(
	rofl::graph::object & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

ROFL_SYMBOL
rofl::graph::const_vertex_iterator
vertices_end(
	rofl::graph::object const &
);

}

#endif

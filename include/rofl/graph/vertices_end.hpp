#ifndef ROFL_GRAPH_VERTICES_END_HPP_INCLUDED
#define ROFL_GRAPH_VERTICES_END_HPP_INCLUDED

#include <rofl/graph/object.hpp>
#include <rofl/graph/vertex_iterator.hpp>
#include <rofl/graph/const_vertex_iterator.hpp>

namespace rofl
{
namespace graph
{
vertex_iterator const vertices_end(
	object &);
const_vertex_iterator const vertices_end(
	object const &);
}
}

#endif
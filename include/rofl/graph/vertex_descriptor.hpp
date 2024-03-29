#ifndef ROFL_GRAPH_VERTEX_DESCRIPTOR_HPP_INCLUDED
#define ROFL_GRAPH_VERTEX_DESCRIPTOR_HPP_INCLUDED

#include <rofl/graph/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/graph/graph_traits.hpp>
#include <fcppt/config/external_end.hpp>


namespace rofl::graph
{

using
vertex_descriptor
=
boost::graph_traits<
	rofl::graph::object
>::vertex_descriptor;

}

#endif

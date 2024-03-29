#ifndef ROFL_GRAPH_EDGE_DESCRIPTOR_HPP_INCLUDED
#define ROFL_GRAPH_EDGE_DESCRIPTOR_HPP_INCLUDED

#include <rofl/graph/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/graph/graph_traits.hpp>
#include <fcppt/config/external_end.hpp>


namespace rofl::graph
{

using
edge_descriptor
=
boost::graph_traits<
	rofl::graph::object
>::edge_descriptor;

}

#endif

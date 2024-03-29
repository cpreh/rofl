#ifndef ROFL_GRAPH_OUT_EDGE_ITERATOR_HPP_INCLUDED
#define ROFL_GRAPH_OUT_EDGE_ITERATOR_HPP_INCLUDED

#include <rofl/graph/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/graph/graph_traits.hpp>
#include <fcppt/config/external_end.hpp>


namespace rofl::graph
{

using
out_edge_iterator
=
boost::graph_traits<
	rofl::graph::object
>::out_edge_iterator;

}

#endif

#ifndef ROFL_GRAPH_CONST_VERTEX_ITERATOR_HPP_INCLUDED
#define ROFL_GRAPH_CONST_VERTEX_ITERATOR_HPP_INCLUDED

#include <rofl/graph/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/graph/graph_traits.hpp>
#include <fcppt/config/external_end.hpp>


namespace rofl
{
namespace graph
{

typedef
boost::graph_traits<
	rofl::graph::object const
>::vertex_iterator
const_vertex_iterator;

}
}

#endif

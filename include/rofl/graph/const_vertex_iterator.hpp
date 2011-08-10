#ifndef ROFL_GRAPH_CONST_VERTEX_ITERATOR_HPP_INCLUDED
#define ROFL_GRAPH_CONST_VERTEX_ITERATOR_HPP_INCLUDED

#include <rofl/graph/object.hpp>

namespace rofl
{
namespace graph
{
typedef
boost::graph_traits<object const>::vertex_iterator
const_vertex_iterator;
}
}

#endif

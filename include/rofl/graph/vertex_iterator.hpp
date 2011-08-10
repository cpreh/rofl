#ifndef ROFL_GRAPH_VERTEX_ITERATOR_HPP_INCLUDED
#define ROFL_GRAPH_VERTEX_ITERATOR_HPP_INCLUDED

#include <rofl/graph/object.hpp>

namespace rofl
{
namespace graph
{
typedef
boost::graph_traits<object>::vertex_iterator
vertex_iterator;
}
}

#endif

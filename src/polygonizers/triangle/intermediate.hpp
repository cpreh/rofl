#ifndef ROFL_POLYGONIZERS_TRIANGLE_INTERMEDIATE_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_INTERMEDIATE_HPP_INCLUDED

#include <tr1/array>
#include <rofl/graph/vertex_descriptor.hpp>

namespace rofl
{
namespace polygonizers
{
namespace triangle
{
// To build the graph, we have to associate the triangle indices with 
// -The graph nodes
// -The triangle's neighbor indices
// To save at least some space/performance we store the neighbors 
// in an array with constant size 3 (-1 being "not a neighbor" like Triangle does)
struct intermediate
{
	typedef int index;
	
	typedef 
	std::tr1::array<index,3>
	neighbor_array;
	
	graph::vertex_descriptor vertex;
	neighbor_array neighbors;
	
	intermediate(
		graph::vertex_descriptor const &,
		neighbor_array const &);
};
}
}
}

#endif
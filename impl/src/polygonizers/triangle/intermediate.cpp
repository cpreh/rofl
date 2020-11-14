#include <rofl/aux/polygonizers/triangle/intermediate.hpp>
#include <rofl/graph/vertex_descriptor.hpp>


rofl::aux::polygonizers::triangle::intermediate::intermediate(
	rofl::graph::vertex_descriptor const &_vertex,
	neighbor_array const &_neighbors
)
:
	vertex(
		_vertex
	),
	neighbors(
		_neighbors
	)
{
}

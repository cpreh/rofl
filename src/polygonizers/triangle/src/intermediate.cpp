#include "../intermediate.hpp"

rofl::polygonizers::triangle::intermediate::intermediate(
	graph::vertex_descriptor const &vertex,
	neighbor_array const &neighbors)
:
	vertex(
		vertex),
	neighbors(
		neighbors)
{
}

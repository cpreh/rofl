#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_INTERMEDIATE_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_INTERMEDIATE_HPP_INCLUDED

#include <rofl/graph/vertex_descriptor.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


namespace rofl::aux::polygonizers::triangle
{
// To build the graph, we have to associate the triangle indices with
// -The graph nodes
// -The triangle's neighbor indices
// To save at least some space/performance we store the neighbors
// in an array with constant size 3 (-1 being "not a neighbor" like Triangle does)
struct intermediate
{
	using
	index
	=
	int;

	using
	neighbor_array
	=
	std::array<
		index,
		3
	>;

	rofl::graph::vertex_descriptor vertex; // NOLINT(misc-non-private-member-variables-in-classes)

	neighbor_array neighbors; // NOLINT(misc-non-private-member-variables-in-classes)

	intermediate(
		rofl::graph::vertex_descriptor const &,
		neighbor_array const &
	);
};

}

#endif

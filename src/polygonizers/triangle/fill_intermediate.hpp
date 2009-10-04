#ifndef ROFL_POLYGONIZERS_TRIANGLE_FILL_INTERMEDIATE_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_FILL_INTERMEDIATE_HPP_INCLUDED

#include "intermediate.hpp"
#include <rofl/indexed_polygon.hpp>
#include <rofl/math/barycenter.hpp>
#include <rofl/index.hpp>
#include <rofl/dereference.hpp>
#include <rofl/graph/object.hpp>
#include <sge/assign/make_array.hpp>
#include <cstddef>

namespace rofl
{
namespace polygonizers
{
namespace triangle
{
template
<
	typename GraphPolygons,
	typename TriList,
	typename NeighborList,
	typename Graph
>
void fill_intermediate(
	Graph &output,
	GraphPolygons &graph_polygons,
	int numberoftriangles,
	TriList const &trilist,
	NeighborList const &neighborlist)
{
	for (int tri = 0; tri < numberoftriangles; ++tri)
	{
		indexed_polygon g;
		std::size_t const tri_base = 
			static_cast<std::size_t>(
				3*tri);
		// NOTE: somehow triangle outputs the corners in _clockwise_ order
		// so we switch it here.
		for (int corner = 2; corner >= 0; --corner)
		{
			std::size_t const corner_base = 
				static_cast<std::size_t>(
					tri_base + corner);
			g.push_back(
				indexed_point(
					output,
					static_cast<index>(
						trilist[corner_base])));
		}
		
		graph_polygons.push_back(
			intermediate(
				boost::add_vertex(
					rofl::graph::vertex_properties(
						g,
						math::barycenter(
							dereference(
								g))),
					output),
				sge::assign::make_array<intermediate::index>
					(neighborlist[3*tri])
					(neighborlist[3*tri+1])
					(neighborlist[3*tri+2])));
	}
}
}
}
}


#endif
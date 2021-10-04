#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_FILL_INTERMEDIATE_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_FILL_INTERMEDIATE_HPP_INCLUDED

#include <rofl/dereference.hpp>
#include <rofl/index.hpp>
#include <rofl/indexed_point.hpp>
#include <rofl/indexed_polygon.hpp>
#include <rofl/aux/polygonizers/triangle/intermediate.hpp>
#include <rofl/graph/object.hpp>
#include <rofl/graph/vertex_properties.hpp>
#include <rofl/math/barycenter.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_const.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace rofl::aux::polygonizers::triangle
{

template<
	typename GraphPolygons,
	typename TriList,
	typename NeighborList,
	typename Graph
>
void
fill_intermediate(
	fcppt::reference<
		Graph
	> const output,
	fcppt::reference<
		GraphPolygons
	> const graph_polygons,
	int numberoftriangles,
	TriList const &trilist,
	NeighborList const &neighborlist
)
{
	// TODO(philipp): reserve graph_polygons's size
	for(
		int tri = 0;
		tri < numberoftriangles;
		++tri
	)
	{
		// TODO(philipp): reserve three elements
		rofl::indexed_polygon indexed_poly;

		auto const tri_base(
			static_cast<
				std::size_t
			>(
				tri
			)
			* 3U
		);

		// NOTE: somehow triangle outputs the corners in _clockwise_ order
		// so we switch it here.
		for(
			unsigned corner = 2U;
			corner <= 2U;
			--corner
		)
		{
			indexed_poly.push_back(
				rofl::indexed_point(
					fcppt::reference_to_const(
						output
					),
					static_cast<
						rofl::index
					>(
						trilist[
							tri_base + corner
						]
					)
				)
			);
		}

		rofl::aux::polygonizers::triangle::intermediate::neighbor_array const neighbors{{
			neighborlist[tri_base],
			neighborlist[tri_base+1],
			neighborlist[tri_base+2]
		}};

		graph_polygons.get().push_back(
			rofl::aux::polygonizers::triangle::intermediate(
				boost::add_vertex(
					rofl::graph::vertex_properties(
						rofl::indexed_polygon{
							indexed_poly
						},
						rofl::math::barycenter(
							rofl::dereference(
								indexed_poly
							)
						)
					),
					output.get()
				),
				neighbors
			)
		);
	}
}

}

#endif

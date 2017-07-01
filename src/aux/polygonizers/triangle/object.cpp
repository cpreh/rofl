#include <rofl/line_segment.hpp>
#include <rofl/point.hpp>
#include <rofl/polygon.hpp>
#include <rofl/polygon_with_holes.hpp>
#include <rofl/unit.hpp>
#include <rofl/aux/polygonizers/triangle/add_polygon.hpp>
#include <rofl/aux/polygonizers/triangle/accumulate_sizes.hpp>
#include <rofl/aux/polygonizers/triangle/clear_pod.hpp>
#include <rofl/aux/polygonizers/triangle/determine_adjacent_edge.hpp>
#include <rofl/aux/polygonizers/triangle/fill_points.hpp>
#include <rofl/aux/polygonizers/triangle/fill_intermediate.hpp>
#include <rofl/aux/polygonizers/triangle/hole_vector.hpp>
#include <rofl/aux/polygonizers/triangle/intermediate.hpp>
//#include <rofl/aux/polygonizers/triangle/is_convex.hpp>
#include <rofl/aux/polygonizers/triangle/log_location.hpp>
#include <rofl/aux/polygonizers/triangle/object.hpp>
#include <rofl/aux/polygonizers/triangle/point_vector.hpp>
#include <rofl/aux/polygonizers/triangle/segment_vector.hpp>
#include <rofl/aux/polygonizers/triangle/triangulation.hpp>
#include <rofl/math/barycenter.hpp>
#include <rofl/graph/object.hpp>
#include <rofl/graph/property_tag.hpp>
#include <rofl/graph/vertex_properties.hpp>
#include <rofl/indexed_point.hpp>
#include <triangle/impl.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/parameters.hpp>
#include <fcppt/log/format/optional_function.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


rofl::aux::polygonizers::triangle::object::object(
	fcppt::log::context &_log_context
)
:
	log_{
		_log_context,
		rofl::aux::polygonizers::triangle::log_location(),
		fcppt::log::parameters{
			fcppt::log::name{
				FCPPT_TEXT("object")
			},
			fcppt::log::format::optional_function()
		}
	}
{
}

rofl::aux::polygonizers::triangle::object::~object()
{
}

void
rofl::aux::polygonizers::triangle::object::polygonize(
	rofl::polygon_with_holes const &_poly,
	rofl::graph::object &_output
)
{
/*
	log_.activate(
		fcppt::log::level::debug);
		*/

	triangulateio
		in,
		out;

	// since triangulateio is a C structure, we can just memset it to 0
	rofl::aux::polygonizers::triangle::clear_pod(
		in
	);

	rofl::aux::polygonizers::triangle::clear_pod(
		out
	);

	// Points
	in.numberofpoints =
		static_cast<int>(
			_poly.border().size()+
			rofl::aux::polygonizers::triangle::accumulate_sizes(
				_poly.holes()));

	rofl::aux::polygonizers::triangle::point_vector points;

	points.reserve(
		static_cast<
			rofl::aux::polygonizers::triangle::point_vector::size_type
		>(
			in.numberofpoints * 2
		)
	);

	in.pointlist =
		&points[0];

	// Segments
	in.numberofsegments =
		in.numberofpoints;
	rofl::aux::polygonizers::triangle::segment_vector
		segments;
	segments.reserve(
		static_cast<rofl::aux::polygonizers::triangle::segment_vector::size_type>(
			in.numberofsegments * 2));
	in.segmentlist =
		&segments[0];

	// Holes
	rofl::aux::polygonizers::triangle::hole_vector holes;

	holes.reserve(
		static_cast<
			rofl::aux::polygonizers::triangle::hole_vector::size_type
		>(
			2u * _poly.holes().size()
		)
	);

	in.numberofholes =
		static_cast<
			int
		>(
			_poly.holes().size()
		);

	in.holelist =
		&holes[0];

	// add points and holes begin
	rofl::aux::polygonizers::triangle::add_polygon(
		points,
		segments,
		_poly.border());

	for(
		auto const &elem : _poly.holes()
	)
	{
		/*
		FCPPT_ASSERT_MESSAGE(
			rofl::aux::polygonizers::triangle::is_convex(r),
			FCPPT_TEXT("Holes have to be convex"));
			*/

		rofl::aux::polygonizers::triangle::add_polygon(
			points,
			segments,
			elem
		);

		point const ip =
			rofl::math::barycenter(
				elem);
		holes.push_back(
			ip.x());
		holes.push_back(
			ip.y());
	}
	// add points and holes end

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_ << FCPPT_TEXT("Outputting points:"));

	for(
		point_vector::const_reference elem : points
	)
	{
		FCPPT_LOG_DEBUG(
			log_,
			fcppt::log::_ << elem
		);
	}

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_ << FCPPT_TEXT("Points end"));

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_ << FCPPT_TEXT("Outputting segments:"));

	for(
		segment_vector::const_reference seg : segments
	)
	{
		FCPPT_LOG_DEBUG(
			log_,
			fcppt::log::_ << seg
		);
	}

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_ << FCPPT_TEXT("Segments end"));

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_ << FCPPT_TEXT("Outputting holes:"));

	for(
		hole_vector::const_reference hole : holes
	)
	{
		FCPPT_LOG_DEBUG(
			log_,
			fcppt::log::_ << hole
		);
	}

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_ << FCPPT_TEXT("Holes end"));

	rofl::aux::polygonizers::triangle::triangulation t(
	//	"pznQ", // q for quality
		"pznqQ", // q for quality
		in,
		out);

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_ << FCPPT_TEXT("Outputting neighbors:"));

	for (int i = 0; i < out.numberoftriangles*3; ++i)
	{
		FCPPT_LOG_DEBUG(
			log_,
			fcppt::log::_ << out.neighborlist[i]);
	}

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_ << FCPPT_TEXT("Neighbors end"));

	FCPPT_ASSERT_ERROR(out.numberofcorners == 3);

	// first, create an array rofl::points from the out.pointlist.
	// This is stored in the graph properties, and the indexed_points
	// use that as their source
	rofl::aux::polygonizers::triangle::fill_points(
		out.pointlist,
		2*out.numberofpoints,
		boost::get_property(
			_output,
			rofl::graph::property_tag()
		).points());

	typedef
	std::vector
	<
		rofl::aux::polygonizers::triangle::intermediate
	>
	graph_polygon_vector;

	graph_polygon_vector
		graph_polygons;

	rofl::aux::polygonizers::triangle::fill_intermediate(
		_output,
		graph_polygons,
		out.numberoftriangles,
		out.trianglelist,
		out.neighborlist
	);

	for(
		auto const &intermediate : graph_polygons
	)
	{
		for(
			auto const index : intermediate.neighbors
		)
		{
			if(
				index == -1
			)
				continue;

			rofl::graph::vertex_descriptor const &
				vertex(
					graph_polygons[
						static_cast<
							graph_polygon_vector::size_type
						>(
							index
						)
					].vertex
				);

			rofl::graph::vertex_properties const
				&props0(
					_output[
						intermediate.vertex
					]
				),
				&props1(
					_output[
						vertex
					]
				);

			indexed_polygon const
				&p0 = props0.polygon(),
				&p1 = props1.polygon();

			point const
				c0 = props0.barycenter(),
				c1 = props1.barycenter();

			unit const
				length =
					fcppt::math::vector::length(
						c0 - c1
					);

			if(
				boost::add_edge(
					intermediate.vertex,
					vertex,
					rofl::graph::edge_properties(
						length,
						rofl::aux::polygonizers::triangle::determine_adjacent_edge(
							p0,
							p1
						)
					),
					_output
				).second
				==
				false
			)
			{
				FCPPT_LOG_DEBUG(
					log_,
					fcppt::log::_ << FCPPT_TEXT("Edge already added"));
			}
			else
			{
				FCPPT_LOG_DEBUG(
					log_,
					fcppt::log::_ << FCPPT_TEXT("Adding edge"));
			}
		}
	}
}

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
#include <rofl/aux/polygonizers/triangle/intermediate.hpp>
//#include <rofl/aux/polygonizers/triangle/is_convex.hpp>
#include <rofl/aux/polygonizers/triangle/log_location.hpp>
#include <rofl/aux/polygonizers/triangle/object.hpp>
#include <rofl/aux/polygonizers/triangle/triangulation.hpp>
#include <rofl/aux/log_parameters.hpp>
#include <rofl/math/barycenter.hpp>
#include <rofl/graph/object.hpp>
#include <rofl/graph/property_tag.hpp>
#include <rofl/graph/vertex_properties.hpp>
#include <rofl/indexed_point.hpp>
#include <triangle/impl.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::log::object
mylogger(
	rofl::aux::log_parameters(
		rofl::aux::polygonizers::triangle::log_location()
		/
		FCPPT_TEXT("object")
	)
);

}

rofl::aux::polygonizers::triangle::object::object()
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
	typedef fcppt::container::raw_vector<
		rofl::unit
	> point_vector;

	typedef fcppt::container::raw_vector<
		int
	> segment_vector;

	typedef fcppt::container::raw_vector<
		rofl::unit
	> hole_vector;
/*
	mylogger.activate(
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
	point_vector points;
	points.reserve(
		static_cast<point_vector::size_type>(
			in.numberofpoints * 2));
	in.pointlist =
		&points[0];

	// Segments
	in.numberofsegments =
		in.numberofpoints;
	segment_vector
		segments;
	segments.reserve(
		static_cast<segment_vector::size_type>(
			in.numberofsegments * 2));
	in.segmentlist =
		&segments[0];

	// Holes
	hole_vector holes;
	holes.reserve(
		static_cast<hole_vector::size_type>(
			2*_poly.holes().size()));
	in.numberofholes =
		_poly.holes().size();
	in.holelist =
		&holes[0];

	// add points and holes begin
	rofl::aux::polygonizers::triangle::add_polygon(
		points,
		segments,
		_poly.border());

	for(
		polygon_with_holes::hole_set::const_reference elem : _poly.holes()
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
			ip[0]);
		holes.push_back(
			ip[1]);
	}
	// add points and holes end

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("Outputting points:"));

	for(
		point_vector::const_reference elem : points
	)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << elem
		);
	}

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("Points end"));

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("Outputting segments:"));

	for(
		segment_vector::const_reference seg : segments
	)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << seg
		);
	}

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("Segments end"));

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("Outputting holes:"));

	for(
		hole_vector::const_reference hole : holes
	)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << hole
		);
	}

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("Holes end"));

	rofl::aux::polygonizers::triangle::triangulation t(
	//	"pznQ", // q for quality
		"pznqQ", // q for quality
		in,
		out);

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("Outputting neighbors:"));

	for (int i = 0; i < out.numberoftriangles*3; ++i)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << out.neighborlist[i]);
	}

	FCPPT_LOG_DEBUG(
		mylogger,
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
		out.neighborlist);

	for(
		auto const &r : graph_polygons
	)
	{
		for(
			auto const &i : r.neighbors
		)
		{
			if (i == -1)
				continue;

			rofl::graph::vertex_properties const
				&props0 = _output[r.vertex],
				&props1 = _output[graph_polygons[i].vertex];

			indexed_polygon const
				&p0 = props0.polygon(),
				&p1 = props1.polygon();
			point const
				c0 = props0.barycenter(),
				c1 = props1.barycenter();
			unit const
				l =
					fcppt::math::vector::length(
						c0-c1);

			if (boost::add_edge(
				r.vertex,
				graph_polygons[i].vertex,
				rofl::graph::edge_properties(
					l,
					rofl::aux::polygonizers::triangle::determine_adjacent_edge(
						p0,
						p1)),
				_output).second == false)
			{
				FCPPT_LOG_DEBUG(
					mylogger,
					fcppt::log::_ << FCPPT_TEXT("Edge already added"));
			}
			else
			{
				FCPPT_LOG_DEBUG(
					mylogger,
					fcppt::log::_ << FCPPT_TEXT("Adding edge"));
			}
		}
	}
}

#include "../object.hpp"
#include "../impl/impl.hpp"
#include "../accumulate_sizes.hpp"
#include "../clear_pod.hpp"
#include "../add_polygon.hpp"
#include "../triangulation.hpp"
#include "../triangle_line_segments.hpp"
#include "../line_segments.hpp"
#include "../is_convex.hpp"
#include "../fill_points.hpp"
#include "../fill_intermediate.hpp"
#include "../determine_adjacent_edge.hpp"
#include "../log.hpp"
#include <rofl/unit.hpp>
#include <rofl/point.hpp>
#include <rofl/polygon_with_holes.hpp>
#include <rofl/line_segment.hpp>
#include <rofl/polygon.hpp>
#include <rofl/math/polygon.hpp>
#include <rofl/math/barycenter.hpp>
#include <rofl/graph/object.hpp>
#include <rofl/graph/vertex_properties.hpp>
#include <rofl/indexed_point.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/null.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/array.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>
#include <cstring>
#include <cstddef>
#include <cmath>

namespace
{
fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		rofl::polygonizers::triangle::log(),
		FCPPT_TEXT("object")));

typedef fcppt::container::raw_vector<rofl::unit> point_vector;
typedef fcppt::container::raw_vector<int> segment_vector;
typedef fcppt::container::raw_vector<rofl::unit> hole_vector;
}

void 
rofl::polygonizers::triangle::object::polygonize(
	polygon_with_holes const &p,
	graph::object &output)
{
/*
	mylogger.activate(
		fcppt::log::level::debug);
		*/
	
	triangulateio 
		in,
		out;
	
	// since triangulateio is a C structure, we can just memset it to 0
	clear_pod(
		in);
	clear_pod(
		out);

	// Points
	in.numberofpoints = 
		static_cast<int>(
			p.border().size()+
			accumulate_sizes(
				p.holes()));
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
			2*p.holes().size()));
	in.numberofholes = 
		p.holes().size();
	in.holelist = 
		&holes[0];

	// add points and holes begin
	add_polygon(
		points,
		segments,
		p.border());
	
	BOOST_FOREACH(polygon_with_holes::hole_set::const_reference r,p.holes())
	{
		/*
		FCPPT_ASSERT_MESSAGE(
			is_convex(r),
			FCPPT_TEXT("Holes have to be convex"));
			*/
			
		add_polygon(
			points,
			segments,
			r);
		
		point const ip = 
			math::barycenter(
				r);
		holes.push_back(
			ip[0]);
		holes.push_back(
			ip[1]);
	}
	// add points and holes end

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("Outputting points:"));
	BOOST_FOREACH(point_vector::const_reference r,points)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << r);
	}
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("Points end"));
		
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("Outputting segments:"));
	BOOST_FOREACH(segment_vector::const_reference r,segments)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << r);
	}
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("Segments end"));
		
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("Outputting holes:"));
	BOOST_FOREACH(hole_vector::const_reference r,holes)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << r);
	}
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("Holes end"));
	
	triangulation t(
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
	
	FCPPT_ASSERT(out.numberofcorners == 3);
	
	// first, create an array rofl::points from the out.pointlist. 
	// This is stored in the graph properties, and the indexed_points 
	// use that as their source
	fill_points(
		out.pointlist,
		2*out.numberofpoints,
		boost::get_property(
			output,
			rofl::graph::property_tag()
		).points());
	
	typedef 
	std::vector
	<
		intermediate
	> 
	graph_polygon_vector;
	
	graph_polygon_vector 
		graph_polygons;

	fill_intermediate(
		output,
		graph_polygons,
		out.numberoftriangles,
		out.trianglelist,
		out.neighborlist);
	
	BOOST_FOREACH(graph_polygon_vector::const_reference r,graph_polygons)
	{
		BOOST_FOREACH(intermediate::neighbor_array::const_reference i,r.neighbors)
		{
			if (i == -1)
				continue;

			graph::vertex_properties const 
				&props0 = output[r.vertex],
				&props1 = output[graph_polygons[i].vertex];

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
				graph::edge_properties(
					l,
					determine_adjacent_edge(
						p0,
						p1)),
				output).second == false)
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

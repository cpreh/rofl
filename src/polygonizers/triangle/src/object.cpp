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
#include <sge/container/raw_vector.hpp>
#include <sge/assign/make_array.hpp>
#include <sge/math/vector/length.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/null.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>
#include <sge/log/headers.hpp>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <tr1/array>

namespace
{
sge::log::object 
mylogger(
	sge::log::parameters::inherited(
		rofl::polygonizers::triangle::log(),
		SGE_TEXT("object")));

typedef sge::container::raw_vector<rofl::unit> point_vector;
typedef sge::container::raw_vector<int> segment_vector;
typedef sge::container::raw_vector<rofl::unit> hole_vector;
}

void 
rofl::polygonizers::triangle::object::polygonize(
	polygon_with_holes const &p,
	graph::object &output)
{
/*
	mylogger.activate(
		sge::log::level::debug);
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
		SGE_ASSERT_MESSAGE(
			is_convex(r),
			SGE_TEXT("Holes have to be convex"));
			
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

	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_ << SGE_TEXT("Outputting points:"));
	BOOST_FOREACH(point_vector::const_reference r,points)
	{
		SGE_LOG_DEBUG(
			mylogger,
			sge::log::_ << r);
	}
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_ << SGE_TEXT("Points end"));
		
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_ << SGE_TEXT("Outputting segments:"));
	BOOST_FOREACH(segment_vector::const_reference r,segments)
	{
		SGE_LOG_DEBUG(
			mylogger,
			sge::log::_ << r);
	}
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_ << SGE_TEXT("Segments end"));
		
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_ << SGE_TEXT("Outputting holes:"));
	BOOST_FOREACH(hole_vector::const_reference r,holes)
	{
		SGE_LOG_DEBUG(
			mylogger,
			sge::log::_ << r);
	}
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_ << SGE_TEXT("Holes end"));
	
	triangulation t(
	//	"pznQ", // q for quality
		"pznqQ", // q for quality
		in,
		out);
	
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_ << SGE_TEXT("Outputting neighbors:"));
	for (int i = 0; i < out.numberoftriangles*3; ++i)
	{
		SGE_LOG_DEBUG(
			mylogger,
			sge::log::_ << out.neighborlist[i]);
	}
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_ << SGE_TEXT("Neighbors end"));
	
	SGE_ASSERT(out.numberofcorners == 3);
	
	// first, create an array rofl::points from the out.pointlist. 
	// This is stored in the graph properties, and the indexed_points 
	// use that as their source
	fill_points(
		out.pointlist,
		2*out.numberofpoints,
		output.m_property.points());
	
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
					sge::math::vector::length(
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
				SGE_LOG_DEBUG(
					mylogger,
					sge::log::_ << SGE_TEXT("Edge already added"));
			}
			else
			{
				SGE_LOG_DEBUG(
					mylogger,
					sge::log::_ << SGE_TEXT("Adding edge"));
			}
		}
	}
}

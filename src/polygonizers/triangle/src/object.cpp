#include "../object.hpp"
#include "../impl/impl.hpp"
#include "../accumulate_sizes.hpp"
#include "../add_polygon.hpp"
#include "../inner_point.hpp"
#include "../triangulation.hpp"
#include "../triangle_line_segments.hpp"
#include "../line_segments.hpp"
#include "../is_convex.hpp"
#include <rofl/unit.hpp>
#include <rofl/point.hpp>
#include <rofl/polygon_with_holes.hpp>
#include <rofl/line_segment.hpp>
#include <rofl/polygon.hpp>
#include <rofl/graph/object.hpp>
#include <sge/container/raw_vector.hpp>
#include <sge/assign/make_array.hpp>
#include <sge/math/vector/length.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>
#include <sge/log/headers.hpp>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <tr1/array>

namespace
{
sge::log::logger mylogger(
	sge::log::global(),
	SGE_TEXT("rofl: polygonizers: triangle: object: "),
	true);

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
	
	typedef 
	boost::graph_traits
	<
		rofl::graph::object
	>::vertex_descriptor vertex_descriptor;
	
	vertex_descriptor
		vertex;
	neighbor_array 
		neighbors;
	bool 
		visited;
	
	intermediate(
		vertex_descriptor const &,
		neighbor_array const &);
};

intermediate::intermediate(
	vertex_descriptor const &vertex,
	neighbor_array const &neighbors)
:
	vertex(
		vertex),
	neighbors(
		neighbors),
	visited(false)
{
}

rofl::line_segment const 
determine_adjacent_edge(
	rofl::polygon const &p0,
	rofl::polygon const &p1)
{
	BOOST_FOREACH(
		rofl::polygonizers::triangle::triangle_line_segments::const_reference r,
		rofl::polygonizers::triangle::line_segments(p0))
	{
		BOOST_FOREACH(
			rofl::polygonizers::triangle::triangle_line_segments::const_reference s,
			rofl::polygonizers::triangle::line_segments(p1))
		{
			if (r == s)
				return r;
		}
	}
	
	SGE_ASSERT_MESSAGE(
		false,
		SGE_TEXT("Triangle reported that two triangles are adjacent. Own testing, however, revealed otherwise"));
}
}

void 
rofl::polygonizers::triangle::object::polygonize(
	polygon_with_holes const &p,
	graph::object &output)
{
	triangulateio 
		in,out;
	
	std::memset(
		&out,
		0,
		sizeof(triangulateio));
		
	std::memset(
		&in,
		0,
		sizeof(triangulateio));
	
	typedef sge::container::raw_vector<unit> point_vector;
	typedef sge::container::raw_vector<int> segment_vector;
	typedef sge::container::raw_vector<unit> hole_vector;

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
	in.numberofsegments = 
		in.numberofpoints;
	segment_vector 
		segments;
	segments.reserve(
		static_cast<segment_vector::size_type>(
			in.numberofsegments * 2));
	in.segmentlist = 
		&segments[0];
		
	add_polygon(
		points,
		segments,
		p.border());
	
	hole_vector holes;
	holes.reserve(
		static_cast<hole_vector::size_type>(
			2*p.holes().size()));
			
	in.numberofholes = 
		p.holes().size();
		
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
			inner_point(
				r);
		holes.push_back(
			ip[0]);
		holes.push_back(
			ip[1]);
	}
	
	in.holelist = 
		&holes[0];

	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_1 << SGE_TEXT("Outputting points:"));
	BOOST_FOREACH(point_vector::const_reference r,points)
	{
		SGE_LOG_DEBUG(
			mylogger,
			sge::log::_1 << r);
	}
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_1 << SGE_TEXT("Points end"));
		
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_1 << SGE_TEXT("Outputting segments:"));
	BOOST_FOREACH(segment_vector::const_reference r,segments)
	{
		SGE_LOG_DEBUG(
			mylogger,
			sge::log::_1 << r);
	}
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_1 << SGE_TEXT("Segments end"));
		
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_1 << SGE_TEXT("Outputting holes:"));
	BOOST_FOREACH(hole_vector::const_reference r,holes)
	{
		SGE_LOG_DEBUG(
			mylogger,
			sge::log::_1 << r);
	}
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_1 << SGE_TEXT("Holes end"));
		
	triangulation t(
		"pzqn",
		in,
		out);
	
	SGE_ASSERT(out.numberofcorners == 3);
	
	typedef 
	std::vector
	<
		intermediate
	> 
	graph_polygon_vector;
	
	graph_polygon_vector 
		graph_polygons;
	
	for (int tri = 0; tri < out.numberoftriangles; ++tri)
	{
		polygon g;
		std::size_t const tri_base = 
			static_cast<std::size_t>(
				3*tri);
		for (int corner = 0; corner < 3; ++corner)
		{
			std::size_t const corner_base = 
				static_cast<std::size_t>(
					tri_base + corner);
			point p;
			for (int xy = 0; xy < 2; ++xy)
				p[xy] = 
					out.pointlist[2*out.trianglelist[corner_base]+xy];
			g.push_back(p);
		}
		graph_polygons.push_back(
			intermediate(
				boost::add_vertex(
					graph::vertex_properties(
						g),
					output),
				sge::assign::make_array<intermediate::index>
					(out.neighborlist[tri])
					(out.neighborlist[tri+1])
					(out.neighborlist[tri+2])));
	}
	
	BOOST_FOREACH(graph_polygon_vector::const_reference r,graph_polygons)
	{
		if (r.visited)
			continue;
		BOOST_FOREACH(intermediate::neighbor_array::const_reference i,r.neighbors)
		{
			if (i == -1)
				continue;
			polygon const 
				&p0 = output[r.vertex].polygon(),
				&p1 = output[graph_polygons[i].vertex].polygon();
			
			boost::add_edge(
				r.vertex,
				graph_polygons[i].vertex,
				graph::edge_properties(
					sge::math::vector::length(
						inner_point(
							p0)-
						inner_point(
							p1)),
					determine_adjacent_edge(
						p0,
						p1)),
				output);
			
			graph_polygons[i].visited = 
				true;
		}
	}
}
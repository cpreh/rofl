#ifndef ROFL_POLYGONIZERS_TRIANGLE_DETERMINATE_ADJACENT_EDGE_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_DETERMINATE_ADJACENT_EDGE_HPP_INCLUDED

#include "line_segments.hpp"
#include "triangle_line_segments.hpp"
#include <rofl/indexed_line_segment.hpp>
#include <rofl/indexed_polygon.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>

namespace rofl
{
namespace polygonizers
{
namespace triangle
{
indexed_line_segment const 
determine_adjacent_edge(
	indexed_polygon const &p0,
	indexed_polygon const &p1)
{
	triangle_line_segments const
		p0s(line_segments(p0)),
		p1s(line_segments(p1));
		
	BOOST_FOREACH(
		triangle_line_segments::const_reference r,
		p0s)
	{
		BOOST_FOREACH(
			triangle_line_segments::const_reference s,
			p1s)
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
}
}

#endif
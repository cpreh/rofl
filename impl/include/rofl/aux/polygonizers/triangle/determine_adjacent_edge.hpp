#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_DETERMINE_ADJACENT_EDGE_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_DETERMINE_ADJACENT_EDGE_HPP_INCLUDED

#include <rofl/indexed_line_segment.hpp>
#include <rofl/indexed_polygon.hpp>
#include <rofl/aux/polygonizers/triangle/line_segments.hpp>
#include <rofl/aux/polygonizers/triangle/triangle_line_segments.hpp>
#include <fcppt/config/external_begin.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>


namespace rofl::aux::polygonizers::triangle
{

inline
rofl::indexed_line_segment
determine_adjacent_edge(
	rofl::indexed_polygon const &_p0,
	rofl::indexed_polygon const &_p1
)
{
	rofl::aux::polygonizers::triangle::triangle_line_segments const p0s(
		rofl::aux::polygonizers::triangle::line_segments(
			_p0
		)
	);

	rofl::aux::polygonizers::triangle::triangle_line_segments const p1s(
		rofl::aux::polygonizers::triangle::line_segments(
			_p1
		)
	);

	for(
		auto const &elem_0 : p0s
	)
	{
		for(
			auto const &elem_1 : p1s
		)
		{
			if(
				elem_0 == elem_1
			)
			{
				return elem_0;
			}
		}
	}

	std::terminate();
}

}

#endif

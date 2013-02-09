#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_DETERMINE_ADJACENT_EDGE_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_DETERMINE_ADJACENT_EDGE_HPP_INCLUDED

#include <rofl/indexed_line_segment.hpp>
#include <rofl/indexed_polygon.hpp>
#include <rofl/aux/polygonizers/triangle/line_segments.hpp>
#include <rofl/aux/polygonizers/triangle/triangle_line_segments.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable_message.hpp>


namespace rofl
{
namespace aux
{
namespace polygonizers
{
namespace triangle
{

rofl::indexed_line_segment const
determine_adjacent_edge(
	rofl::indexed_polygon const &_p0,
	rofl::indexed_polygon const &_p1
)
{
	rofl::aux::polygonizers::triangle::triangle_line_segments const
		p0s(
			rofl::aux::polygonizers::triangle::line_segments(
				_p0
			)
		),
		p1s(
			rofl::aux::polygonizers::triangle::line_segments(
				_p1
			)
		);

	for(
		auto const &elem_0 : p0s
	)
		for(
			auto const &elem_1 : p1s
		)
			if(
				elem_0 == elem_1
			)
				return elem_0;

	FCPPT_ASSERT_UNREACHABLE_MESSAGE(
		FCPPT_TEXT("Triangle reported that two triangles are adjacent. Own testing, however, revealed otherwise")
	);
}

}
}
}
}

#endif

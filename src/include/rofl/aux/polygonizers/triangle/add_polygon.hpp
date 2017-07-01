#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_ADD_POLYGON_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_ADD_POLYGON_HPP_INCLUDED

#include <rofl/aux/polygonizers/triangle/point_vector.hpp>
#include <rofl/aux/polygonizers/triangle/segment_vector.hpp>


namespace rofl
{
namespace aux
{
namespace polygonizers
{
namespace triangle
{

// The function adds a polygon to the segment and the point list
template
<
	typename Polygon
>
void
add_polygon(
	rofl::aux::polygonizers::triangle::point_vector &_points,
	rofl::aux::polygonizers::triangle::segment_vector &_segments,
	Polygon const &_poly
)
{
	rofl::aux::polygonizers::triangle::point_vector::size_type base(
		_points.size() / 2u
	);

	for(
		typename Polygon::size_type index(
			0u
		);
		index < _poly.size();
		index++
	)
	{
		_points.push_back(
			_poly[index].x()
		);

		_points.push_back(
			_poly[index].y()
		);

		_segments.push_back(
			static_cast<
				rofl::aux::polygonizers::triangle::segment_vector::value_type
			>(
				base + index
			)
		);
		// At the end, loop back to the first vertex in the
		// polygon (do not use 0 here but "base" instead)
		_segments.push_back(
			static_cast<
				rofl::aux::polygonizers::triangle::segment_vector::value_type
			>(
				index == _poly.size() - 1u
				?
					base
				:
					base
					+
					index
					+
					1u
			)
		);
	}
}

}
}
}
}

#endif

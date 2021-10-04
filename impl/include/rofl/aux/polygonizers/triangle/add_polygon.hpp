#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_ADD_POLYGON_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_ADD_POLYGON_HPP_INCLUDED

#include <rofl/aux/polygonizers/triangle/point_vector.hpp>
#include <rofl/aux/polygonizers/triangle/segment_vector.hpp>
#include <fcppt/reference_impl.hpp>


namespace rofl::aux::polygonizers::triangle
{

// The function adds a polygon to the segment and the point list
template
<
	typename Polygon
>
void
add_polygon(
	fcppt::reference<
		rofl::aux::polygonizers::triangle::point_vector
	> const _points,
	fcppt::reference<
		rofl::aux::polygonizers::triangle::segment_vector
	> const _segments,
	Polygon const &_poly
)
{
	rofl::aux::polygonizers::triangle::point_vector::size_type base(
		_points.get().size() / 2U
	);

	for(
		typename Polygon::size_type index(
			0U
		);
		index < _poly.size();
		index++
	)
	{
		_points.get().push_back(
			_poly[index].x()
		);

		_points.get().push_back(
			_poly[index].y()
		);

		_segments.get().push_back(
			static_cast<
				rofl::aux::polygonizers::triangle::segment_vector::value_type
			>(
				base + index
			)
		);
		// At the end, loop back to the first vertex in the
		// polygon (do not use 0 here but "base" instead)
		_segments.get().push_back(
			static_cast<
				rofl::aux::polygonizers::triangle::segment_vector::value_type
			>(
				index == _poly.size() - 1U
				?
					base
				:
					base
					+
					index
					+
					1U
			)
		);
	}
}

}

#endif

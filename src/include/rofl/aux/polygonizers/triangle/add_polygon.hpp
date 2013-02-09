#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_ADD_POLYGON_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_ADD_POLYGON_HPP_INCLUDED


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
	typename Points,
	typename Segments,
	typename Polygon
>
void
add_polygon(
	Points &_ps,
	Segments &_ss,
	Polygon const &_p
)
{
	typename
	Points::size_type base(
		_ps.size() / 2u
	);

	for(
		typename Polygon::size_type i = 0;
		i < _p.size();
		i++
	)
	{
		_ps.push_back(
			_p[i][0]
		);

		_ps.push_back(
			_p[i][1]
		);

		_ss.push_back(
			base+i
		);
		// At the end, loop back to the first vertex in the
		// polygon (do not use 0 here but "base" instead)
		_ss.push_back(
			i == _p.size()-1u
			?
				base
			:
				base+i+1u);
	}
}

}
}
}
}

#endif

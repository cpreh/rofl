#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_FILL_POINTS_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_FILL_POINTS_HPP_INCLUDED


namespace rofl
{
namespace aux
{
namespace polygonizers
{
namespace triangle
{

template
<
	typename Coords,
	typename SizeType,
	typename Points
>
void
fill_points(
	Coords &cs,
	SizeType const size,
	Points &p
)
{
	typedef
	SizeType
	size_type;

	typedef typename
	Points::value_type
	point;

	typedef typename
	point::value_type
	unit;

	for (size_type i = 0u; i < size; i += static_cast<size_type>(2))
		p.push_back(
			point(
				static_cast<unit>(
					cs[i]),
				static_cast<unit>(
					cs[i+1])));
}

}
}
}
}

#endif

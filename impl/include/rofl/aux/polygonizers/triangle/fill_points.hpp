#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_FILL_POINTS_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_FILL_POINTS_HPP_INCLUDED

#include <fcppt/reference_impl.hpp>


namespace rofl
{
namespace aux
{
namespace polygonizers
{
namespace triangle
{

template<
	typename Coords,
	typename SizeType,
	typename Points
>
void
fill_points(
	fcppt::reference<
		Coords
	> const cs,
	SizeType const size,
	fcppt::reference<
		Points
	> const p
)
{
	using
	size_type
	=
	SizeType;

	using
	point
	=
	typename
	Points::value_type;

	using
	unit
	=
	typename
	point::value_type;

	for (size_type i = 0U; i < size; i += static_cast<size_type>(2))
	{
		p.get().push_back(
			point(
				static_cast<unit>(
					cs.get()[i]),
				static_cast<unit>(
					cs.get()[i+1])));
	}
}

}
}
}
}

#endif

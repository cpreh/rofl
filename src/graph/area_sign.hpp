#ifndef ROFL_GRAPH_AREA_SIGN_HPP_INCLUDED
#define ROFL_GRAPH_AREA_SIGN_HPP_INCLUDED

#include <sge/math/vector/cross.hpp>
#include <sge/math/vector/arithmetic.hpp>

namespace rofl
{
namespace graph
{
template<typename T>
int area_sign(
	T const &a,
	T const &b,
	T const &c)
{
	/*(b-a).x()*(c-a).y() - (c-a).x()*(b-a).y();
	cross(b-a,c-a)*/
	typename T::value_type area2 = 
		sge::math::vector::cross(
			b-a,
			c-a);
		/*
		(b[0] - a[0]) * (c[1] - a[1]) -
		(c[0] - a[0]) * (b[1] - a[1]);
		*/

    if (area2 > static_cast<typename T::value_type>(0.5)) 
		return 1;
	return 
		area2 < static_cast<typename T::value_type>(-0.5)
		?
			-1
		: 
			0;

}
}
}

#endif
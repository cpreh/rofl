#ifndef ROFL_GRAPH_AREA_SIGN_HPP_INCLUDED
#define ROFL_GRAPH_AREA_SIGN_HPP_INCLUDED

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
	typename T::value_type area2 = 
		(b[0] - a[0]) * (c[1] - a[1]) -
		(c[0] - a[0]) * (b[1] - a[1]);

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
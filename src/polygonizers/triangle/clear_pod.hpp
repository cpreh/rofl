#ifndef ROFL_POLYGONIZERS_TRIANGLE_CLEAR_POD_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_CLEAR_POD_HPP_INCLUDED

#include <boost/type_traits/is_pod.hpp>
#include <boost/utility/enable_if.hpp>
#include <cstring>

namespace rofl
{
namespace polygonizers
{
namespace triangle
{
template
<
	typename T
>
typename
boost::enable_if
<
	boost::is_pod<T>,
	void
>::type
clear_pod(
	T &t)
{
	std::memset(
		&t,
		0,
		sizeof(T));
}
}
}
}

#endif

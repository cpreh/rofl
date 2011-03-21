#ifndef ROFL_POLYGONIZERS_TRIANGLE_ACCUMULATE_SIZES_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_ACCUMULATE_SIZES_HPP_INCLUDED

#include <fcppt/math/null.hpp>
#include <boost/foreach.hpp>

namespace rofl
{
namespace polygonizers
{
namespace triangle
{
template<typename Container>
typename Container::size_type accumulate_sizes(
	Container const &c)
{
	typename Container::size_type s = 
		fcppt::math::null<typename Container::size_type>();
	BOOST_FOREACH(typename Container::const_reference r,c)
		s += r.size();
	return s;
}

}
}
}

#endif

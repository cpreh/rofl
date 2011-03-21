#ifndef ROFL_MATH_BARYCENTER_HPP_INCLUDED
#define ROFL_MATH_BARYCENTER_HPP_INCLUDED

#include <boost/foreach.hpp>

namespace rofl
{
namespace math
{
template<typename Container>
typename Container::value_type barycenter(
	Container const &p)
{
	typedef
	typename
	Container::value_type
	vector;
	
	typedef 
	typename 
	vector::value_type 
	scalar;
	
	scalar const r =
		static_cast<scalar>(1)/
		static_cast<scalar>(p.size());
	
	vector out = 
		vector::null();
	
	BOOST_FOREACH(typename Container::const_reference i,p)
		out += i;
	
	return 
		r * out;
}
}
}

#endif

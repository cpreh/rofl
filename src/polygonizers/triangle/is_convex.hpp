#ifndef ROFL_POLYGONIZERS_TRIANGLE_IS_CONVEX_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_IS_CONVEX_HPP_INCLUDED

#include "edge_angle.hpp"
#include <sge/assert.hpp>
#include <sge/math/compare.hpp>
#include <boost/next_prior.hpp>

namespace rofl
{
namespace polygonizers
{
namespace triangle
{
template<typename Polygon>
bool is_convex(
	Polygon const &p)
{
/*
	SGE_ASSERT(
		p.size() > static_cast<typename Polygon::size_type>(3));*/
		
	typedef
	typename
	Polygon::value_type
	vector;
	
	typedef 
	typename 
	vector::value_type 
	scalar;
	
	scalar const sign = 
		edge_angle(
			p.front(),
			*boost::next(p.begin()),
			*boost::next(p.begin(),2));
	
			/*
	cyclic_iterator<Polygon::const_iterator> i;
	for (typename Polygon::size_type c = 0; c < p.size(); ++c)
		if(
			sge::math::compare(
				edge_angle(*i,*boost::next(i),*boost::next(i,2)),
				sign))
				*/
	
	for (typename Polygon::const_iterator i = p.begin(); i != p.end(); ++i)
	{
		vector const 
			&a = *i,
			&b = 
				i == boost::prior(p.end()) 
				? 
					p.front() 
				: 
					*boost::next(i),
			&c = 
				i == boost::prior(p.end())
				?
					*boost::next(p.begin(),2)
				:
					(i == boost::prior(p.end(),2)
					?
						p.front()
					:
						*boost::next(i,2));
		
		if (!sge::math::compare(edge_angle(a,b,c),sign))
			return false;
	}
	return true;
}
}
}
}

#endif

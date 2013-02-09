#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_IS_CONVEX_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_IS_CONVEX_HPP_INCLUDED

#include <rofl/aux/polygonizers/triangle/edge_angle.hpp>
#include <fcppt/math/diff.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace rofl
{
namespace aux
{
namespace polygonizers
{
namespace triangle
{

template<
	typename Polygon
>
bool
is_convex(
	Polygon const &p
)
{
	typedef
	typename
	Polygon::value_type
	vector;

	typedef
	typename
	vector::value_type
	scalar;

	scalar const sign =
		rofl::aux::polygonizers::triangle::edge_angle(
			p.front(),
			*std::next(p.begin()),
			*std::next(p.begin(),2));

			/*
	cyclic_iterator<Polygon::const_iterator> i;
	for (typename Polygon::size_type c = 0; c < p.size(); ++c)
		if(
			fcppt::math::compare(
				edge_angle(*i,*std::next(i),*std::next(i,2)),
				sign))
				*/

	for (typename Polygon::const_iterator i = p.begin(); i != p.end(); ++i)
	{
		vector const
			&a = *i,
			&b =
				i == std::prev(p.end())
				?
					p.front()
				:
					*dstd::next(i),
			&c =
				i == std::prev(p.end())
				?
					*std::next(p.begin(),2)
				:
					(i == std::prev(p.end(),2)
					?
						p.front()
					:
						*std::next(i,2));

		if(
			fcppt::math::diff(
				rofl::aux::polygonizers::edge_angle(a,b,c),
				sign
			)
			>
			static_cast<
				scalar
			>(
				0.001f
			)
		)
			return false;
	}
	return true;
}

}
}
}
}

#endif

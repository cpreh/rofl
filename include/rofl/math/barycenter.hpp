#ifndef ROFL_MATH_BARYCENTER_HPP_INCLUDED
#define ROFL_MATH_BARYCENTER_HPP_INCLUDED

#include <fcppt/math/vector/null.hpp>

namespace rofl::math
{

template<typename Container>
typename Container::value_type
barycenter(
	Container const &p)
{
	using
	vector
	=
	typename
	Container::value_type;

	using
	scalar
	=
	typename
	vector::value_type;

	scalar const r =
		static_cast<scalar>(1)/
		static_cast<scalar>(p.size());

	vector out{
		fcppt::math::vector::null<
			vector
		>()
	};

	for(typename Container::const_reference i : p)
	{
		out += i;
	}

	return
		r * out;
}
}

#endif

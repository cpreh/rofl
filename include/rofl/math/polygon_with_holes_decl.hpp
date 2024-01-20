#ifndef ROFL_MATH_POLYGON_WITH_HOLES_DECL_HPP_INCLUDED
#define ROFL_MATH_POLYGON_WITH_HOLES_DECL_HPP_INCLUDED

#include <rofl/math/polygon_impl.hpp>
#include <rofl/math/polygon_with_holes_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace rofl::math
{

template<
	typename T
>
class polygon_with_holes
{
public:
	using
	polygon
	=
	rofl::math::polygon<
		T
	>;

	using
	hole_set
	=
	std::vector<
		polygon
	>;

	polygon_with_holes();

	explicit
	polygon_with_holes(
		polygon &&
	);

	polygon_with_holes(
		polygon &&,
		hole_set &&
	);

	void
	border(
		polygon &&
	);

	[[nodiscard]]
	polygon const &
	border() const;

	void
	add_hole(
		polygon &&
	);

	[[nodiscard]]
	hole_set const &
	holes() const;

	[[nodiscard]]
	polygon &
	border();

	[[nodiscard]]
	hole_set &
	holes();
private:
	polygon border_;

	hole_set holes_;
};

}

#endif

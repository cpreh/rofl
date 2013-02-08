#ifndef ROFL_MATH_POLYGON_WITH_HOLES_DECL_HPP_INCLUDED
#define ROFL_MATH_POLYGON_WITH_HOLES_DECL_HPP_INCLUDED

#include <rofl/math/polygon_impl.hpp>
#include <rofl/math/polygon_with_holes_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace rofl
{
namespace math
{

template<
	typename T
>
class polygon_with_holes
{
public:
	typedef rofl::math::polygon<
		T
	> polygon;

	typedef
	std::vector<
		polygon
	>
	hole_set;

	polygon_with_holes();

	explicit
	polygon_with_holes(
		polygon const &,
		hole_set const & = hole_set()
	);

	void
	border(
		polygon const &
	);

	polygon const &
	border() const;

	void
	add_hole(
		polygon const &
	);

	hole_set const &
	holes() const;

	polygon &
	border();

	hole_set &
	holes();
private:
	polygon border_;

	hole_set holes_;
};

}
}

#endif

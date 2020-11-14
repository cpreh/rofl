#ifndef ROFL_MATH_LINE_SEGMENT_DECL_HPP_INCLUDED
#define ROFL_MATH_LINE_SEGMENT_DECL_HPP_INCLUDED

#include <rofl/math/line_segment_fwd.hpp>


namespace rofl
{
namespace math
{

template<
	typename Vector
>
class line_segment
{
public:
	using
	point
	=
	Vector;

	line_segment();

	line_segment(
		point const &start,
		point const &end
	);

	[[nodiscard]]
	point const &
	start() const;

	[[nodiscard]]
	point const &
	end() const;

	[[nodiscard]]
	bool
	operator==(
		line_segment const &
	) const;
private:
	point start_;

	point end_;
};

}
}

#endif

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
	typedef Vector point;

	line_segment();

	line_segment(
		point const &start,
		point const &end
	);

	point const &
	start() const;

	point const &
	end() const;

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

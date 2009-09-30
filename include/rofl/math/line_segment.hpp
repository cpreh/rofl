#ifndef ROFL_MATH_LINE_SEGMENT_HPP_INCLUDED
#define ROFL_MATH_LINE_SEGMENT_HPP_INCLUDED

namespace rofl
{
namespace math
{
template<typename Vector>
class line_segment
{
public:
	typedef Vector point;
	
	line_segment();
	
	line_segment(
		point const &start,
		point const &end);
	
	point const &start() const;
	point const &end() const;
	
	bool operator==(
		line_segment const &) const;
private:
	point 
		start_,end_;
};
}
}

template<typename Vector>
rofl::math::line_segment<Vector>::line_segment()
:
	start_(),
	end_()
{
}

template<typename Vector>
rofl::math::line_segment<Vector>::line_segment(
	point const &_start,
	point const &_end)
:
	start_(
		_start),
	end_(
		_end)
{
}

template<typename Vector>
typename 
rofl::math::line_segment<Vector>::point const &
rofl::math::line_segment<Vector>::start() const
{
	return 
		start_;
}

template<typename Vector>
typename 
rofl::math::line_segment<Vector>::point const &
rofl::math::line_segment<Vector>::end() const
{
	return end_;
}

template<typename Vector>
bool
rofl::math::line_segment<Vector>::operator==(
	line_segment const &r) const
{
	return 
		(start_ == r.start_ &&
		end_ == r.end_) ||
		(start_ == r.end_ &&
		end_ == r.start_);
}

#endif

#ifndef ROFL_MATH_POLYGON_HPP_INCLUDED
#define ROFL_MATH_POLYGON_HPP_INCLUDED

#include <fcppt/math/detail/one_dimensional_output.hpp>
#include <fcppt/text.hpp>
#include <vector>
#include <ostream>
#include <limits>

namespace rofl
{
namespace math
{
template
<
	typename T
>
class polygon
{
public:
	typedef T point;
private:
	typedef
	std::vector
	<
		point
	>
	container;
public:
	typedef typename container::value_type value_type;
	typedef typename container::reference reference;
	typedef typename container::const_reference const_reference;
	typedef typename container::size_type size_type;
	typedef typename container::iterator iterator;
	typedef typename container::const_iterator const_iterator;
	
	void push_back(point const &p) { points_.push_back(p); }
	size_type size() const { return points_.size(); }
	reference front() { return points_.front(); }
	const_reference front() const { return points_.front(); }
	reference back() { return points_.back(); }
	const_reference back() const { return points_.back(); }
	reference operator[](size_type const s) { return points_[s]; }
	const_reference operator[](size_type const s) const { return points_[s]; }
	iterator begin() { return points_.begin(); }
	const_iterator begin() const { return points_.begin(); }
	iterator end() { return points_.end(); }
	const_iterator end() const { return points_.end(); }
	bool empty() const { return points_.empty(); }
	template<typename It>
	void insert(iterator const x, It const b, It const e) 
	{ 
		points_.insert(x,b,e); 
	}
private:
	container points_;
};

template
<
	typename T,
	typename Ch,
	typename Traits
>
std::basic_ostream<Ch, Traits> &
operator<<(
	std::basic_ostream<Ch, Traits> &s,
	math::polygon<T> const &p)
{
	return
		fcppt::math::detail::one_dimensional_output(
			s,
			p);
}

template
<
	typename T,
	typename Ch,
	typename Traits
>
std::basic_istream<Ch, Traits> &
operator>>(
	std::basic_istream<Ch, Traits> &s,
	math::polygon<T> &p)
{
	Ch c;
	s >> c;
	if(c != s.widen('(') || s.eof())
	{
		s.setstate(
			std::ios_base::failbit);
		return s;
	}

	if (s.peek() == s.widen(')'))
	{
		s.ignore();
		return s;
	}

	while (true)
	{
		T t;
		s >> t;
		if (!s)
			return s;
		p.push_back(
			t);
		if (s.eof())
		{
			s.setstate(
				std::ios_base::failbit);
			return s;
		}
		s >> c;
		if (c == s.widen(')'))
			break;
		if (c != s.widen(','))
		{
			s.setstate(
				std::ios_base::failbit);
			return s;
		}
	}

	return s;
}
}
}

#endif

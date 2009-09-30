#ifndef ROFL_MATH_POLYGON_HPP_INCLUDED
#define ROFL_MATH_POLYGON_HPP_INCLUDED

#include <vector>

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
	reference operator[](size_type const s) { return points_[s]; }
	const_reference operator[](size_type const s) const { return points_[s]; }
	iterator begin() { return points_.begin(); }
	const_iterator begin() const { return points_.begin(); }
	iterator end() { return points_.end(); }
	const_iterator end() const { return points_.end(); }
private:
	container points_;
};
}
}

#endif

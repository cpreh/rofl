#ifndef ROFL_MATH_POLYGON_DECL_HPP_INCLUDED
#define ROFL_MATH_POLYGON_DECL_HPP_INCLUDED

#include <rofl/math/polygon_fwd.hpp>
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

	polygon();

	// TODO: Add move, etc.

	void
	push_back(
		point const &
	);

	size_type
	size() const;

	reference
	front();

	const_reference
	front() const;

	reference
	back();

	const_reference
	back() const;

	reference
	operator[](
		size_type
	);

	const_reference
	operator[](
		size_type
	) const;

	iterator
	begin();

	const_iterator
	begin() const;

	iterator
	end();

	const_iterator
	end() const;

	bool
	empty() const;

	template<
		typename It
	>
	void
	insert(
		iterator pos,
		It begin,
		It end
	);
private:
	container points_;
};


}
}

#endif

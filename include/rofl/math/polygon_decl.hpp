#ifndef ROFL_MATH_POLYGON_DECL_HPP_INCLUDED
#define ROFL_MATH_POLYGON_DECL_HPP_INCLUDED

#include <rofl/math/polygon_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace rofl::math
{

template<
	typename T
>
class polygon
{
public:
	using
	point
	=
	T;
private:
	using
	container
	=
	std::vector<
		point
	>;
public:
	using
	value_type
	=
	typename
	container::value_type;

	using
	reference
	=
	typename
	container::reference;

	using
	const_reference
	=
	typename
	container::const_reference;

	using
	size_type
	=
	typename
	container::size_type;

	using
	iterator
	=
	typename
	container::iterator;

	using
	const_iterator
	=
	typename
	container::const_iterator;

	polygon();

	void
	push_back(
		point const &
	);

	[[nodiscard]]
	size_type
	size() const;

	[[nodiscard]]
	reference
	front();

	[[nodiscard]]
	const_reference
	front() const;

	[[nodiscard]]
	reference
	back();

	[[nodiscard]]
	const_reference
	back() const;

	[[nodiscard]]
	reference
	operator[](
		size_type
	);

	[[nodiscard]]
	const_reference
	operator[](
		size_type
	) const;

	[[nodiscard]]
	iterator
	begin();

	[[nodiscard]]
	const_iterator
	begin() const;

	[[nodiscard]]
	iterator
	end();

	[[nodiscard]]
	const_iterator
	end() const;

	[[nodiscard]]
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

#endif

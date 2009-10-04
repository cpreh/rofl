#ifndef ROFL_GRAPH_CYCLIC_ITERATOR_HPP_INCLUDED
#define ROFL_GRAPH_CYCLIC_ITERATOR_HPP_INCLUDED

#include <boost/iterator/iterator_facade.hpp>
#include <boost/next_prior.hpp>
#include <iterator>

namespace rofl
{
namespace graph
{
template<typename>
class cyclic_iterator;

namespace detail
{

template<typename ContainerIterator>
struct cyclic_iterator_helper 
{
	typedef 
	boost::iterator_facade
	<
		cyclic_iterator<ContainerIterator>,
		typename std::iterator_traits<ContainerIterator>::value_type,
		boost::bidirectional_traversal_tag,
		typename std::iterator_traits<ContainerIterator>::reference
	> base_type;
};

}

template<typename ContainerIterator>
class cyclic_iterator
:
	public detail::cyclic_iterator_helper<ContainerIterator>::base_type 
{
public:
	typedef typename 
	detail::cyclic_iterator_helper
	<
		ContainerIterator
	>::base_type
	base_type;

	typedef ContainerIterator container_iterator_type;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::reference reference;
	typedef typename base_type::pointer pointer;
	typedef typename base_type::difference_type difference_type;

	cyclic_iterator();

	template<typename OtherIterator>
	explicit cyclic_iterator(
		cyclic_iterator<OtherIterator> const &);

	cyclic_iterator(
		container_iterator_type const &it,
		container_iterator_type const &begin,
		container_iterator_type const &end);
		
	template<typename OtherIterator>
	cyclic_iterator<ContainerIterator> &
	operator=(
		cyclic_iterator<OtherIterator> const &);

	void 
	begin(
		container_iterator_type const &);
		
	void 
	end(
		container_iterator_type const &);

	container_iterator_type 
	begin() const;
	
	container_iterator_type 
	end() const;

	container_iterator_type 
	get() const;
private:
	friend class boost::iterator_core_access;
	void 
	increment();

	void 
	decrement();

	template<typename OtherIterator>
	bool 
	equal(
		cyclic_iterator<OtherIterator> const &r) const;

	reference 
	dereference() const;

	template<typename OtherIterator>
	difference_type 
	distance_to(
		cyclic_iterator<OtherIterator> const &r) const;
private:
	container_iterator_type 
		it_,
		begin_,
		end_;
};

}
}

#endif

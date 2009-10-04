template<typename ContainerIterator>
rofl::graph::cyclic_iterator<ContainerIterator>::cyclic_iterator()
:
	it_(),
	begin_(),
	end_()
{}


template<typename ContainerIterator>
template<typename OtherIterator>
rofl::graph::cyclic_iterator<ContainerIterator>::cyclic_iterator(
	cyclic_iterator<OtherIterator> const &other)
: 
	it_(
		other.it_),
	begin_(
		other.begin_),
	end_(
		other.end_)
{}

template<typename ContainerIterator>
rofl::graph::cyclic_iterator<ContainerIterator>::cyclic_iterator(
	container_iterator_type const &_it,
	container_iterator_type const &_begin,
	container_iterator_type const &_end)
: 
	it_(
		_it),
	begin_(
		_begin),
	end_(
		_end)
{}

template<typename ContainerIterator>
template<typename OtherIterator>
rofl::graph::cyclic_iterator<ContainerIterator> &
rofl::graph::cyclic_iterator<ContainerIterator>::operator=(
	cyclic_iterator<OtherIterator> const &r)
{
	it_ = r.it_;
	begin_ = r.begin_;
	end_ = r.end_;
	return *this;
}

template<typename ContainerIterator>
void 
rofl::graph::cyclic_iterator<ContainerIterator>::begin(
	container_iterator_type const &_begin)
{
	begin_ = _begin;
}

template<typename ContainerIterator>
void 
rofl::graph::cyclic_iterator<ContainerIterator>::end(
	container_iterator_type const &_end)
{
	end_ = _end;
}

template<typename ContainerIterator>
typename 
rofl::graph::cyclic_iterator<ContainerIterator>::container_iterator_type
rofl::graph::cyclic_iterator<ContainerIterator>::begin() const
{
	return begin_;
}

template<typename ContainerIterator>
typename 
rofl::graph::cyclic_iterator<ContainerIterator>::container_iterator_type
rofl::graph::cyclic_iterator<ContainerIterator>::end() const
{
	return end_;
}

template<typename ContainerIterator>
typename 
rofl::graph::cyclic_iterator<ContainerIterator>::container_iterator_type
rofl::graph::cyclic_iterator<ContainerIterator>::get() const
{
	return it_;
}

template<typename ContainerIterator>
void 
rofl::graph::cyclic_iterator<ContainerIterator>::increment()
{
	if (begin_ != end_ && ++it_ == end_)
		it_ = begin_;
}

template<typename ContainerIterator>
void 
rofl::graph::cyclic_iterator<ContainerIterator>::decrement()
{
	if (begin_ != end_ && it_ == begin_)
		it_ = 
			boost::prior(
				end_);
}

template<typename ContainerIterator>
template<typename OtherIterator>
bool 
rofl::graph::cyclic_iterator<ContainerIterator>::equal(
	cyclic_iterator<OtherIterator> const &r) const
{
	return it_ == r.it_;
}

template<typename ContainerIterator>
typename rofl::graph::cyclic_iterator<ContainerIterator>::reference
rofl::graph::cyclic_iterator<ContainerIterator>::dereference() const
{
	return *it_;
}

template<typename ContainerIterator>
template<typename OtherIterator>
typename 
rofl::graph::cyclic_iterator<ContainerIterator>::difference_type
rofl::graph::cyclic_iterator<ContainerIterator>::distance_to(
	cyclic_iterator<OtherIterator> const &r) const
{
	return r.it_ - it_;
}
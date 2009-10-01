#include <rofl/indexed_point.hpp>
#include <rofl/graph/properties.hpp>
#include <sge/math/vector/basic_impl.hpp>

rofl::indexed_point::indexed_point(
	graph::object const &_parent,
	index const _index)
:
	parent_(
		&_parent),
	index_(
		_index)
{
}
	
rofl::point const &
rofl::indexed_point::representation() const
{
	return 
		parent_->m_property.points()[index_];
}

bool 
rofl::indexed_point::operator==(
	indexed_point const &p) const
{
	return 
		index_ == p.index_;
}

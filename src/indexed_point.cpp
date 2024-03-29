#include <rofl/index.hpp>
#include <rofl/indexed_point.hpp>
#include <rofl/point.hpp>
#include <rofl/graph/object.hpp> // NOLINT(misc-include-cleaner)
#include <rofl/graph/property_tag.hpp>
#include <rofl/graph/properties.hpp>

rofl::indexed_point::indexed_point(graph_reference const _parent, rofl::index const _index)
    : parent_(_parent), index_(_index)
{
}

rofl::point const &rofl::indexed_point::representation() const
{
  return boost::get_property(parent_.get(), rofl::graph::property_tag()).points()[index_];
}

bool rofl::indexed_point::operator==(rofl::indexed_point const &_other) const
{
  return index_ == _other.index_;
}

bool rofl::operator!=(rofl::indexed_point const &_p1, rofl::indexed_point const &_p2)
{
  return !(_p1 == _p2);
}

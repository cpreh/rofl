#ifndef ROFL_ASTAR_HEURISTIC_HPP_INCLUDED
#define ROFL_ASTAR_HEURISTIC_HPP_INCLUDED

#include <rofl/graph/object.hpp>
#include <rofl/graph/vertex_descriptor.hpp>

namespace rofl
{
namespace astar
{
class heuristic
{
public:
	inline 
	heuristic(
		graph::object const &,
		graph::vertex_descriptor const &);
		
	inline
	unit
	operator()(
		graph::vertex_descriptor const &) const;
private:
	graph::object const &graph_;
	graph::vertex_descriptor destination_;
};
}
}

#include "heuristic_impl.hpp"

#endif

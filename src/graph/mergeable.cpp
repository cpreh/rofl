#include "mergeable.hpp"
#include "find_previous.hpp"
#include "left_on.hpp"
#include <sge/math/vector/basic_impl.hpp>

bool rofl::graph::mergeable(
	rofl::indexed_polygon const &a,
	rofl::indexed_polygon const &b,
	rofl::indexed_line_segment const &l)
{
	rofl::point const 
		p0 = 
			find_previous(a,l.start(),l.end()).representation(),
		p1 = 
			find_previous(b,l.start(),l.end()).representation();
	
	if (left_on(l.start().representation(),p1,p0))
		return false;
	
	rofl::point const 
		p2 = 
			find_previous(a,l.end(),l.start()).representation(),
		p3 = 
			find_previous(b,l.end(),l.start()).representation();
	
	if (left_on(l.end().representation(),p2,p3))
		return false;

	return true;
}
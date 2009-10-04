#include "mergeable.hpp"
#include "find_previous.hpp"
#include "left_on.hpp"
#include "left.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/cerr.hpp>

bool rofl::graph::mergeable(
	rofl::indexed_polygon const &a,
	rofl::indexed_polygon const &b,
	rofl::indexed_line_segment const &l)
{
	// find_previous gibt paar zurück aus Vertex und ob prev oder next gewählt wurde (bool oder enum)
	rofl::point const 
		p0 = 
			find_previous(a,l.start(),l.end()).representation(),
		p1 = 
			find_previous(b,l.start(),l.end()).representation();
	
	sge::cerr << "previous on a is " << p0 << ", and on b " << p1 << "\n";
	
	// p1 und p0 tauschen, wenn Reihenfolge nicht stimmt
	if (left(l.start().representation(),p1,p0))
	{
		sge::cerr << "returned false\n";
		return false;
	}
	
	rofl::point const 
		p2 = 
			find_previous(a,l.end(),l.start()).representation(),
		p3 = 
			find_previous(b,l.end(),l.start()).representation();
			
	sge::cerr << "previous on a is " << p2 << ", and on b " << p3 << "\n";
	sge::cerr 
		<< "area_sign(" << l.end().representation() << "," << p2 << "," << p3 << ")=" << area_sign(l.end().representation(),p2,p3) << "\n";
	
	if (left(l.end().representation(),p2,p3))
	{
		sge::cerr << "returned false\n";
		return false;
	}

	return true;
}
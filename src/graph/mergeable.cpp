#include "mergeable.hpp"
#include "find_adjacent.hpp"
#include "left_on.hpp"
#include "left.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/cerr.hpp>

bool rofl::graph::mergeable(
	indexed_polygon const &a,
	indexed_polygon const &b,
	indexed_line_segment const &l)
{
	// find_adjacent gibt paar zur?ck aus Vertex und ob prev oder next gew?hlt wurde (bool oder enum)
	std::pair
	<
		indexed_point,
		placement::type
	> const 
		p0 = 
			find_adjacent(a,l.start(),l.end()),
		p1 = 
			find_adjacent(b,l.start(),l.end());
	
	//sge::cerr << "previous on a is " << p0 << ", and on b " << p1 << "\n";
	
	// p1 und p0 tauschen, wenn Reihenfolge nicht stimmt
	if(
		left(
			l.start().representation(),
			(p0.second == placement::previous ? p1.first : p0.first).representation(),
			(p0.second == placement::previous ? p0.first : p1.first).representation()))
	{
		sge::cerr << "returned false\n";
		return false;
	}
	
	std::pair
	<
		indexed_point,
		placement::type
	> const 
		p2 = 
			find_adjacent(a,l.end(),l.start()),
		p3 = 
			find_adjacent(b,l.end(),l.start());
	
	//sge::cerr << "previous on a is " << p0 << ", and on b " << p1 << "\n";
	
	// p1 und p0 tauschen, wenn Reihenfolge nicht stimmt
	if(
		left(
			l.end().representation(),
			(p2.second == placement::previous ? p3.first : p2.first).representation(),
			(p2.second == placement::previous ? p2.first : p3.first).representation()))
	{
		sge::cerr << "returned false\n";
		return false;
	}
	
	/*
	rofl::point const 
		p2 = 
			find_adjacent(a,l.end(),l.start()).representation(),
		p3 = 
			find_adjacent(b,l.end(),l.start()).representation();
			
	sge::cerr << "previous on a is " << p2 << ", and on b " << p3 << "\n";
	sge::cerr 
		<< "area_sign(" << l.end().representation() << "," << p2 << "," << p3 << ")=" << area_sign(l.end().representation(),p2,p3) << "\n";
	
	if (left(l.end().representation(),p2,p3))
	{
		sge::cerr << "returned false\n";
		return false;
	}
	*/

	return true;
}

#include "merge.hpp"
#include "on_boundary.hpp"
#include "../cyclic_iterator.hpp"
#include "../cyclic_iterator_impl.hpp"
#include <sge/math/vector/output.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/cerr.hpp>

rofl::indexed_polygon const rofl::graph::merge(
	rofl::indexed_polygon const &a,
	rofl::indexed_polygon const &b,
	rofl::indexed_line_segment const &l)
{
	/*
	Idee: 
	Laufe durch Polygon 'a', seien a_n die dabei entstehenden Ecken. 
	Kommt man an den Punkt, wo a_n in { l.start,l.end } ist und 
	a_{n+1} in { l.start,l.end } (wenn man also beim line segment angekommen 
	ist, was die beiden Polygone trennt), f?ge a_n bzw. a_{n+1} nicht hinzu
	und wechsle stattdessen zu Polygon 'b', und zwar 
	an die Ecke vom Polygon, die a_n entspricht. F?ge solange Punkte hinzu,
	bis man an { l.start,l.end } angekommen ist. Wechsle dann wieder zu 
	Polygon 'a' und laufe solange, bis a_0 erreicht wird.
	
	Das Durchlaufen erfolgt zyklisch.
	*/
	typedef 
	rofl::cyclic_iterator
	<
		rofl::indexed_polygon::const_iterator
	> cyclic_iterator;
	
	rofl::indexed_polygon output;
	cyclic_iterator i(
		a.begin(),
		a.begin(),
		a.end());
		
	while(
		!rofl::graph::on_boundary(*i,l) ||
		!rofl::graph::on_boundary(*boost::next(i),l))
		output.push_back(
			*i++);
	
	cyclic_iterator j(
		std::find(
			b.begin(),
			b.end(),
			*i),
		b.begin(),
		b.end());
	
	while(
		!rofl::graph::on_boundary(*j,l) ||
		!rofl::graph::on_boundary(*boost::next(j),l))
		output.push_back(
			*j++);
	
	++i;
			
	while (*i != *a.begin())
		output.push_back(
			*i++);
	
	return 
		output;
}

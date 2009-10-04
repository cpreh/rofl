#include "merge.hpp"
#include "on_boundary.hpp"
#include "cyclic_iterator.hpp"
#include "cyclic_iterator_impl.hpp"
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
	sge::cerr << "in merge, points of line segment are: " << l.start().representation() << ", " << l.end().representation() << "\n";
	
	typedef 
	rofl::graph::cyclic_iterator
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
	/*
	// laufe in polygon a bis zum Index wo l.start() ist. Sei i dieser Index. 
	// Laufe in b auch bis zum Index, dieser sei j
	rofl::indexed_polygon::size_type ia;
	//for (ia = a.size()-1; ia >= 0; --ia)
	for (ia = 0; ia < a.size(); ++ia)
		if (a[ia] == l.start() || a[ia] == l.end())
			break;
	
	rofl::indexed_polygon::size_type ib;
	for (ib = 0; ib < b.size(); ++ib)
		if (b[ib] == a[ia])
			break;
	
	SGE_ASSERT(ia < a.size() && ib < b.size());
		
	sge::cerr 
		<< "points of a are: " 
		<< a[0].representation()
		<< a[1].representation()
		<< a[2].representation()
		<< "\n";
		
	sge::cerr 
		<< "points of b are: " 
		<< b[0].representation()
		<< b[1].representation()
		<< b[2].representation()
		<< "\n";
	sge::cerr << "ia is " << ia << ", ib is " << ib << "\n";
	
	typedef 
	rofl::graph::cyclic_iterator
	<
		rofl::indexed_polygon::const_iterator
	> 
	cyclic_iterator;
	
	cyclic_iterator 
		bbegin(
			b.begin()+ib+1 == b.end() ? b.begin() : (b.begin()+ib+1),
			b.begin(),
			b.end()),
		bend(
			boost::next(
				bbegin,
				b.size()-2).get(),
			b.begin(),
			b.end());
			
	a.insert(
		a.begin()+ia+1,
		bbegin,
		bend);
		*/
}

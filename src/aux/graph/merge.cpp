#include <rofl/indexed_line_segment.hpp>
#include <rofl/indexed_polygon.hpp>
#include <rofl/aux/graph/merge.hpp>
#include <rofl/aux/graph/on_boundary.hpp>
#include <fcppt/cyclic_iterator.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <iterator>
#include <fcppt/config/external_end.hpp>


rofl::indexed_polygon
rofl::aux::graph::merge(
	rofl::indexed_polygon const &_poly_a,
	rofl::indexed_polygon const &_poly_b,
	rofl::indexed_line_segment const &_line
)
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
	fcppt::cyclic_iterator
	<
		rofl::indexed_polygon::const_iterator
	> cyclic_iterator;

	rofl::indexed_polygon output;

	cyclic_iterator it_a(
		_poly_a.begin(),
		cyclic_iterator::boundary{
			_poly_a.begin(),
			_poly_a.end()
		}
	);

	// TODO: Refactor this into a helper function!
	while(
		!rofl::aux::graph::on_boundary(
			*it_a,
			_line
		)
		||
		!rofl::aux::graph::on_boundary(
			*std::next(
				it_a
			),
			_line
		)
	)
		output.push_back(
			*it_a++
		);

	cyclic_iterator it_b(
		std::find(
			_poly_b.begin(),
			_poly_b.end(),
			*it_a
		),
		cyclic_iterator::boundary{
			_poly_b.begin(),
			_poly_b.end()
		}
	);

	while(
		!rofl::aux::graph::on_boundary(
			*it_b,
			_line
		)
		||
		!rofl::aux::graph::on_boundary(
			*std::next(
				it_b
			),
			_line
		)
	)
		output.push_back(
			*it_b++
		);

	++it_a;

	while(
		*it_a
		!=
		*_poly_a.begin()
	)
		output.push_back(
			*it_a++
		);

	return
		output;
}

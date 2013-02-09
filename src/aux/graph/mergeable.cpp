#include <rofl/indexed_line_segment.hpp>
#include <rofl/indexed_point.hpp>
#include <rofl/indexed_polygon.hpp>
#include <rofl/aux/graph/find_adjacent.hpp>
#include <rofl/aux/graph/mergeable.hpp>
#include <rofl/aux/graph/placement.hpp>
#include <rofl/aux/math/left.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


bool
rofl::aux::graph::mergeable(
	rofl::indexed_polygon const &_poly_a,
	rofl::indexed_polygon const &_poly_b,
	rofl::indexed_line_segment const &_line
)
{
	// TODO: Refactor this code into a helper function!

	// find_adjacent sucht die Nachbarn der Endpunkte des line_segments auf den
	// zwei Polygonen. Es gibt paar zurück aus Vertex und ob prev oder next
	// gewählt wurde (bool oder enum). Das benutzen wir, um die Reihenfolge
	// "Gegen den Uhrzeigersinn" beizubehalten.
	std::pair
	<
		rofl::indexed_point,
		rofl::aux::graph::placement
	> const
		p0 =
			rofl::aux::graph::find_adjacent(
				_poly_a,
				_line.start(),
				_line.end()
			),
		p1 =
			rofl::aux::graph::find_adjacent(
				_poly_b,
				_line.start(),
				_line.end()
			);

	// p1 und p0 tauschen, wenn Reihenfolge nicht stimmt
	if(
		rofl::aux::math::left(
			_line.start().representation(),
			(
				p0.second
				==
				rofl::aux::graph::placement::previous
				?
					p1.first
				:
					p0.first
			).representation(),
			(
				p0.second
				==
				rofl::aux::graph::placement::previous
				?
					p0.first
				:
					p1.first
			).representation()
		)
	)
		return false;

	// selbe Logik wie oben
	std::pair
	<
		rofl::indexed_point,
		rofl::aux::graph::placement
	> const
		p2 =
			rofl::aux::graph::find_adjacent(
				_poly_a,
				_line.end(),
				_line.start()
			),
		p3 =
			rofl::aux::graph::find_adjacent(
				_poly_b,
				_line.end(),
				_line.start()
			);

	// p1 und p0 tauschen, wenn Reihenfolge nicht stimmt
	if(
		rofl::aux::math::left(
			_line.end().representation(),
			(
				p2.second
				==
				rofl::aux::graph::placement::previous
				?
					p3.first
				:
					p2.first
			).representation(),
			(
				p2.second
				==
				rofl::aux::graph::placement::previous
				?
					p2.first
				:
					p3.first
			).representation()
		)
	)
		return false;

	return true;
}

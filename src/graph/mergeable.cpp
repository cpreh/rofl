#include "mergeable.hpp"
#include "find_adjacent.hpp"
#include "../math/left_on.hpp"
#include "../math/left.hpp"
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/output.hpp>

bool rofl::graph::mergeable(
	indexed_polygon const &a,
	indexed_polygon const &b,
	indexed_line_segment const &l)
{
	// find_adjacent sucht die Nachbarn der Endpunkte des line_segments auf den
	// zwei Polygonen. Es gibt paar zurück aus Vertex und ob prev oder next
	// gewählt wurde (bool oder enum). Das benutzen wir, um die Reihenfolge
	// "Gegen den Uhrzeigersinn" beizubehalten.
	std::pair
	<
		indexed_point,
		placement::type
	> const
		p0 =
			find_adjacent(
				a,
				l.start(),
				l.end()),
		p1 =
			find_adjacent(
				b,
				l.start(),
				l.end());

	// p1 und p0 tauschen, wenn Reihenfolge nicht stimmt
	if(
		math::left(
			l.start().representation(),
			(p0.second == placement::previous ? p1.first : p0.first).representation(),
			(p0.second == placement::previous ? p0.first : p1.first).representation()))
		return false;

	// selbe Logik wie oben
	std::pair
	<
		indexed_point,
		placement::type
	> const
		p2 =
			find_adjacent(a,l.end(),l.start()),
		p3 =
			find_adjacent(b,l.end(),l.start());

	// p1 und p0 tauschen, wenn Reihenfolge nicht stimmt
	if(
		math::left(
			l.end().representation(),
			(p2.second == placement::previous ? p3.first : p2.first).representation(),
			(p2.second == placement::previous ? p2.first : p3.first).representation()))
		return false;

	return true;
}

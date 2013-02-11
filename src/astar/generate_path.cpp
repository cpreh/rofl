#include <rofl/line_segment.hpp>
#include <rofl/point.hpp>
#include <rofl/astar/generate_path.hpp>
#include <rofl/graph/object.hpp>
#include <rofl/astar/path.hpp>
#include <rofl/astar/trail.hpp>


/* Pseudocode
 */
// Sei der Pfad hier gespeichert

/*
typedef (punkt,kante) paar;
paar pfad[n];

int current = 0;
while (true)
{
	int i;
	for (i = current+1; i < n; ++i)
	{
		c =
			strecke
			(
				pfad[current].punkt,
				pfad[i].punkt
			);

		for (int j = current+1; j < i; ++j)
			if (!intersect(c,pfad[j].kante))
				break;
	}
	ergebnis.push_back(
		strecke(
			pfad[current].punkt,
			pfad[i-1].punkt));

	// in i-1 steht jetzt der letzte gueltige Index
	if (i == n)
		break;

	current = i-1;
}
*/


rofl::astar::path
rofl::astar::generate_path(
	rofl::graph::object const &_graph,
	rofl::astar::trail const &_trail,
	rofl::point const &_start,
	rofl::point const &_end
)
{
	rofl::astar::path result;

	// Erster Schritt: Generiere Uebergangspfad aus Paaren (Punkt,Kante), wobei Kante die Kante ist, die zwei
	// Polygone verbindet und Punkt der Mittelpunkt. Die Kante kann natuerlich leer sein, wenn es sich um den
	// Start- bzw. Endpunkt handelt.
	/*
	typedef
	sge::optional<rofl::line_segment>
	optional_line_segment;

	typedef
	std::pair
	<
		optional_line_segment,
		rofl::point
	>
	pair;

	typedef
	std::vector<pair>
	intermediate_path;

	intermediate_path ip;
	ip.push_back(
		pair(
			optional_line_segment(),
			start));

	for (trail::const_iterator i = t.begin(); i != t.end(); ++i)
	{
		boost::edges(*i,*boost::next(i));
	}
	*/
	/*
	FCPPT_ASSERT(
		!t.empty());

	if (t.size() == 1)
	{
		p.push_back(
			start);
		p.push_back(
			end);
		return;
	}

	point last_point =
		start;
	graph::vertex_descriptor last_vertex =
		t.front();

	for(
		trail::const_iterator i =
			boost::next(
				t.begin());
		i != t.end();
		++i)
	{
		line_segment const &r =
			g[boost::edge(
				last_vertex,
				*i,
				g)].adjacent_edge();

		if (!math::line_segments_intersect(l,r))
			break;
	}
	*/
}
